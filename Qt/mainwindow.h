#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QByteArray>
#include <QSerialPort>


#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void q_timer_event( );
    void serial_RX_event( );
    void serialPortError(QSerialPort::SerialPortError error);

    void on_btn_serial_refresh_clicked();
    void on_btn_serial_connect_clicked();

    void on_btn_serial_disconnect_clicked();
    void on_lineEdit_0_returnPressed( );

    bool eventFilter(QObject *object, QEvent *e);

private:

    Ui::MainWindow *ui;

    QSerialPort *serial_port;
    QLabel *status_label;
    QTimer *q_timer;

    double sin_shifter;

    // RX variables
    int rx_state;
    int rx_header;
    int bytes_to_receieve;
    int bytes_received;
    char unsigned rx_buffer[2048];
    int rx_buf_pointer;
    QString RX_ascii_buffer;


    // Data vector for the plots.
    static const int max_vector_size = 300;
    QVector<double> x_axis;

    QVector<double> barometer_BMP280;

    QVector<double> ISL29125_R;
    QVector<double> ISL29125_G;
    QVector<double> ISL29125_B;


    QVector<double> temperature_0;
    QVector<double> humidity_0;
    QVector<double> ambient_light_0;
    QVector<double> IMU_accelerometer_x;
    QVector<double> IMU_accelerometer_y;
    QVector<double> IMU_accelerometer_z;
    QVector<double> IMU_gyroscope_x;
    QVector<double> IMU_gyroscope_y;
    QVector<double> IMU_gyroscope_z;
    QVector<double> IMU_magnetometer_x;
    QVector<double> IMU_magnetometer_y;
    QVector<double> IMU_magnetometer_z;
    QVector<double> RGB_sensor_0_R;
    QVector<double> RGB_sensor_0_G;
    QVector<double> RGB_sensor_0_B;
    QVector<double> UV_0;

    // Plot functions.
    void init_plots( );
    void init_plot_barometer( );
    void init_plot_temperature( );
    void init_plot_humidity( );
    void init_plot_ambient_light( );
    void init_plot_IMU( );
    void init_plot_RGB( );
    void init_plot_UV( );

    void update_plots( );
    void update_plot_barometer( );
    void update_plot_temperature( );
    void update_plot_humidity( );
    void update_plot_ambient_light( );
    void update_plot_IMU( );
    void update_plot_RGB( );
    void update_plot_UV( );


    void process_RX_data(QByteArray &data);
    void process_RX_package(int rx_header, char unsigned *rx_data, int received_bytes);
    void shift_in_to_vector(QVector<double> *vector, double value, int max_size);

    void rx_unpack_IMU(unsigned char *rx_data, int received_bytes);
    void rx_unpack_BMP280(unsigned char *rx_data, int received_bytes);
    void rx_unpack_ISL29125(unsigned char *grb, int received_bytes);
    void rx_unpack_MPU9250(unsigned char *rx_data, int received_bytes);


    void serial_TX_send(QByteArray &data);
    void refreshSerialDevices( );

    void print_to_terminal(QString str);
    void print_to_sfp_reg_browser(QString str);

    typedef enum {						// USB RX package identifiers.
        COM_PACKAGE_IMU = 0,
        COM_PACKAGE_BAROMETER_BMP280,
        COM_PACKAGE_ISL29125,
        COM_PACKAGE_VEML6070,
        COM_PACKAGE_TCS3472,
        COM_PACKAGE_MPU9250
    //	COM_PACKAGE_RGB,
    //	COM_PACKAGE_UV,
    //	COM_PACKAGE_BAROMETER,
    //	COM_PACKAGE_HUMIDITY,
    //	COM_PACKAGE_TEMPERATURE,
    //	COM_PACKAGE_AMBIENT,
    //	COM_PACKAGE_AUDIO,
    //	COM_PACKAGE_LOGIC,
    //	COM_PACKAGE_CAN
    } COM_HEADER;

};

#endif // MAINWINDOW_H
