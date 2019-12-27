/*
 * hw_setup.c
 *
 *  Created on: Aug 8, 2017
 *      Author: freakuency
 */

#include "ch.h"
#include "hal.h"
#include "usbcfg.h"

#include "hw_setup.h"

    /*
     *  SPI struct format.
     *  Bits 5:3 SPI_CR1_BR[2:0]: Baud rate control
     *  000: f_PCLK/2   100: f_PCLK/32
     *  001: f_PCLK/4   101: f_PCLK/64
     *  010: f_PCLK/8   110: f_PCLK/128
     *  011: f_PCLK/16  111: f_PCLK/256
     */

/*
 * SPI2
 */
static const SPIConfig spi2cfg = {
	NULL,
	/* HW dependent part.*/
	GPIOB,	// CS
	12,		// CS
	SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_CPOL | SPI_CR1_CPHA,		// CR1
	0		// CR2
};


void hw_initialization( ){

    hw_setup_USB( );
	setup_GPIO( ); 		// SSD1331,
	hw_setup_SPI2( );	// SSD1331,
}

void hw_setup_USB( ){

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
//  start_usb( );
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
