#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::rx_unpack_IMU(unsigned char *rx_data, int received_bytes){

    if (received_bytes >= 6){
        int16_t accelerometer_x = ((uint8_t)rx_data[0] << 8) | ((uint8_t)rx_data[1]);
        int16_t accelerometer_y = ((uint8_t)rx_data[2] << 8) | ((uint8_t)rx_data[3]);
        int16_t accelerometer_z = ((uint8_t)rx_data[4] << 8) | ((uint8_t)rx_data[5]);
//        print_to_terminal("accelerometer_x = "+ QString::number(accelerometer_x));
//        print_to_terminal("accelerometer_y = "+ QString::number(accelerometer_y));
//        print_to_terminal("accelerometer_z = "+ QString::number(accelerometer_z));
        shift_in_to_vector(&IMU_accelerometer_x, (double)accelerometer_x, max_vector_size);
        shift_in_to_vector(&IMU_accelerometer_y, (double)accelerometer_y, max_vector_size);
        shift_in_to_vector(&IMU_accelerometer_z, (double)accelerometer_z, max_vector_size);
    }
    if (received_bytes >= 12){
        int16_t gyroscope_x = ((uint8_t)rx_data[6] << 8) | ((uint8_t)rx_data[7]);
        int16_t gyroscope_y = ((uint8_t)rx_data[8] << 8) | ((uint8_t)rx_data[9]);
        int16_t gyroscope_z = ((uint8_t)rx_data[10] << 8) | ((uint8_t)rx_data[11]);
//        print_to_terminal("gyroscope_x = "+ QString::number(gyroscope_x));
//        print_to_terminal("gyroscope_y = "+ QString::number(gyroscope_y));
//        print_to_terminal("gyroscope_z = "+ QString::number(gyroscope_z));
        shift_in_to_vector(&IMU_gyroscope_x, (double)gyroscope_x, max_vector_size);
        shift_in_to_vector(&IMU_gyroscope_y, (double)gyroscope_y, max_vector_size);
        shift_in_to_vector(&IMU_gyroscope_z, (double)gyroscope_z, max_vector_size);
    }
    if (received_bytes >= 6){
        double magnetometer = (rx_data[4] << 8) + (rx_data[5]);
        //shift_in_to_vector(&IMU_gyroscope, magnetometer, max_vector_size);
    }
}


void MainWindow::rx_unpack_BMP280(unsigned char *rx_data, int received_bytes){

    if (received_bytes == 4){
        double pressure = ((uint8_t)rx_data[0] << 24) | ((uint8_t)rx_data[1] << 16) | ((uint8_t)rx_data[2] << 8) | (uint8_t)rx_data[3];
        shift_in_to_vector(&barometer_BMP280, pressure, max_vector_size);
    }
}

void MainWindow::rx_unpack_ISL29125(unsigned char *grb, int received_bytes){

    double green = (uint8_t)grb[0] | ((uint8_t)grb[1] << 8);
    double red   = (uint8_t)grb[2] | ((uint8_t)grb[3] << 8);
    double blue  = (uint8_t)grb[4] | ((uint8_t)grb[5] << 8);
    shift_in_to_vector(&ISL29125_G, green, max_vector_size);
    shift_in_to_vector(&ISL29125_R, red,   max_vector_size);
    shift_in_to_vector(&ISL29125_B, blue,  max_vector_size);
}


void MainWindow::rx_unpack_MPU9250(unsigned char *rx_data, int received_bytes){

    if (received_bytes >= 6){
        int16_t accelerometer_x = ((uint8_t)rx_data[0] << 8) | ((uint8_t)rx_data[1]);
        int16_t accelerometer_y = ((uint8_t)rx_data[2] << 8) | ((uint8_t)rx_data[3]);
        int16_t accelerometer_z = ((uint8_t)rx_data[4] << 8) | ((uint8_t)rx_data[5]);
        shift_in_to_vector(&IMU_accelerometer_x, (double)accelerometer_x, max_vector_size);
        shift_in_to_vector(&IMU_accelerometer_y, (double)accelerometer_y, max_vector_size);
        shift_in_to_vector(&IMU_accelerometer_z, (double)accelerometer_z, max_vector_size);
    }
    if (received_bytes >= 12){
        int16_t gyroscope_x = ((uint8_t)rx_data[6] << 8) | ((uint8_t)rx_data[7]);
        int16_t gyroscope_y = ((uint8_t)rx_data[8] << 8) | ((uint8_t)rx_data[9]);
        int16_t gyroscope_z = ((uint8_t)rx_data[10] << 8) | ((uint8_t)rx_data[11]);
        shift_in_to_vector(&IMU_gyroscope_x, (double)gyroscope_x, max_vector_size);
        shift_in_to_vector(&IMU_gyroscope_y, (double)gyroscope_y, max_vector_size);
        shift_in_to_vector(&IMU_gyroscope_z, (double)gyroscope_z, max_vector_size);
    }
    if (received_bytes >= 18){
        int16_t magnetometer_x = ((uint8_t)rx_data[12] << 8) | ((uint8_t)rx_data[13]);
        int16_t magnetometer_y = ((uint8_t)rx_data[14] << 8) | ((uint8_t)rx_data[15]);
        int16_t magnetometer_z = ((uint8_t)rx_data[16] << 8) | ((uint8_t)rx_data[17]);
        shift_in_to_vector(&IMU_magnetometer_x, (double)magnetometer_x, max_vector_size);
        shift_in_to_vector(&IMU_magnetometer_y, (double)magnetometer_y, max_vector_size);
        shift_in_to_vector(&IMU_magnetometer_z, (double)magnetometer_z, max_vector_size);
    }
}


