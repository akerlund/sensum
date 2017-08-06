/*
 * i2c_functions.c
 *
 *  Created on: Aug 2, 2017
 *      Author: freakuency
 */

#include "ch.h"
#include "hal.h"

#include "i2c_functions.h"

static uint8_t txbuf[2];
//static uint8_t rxbuf[14];

static i2cflags_t errors = 0;

/* I2C interface #1 */
static const I2CConfig i2cfg1 = {
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};



void i2c_initialization(void) {

	i2cStart(&I2CD1, &i2cfg1);
	palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
	palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
	chThdSleepMilliseconds(100);
}

msg_t i2c_read_MPU6050(uint8_t *rx_buffer){

	systime_t timeout = MS2ST(10);
	msg_t status = MSG_OK;

	txbuf[0] = MPU6050_ACCEL_XOUT_H; /* register address */
	txbuf[1] = 0x0;
    i2cAcquireBus(&I2CD1);
    status = i2cMasterTransmitTimeout(&I2CD1, MPU6050_ADDR_AD0_LOW, txbuf, 1, rx_buffer, MPU6050_REGS_TO_READ, timeout);
    i2cReleaseBus(&I2CD1);

    if (status != MSG_OK){
    	errors = i2cGetErrors(&I2CD1);
      	return errors;
    } else {
    	return 0;
    }
}
