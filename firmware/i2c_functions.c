/*
 * i2c_functions.c
 *
 *  Created on: Aug 2, 2017
 *      Author: freakuency
 */

#include "ch.h"
#include "hal.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "i2c_functions.h"

static uint8_t tx_buf[I2C_BUFFER_LENGTH];
static uint8_t rx_buf[2];

static i2cflags_t errors = 0;

static const I2CConfig i2cfg1 = { // I2C interface 1.
    OPMODE_I2C,
    400000,
    FAST_DUTY_CYCLE_2,
};

static systime_t I2C_timeout = MS2ST(500);

void i2c_initialization(void) {

	i2cStart(&I2CD1, &i2cfg1);
	palSetPadMode(GPIOB, 8, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
	palSetPadMode(GPIOB, 9, PAL_MODE_ALTERNATE(4) | PAL_STM32_OTYPE_OPENDRAIN);
	chThdSleepMilliseconds(100);
}

bool I2C_write_byte(uint8_t device_address, uint8_t register_address, uint8_t data) {

    return I2C_write_bytes(device_address, register_address, &data, 1);
}

bool I2C_write_bytes(uint8_t device_address, uint8_t register_address, uint8_t *data, uint8_t length) {

    msg_t rdymsg;

    if((length + 1) > I2C_BUFFER_LENGTH) {
        return false;
    }

    tx_buf[0] = register_address;
    memcpy(tx_buf + sizeof(uint8_t), data, sizeof(uint8_t) * length);

    i2cAcquireBus(&I2CD1);
    rdymsg = i2cMasterTransmit(&I2CD1, device_address, tx_buf, length + 1, rx_buf, I2C_timeout);
    i2cReleaseBus(&I2CD1);

    if(rdymsg == MSG_TIMEOUT || rdymsg == MSG_RESET) {
        return false;
    }

    return true;
}

bool I2C_read_byte(uint8_t device_address, uint8_t register_address, uint8_t *data) {

    return I2C_read_bytes(device_address, register_address, data, 1);
}

bool I2C_read_bytes(uint8_t device_address, uint8_t register_address, uint8_t *data, uint8_t length) {

    msg_t status = MSG_OK;

    tx_buf[0] = register_address; // Register address.
    tx_buf[1] = 0x0;

    i2cAcquireBus(&I2CD1);
    status = i2cMasterTransmitTimeout(&I2CD1, device_address, tx_buf, 1, data, length, I2C_timeout);
    i2cReleaseBus(&I2CD1);

    if (status != MSG_OK){
        errors = i2cGetErrors(&I2CD1);
        return errors;
    } else {
        return 0;
    }
}
