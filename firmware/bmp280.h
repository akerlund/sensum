/*
 * bmp280.h
 *
 *  Created on: Aug 20, 2017
 *      Author: freakuency
 */

#ifndef SENSORS_BMP280_H_
#define SENSORS_BMP280_H_

#define BMP280_ADDRESS_LOW  0x76 // I2C, SDO
#define BMP280_ADDRESS_HIGH 0x77 // I2C, SDO

#define BMP280_CHIPID 		0xD0 // Which is 0x58.
#define BMP280_RESET  		0xE0 // Write 0xB6 for reseting.
#define BMP280_STATUS 		0xF3 // measuring[0] & im_update[0]
#define BMP280_CTRL_MEAS	0xF4 // Data acquisition options, oversampling.
#define BMP280_CONFIG		0xF5 // Rate, filter and interface options.

#define BMP280_PRESS		0xF7 // raw pressure measurement output data up[19:0] ... to 0xF9
#define BMP280_TEMP			0xFA // raw temperature measurement output data ut[19:0] ... to 0xFC

// Compensation parameters.
#define BMP280_DIG_T1		0x88 // unsigned short
#define BMP280_DIG_T2		0x8A // signed short
#define BMP280_DIG_T3		0x8C // signed short

#define BMP280_DIG_P1		0x8E // unsigned short
#define BMP280_DIG_P2		0x90 // signed short
#define BMP280_DIG_P3		0x92 // signed short
#define BMP280_DIG_P4		0x94 // signed short
#define BMP280_DIG_P5		0x96 // signed short
#define BMP280_DIG_P6		0x98 // signed short
#define BMP280_DIG_P7		0x9A // signed short
#define BMP280_DIG_P8		0x9C // signed short
#define BMP280_DIG_P9		0x9E // signed short

void bmp280_initialize(uint8_t add);

float bmp280_read_temperature(void);
float bmp280_read_pressure(void);

float bmp280_read_altitude(float ref_pressure);
float bmp280_read_altitude_2(float ref_hPa);

#endif /* SENSORS_BMP280_H_ */
