#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::init_plots( ){

    // Allowing drag and zoom in the plots.
    ui->plot_barometer->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot_temperature->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot_humidity->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot_ambient_light->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot_IMU_accelerometer->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot_IMU_gyroscope->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot_IMU_magnetometer->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot_RGB->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->plot_UV->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    init_plot_barometer( );
    init_plot_temperature( );
    init_plot_humidity( );
    init_plot_ambient_light( );
    init_plot_IMU( );
    init_plot_RGB( );
    init_plot_UV( );

}

void MainWindow::init_plot_barometer( ){

    ui->plot_barometer->addGraph( );
    ui->plot_barometer->graph(0)->setPen(QPen(Qt::darkBlue));
    ui->plot_barometer->graph(0)->setName("N/m^2");

//    ui->plot_barometer->xAxis->setLabel("Time (s)");
//    ui->plot_barometer->yAxis->setLabel("Pressure (Nm/m2)");
//    ui->plot_barometer->yAxis->setRange(0, 100);

    QFont legendFont = font( );
    legendFont.setPointSize(9);
    ui->plot_barometer->legend->setVisible(true);
    ui->plot_barometer->legend->setFont(legendFont);
    ui->plot_barometer->legend->setBrush(QBrush(QColor(255,255,255,230)));

    ui->plot_barometer->axisRect( )->insetLayout( )->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
    ui->plot_barometer->yAxis->setRange(0, 10);

    for (int i = 0; i < max_vector_size; i++) {
        barometer_BMP280.append(0);
    }

    ui->plot_barometer->graph(0)->setData(x_axis, barometer_BMP280);
    ui->plot_barometer->replot( );
    ui->plot_barometer->rescaleAxes();
}

void MainWindow::init_plot_temperature( ){

    ui->plot_temperature->addGraph( );
    ui->plot_temperature->graph(0)->setPen(QPen(Qt::darkBlue));
    ui->plot_temperature->graph(0)->setName("N/m^2");

//    ui->plot_temperature->xAxis->setLabel("Time (s)");
//    ui->plot_temperature->yAxis->setLabel("Pressure (Nm/m2)");
//    ui->plot_temperature->yAxis->setRange(0, 100);

    QFont legendFont = font( );
    legendFont.setPointSize(9);
    ui->plot_temperature->legend->setVisible(true);
    ui->plot_temperature->legend->setFont(legendFont);
    ui->plot_temperature->legend->setBrush(QBrush(QColor(255,255,255,230)));

    ui->plot_temperature->axisRect( )->insetLayout( )->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
    ui->plot_temperature->yAxis->setRange(0, 10);

    for (int i = 0; i < max_vector_size; i++) {
        temperature_0.append(i);
    }

    ui->plot_temperature->graph(0)->setData(x_axis, temperature_0);
    ui->plot_temperature->replot( );
    ui->plot_temperature->rescaleAxes();
}

void MainWindow::init_plot_humidity( ){

    ui->plot_humidity->addGraph( );
    ui->plot_humidity->graph(0)->setPen(QPen(Qt::darkBlue));
    ui->plot_humidity->graph(0)->setName("N/m^2");

//    ui->plot_humidity->xAxis->setLabel("Time (s)");
//    ui->plot_humidity->yAxis->setLabel("Pressure (Nm/m2)");
//    ui->plot_humidity->yAxis->setRange(0, 100);

    QFont legendFont = font( );
    legendFont.setPointSize(9);
    ui->plot_humidity->legend->setVisible(true);
    ui->plot_humidity->legend->setFont(legendFont);
    ui->plot_humidity->legend->setBrush(QBrush(QColor(255,255,255,230)));

    ui->plot_humidity->axisRect( )->insetLayout( )->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
    ui->plot_humidity->yAxis->setRange(0, 10);

    for (int i = 0; i < max_vector_size; i++) {
        humidity_0.append(i);
    }

    ui->plot_humidity->graph(0)->setData(x_axis, humidity_0);
    ui->plot_humidity->replot( );
    ui->plot_humidity->rescaleAxes();
}

void MainWindow::init_plot_ambient_light( ){

    ui->plot_ambient_light->addGraph( );
    ui->plot_ambient_light->graph(0)->setPen(QPen(Qt::darkBlue));
    ui->plot_ambient_light->graph(0)->setName("N/m^2");

//    ui->plot_ambient_light->xAxis->setLabel("Time (s)");
//    ui->plot_ambient_light->yAxis->setLabel("Pressure (Nm/m2)");
//    ui->plot_ambient_light->yAxis->setRange(0, 100);

    QFont legendFont = font( );
    legendFont.setPointSize(9);
    ui->plot_ambient_light->legend->setVisible(true);
    ui->plot_ambient_light->legend->setFont(legendFont);
    ui->plot_ambient_light->legend->setBrush(QBrush(QColor(255,255,255,230)));

    ui->plot_ambient_light->axisRect( )->insetLayout( )->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
    ui->plot_ambient_light->yAxis->setRange(0, 10);

    for (int i = 0; i < max_vector_size; i++) {
        ambient_light_0.append(i);
    }

    ui->plot_ambient_light->graph(0)->setData(x_axis, ambient_light_0);
    ui->plot_ambient_light->replot( );
    ui->plot_ambient_light->rescaleAxes();
}

void MainWindow::init_plot_IMU( ){

    QFont legendFont = font( );
    legendFont.setPointSize(9);

    ui->plot_IMU_accelerometer->legend->setVisible(true);
    ui->plot_IMU_accelerometer->legend->setFont(legendFont);
    ui->plot_IMU_accelerometer->legend->setBrush(QBrush(QColor(255,255,255,230)));
    ui->plot_IMU_accelerometer->axisRect( )->insetLayout( )->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
    //ui->plot_IMU_accelerometer->yAxis->setRange(0, 10);

    // Acceleropmeter.
    ui->plot_IMU_accelerometer->addGraph( );
    ui->plot_IMU_accelerometer->graph(0)->setPen(QPen(Qt::darkBlue));
    ui->plot_IMU_accelerometer->graph(0)->setName("X");
    ui->plot_IMU_accelerometer->addGraph( );
    ui->plot_IMU_accelerometer->graph(1)->setPen(QPen(Qt::darkRed));
    ui->plot_IMU_accelerometer->graph(1)->setName("Y");
    ui->plot_IMU_accelerometer->addGraph( );
    ui->plot_IMU_accelerometer->graph(2)->setPen(QPen(Qt::darkGreen));
    ui->plot_IMU_accelerometer->graph(2)->setName("Z");


    // Gyroscope.
    ui->plot_IMU_gyroscope->legend->setVisible(true);
    ui->plot_IMU_gyroscope->legend->setFont(legendFont);
    ui->plot_IMU_gyroscope->legend->setBrush(QBrush(QColor(255,255,255,230)));
    ui->plot_IMU_gyroscope->axisRect( )->insetLayout( )->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
    //ui->plot_IMU_gyroscope->yAxis->setRange(0, 10);

    ui->plot_IMU_gyroscope->addGraph( );
    ui->plot_IMU_gyroscope->graph(0)->setPen(QPen(Qt::darkBlue));
    ui->plot_IMU_gyroscope->graph(0)->setName("X");
    ui->plot_IMU_gyroscope->addGraph( );
    ui->plot_IMU_gyroscope->graph(1)->setPen(QPen(Qt::darkRed));
    ui->plot_IMU_gyroscope->graph(1)->setName("Y");
    ui->plot_IMU_gyroscope->addGraph( );
    ui->plot_IMU_gyroscope->graph(2)->setPen(QPen(Qt::darkGreen));
    ui->plot_IMU_gyroscope->graph(2)->setName("Z");


    // Magnetometer.
    ui->plot_IMU_magnetometer->legend->setVisible(true);
    ui->plot_IMU_magnetometer->legend->setFont(legendFont);
    ui->plot_IMU_magnetometer->legend->setBrush(QBrush(QColor(255,255,255,230)));
    ui->plot_IMU_magnetometer->axisRect( )->insetLayout( )->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
    //ui->plot_IMU_magnetometer->yAxis->setRange(0, 10);

    // Acceleropmeter.
    ui->plot_IMU_magnetometer->addGraph( );
    ui->plot_IMU_magnetometer->graph(0)->setPen(QPen(Qt::darkBlue));
    ui->plot_IMU_magnetometer->graph(0)->setName("X");
    ui->plot_IMU_magnetometer->addGraph( );
    ui->plot_IMU_magnetometer->graph(1)->setPen(QPen(Qt::darkRed));
    ui->plot_IMU_magnetometer->graph(1)->setName("Y");
    ui->plot_IMU_magnetometer->addGraph( );
    ui->plot_IMU_magnetometer->graph(2)->setPen(QPen(Qt::darkGreen));
    ui->plot_IMU_magnetometer->graph(2)->setName("Z");



//    ui->plot_IMU->replot( );
//    ui->plot_IMU->rescaleAxes();
}

void MainWindow::init_plot_RGB( ){

//    ui->plot_RGB->xAxis->setLabel("Time (s)");
//    ui->plot_RGB->yAxis->setLabel("Pressure (Nm/m2)");
//    ui->plot_RGB->yAxis->setRange(0, 100);

    QFont legendFont = font( );
    legendFont.setPointSize(9);
    ui->plot_RGB->legend->setVisible(true);
    ui->plot_RGB->legend->setFont(legendFont);
    ui->plot_RGB->legend->setBrush(QBrush(QColor(255,255,255,230)));

    ui->plot_RGB->axisRect( )->insetLayout( )->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
//    ui->plot_RGB->yAxis->setRange(0, 10);

    // Red.
    ui->plot_RGB->addGraph( );
    ui->plot_RGB->graph(0)->setPen(QPen(Qt::red));
    ui->plot_RGB->graph(0)->setName("Red");

    for (int i = 0; i < max_vector_size; i++) {
        ISL29125_R.append(0);
    }
    ui->plot_RGB->graph(0)->setData(x_axis, ISL29125_R);

    // Green.
    ui->plot_RGB->addGraph( );
    ui->plot_RGB->graph(1)->setPen(QPen(Qt::green));
    ui->plot_RGB->graph(1)->setName("Green");

    for (int i = 0; i < max_vector_size; i++) {
        ISL29125_G.append(0);
    }
    ui->plot_RGB->graph(1)->setData(x_axis, ISL29125_G);

    // Blue.
    ui->plot_RGB->addGraph( );
    ui->plot_RGB->graph(2)->setPen(QPen(Qt::blue));
    ui->plot_RGB->graph(2)->setName("Blue");

    for (int i = 0; i < max_vector_size; i++) {
        ISL29125_B.append(0);
    }
    ui->plot_RGB->graph(2)->setData(x_axis, ISL29125_B);


    ui->plot_RGB->replot( );
    ui->plot_RGB->rescaleAxes();
}

void MainWindow::init_plot_UV( ){

    ui->plot_UV->addGraph( );
    ui->plot_UV->graph(0)->setPen(QPen(Qt::darkBlue));
    ui->plot_UV->graph(0)->setName("N/m^2");

//    ui->plot_UV->xAxis->setLabel("Time (s)");
//    ui->plot_UV->yAxis->setLabel("Pressure (Nm/m2)");
//    ui->plot_UV->yAxis->setRange(0, 100);

    QFont legendFont = font( );
    legendFont.setPointSize(9);
    ui->plot_UV->legend->setVisible(true);
    ui->plot_UV->legend->setFont(legendFont);
    ui->plot_UV->legend->setBrush(QBrush(QColor(255,255,255,230)));

    ui->plot_UV->axisRect( )->insetLayout( )->setInsetAlignment(0, Qt::AlignRight|Qt::AlignBottom);
    ui->plot_UV->yAxis->setRange(0, 10);

    for (int i = 0; i < max_vector_size; i++) {
        UV_0.append(i);
    }

    ui->plot_UV->graph(0)->setData(x_axis, UV_0);
    ui->plot_UV->replot( );
    ui->plot_UV->rescaleAxes();
}








void MainWindow::update_plots( ){
    update_plot_barometer( );
    update_plot_temperature( );
    update_plot_humidity( );
    update_plot_ambient_light( );
    update_plot_IMU( );
    update_plot_RGB( );
    update_plot_UV( );
}
void MainWindow::update_plot_barometer( ){
    ui->plot_barometer->graph(0)->setData(x_axis, barometer_BMP280);
    ui->plot_barometer->replot( );
    ui->plot_barometer->rescaleAxes();
}
void MainWindow::update_plot_temperature( ){
    ui->plot_temperature->graph(0)->setData(x_axis, temperature_0);
    ui->plot_temperature->replot( );
    ui->plot_temperature->rescaleAxes();
}
void MainWindow::update_plot_humidity( ){
    ui->plot_humidity->graph(0)->setData(x_axis, humidity_0);
    ui->plot_humidity->replot( );
    ui->plot_humidity->rescaleAxes();
}
void MainWindow::update_plot_ambient_light( ){
    ui->plot_ambient_light->graph(0)->setData(x_axis, ambient_light_0);
    ui->plot_ambient_light->replot( );
    ui->plot_ambient_light->rescaleAxes();
}
void MainWindow::update_plot_IMU( ){
    ui->plot_IMU_accelerometer->graph(0)->setData(x_axis, IMU_accelerometer_x);
    ui->plot_IMU_accelerometer->graph(1)->setData(x_axis, IMU_accelerometer_y);
    ui->plot_IMU_accelerometer->graph(2)->setData(x_axis, IMU_accelerometer_z);
    ui->plot_IMU_accelerometer->replot( );
    ui->plot_IMU_accelerometer->rescaleAxes();

    ui->plot_IMU_gyroscope->graph(0)->setData(x_axis, IMU_gyroscope_x);
    ui->plot_IMU_gyroscope->graph(1)->setData(x_axis, IMU_gyroscope_y);
    ui->plot_IMU_gyroscope->graph(2)->setData(x_axis, IMU_gyroscope_z);
    ui->plot_IMU_gyroscope->replot( );
    ui->plot_IMU_gyroscope->rescaleAxes();

    ui->plot_IMU_magnetometer->graph(0)->setData(x_axis, IMU_magnetometer_x);
    ui->plot_IMU_magnetometer->graph(1)->setData(x_axis, IMU_magnetometer_y);
    ui->plot_IMU_magnetometer->graph(2)->setData(x_axis, IMU_magnetometer_z);
    ui->plot_IMU_magnetometer->replot( );
    ui->plot_IMU_magnetometer->rescaleAxes();
}
void MainWindow::update_plot_RGB( ){
    ui->plot_RGB->graph(0)->setData(x_axis, ISL29125_R);
    ui->plot_RGB->graph(1)->setData(x_axis, ISL29125_G);
    ui->plot_RGB->graph(2)->setData(x_axis, ISL29125_B);
    ui->plot_RGB->replot( );
    ui->plot_RGB->rescaleAxes();
}
void MainWindow::update_plot_UV( ){
    ui->plot_UV->graph(0)->setData(x_axis, UV_0);
    ui->plot_UV->replot( );
    ui->plot_UV->rescaleAxes();
}
