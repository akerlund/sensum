/*
 * mpu9250.c
 *
 *  Created on: Oct 10, 2017
 *      Author: freakuency
 *
 *      Based on https://github.com/sparkfun/MPU-9250_Breakout
 *
 *      Customized for my project, i.e., using ChibiOS.
 */

#include "ch.h"
#include "hal.h"

#include <stdbool.h>
#include <math.h>

#include "mpu9250.h"
#include "i2c_functions.h"

/**
 *  @brief Reads the accelerometer data and stores them to the
 *         address given by the pointer argument.
 *
 *  @param accelerometer_data
 *         The pointer to an address space of 6 bytes.
 *
 *  @return Successrate of I2C read.
 */
bool get_accelerometer_data(int16_t *accelerometer_data){

    uint8_t raw_data[6];
    bool ret = true;

    ret &= I2C_read_bytes(MPU9250_ADDRESS, ACCEL_XOUT_H, &raw_data[0], 6);

    if(ret){
        accelerometer_data[0] = ((int16_t)raw_data[0] << 8) | raw_data[1];
        accelerometer_data[1] = ((int16_t)raw_data[2] << 8) | raw_data[3];
        accelerometer_data[2] = ((int16_t)raw_data[4] << 8) | raw_data[5];
    }

    return ret;
}

/**
 *  @brief Reads the gyroscope data and stores them to the
 *         address given by the pointer argument.
 *
 *  @param gyroscope_data
 *         The pointer to an address space of 6 bytes.
 *
 *  @return Successrate of I2C read.
 */
bool get_gyroscope_data(int16_t *gyroscope_data){

    uint8_t raw_data[6];
    bool ret = true;

    ret &= I2C_read_bytes(MPU9250_ADDRESS, GYRO_XOUT_H, &raw_data[0], 6);

    if(ret){
        gyroscope_data[0] = ((int16_t)raw_data[0] << 8) | raw_data[1];
        gyroscope_data[1] = ((int16_t)raw_data[2] << 8) | raw_data[3];
        gyroscope_data[2] = ((int16_t)raw_data[4] << 8) | raw_data[5];
    }

    return ret;
}

/**
 *  @brief Reads the magnetometer data and stores them to the
 *         address given by the pointer argument.
 *
 *  @param magnetometer_data
 *         The pointer to an address space of 6 bytes.
 *
 *  @return Successrate of I2C read OR sensor overflow.
 */
bool get_magnetometer_data(int16_t *magnetometer_data){

    uint8_t raw_data[7]; // X,Y,Z and ST2 (Status). Vectors are 14-bit.
    /*
    * ST2 register has a role as data reading end register, also. When any of
    * measurement data register is read in continuous measurement mode or
    * external trigger measurement mode, it means data reading start and
    * taken as data reading until ST2 register is read. Therefore, when any
    * of measurement data is read, be sure to read ST2 register at the end.
    */
    uint8_t ST1 = 0;
    bool ret = true;

    // Checking the data ready bit.
    ret &= I2C_read_byte(AK8963_ADDRESS, AK8963_ST1, &ST1);

    if(ret & (ST1 & 0x01)) {

        ret &= I2C_read_bytes(AK8963_ADDRESS, AK8963_XOUT_L, &raw_data[0], 7);

        // Check if magnetic sensor overflow set, if not then report data
        if(!(raw_data[6] & 0x08)){
            magnetometer_data[0] = ((int16_t)raw_data[1] << 8) | raw_data[0];
            magnetometer_data[1] = ((int16_t)raw_data[3] << 8) | raw_data[2];
            magnetometer_data[2] = ((int16_t)raw_data[5] << 8) | raw_data[4];
        }
    }

    return ret;
}

bool get_temperature_data(int16_t *temperature_data){

    uint8_t raw_data[2];
    bool ret = true;

    ret &= I2C_read_bytes(MPU9250_ADDRESS, TEMP_OUT_H, &raw_data[0], 2);

    if(ret){
        temperature_data[0] = ((int16_t)raw_data[0] << 8) | raw_data[1];
    }

    return ret;
}

void init_AK8963(float *calibration){

    uint8_t raw_data[3];

    // Power down magnetometer.
    I2C_write_byte(AK8963_ADDRESS, AK8963_CNTL, 0x00);
    chThdSleepMilliseconds(10);

    // Enter Fuse ROM access mode.
    I2C_write_byte(AK8963_ADDRESS, AK8963_CNTL, 0x0F);
    chThdSleepMilliseconds(10);

    // Read the calibration values.
    I2C_read_bytes(AK8963_ADDRESS, AK8963_ASAX, &raw_data[0], 3);

    // Return x-axis sensitivity adjustment values, etc.
    calibration[0] =  (float)(raw_data[0] - 128)/256. + 1.;
    calibration[1] =  (float)(raw_data[1] - 128)/256. + 1.;
    calibration[2] =  (float)(raw_data[2] - 128)/256. + 1.;

    // Power down magnetometer.
    I2C_write_byte(AK8963_ADDRESS, AK8963_CNTL, 0x00);
    chThdSleepMilliseconds(10);

    // Configure the magnetometer.
    //uint8_t AK8963_14BITS = 0; // 0.6 mG per LSB
    uint8_t AK8963_16BITS = 1; // 0.15 mG per LSB

    //uint8_t AK8963_MODE_8Hz   = 0x02;
    uint8_t AK8963_MODE_100Hz = 0x06;

    I2C_write_byte(AK8963_ADDRESS, AK8963_CNTL, AK8963_16BITS << 4 | AK8963_MODE_100Hz);
    chThdSleepMilliseconds(10);
}

bool init_MPU9250( ){

    bool ret = true;

    // Wake up device by clearing sleep mode bit, and enable all sensors.
    ret &= I2C_write_byte(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);
    if(ret){
        palSetLine(LINE_LED3);
    }
    chThdSleepMilliseconds(100);

    // Auto selects the best available clock source – PLL if ready, else
    // use the Internal oscillator.
    ret &= I2C_write_byte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
    if(ret){
        palSetLine(LINE_LED4);
    }
    chThdSleepMilliseconds(200);

    // Configure Gyro and Thermometer
    // Disable FSYNC and set thermometer and gyro bandwidth to 41 and 42 Hz, respectively;
    // minimum delay time for this setting is 5.9 ms, which means sensor fusion update rates cannot
    // be higher than 1 / 0.0059 = 170 Hz
    // DLPF_CFG = bits 2:0 = 011; this limits the sample rate to 1000 Hz for both
    // With the MPU9250, it is possible to get gyro sample rates of 32 kHz (!), 8 kHz, or 1 kHz
    ret &= I2C_write_byte(MPU9250_ADDRESS, CONFIG, 0x03);
    if(ret){
        palSetLine(LINE_LED5);
    }

    // Set sample rate = gyroscope output rate/(1 + SMPLRT_DIV)
    ret &= I2C_write_byte(MPU9250_ADDRESS, SMPLRT_DIV, 0x04);  // Use a 200 Hz rate; a rate consistent with the filter update rate
                                    // determined inset in CONFIG above

    if(ret){
        palSetLine(LINE_LED6);
    }

    for(int j = 0; j < 50; j++){
        palToggleLine(LINE_LED4);
        chThdSleepMilliseconds(100);
    }
    palClearLine(LINE_LED3);
    palClearLine(LINE_LED4);
    palClearLine(LINE_LED5);
    palClearLine(LINE_LED6);

    // Set gyroscope full scale range
    // Range selects FS_SEL and AFS_SEL are 0 - 3, so 2-bit values are left-shifted into positions 4:3
    uint8_t c2[8];
    ret &= I2C_read_byte(MPU9250_ADDRESS, GYRO_CONFIG, &c2[0]); // get current GYRO_CONFIG register value
    // c = c & ~0xE0; // Clear self-test bits [7:5]
    uint8_t c = c2[0];
    if(ret){
        palSetLine(LINE_LED3);
    }
    enum gyroscope_s {
        GFS_250DPS = 0,
        GFS_500DPS,
        GFS_1000DPS,
        GFS_2000DPS
    } gyroscope_scale = 0;

    c = c & ~0x02; // Clear Fchoice bits [1:0]
    c = c & ~0x18; // Clear AFS bits [4:3]
    c = c | gyroscope_scale << 3; // Set full scale range for the gyro
    // c =| 0x00; // Set Fchoice for the gyro to 11 by writing its inverse to bits 1:0 of GYRO_CONFIG

    ret &= I2C_write_byte(MPU9250_ADDRESS, GYRO_CONFIG, c); // Write new GYRO_CONFIG value to register
    if(ret){
        palSetLine(LINE_LED4);
    }
    // Set accelerometer full-scale range configuration.
    enum accelerometer_s {
        AFS_2G = 0,
        AFS_4G,
        AFS_8G,
        AFS_16G
    } accelerometer_scale = 0;

    ret &= I2C_read_byte(MPU9250_ADDRESS, ACCEL_CONFIG, &c); // get current ACCEL_CONFIG register value
    if(ret){
        palSetLine(LINE_LED5);
    }
    // c = c & ~0xE0; // Clear self-test bits [7:5]
    c = c & ~0x18;  // Clear AFS bits [4:3]
    c = c | accelerometer_scale << 3; // Set full scale range for the accelerometer
    ret &= I2C_write_byte(MPU9250_ADDRESS, ACCEL_CONFIG, c); // Write new ACCEL_CONFIG register value
    if(ret){
        palSetLine(LINE_LED6);
    }

    chThdSleepMilliseconds(500);

    for(int j = 0; j < 50; j++){
        palToggleLine(LINE_LED5);
        chThdSleepMilliseconds(100);
    }
    palClearLine(LINE_LED3);
    palClearLine(LINE_LED4);
    palClearLine(LINE_LED5);
    palClearLine(LINE_LED6);
    // Set accelerometer sample rate configuration
    // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
    // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz

    ret &= I2C_read_byte(MPU9250_ADDRESS, ACCEL_CONFIG2, &c); // get current ACCEL_CONFIG2 register value
    if(ret){
        palSetLine(LINE_LED3);
    }
    c = c & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
    c = c | 0x03;  // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz

    ret &= I2C_write_byte(MPU9250_ADDRESS, ACCEL_CONFIG2, c); // Write new ACCEL_CONFIG2 register value
    if(ret){
        palSetLine(LINE_LED4);
    }
    // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates,
    // but all these rates are further reduced by a factor of 5 to 200 Hz because of the SMPLRT_DIV setting

    // Configure Interrupts and Bypass Enable
    // Set interrupt pin active high, push-pull, hold interrupt pin level HIGH until interrupt cleared,
    // clear on read of INT_STATUS, and enable I2C_BYPASS_EN so additional chips
    // can join the I2C bus and all can be controlled by the Arduino as master
    ret &= I2C_write_byte(MPU9250_ADDRESS, INT_PIN_CFG, 0x22);
    if(ret){
        palSetLine(LINE_LED5);
    }
    ret &= I2C_write_byte(MPU9250_ADDRESS, INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
    if(ret){
        palSetLine(LINE_LED6);
    }
    chThdSleepMilliseconds(100);

    return ret;
}


// Function which accumulates gyro and accelerometer data after device
// initialization. It calculates the average of the at-rest readings and then
// loads the resulting offsets into accelerometer and gyro bias registers.
void MPU9250_calibrate(float *gyroBias, float *accelBias){

    uint8_t data[12];
    uint16_t ii, packet_count, fifo_count;
    int32_t gyro_bias[3] = {0, 0, 0}, accel_bias[3] = {0, 0, 0};

    // Write a one to bit 7 reset bit; toggle reset device
    I2C_write_byte(MPU9250_ADDRESS, PWR_MGMT_1, 0x80);
    chThdSleepMilliseconds(100);

    // Auto select clock source to be PLL gyroscope
    // reference if ready else use the internal oscillator, bits 2:0 = 001
    I2C_write_byte(MPU9250_ADDRESS, PWR_MGMT_1, 0x01);
    I2C_write_byte(MPU9250_ADDRESS, PWR_MGMT_2, 0x00);
    chThdSleepMilliseconds(200);

    // Configure device for bias calculation
    I2C_write_byte(MPU9250_ADDRESS, INT_ENABLE,   0x00); // Disable all interrupts
    I2C_write_byte(MPU9250_ADDRESS, FIFO_EN,      0x00); // Disable FIFO
    I2C_write_byte(MPU9250_ADDRESS, PWR_MGMT_1,   0x00); // Turn on internal clock source
    I2C_write_byte(MPU9250_ADDRESS, I2C_MST_CTRL, 0x00); // Disable I2C master
    I2C_write_byte(MPU9250_ADDRESS, USER_CTRL,    0x00); // Disable FIFO and I2C master modes
    I2C_write_byte(MPU9250_ADDRESS, USER_CTRL,    0x0C); // Reset FIFO and DMP
    chThdSleepMilliseconds(15);

    // Configure MPU6050 gyro and accelerometer for bias calculation
    I2C_write_byte(MPU9250_ADDRESS, CONFIG,       0x01); // Set low-pass filter to 188 Hz
    I2C_write_byte(MPU9250_ADDRESS, SMPLRT_DIV,   0x00); // Set sample rate to 1 kHz
    I2C_write_byte(MPU9250_ADDRESS, GYRO_CONFIG,  0x00); // Set gyro full-scale to 250 degrees per second, maximum sensitivity
    I2C_write_byte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00); // Set accelerometer full-scale to 2 g, maximum sensitivity

    uint16_t gyrosensitivity  = 131;   // = 131 LSB/degrees/sec
    uint16_t accelsensitivity = 16384; // = 16384 LSB/g

    // Configure FIFO to capture accelerometer and gyro data for bias calculation
    I2C_write_byte(MPU9250_ADDRESS, USER_CTRL, 0x40);   // Enable FIFO
    I2C_write_byte(MPU9250_ADDRESS, FIFO_EN, 0x78);     // Enable gyro and accelerometer sensors for FIFO  (max size 512 bytes in MPU-9150)
    chThdSleepMilliseconds(40); // accumulate 40 samples in 40 milliseconds = 480 bytes

    // At end of sample accumulation, turn off FIFO sensor read
    I2C_write_byte(MPU9250_ADDRESS, FIFO_EN, 0x00);        // Disable gyro and accelerometer sensors for FIFO
    I2C_read_bytes(MPU9250_ADDRESS, FIFO_COUNTH, &data[0], 2); // read FIFO sample count
    fifo_count = ((uint16_t)data[0] << 8) | data[1];
    packet_count = fifo_count/12;// How many sets of full gyro and accelerometer data for averaging

    for(ii = 0; ii < packet_count; ii++){
        int16_t accel_temp[3] = {0, 0, 0}, gyro_temp[3] = {0, 0, 0};
        I2C_read_bytes(MPU9250_ADDRESS, FIFO_R_W, &data[0], 12); // read data for averaging
        accel_temp[0] = (int16_t) (((int16_t)data[0] << 8) | data[1]  );  // Form signed 16-bit integer for each sample in FIFO
        accel_temp[1] = (int16_t) (((int16_t)data[2] << 8) | data[3]  );
        accel_temp[2] = (int16_t) (((int16_t)data[4] << 8) | data[5]  );
        gyro_temp[0]  = (int16_t) (((int16_t)data[6] << 8) | data[7]  );
        gyro_temp[1]  = (int16_t) (((int16_t)data[8] << 8) | data[9]  );
        gyro_temp[2]  = (int16_t) (((int16_t)data[10] << 8) | data[11]);

        accel_bias[0] += (int32_t) accel_temp[0]; // Sum individual signed 16-bit biases to get accumulated signed 32-bit biases
        accel_bias[1] += (int32_t) accel_temp[1];
        accel_bias[2] += (int32_t) accel_temp[2];
        gyro_bias[0]  += (int32_t) gyro_temp[0];
        gyro_bias[1]  += (int32_t) gyro_temp[1];
        gyro_bias[2]  += (int32_t) gyro_temp[2];
    }

    accel_bias[0] /= (int32_t) packet_count; // Normalize sums to get average count biases
    accel_bias[1] /= (int32_t) packet_count;
    accel_bias[2] /= (int32_t) packet_count;
    gyro_bias[0]  /= (int32_t) packet_count;
    gyro_bias[1]  /= (int32_t) packet_count;
    gyro_bias[2]  /= (int32_t) packet_count;

    if(accel_bias[2] > 0L) {accel_bias[2] -= (int32_t) accelsensitivity;}  // Remove gravity from the z-axis accelerometer bias calculation
    else {accel_bias[2] += (int32_t) accelsensitivity;}

    // Construct the gyro biases for push to the hardware gyro bias registers, which are reset to zero upon device startup
    data[0] = (-gyro_bias[0]/4  >> 8) & 0xFF; // Divide by 4 to get 32.9 LSB per deg/s to conform to expected bias input format
    data[1] = (-gyro_bias[0]/4)       & 0xFF; // Biases are additive, so change sign on calculated average gyro biases
    data[2] = (-gyro_bias[1]/4  >> 8) & 0xFF;
    data[3] = (-gyro_bias[1]/4)       & 0xFF;
    data[4] = (-gyro_bias[2]/4  >> 8) & 0xFF;
    data[5] = (-gyro_bias[2]/4)       & 0xFF;

    // Push gyro biases to hardware registers
    I2C_write_byte(MPU9250_ADDRESS, XG_OFFSET_H, data[0]);
    I2C_write_byte(MPU9250_ADDRESS, XG_OFFSET_L, data[1]);
    I2C_write_byte(MPU9250_ADDRESS, YG_OFFSET_H, data[2]);
    I2C_write_byte(MPU9250_ADDRESS, YG_OFFSET_L, data[3]);
    I2C_write_byte(MPU9250_ADDRESS, ZG_OFFSET_H, data[4]);
    I2C_write_byte(MPU9250_ADDRESS, ZG_OFFSET_L, data[5]);

    // Output scaled gyro biases for display in the main program
    gyroBias[0] = (float) gyro_bias[0]/(float) gyrosensitivity;
    gyroBias[1] = (float) gyro_bias[1]/(float) gyrosensitivity;
    gyroBias[2] = (float) gyro_bias[2]/(float) gyrosensitivity;

    // Construct the accelerometer biases for push to the hardware accelerometer bias registers. These registers contain
    // factory trim values which must be added to the calculated accelerometer biases; on boot up these registers will hold
    // non-zero values. In addition, bit 0 of the lower byte must be preserved since it is used for temperature
    // compensation calculations. Accelerometer bias registers expect bias input as 2048 LSB per g, so that
    // the accelerometer biases calculated above must be divided by 8.

    int32_t accel_bias_reg[3] = {0, 0, 0}; // A place to hold the factory accelerometer trim biases
    I2C_read_bytes(MPU9250_ADDRESS, XA_OFFSET_H, &data[0], 2); // Read factory accelerometer trim values
    accel_bias_reg[0] = (int32_t) (((int16_t)data[0] << 8) | data[1]);
    I2C_read_bytes(MPU9250_ADDRESS, YA_OFFSET_H, &data[0], 2);
    accel_bias_reg[1] = (int32_t) (((int16_t)data[0] << 8) | data[1]);
    I2C_read_bytes(MPU9250_ADDRESS, ZA_OFFSET_H, &data[0], 2);
    accel_bias_reg[2] = (int32_t) (((int16_t)data[0] << 8) | data[1]);

    uint32_t mask = 1uL; // Define mask for temperature compensation bit 0 of lower byte of accelerometer bias registers
    uint8_t mask_bit[3] = {0, 0, 0}; // Define array to hold mask bit for each accelerometer bias axis

    for(ii = 0; ii < 3; ii++) {
        if((accel_bias_reg[ii] & mask)) mask_bit[ii] = 0x01; // If temperature compensation bit is set, record that fact in mask_bit
    }

    // Construct total accelerometer bias, including calculated average accelerometer bias from above
    accel_bias_reg[0] -= (accel_bias[0]/8); // Subtract calculated averaged accelerometer bias scaled to 2048 LSB/g (16 g full scale)
    accel_bias_reg[1] -= (accel_bias[1]/8);
    accel_bias_reg[2] -= (accel_bias[2]/8);

    data[0] = (accel_bias_reg[0] >> 8) & 0xFF;
    data[1] = (accel_bias_reg[0])      & 0xFF;
    data[1] = data[1] | mask_bit[0]; // preserve temperature compensation bit when writing back to accelerometer bias registers
    data[2] = (accel_bias_reg[1] >> 8) & 0xFF;
    data[3] = (accel_bias_reg[1])      & 0xFF;
    data[3] = data[3] | mask_bit[1]; // preserve temperature compensation bit when writing back to accelerometer bias registers
    data[4] = (accel_bias_reg[2] >> 8) & 0xFF;
    data[5] = (accel_bias_reg[2])      & 0xFF;
    data[5] = data[5] | mask_bit[2]; // preserve temperature compensation bit when writing back to accelerometer bias registers

    // Apparently this is not working for the acceleration biases in the MPU-9250
    // Are we handling the temperature correction bit properly?
    // Push accelerometer biases to hardware registers
    I2C_write_byte(MPU9250_ADDRESS, XA_OFFSET_H, data[0]);
    I2C_write_byte(MPU9250_ADDRESS, XA_OFFSET_L, data[1]);
    I2C_write_byte(MPU9250_ADDRESS, YA_OFFSET_H, data[2]);
    I2C_write_byte(MPU9250_ADDRESS, YA_OFFSET_L, data[3]);
    I2C_write_byte(MPU9250_ADDRESS, ZA_OFFSET_H, data[4]);
    I2C_write_byte(MPU9250_ADDRESS, ZA_OFFSET_L, data[5]);

    // Output scaled accelerometer biases for display in the main program
    accelBias[0] = (float)accel_bias[0]/(float)accelsensitivity;
    accelBias[1] = (float)accel_bias[1]/(float)accelsensitivity;
    accelBias[2] = (float)accel_bias[2]/(float)accelsensitivity;
}


// Accelerometer and gyroscope self test; check calibration wrt factory settings
// Should return percent deviation from factory trim values, +/- 14 or less deviation is a pass
void MPU9250_self_test(float *deviation){

    uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};
    uint8_t selfTest[6];
    int16_t gAvg[3], aAvg[3], aSTAvg[3], gSTAvg[3];
    float factoryTrim[6];
    uint8_t FS = 0;

    I2C_write_byte(MPU9250_ADDRESS, SMPLRT_DIV, 0x00);    // Set gyro sample rate to 1 kHz
    I2C_write_byte(MPU9250_ADDRESS, CONFIG, 0x02);        // Set gyro sample rate to 1 kHz and DLPF to 92 Hz
    I2C_write_byte(MPU9250_ADDRESS, GYRO_CONFIG, 1<<FS);  // Set full scale range for the gyro to 250 dps
    I2C_write_byte(MPU9250_ADDRESS, ACCEL_CONFIG2, 0x02); // Set accelerometer rate to 1 kHz and bandwidth to 92 Hz
    I2C_write_byte(MPU9250_ADDRESS, ACCEL_CONFIG, 1<<FS); // Set full scale range for the accelerometer to 2 g

    // Get average current values of gyro and acclerometer.
    for(int ii = 0; ii < 200; ii++){

        I2C_read_bytes(MPU9250_ADDRESS, ACCEL_XOUT_H, &rawData[0], 6);      // Read the six raw data registers into data array
        aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
        aAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
        aAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);

        I2C_read_bytes(MPU9250_ADDRESS, GYRO_XOUT_H, &rawData[0], 6);       // Read the six raw data registers sequentially into data array
        gAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]); // Turn the MSB and LSB into a signed 16-bit value
        gAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
        gAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);
    }

    // Get average of 200 values and store as average current readings.
    for (int ii =0; ii < 3; ii++) {
        aAvg[ii] /= 200;
        gAvg[ii] /= 200;
    }

    // Configure the accelerometer for self-test
    I2C_write_byte(MPU9250_ADDRESS, ACCEL_CONFIG, 0xE0); // Enable self test on all three axes and set accelerometer range to +/- 2 g
    I2C_write_byte(MPU9250_ADDRESS, GYRO_CONFIG,  0xE0); // Enable self test on all three axes and set gyro range to +/- 250 degrees/s
    chThdSleepMilliseconds(25);  // chThdSleepMilliseconds a while to let the device stabilize

    for( int ii = 0; ii < 200; ii++) {  // get average self-test values of gyro and acclerometer

        I2C_read_bytes(MPU9250_ADDRESS, ACCEL_XOUT_H, &rawData[0], 6);  // Read the six raw data registers into data array
        aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]);  // Turn the MSB and LSB into a signed 16-bit value
        aSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
        aSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);

        I2C_read_bytes(MPU9250_ADDRESS, GYRO_XOUT_H, &rawData[0], 6);  // Read the six raw data registers sequentially into data array
        gSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]);  // Turn the MSB and LSB into a signed 16-bit value
        gSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]);
        gSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]);
    }

    for (int ii =0; ii < 3; ii++) {  // Get average of 200 values and store as average self-test readings
        aSTAvg[ii] /= 200;
        gSTAvg[ii] /= 200;
    }

    // Configure the gyro and accelerometer for normal operation
    I2C_write_byte(MPU9250_ADDRESS, ACCEL_CONFIG, 0x00);
    I2C_write_byte(MPU9250_ADDRESS, GYRO_CONFIG,  0x00);
    chThdSleepMilliseconds(25);  // chThdSleepMilliseconds a while to let the device stabilize

    // Retrieve accelerometer and gyro factory Self-Test Code from USR_Reg
    I2C_read_byte(MPU9250_ADDRESS, SELF_TEST_X_ACCEL, &selfTest[0]); // X-axis accel self-test results
    I2C_read_byte(MPU9250_ADDRESS, SELF_TEST_Y_ACCEL, &selfTest[1]); // Y-axis accel self-test results
    I2C_read_byte(MPU9250_ADDRESS, SELF_TEST_Z_ACCEL, &selfTest[2]); // Z-axis accel self-test results
    I2C_read_byte(MPU9250_ADDRESS, SELF_TEST_X_GYRO, &selfTest[3]);  // X-axis gyro self-test results
    I2C_read_byte(MPU9250_ADDRESS, SELF_TEST_Y_GYRO, &selfTest[4]);  // Y-axis gyro self-test results
    I2C_read_byte(MPU9250_ADDRESS, SELF_TEST_Z_GYRO, &selfTest[5]);  // Z-axis gyro self-test results

    // Retrieve factory self-test value from self-test code reads
    factoryTrim[0] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[0] - 1.0) )); // FT[Xa] factory trim calculation
    factoryTrim[1] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[1] - 1.0) )); // FT[Ya] factory trim calculation
    factoryTrim[2] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[2] - 1.0) )); // FT[Za] factory trim calculation
    factoryTrim[3] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[3] - 1.0) )); // FT[Xg] factory trim calculation
    factoryTrim[4] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[4] - 1.0) )); // FT[Yg] factory trim calculation
    factoryTrim[5] = (float)(2620/1<<FS)*(pow( 1.01 , ((float)selfTest[5] - 1.0) )); // FT[Zg] factory trim calculation

    // Report results as a ratio of (STR - FT)/FT; the change from Factory Trim of the Self-Test Response
    // To get percent, must multiply by 100
    for (int i = 0; i < 3; i++) {
        deviation[i]   = 100.0*((float)(aSTAvg[i] - aAvg[i]))/factoryTrim[i];   // Report percent differences
        deviation[i+3] = 100.0*((float)(gSTAvg[i] - gAvg[i]))/factoryTrim[i+3]; // Report percent differences
    }
}
