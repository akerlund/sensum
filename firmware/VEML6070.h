/*
 * VEML6070.h
 *
 *  Created on: Sep 23, 2017
 *      Author: freakuency
 */

#ifndef VEML6070_H_
#define VEML6070_H_

#include <stdbool.h>
#include <stdint.h>

#define VEML6070_ADDR_1 0x38
#define VEML6070_ADDR_2 0x39

bool VEML6070_initialize(uint8_t integration_time);
uint16_t VEML6070_get_UV(void);

#endif /* VEML6070_H_ */
