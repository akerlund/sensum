/*
 *  Fredrik Åkerlund 2017
 *  Application for interfacing with a microcontroller.
 *  A terminal can both read strings and custom packages and send commands.
 *  QCustom plot is used for plotting received data in real-time.
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <math.h>
#define pi 3.14159

#include "custom_plots.h"
#include "rx_unpacking.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){

    ui->setupUi(this);

    status_label = new QLabel(this);
    ui->statusBar->addPermanentWidget(status_label);
    status_label->setText("Port disconnected.");

    serial_port = new QSerialPort(this);
    connect(serial_port, SIGNAL(readyRead( )), this, SLOT(serial_RX_event( )));
    connect(serial_port, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(serialPortError(QSerialPort::SerialPortError)));
    refreshSerialDevices( );



    qApp->installEventFilter(this);

    // Plot updates.
    q_timer = new QTimer(this);
    q_timer->setInterval(20);
    q_timer->start( );
    connect(q_timer, SIGNAL(timeout()), this, SLOT(q_timer_event( )));

    // Updating the serial connection at 10Hz.
//    q_timer_status_label = new QTimer(this);
//    q_timer_status_label->setInterval(100);
//    q_timer_status_label->start( );
//    connect(q_timer_status_label, SIGNAL(timeout()), this, SLOT(q_timer_status_label( )));

    // Setting the terminals colors to black and green.
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    ui->text_browser_0->setPalette(p);

    for (int i = 0; i < max_vector_size; i++) {
        x_axis.append(i);
    }
    init_plots( );
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
*   @brief  Updates all the plots if they are visible.
*
*   @return void
*/
void MainWindow::q_timer_event( )
{
    sin_shifter += 0.25;
    QVector<double> sine_data;

    for (int i = 0; i < max_vector_size; i++){
        sine_data.append(sin(2*pi*i/max_vector_size*20+sin_shifter));
    }

    int index = ui->tabWidget_plots->currentIndex();
    QString currentTabText = ui->tabWidget_plots->tabText(index);


    if((currentTabText == "Environment") & ui->tabWidget_plots->isVisible()){
        //barometer_0 = sine_data;
        temperature_0 = sine_data;
        humidity_0 = sine_data;
        ambient_light_0 = sine_data;
        update_plot_barometer( );
        update_plot_temperature( );
        update_plot_humidity( );
        update_plot_ambient_light( );
    }


    bool tab_IMU = (currentTabText == "IMU") & ui->tabWidget_plots->isVisible();
    if(tab_IMU){
        //IMU_accelerometer = sine_data;
        //IMU_gyroscope = sine_data;
        //IMU_magnetometer = sine_data;
        update_plot_IMU( );
    }


    bool tab_light = (currentTabText == "Light") & ui->tabWidget_plots->isVisible();
    if(tab_light){
//        RGB_sensor_0_R = sine_data;
//        RGB_sensor_0_G = sine_data;
//        RGB_sensor_0_B = sine_data;
//        UV_0 = sine_data;
        update_plot_RGB( );
        update_plot_UV( );
    }


}

/**
*   @brief  Fetches a list of all serial ports and inserts
*           them into the combo box.
*
*   @return void
*/
void MainWindow::refreshSerialDevices( )
{
    ui->comboBox_serial->clear( );

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts( );
    foreach(const QSerialPortInfo &port, ports) {
        QString name = port.portName( );
        int index = ui->comboBox_serial->count( );
        if(port.manufacturer() == "STMicroelectronics") {
            name.insert(0, "STM - ");
            index = 0;
        }
        ui->comboBox_serial->insertItem(index, name, port.systemLocation( ));
    }
    ui->comboBox_serial->setCurrentIndex(0);
    status_label->setText(tr("Ports refreshed."));
}

/**
*   @brief  Continously listens for a received bytes.
*
*   @return void
*/
void MainWindow::serial_RX_event( )
{
    while (serial_port->bytesAvailable() > 0) {
        QByteArray data = serial_port->readAll( );
        process_RX_data(data);
    }
}

/**
*   @brief  Collects received bytes. Builds strings or reads custom packages.
*
*   @param  &data is a QByteArray with received bytes
*   @return void
*/
void MainWindow::process_RX_data(QByteArray &data)
{
    //print_to_terminal("process_RX_data: " + QString::number(data.length( )));
    unsigned char rx_data;
    QString rx_ascii;

    for(int i = 0; i < data.length( ); i++) {
        rx_data = data[i];

        if (ui->radioButton_strings->isChecked( )){

            rx_ascii = QString(rx_data);
            RX_ascii_buffer += rx_ascii;

            if ( rx_ascii == "\n") {
                //ui->text_browser_0->clear( );
                print_to_terminal(RX_ascii_buffer);
                RX_ascii_buffer = "";
            }
        } else {
            switch(rx_state) {
                // Start byte.
                case 0:
                if(rx_data == 170){
                    //print_to_terminal("Start byte.");
                    rx_buf_pointer = 0;
                    rx_state++;
                }
                break;

                // Package identifier.
                case 1:
                    rx_header = rx_data;
                    rx_state++;
                    //print_to_terminal("Package identifier = "+ QString::number(rx_header));
                break;

                // Package length.
                case 2:
                    //print_to_terminal("Package length.");
                    bytes_to_receieve = (unsigned)rx_data;
                    //if()
                    rx_state++;
                    //print_to_terminal("bytes_to_receieve = "+ QString::number(bytes_to_receieve));
                break;

                // Package data.
                case 3:
                    rx_buffer[rx_buf_pointer++] = rx_data;
                    if (rx_buf_pointer == bytes_to_receieve){
                        process_RX_package(rx_header, rx_buffer, rx_buf_pointer);
                        rx_buf_pointer = 0;
                        rx_state = 0;
                    }
                    //print_to_terminal("bytes_to_receieve = "+ QString::number(bytes_to_receieve));
                    //print_to_terminal("bytes_receieved = "+ QString::number(rx_buf_pointer));
                break;

                default: rx_state = 0; break;
                print_to_terminal("default");
            }
        }
    }
}

/**
*   @brief  Handles a received custom package.
*
*   @param  *rx_data is passed with the received bytes.
*   @param  received_bytes is the number of bytes.
*   @return void
*/
void MainWindow::process_RX_package(int rx_header, char unsigned *rx_data, int received_bytes) {

    COM_HEADER com_head = (COM_HEADER)rx_header;

    switch(com_head){
    case COM_PACKAGE_IMU:
        rx_unpack_IMU(rx_data, received_bytes);
        //print_to_terminal("COM_PACKAGE_IMU");
        break;
    case COM_PACKAGE_BAROMETER_BMP280:
        rx_unpack_BMP280(rx_data, received_bytes);
        //print_to_terminal("COM_PACKAGE_BAROMETER_BMP280");
        break;
    case COM_PACKAGE_ISL29125:
        rx_unpack_ISL29125(rx_data, received_bytes);
        //print_to_terminal("COM_PACKAGE_ISL29125");
        break;
    case COM_PACKAGE_MPU9250:
        rx_unpack_MPU9250(rx_data, received_bytes);
        //print_to_terminal("COM_PACKAGE_MPU9250");
        break;
    default:
        break;
    }
}

/**
*   @brief  Appends data for the vectors used in the plots. If full
*           one value will be deleted.
*
*   @param  *vector will be appended the new value.
*   @param  value is the new data.
*   @param  max_size decides the maximum size of the vector.*
*   @return void
*/
void MainWindow::shift_in_to_vector(QVector<double> *vector, double value, int max_size)
{
    vector->append(value);

    if(vector->size( ) > max_size) {
        vector->remove(0, vector->size( ) - max_size);
    }
}


void MainWindow::serial_TX_send(QByteArray &data)
{
    if (serial_port->isOpen( )) {
        serial_port->write(data);
    }
}


void MainWindow::serialPortError(QSerialPort::SerialPortError error)
{
    QString message;

    switch (error) {
    case QSerialPort::NoError:
        break;
    case QSerialPort::DeviceNotFoundError:
        message = tr("Device not found.");
        break;
    case QSerialPort::OpenError:
        message = tr("Can't open device.");
        break;
    case QSerialPort::NotOpenError:
        message = tr("Not open error.");
        break;
    case QSerialPort::ResourceError:
        message = tr("Port disconnected.");
        break;
    case QSerialPort::UnknownError:
        message = tr("Unknown error.");
        break;
    default:
        message = "Serial port error: " + QString::number(error) + ".";
        break;
    }

    if(!message.isEmpty( )) {
        //status_label->setText(message);
        if(serial_port->isOpen( )) {
            serial_port->close( );
        }
    } else {

        //status_label->setText(tr("Port disconnecteDDd."));
    }
}


void MainWindow::print_to_terminal(QString str)
{
    ui->text_browser_0->append(str);
}

bool MainWindow::eventFilter(QObject *object, QEvent *e)
{
    Q_UNUSED(object);
    if (e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        bool isPress = e->type() == QEvent::KeyPress;

        switch(keyEvent->key()) {
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_PageDown:
        case Qt::Key_Escape:
            break;

        default:
            return false;
        }

        if(keyEvent->isAutoRepeat()) {
            return true;
        }

        switch(keyEvent->key()) {
        case Qt::Key_Up:
            if (isPress) {
                print_to_terminal("QString str");
            } else {

            }
            break;

        case Qt::Key_Down:
            if (isPress) {

            } else {

            }
            break;

        case Qt::Key_Left:
            if (isPress) {

            } else {

            }
            break;

        case Qt::Key_Right:
            if (isPress) {

            } else {

            }
            break;

        case Qt::Key_PageDown:
            if (isPress) {

            } else {

            }
            break;

        case Qt::Key_Escape:

            break;

        default:
            break;
        }

        return true;
    }

    return false;
}




// Event functions.
void MainWindow::on_btn_serial_connect_clicked()
{
    if(serial_port->isOpen( )) {
        status_label->setText("Serial already open.");
        return;
    }

    serial_port->setPortName(ui->comboBox_serial->currentData( ).toString( ));
    serial_port->open(QIODevice::ReadWrite);

    if(!serial_port->isOpen( )) {

        print_to_terminal("Serial not open.");
        status_label->setText("Serial not open.");
        return;
    } else {
        print_to_terminal("Serial open.");
        status_label->setText("Serial open.");
    }

    //serial_port->setBaudRate(921600);//(QSerialPort::Baud115200);
    serial_port->setBaudRate(QSerialPort::Baud115200);
    serial_port->setDataBits(QSerialPort::Data8);
    serial_port->setParity(QSerialPort::NoParity);
    serial_port->setStopBits(QSerialPort::OneStop);
    serial_port->setFlowControl(QSerialPort::NoFlowControl);
}

void MainWindow::on_btn_serial_refresh_clicked()
{
    refreshSerialDevices( );
}

void MainWindow::on_btn_serial_disconnect_clicked()
{
    if (serial_port->isOpen( )) {
        serial_port->close( );
    }
    status_label->setText("Disconnected.");
}


void MainWindow::on_lineEdit_0_returnPressed( )
{
    QString written = ui->lineEdit_0->text();
    written += "\r";
    //print_to_terminal(written); // QString
    print_to_terminal(QString::number(written.length())); // QString

    ui->lineEdit_0->clear();

    QByteArray tx;
    tx.append(written);

    serial_TX_send(tx); //QByteArray &data
}
