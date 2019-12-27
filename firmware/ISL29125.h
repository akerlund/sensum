/*
 * ISL29125.h
 *
 *  Created on: Sep 23, 2017
 *      Author: freakuency
 */

#ifndef ISL29125_H_
#define ISL29125_H_

#include <stdbool.h>
#include <stdint.h>

// ISL29125 I2C Address
#define ISL29125_ADDR 0x44

// ISL29125 Registers
#define ISL29125_DEVICE_ID 0x00
#define ISL29125_CONFIG_1 0x01
#define ISL29125_CONFIG_2 0x02
#define ISL29125_CONFIG_3 0x03
#define ISL29125_LOW_THRESHOLD_L 0x04
#define ISL29125_LOW_THRESHOLD_H 0x05
#define ISL29125_HIGH_THRESHOLD_L 0x06
#define ISL29125_HIGH_THRESHOLD_H 0x07
#define ISL29125_STATUS_FLAGS 0x08
#define ISL29125_GREEN_L 0x09
#define ISL29125_GREEN_H 0x0A
#define ISL29125_RED_L 0x0B
#define ISL29125_RED_H 0x0C
#define ISL29125_BLUE_L 0x0D
#define ISL29125_BLUE_H 0x0E

// Configuration Settings
#define ISL29125_CFG_DEFAULT 0x00

// CONFIG1
// Pick a mode, determines what color[s] the sensor samples, if any
#define ISL29125_CFG1_MODE_POWERDOWN 0x00
#define ISL29125_CFG1_MODE_G 0x01
#define ISL29125_CFG1_MODE_R 0x02
#define ISL29125_CFG1_MODE_B 0x03
#define ISL29125_CFG1_MODE_STANDBY 0x04
#define ISL29125_CFG1_MODE_RGB 0x05
#define ISL29125_CFG1_MODE_RG 0x06
#define ISL29125_CFG1_MODE_GB 0x07

// Light intensity range
// In a dark environment 375Lux is best, otherwise 10KLux is likely the best option
#define ISL29125_CFG1_375LUX 0x00
#define ISL29125_CFG1_10KLUX 0x08

// Change this to 12 bit if you want less accuracy, but faster sensor reads
// At default 16 bit, each sensor sample for a given color is about ~100ms
#define ISL29125_CFG1_16BIT 0x00
#define ISL29125_CFG1_12BIT 0x10

// Unless you want the interrupt pin to be an input that triggers sensor sampling, leave this on normal
#define ISL29125_CFG1_ADC_SYNC_NORMAL 0x00
#define ISL29125_CFG1_ADC_SYNC_TO_INT 0x20

// CONFIG2
// Selects upper or lower range of IR filtering
#define ISL29125_CFG2_IR_OFFSET_OFF 0x00
#define ISL29125_CFG2_IR_OFFSET_ON 0x80

// Sets amount of IR filtering, can use these presets or any value between 0x00 and 0x3F
// Consult datasheet for detailed IR filtering calibration
#define ISL29125_CFG2_IR_ADJUST_LOW 0x00
#define ISL29125_CFG2_IR_ADJUST_MID 0x20
#define ISL29125_CFG2_IR_ADJUST_HIGH 0x3F

// CONFIG3
// No interrupts, or interrupts based on a selected color
#define ISL29125_CFG3_NO_INT 0x00
#define ISL29125_CFG3_G_INT 0x01
#define ISL29125_CFG3_R_INT 0x02
#define ISL29125_CFG3_B_INT 0x03

// How many times a sensor sample must hit a threshold before triggering an interrupt
// More consecutive samples means more times between interrupts, but less triggers from short transients
#define ISL29125_CFG3_INT_PRST1 0x00
#define ISL29125_CFG3_INT_PRST2 0x04
#define ISL29125_CFG3_INT_PRST4 0x08
#define ISL29125_CFG3_INT_PRST8 0x0C

// If you would rather have interrupts trigger when a sensor sampling is complete, enable this
// If this is disabled, interrupts are based on comparing sensor data to threshold settings
#define ISL29125_CFG3_RGB_CONV_TO_INT_DISABLE 0x00
#define ISL29125_CFG3_RGB_CONV_TO_INT_ENABLE 0x10

// STATUS FLAG MASKS
#define ISL29125_FLAG_INT 0x01
#define ISL29125_FLAG_CONV_DONE 0x02
#define ISL29125_FLAG_BROWNOUT 0x04
#define ISL29125_FLAG_CONV_G 0x10
#define ISL29125_FLAG_CONV_R 0x20
#define ISL29125_FLAG_CONV_B 0x30



bool ISL29125_initialize(void);
bool ISL29125_reset(void);
bool ISL29125_configure(uint8_t config_1, uint8_t config_2, uint8_t config_3);

bool ISL29125_set_upper_threshold(uint8_t *data);
bool ISL29125_set_lower_threshold(uint8_t *data);
bool ISL29125_get_upper_threshold(uint8_t *data);
bool ISL29125_get_lower_threshold(uint8_t *data);

bool ISL29125_get_red(uint8_t *red);
bool ISL29125_get_green(uint8_t *green);
bool ISL29125_get_blue(uint8_t *blue);
bool ISL29125_get_GRB(uint8_t *grb);

bool ISL29125_get_status(uint8_t *status);

#endif /* ISL29125_H_ */
