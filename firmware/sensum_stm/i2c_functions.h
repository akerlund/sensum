/*
 * i2c_functions.h
 *
 *  Created on: Aug 2, 2017
 *      Author: freakuency
 */


#ifndef I2C_FUNCTIONS_
#define I2C_FUNCTIONS_

// MPU6050 ADDRESS
#define MPU6050_ADDR_AD0_LOW    0b1101000
#define MPU6050_ADDR_AD0_HIGH   0b1101001
#define MPU6050_REGS_TO_READ    14

// MPU6050 REGISTERS
#define MPU6050_ACCEL_XOUT_H    0x3B
#define MPU6050_ACCEL_XOUT_L    0x3C
#define MPU6050_ACCEL_YOUT_H    0x3D
#define MPU6050_ACCEL_YOUT_L    0x3E
#define MPU6050_ACCEL_ZOUT_H    0x3F
#define MPU6050_ACCEL_ZOUT_L    0x40
#define MPU6050_TEMP_OUT_H R    0x41
#define MPU6050_TEMP_OUT_L R    0x42
#define MPU6050_GYRO_XOUT_H     0x43
#define MPU6050_GYRO_XOUT_L     0x44
#define MPU6050_GYRO_YOUT_H     0x45
#define MPU6050_GYRO_YOUT_L     0x46
#define MPU6050_GYRO_ZOUT_H     0x47
#define MPU6050_GYRO_ZOUT_L     0x48


void i2c_initialization(void);
msg_t i2c_read_MPU6050(uint8_t *rx_buffer);

#endif /* I2C_FUNCTIONS_ */
