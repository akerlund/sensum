/*
 * ISL29125.c
 *
 *  Created on: Sep 23, 2017
 *      Author: freakuency
 */

#include "ch.h"
#include "hal.h"

#include "ISL29125.h"
#include "i2c_functions.h"

static int ISL29125_I2C_timeout;

bool ISL29125_initialize( ){

    ISL29125_I2C_timeout = 500;

    bool ret = true;
    uint8_t data = 0x00;

    // Check device ID
    I2C_read_byte(ISL29125_ADDR, ISL29125_DEVICE_ID, &data);
    if (data != 0x7D) {
        ret &= false;
    }

    ret &= ISL29125_reset( );

    // Set to RGB mode, 10k lux, and high IR compensation

    //ret &= ISL29125_configure(ISL29125_CFG1_MODE_RGB | ISL29125_CFG1_10KLUX, ISL29125_CFG2_IR_ADJUST_LOW, ISL29125_CFG_DEFAULT);
    ret &= ISL29125_configure(ISL29125_CFG1_MODE_RGB | ISL29125_CFG1_375LUX, ISL29125_CFG2_IR_ADJUST_LOW, ISL29125_CFG_DEFAULT);

    return ret;
}

bool ISL29125_reset( ){

    uint8_t data = 0x46;
    uint8_t temp = 0x00;

    I2C_write_byte(ISL29125_ADDR, ISL29125_DEVICE_ID, data);

    I2C_read_byte(ISL29125_ADDR, ISL29125_CONFIG_1, &temp);
    data = temp;
    I2C_read_byte(ISL29125_ADDR, ISL29125_CONFIG_2, &temp);
    data |= temp;
    I2C_read_byte(ISL29125_ADDR, ISL29125_CONFIG_3, &temp);
    data |= temp;
    I2C_read_byte(ISL29125_ADDR, ISL29125_STATUS_FLAGS, &temp);
    data |= temp;

    if (data != 0x00){
        return false;
    } else {
        return true;
    }
}

bool ISL29125_configure(uint8_t config_1, uint8_t config_2, uint8_t config_3){
    I2C_write_byte(ISL29125_ADDR, ISL29125_CONFIG_1, config_1);
    I2C_write_byte(ISL29125_ADDR, ISL29125_CONFIG_2, config_2);
    I2C_write_byte(ISL29125_ADDR, ISL29125_CONFIG_3, config_3);

    return true;
}

bool ISL29125_set_upper_threshold(uint8_t *data){
    return I2C_write_bytes(ISL29125_ADDR, ISL29125_HIGH_THRESHOLD_L, data, 2);
}

bool ISL29125_set_lower_threshold(uint8_t *data){
    return I2C_write_bytes(ISL29125_ADDR, ISL29125_LOW_THRESHOLD_L, data, 2);
}

bool ISL29125_get_upper_threshold(uint8_t *data){
    return I2C_read_bytes(ISL29125_ADDR, ISL29125_HIGH_THRESHOLD_L, data, 2);
}

bool ISL29125_get_lower_threshold(uint8_t *data){
    return I2C_read_bytes(ISL29125_ADDR, ISL29125_LOW_THRESHOLD_L, data, 2);
}

bool ISL29125_get_red(uint8_t *red){
    return I2C_read_bytes(ISL29125_ADDR, ISL29125_RED_L, red, 2);
}

bool ISL29125_get_green(uint8_t *green){
    return I2C_read_bytes(ISL29125_ADDR, ISL29125_GREEN_L, green, 2);
}

bool ISL29125_get_blue(uint8_t *blue){
    return I2C_read_bytes(ISL29125_ADDR, ISL29125_BLUE_L, blue, 2);
}

bool ISL29125_get_GRB(uint8_t *grb){
    return I2C_read_bytes(ISL29125_ADDR, ISL29125_GREEN_L, grb, 6);
}

bool ISL29125_get_status(uint8_t *status){
    return I2C_read_bytes(ISL29125_ADDR, ISL29125_STATUS_FLAGS, status, 2);
}
