/*
 * data_types.h
 *
 *  Created on: Aug 4, 2017
 *      Author: freakuency
 */

#ifndef DATA_TYPES_H_
#define DATA_TYPES_H_


#define START_BYTE 0xAA				// Used in the serial communication.
#define SERIAL_RX_BUFFER_SIZE 2048  // Size of the RX buffer.

typedef enum {						// USB RX package identifiers.
	COM_PACKAGE_IMU = 0,
	COM_PACKAGE_BAROMETER_BMP280,
	COM_PACKAGE_ISL29125,
	COM_PACKAGE_VEML6070,
    COM_PACKAGE_TCS3472,
    COM_PACKAGE_MPU9250
//	COM_PACKAGE_RGB,
//	COM_PACKAGE_UV,
//	COM_PACKAGE_BAROMETER,
//	COM_PACKAGE_HUMIDITY,
//	COM_PACKAGE_TEMPERATURE,
//	COM_PACKAGE_AMBIENT,
//	COM_PACKAGE_AUDIO,
//	COM_PACKAGE_LOGIC,
//	COM_PACKAGE_CAN
} COM_HEADER;

#endif /* DATA_TYPES_H_ */
