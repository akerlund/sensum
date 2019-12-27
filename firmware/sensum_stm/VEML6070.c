/*
 * VEML6070.c
 *
 *  Created on: Sep 23, 2017
 *      Author: freakuency
 */

#include "ch.h"
#include "hal.h"

#include "VEML6070.h"
#include "i2c_functions.h"

bool VEML6070_initialize(uint8_t integration_time){

    uint8_t cmd = 0x02;
    if(integration_time >= 4){
        cmd |= 0x0C;
    } else {
        cmd |= (integration_time << 2);
    }

    I2C_write_byte(VEML6070_ADDR_1, 0x00, cmd);

    return true;
}

uint16_t VEML6070_get_UV( ){

    uint8_t uv_temp = 0;
    uint16_t uv = 0;

    I2C_read_byte(VEML6070_ADDR_2, 0x00, &uv_temp);
    uv |= (uv_temp << 8);
    I2C_read_byte(VEML6070_ADDR_1, 0x00, &uv_temp);
    uv |= uv_temp;

    return uv;
}


