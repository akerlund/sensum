/*
 * hw_setup.c
 *
 *  Created on: Aug 8, 2017
 *      Author: freakuency
 */

#include "ch.h"
#include "hal.h"

#include "hw_setup.h"

	static const SPIConfig spi2cfg = {
		NULL,
		/* HW dependent part.*/
		GPIOB,
		12,
		0,
		0
	};
void hw_initialization( ){
	setup_GPIO( );
	hw_setup_SPI2( );
}

void hw_setup_SPI2( ){
	/*
	* Initializes the SPI driver 2. The SPI2 signals are routed as follow:
	* PB12 - NSS.
	* PB13 - SCK.
	* PB14 - MISO.
	* PB15 - MOSI.
	*/

	spiStart(&SPID2, &spi2cfg);
	palSetPad(GPIOB, 12);
	palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST); // NSS.
	palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);    // SCK.
	palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);    // MISO.
	palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);    // MOSI.
	palSetPad(GPIOB, 12);
}

void setup_GPIO( ){
	// ssd1331 reset and DC.
	palSetPadMode(GPIOB, 10, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOB, 11, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
}
