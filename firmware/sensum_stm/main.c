/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"

#include "usbcfg.h"
#include "string.h"
#include "shell.h"
#include "chprintf.h"
#include <stdbool.h>
//#include "math.h"

#include "data_types.h"
#include "i2c_functions.h"
#include "usb_functions.h"
#include "mpu6050.h"
#include "buffer.h"
#include "rx_requests.h"


static const SPIConfig spicfg = {
  NULL,
  GPIOE,                                     /* port of LIS302DL CS.*/
  GPIOE_CS_SPI,                              /* pin of LIS302DL CS.*/
  SPI_CR1_BR_0 | SPI_CR1_CPOL | SPI_CR1_CPHA,/* CR1 register.*/
  0                                          /* CR2 register.*/
};


/*===========================================================================*/
/* Main code.                                                                */
/*===========================================================================*/
#define RAD_TO_DEG 57.2957786

int16_t XaccelRaw, YaccelRaw, ZaccelRaw;
int16_t XgyroRaw, YgyroRaw, ZgyroRaw;

double XaccelAngle, YaccelAngle;
static bool initSensors(void);
/*
 * LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(blinker_thread_wa, 128);
static THD_FUNCTION(blinker_thread, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    systime_t time;

    time = serusbcfg.usbp->state == USB_ACTIVE ? 250 : 500;
    palClearLine(LINE_LED6);
    chThdSleepMilliseconds(time);
    palSetLine(LINE_LED6);
    chThdSleepMilliseconds(time);
    //chprintf((BaseSequentialStream *)&SDU1, "Test\r\n");
  }
}

/*
 * Application entry point.
 */
int main(void) {

	/*
	* System initializations.
	* - HAL initialization, this also initializes the configured device drivers
	*   and performs the board-specific initializations.
	* - Kernel initialization, the main() function becomes a thread and the
	*   RTOS is active.
	*/
	halInit();
	chSysInit();
	palSetLine(LINE_LED3);

	/* Initializes a serial-over-USB CDC driver.*/
	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);

	/*
	* Activates the USB driver and then the USB bus pull-up on D+.
	* Note, a delay is inserted in order to not have to disconnect the cable
	* after a reset.
	*/
	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1500);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);
//	start_usb( );
	i2c_initialization( );
	palSetLine(LINE_LED3);

	if(initSensors( )){
		palSetLine(LINE_LED4);
	} else {

		palSetLine(LINE_LED5);
	}
	/* Creates the blinker thread.*/
	chThdCreateStatic(blinker_thread_wa, sizeof(blinker_thread_wa), NORMALPRIO + 1, blinker_thread, NULL);

	/* LIS302DL Object Initialization.*/
	//lis302dlObjectInit(&LIS302DLD1);

	/* Activates the LIS302DL driver.*/
	//lis302dlStart(&LIS302DLD1, &l3gd20cfg);

	/* Shell manager initialization.*/
	//shellInit();

	COM_HEADER header = COM_PACKAGE_IMU;
	unsigned char tx_buffer[64];
	unsigned int tx_length;
	tx_buffer[0] = START_BYTE;
	tx_buffer[1] = header;
	tx_buffer[2] = 0;

	while (TRUE){
//		MPUgetMotion6(&XaccelRaw, &YaccelRaw, &ZaccelRaw, &XgyroRaw, &YgyroRaw, &ZgyroRaw);


//		chprintf((BaseSequentialStream *)&SDU1, "A: X-axis: %d mg\r\n", XaccelRaw);
//		chprintf((BaseSequentialStream *)&SDU1, "A: Y-axis: %d mg\r\n", YaccelRaw);
//		chprintf((BaseSequentialStream *)&SDU1, "A: Z-axis: %d mg\r\n", ZaccelRaw);
//		chprintf((BaseSequentialStream *)&SDU1, "G: X-axis: %d mg\r\n", XgyroRaw);
//		chprintf((BaseSequentialStream *)&SDU1, "G: Y-axis: %d mg\r\n", YgyroRaw);
//		chprintf((BaseSequentialStream *)&SDU1, "G: Z-axis: %d mg\r\n", ZgyroRaw);

		tx_length = 3;
		get_data_IMU(tx_buffer, &tx_length);
		tx_buffer[2] = (unsigned char)tx_length-3;
		streamWrite(&SDU1, tx_buffer, tx_length);
//
		chThdSleepMilliseconds(20);
	}

	static uint8_t mpu6050_buffer[20];
	static int i2c_error = 0;
	while(TRUE) {
//    if (SDU1.config->usbp->state == USB_ACTIVE) {
//      thread_t *shelltp = chThdCreateFromHeap(NULL, SHELL_WA_SIZE,
//                                              "shell", NORMALPRIO + 1,
//                                              shellThread, (void *)&shell_cfg1);
//      chThdWait(shelltp);               /* Waiting termination.             */
//    }
		palSetLine(LINE_LED4);
		chThdSleepMilliseconds(500);
		i2c_error = i2c_read_MPU6050(mpu6050_buffer);
		if (i2c_error == 0) {
			//palSetLine(LINE_LED5);
			palClearLine(LINE_LED5);
		} else {
			//palClearLine(LINE_LED5);
			palSetLine(LINE_LED5);

			//chprintf(chp, "%c-axis: %d\r\n", axisID[i]);
		}
		palClearLine(LINE_LED4);
		chThdSleepMilliseconds(500);
	}
	//lis302dlStop(&LIS302DLD1);
	return 0;
}

static bool initSensors(void){
	bool sts = 0;

	/* MPU6050, AD0 is connected to VCC */
	MPU6050(MPU6050_ADDRESS_AD0_LOW);

	/* Test connection */
	sts = MPUtestConnection();
	if (!sts) return FALSE;

	MPUreset();
	MPUresetSensors();
	chThdSleepMilliseconds(100);
	MPUinitialize();
	chThdSleepMilliseconds(100);

//	MPUgetMotion6(&XaccelRaw, &YaccelRaw, &ZaccelRaw, &XgyroRaw, &YgyroRaw, &ZgyroRaw);
//
////	XaccelAngle = (atan2(YaccelRaw,ZaccelRaw)+M_PI)*RAD_TO_DEG;
////	YaccelAngle = (atan2(XaccelRaw,ZaccelRaw)+M_PI)*RAD_TO_DEG;
//	//        chprintf(chp, "%c-axis: %d\r\n", axisID[i], rawdata[i]);
//	chprintf((BaseSequentialStream *)&SDU1, "A: X-axis: %d mg\r\n", XaccelRaw);
//	chprintf((BaseSequentialStream *)&SDU1, "A: Y-axis: %d mg\r\n", YaccelRaw);
//	chprintf((BaseSequentialStream *)&SDU1, "A: Z-axis: %d mg\r\n", ZaccelRaw);
//	chprintf((BaseSequentialStream *)&SDU1, "G: X-axis: %d mg\r\n", XgyroRaw);
//	chprintf((BaseSequentialStream *)&SDU1, "G: Y-axis: %d mg\r\n", YgyroRaw);
//	chprintf((BaseSequentialStream *)&SDU1, "G: Z-axis: %d mg\r\n", ZgyroRaw);

	return TRUE;
}
