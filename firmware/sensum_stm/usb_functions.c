/*
 * usb_functions.c
 *
 *  Created on: Aug 1, 2017
 *      Author: freakuency
 */

#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "usbcfg.h"

#include "usb_functions.h"
#include "data_types.h"
#include "rx_requests.h"

// Variables for receiving data and threads.
#define START_BYTE 0xAA				// Used in the serial communication.
#define SERIAL_RX_BUFFER_SIZE 2048  // Size of the RX buffer.
#define SERIAL_TX_BUFFER_SIZE 2048  // Size of the TX buffer.
typedef struct {					// FSM variables for USB RX.
	volatile unsigned char rx_state;
	volatile unsigned int payload_length;
	volatile unsigned int rx_data_ptr;
	unsigned char rx_buffer[SERIAL_RX_BUFFER_SIZE];
} RX_FSM_STRUCT;
static RX_FSM_STRUCT RX_FSM_STATE;
static uint8_t serial_rx_buffer[SERIAL_RX_BUFFER_SIZE];
static int serial_rx_read_pos = 0;
static int serial_rx_write_pos = 0;

// Thread variables.
static THD_WORKING_AREA(serial_read_thread_wa, 512);
static THD_WORKING_AREA(serial_process_thread_wa, 4096);
static mutex_t send_mutex;
static thread_t *process_tp;

// Variables for TX.
unsigned char tx_buffer[SERIAL_TX_BUFFER_SIZE];
unsigned int tx_length;

// Private functions.
static void usb_serial_initialization(void);
static void serial_RX_FSM(uint8_t rx_byte);
static void process_packet(unsigned char *data, unsigned int len);




/**
*   @brief  This thread read RX bytes in a small
*   		circular buffer which is then copied over
*   		to a larger buffer and signals out that it
*   		has data.
*
*   @return void
*/
static THD_FUNCTION(serial_read_thread, arg){
	(void)arg;

	chRegSetThreadName("USB Reader");

	uint8_t buffer[128];
	int i;
	int len;
	int had_data = 0;

	for(;;) {

		len = streamRead(&SDU1, (uint8_t*) buffer, 1);

		for (i = 0;i < len;i++) {
			serial_rx_buffer[serial_rx_write_pos++] = buffer[i];

			if (serial_rx_write_pos == SERIAL_RX_BUFFER_SIZE) {
				serial_rx_write_pos = 0;
			}

			had_data = 1;
		}

		if (had_data) {
			chEvtSignal(process_tp, (eventmask_t) 1);
			had_data = 0;
		}
	}
}

/**
*   @brief  This thread reads the RX bytes received in
*   		the other thread and calls the RX FSM
*   		to handle the interpretation of them.
*
*   @return void
*/
static THD_FUNCTION(serial_process_thread, arg){
	(void)arg;

	chRegSetThreadName("USB Appender");

	process_tp = chThdGetSelfX();

	for(;;) {
		chEvtWaitAny((eventmask_t) 1);

		while (serial_rx_read_pos != serial_rx_write_pos) {

			serial_RX_FSM(serial_rx_buffer[serial_rx_read_pos++]);

			if (serial_rx_read_pos == SERIAL_RX_BUFFER_SIZE) {
				serial_rx_read_pos = 0;
			}
		}
	}
}
/**
*   @brief  Starts the USB by initialize ChibiOS and start the
*   		corresponding USB threads.
*
*   @return void
*/
void start_usb( ){

	usb_serial_initialization();
	//chMtxObjectInit(&send_mutex);

	// Threads for receiving data.
	//chThdCreateStatic(serial_read_thread_wa, sizeof(serial_read_thread_wa), NORMALPRIO, serial_read_thread, NULL);
	//chThdCreateStatic(serial_process_thread_wa, sizeof(serial_process_thread_wa), NORMALPRIO, serial_process_thread, NULL);
}

/**
*   @brief  Initializes the USB for ChibiOS.
*
*   @return void
*/
static void usb_serial_initialization( ){
	/*
	* Initializes a serial-over-USB CDC driver.
	*/
	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);

	/*
	* Activates the USB driver and then the USB bus pull-up on D+.
	* Note, a delay is inserted in order to not have to disconnect the cable
	* after a reset.
	*/
	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1000);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);
}



/**
*   @brief  A FSM which builds together packages from the
*   		the RX data. The packages depend on their header
*   		which contains a start-word, package length and
*   		data identifier, i.e., about what the data is.
*   		The identifiers are defined in data_types.h.
*
*   @return void
*/
static void serial_RX_FSM(uint8_t rx_byte){

	switch (RX_FSM_STATE.rx_state) {
	case 0:	// Header
		if (rx_byte == START_BYTE){
			RX_FSM_STATE.rx_state++;
			RX_FSM_STATE.payload_length = 0;
			RX_FSM_STATE.rx_data_ptr = 0;
		}
		break;

	case 1: // Length of RX data
		RX_FSM_STATE.payload_length = (unsigned int)rx_byte;
		RX_FSM_STATE.rx_state++;
		break;

	case 2: // Filling the buffer
		RX_FSM_STATE.rx_buffer[RX_FSM_STATE.rx_data_ptr++] = rx_byte;
		if (RX_FSM_STATE.rx_data_ptr == RX_FSM_STATE.payload_length) {
			RX_FSM_STATE.rx_state++;
		}
		break;

	case 3: // Buffer is full
		process_packet(RX_FSM_STATE.rx_buffer, RX_FSM_STATE.payload_length);
		RX_FSM_STATE.rx_state = 0;
		break;

//	case 4:
//		break;
//
//	case 5:
//		break;
//
//	case 6:
//		break;

	default:
		RX_FSM_STATE.rx_state = 0;
		break;
	}
}

/**
*   @brief  A function which takes actions on the received
*   		data packages.
*
*   		Just handling requests to send atm.
*
*   @return void
*/
static void process_packet(unsigned char *data, unsigned int len){

	COM_HEADER header = data[0];
	tx_buffer[0] = START_BYTE;
	tx_buffer[1] = data[0];
	tx_length = 2;

	switch(header){
	case COM_PACKAGE_IMU:
		get_data_IMU(tx_buffer, &tx_length);
		break;
	case COM_PACKAGE_RGB:
		break;
	case COM_PACKAGE_UV:
		break;
	case COM_PACKAGE_BAROMETER:
		break;
	case COM_PACKAGE_HUMIDITY:
		break;
	case COM_PACKAGE_TEMPERATURE:
		break;
	case COM_PACKAGE_AMBIENT:
		break;
	case COM_PACKAGE_AUDIO:
		break;
	case COM_PACKAGE_LOGIC:
		break;
	case COM_PACKAGE_CAN:
		break;
	default:
		break;
	}
	//crc_32(tx_buffer, tx_length);
	send_packet(tx_buffer, tx_length);
}


void send_packet(unsigned char *buffer, unsigned int len) {
	chMtxLock(&send_mutex);
	streamWrite(&SDU1, buffer, len);
	chMtxUnlock(&send_mutex);
}




