/*
 * TCS3472.c
 *
 *  Created on: Sep 24, 2017
 *      Author: freakuency
 */

#include "ch.h"
#include "hal.h"

#include "TCS3472.h"
#include "i2c_functions.h"


bool TCS3472_initialize( ){

    tcs34725IntegrationTime_t it = TCS34725_INTEGRATIONTIME_50MS;
    tcs34725Gain_t g = TCS34725_GAIN_1X;

    TCS3472_set_integration_time(it);
    TCS3472_set_gain(g);
    TCS3472_enable( );

    return true;
}

void TCS3472_set_integration_time(tcs34725IntegrationTime_t it){

    I2C_write_byte(TCS34725_ADDRESS, TCS34725_ATIME, it);
}

void TCS3472_set_gain(tcs34725Gain_t g){

    I2C_write_byte(TCS34725_ADDRESS, TCS34725_CONTROL, g);
}

void TCS3472_enable( ){

    I2C_write_byte(TCS34725_ADDRESS, TCS34725_ENABLE, TCS34725_ENABLE_PON);
    chThdSleepMilliseconds(5); // 2.4ms minimum.
    I2C_write_byte(TCS34725_ADDRESS, TCS34725_ENABLE, TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN);
}


void TCS3472_disable( ){

    I2C_write_byte(TCS34725_ADDRESS, TCS34725_ENABLE, 0x00);
}

void get_CRGB(uint8_t *crgb){

    I2C_read_bytes(TCS34725_ADDRESS, TCS34725_CDATAL, crgb, 8);
}

uint16_t calculate_color_temperature(uint16_t r, uint16_t g, uint16_t b){

    float X, Y, Z;      /* RGB to XYZ correlation      */
    float xc, yc;       /* Chromaticity co-ordinates   */
    float n;            /* McCamy's formula            */
    float cct;

    /* 1. Map RGB values to their XYZ counterparts.    */
    /* Based on 6500K fluorescent, 3000K fluorescent   */
    /* and 60W incandescent values for a wide range.   */
    /* Note: Y = Illuminance or lux                    */
    X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
    Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
    Z = (-0.68202F * r) + (0.77073F * g) + ( 0.56332F * b);

    /* 2. Calculate the chromaticity co-ordinates      */
    xc = (X) / (X + Y + Z);
    yc = (Y) / (X + Y + Z);

    /* 3. Use McCamy's formula to determine the CCT    */
    n = (xc - 0.3320F) / (0.1858F - yc);

    /* Calculate the final CCT */
    //cct = (449.0F * powf(n, 3)) + (3525.0F * powf(n, 2)) + (6823.3F * n) + 5520.33F;
    cct = (449.0F * n*n*n) + (3525.0F * n*n) + (6823.3F * n) + 5520.33F;
    /* Return the results in degrees Kelvin */
    return (uint16_t)cct;
}

uint16_t calculate_lux(uint16_t r, uint16_t g, uint16_t b){

  float illuminance;

  /* This only uses RGB ... how can we integrate clear or calculate lux */
  /* based exclusively on clear since this might be more reliable?      */
  illuminance = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);

  return (uint16_t)illuminance;
}

void set_interrupt(bool b) {

    uint8_t temp = 0;
    I2C_read_byte(TCS34725_ADDRESS, TCS34725_ENABLE, &temp);

    if(b){
        temp |= TCS34725_ENABLE_AIEN;
    } else {
        temp &= ~TCS34725_ENABLE_AIEN;
    }

    I2C_write_byte(TCS34725_ADDRESS, TCS34725_ENABLE, temp);
}

void clear_interrupt( ){

    I2C_write_byte(TCS34725_ADDRESS, TCS34725_ENABLE, TCS34725_COMMAND_BIT | 0x66);
}


void set_interrupt_limits(uint16_t low, uint16_t high) {

    I2C_write_byte(TCS34725_ADDRESS, TCS34725_AILTL, low & 0xFF);
    I2C_write_byte(TCS34725_ADDRESS, TCS34725_AILTH, low >> 8);
    I2C_write_byte(TCS34725_ADDRESS, TCS34725_AIHTL, high & 0xFF);
    I2C_write_byte(TCS34725_ADDRESS, TCS34725_AIHTH, high >> 8);
}

