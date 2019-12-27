/*
 * i2c_functions.h
 *
 *  Created on: Aug 2, 2017
 *      Author: freakuency
 */

#include "ch.h"
#include "hal.h"

#ifndef I2C_FUNCTIONS_
#define I2C_FUNCTIONS_

#define I2C_BUFFER_LENGTH       64

void i2c_initialization(void);

bool I2C_write_byte( uint8_t devAddr, uint8_t regAddr, uint8_t data);
bool I2C_write_bytes(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t length);
bool I2C_read_byte(  uint8_t devAddr, uint8_t regAddr, uint8_t *data);
bool I2C_read_bytes( uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t length);

#endif /* I2C_FUNCTIONS_ */
