/*
 * rx_requests.c
 *
 *  Created on: Aug 5, 2017
 *      Author: freakuency
 */

#include "rx_requests.h"
#include "data_types.h"
#include "mpu6050.h"
#include "buffer.h"

//void get_chibi_status( ){
//	//if (strcmp(argv[0], "mem") == 0) {
//			size_t n, size;
//			n = chHeapStatus(NULL, &size);
//			commands_printf("core free memory : %u bytes", chCoreGetStatusX());
//			commands_printf("heap fragments   : %u", n);
//			commands_printf("heap free total  : %u bytes\n", size);
//	//	} else if (strcmp(argv[0], "threads") == 0) {
//			thread_t *tp;
//			static const char *states[] = {CH_STATE_NAMES};
//			commands_printf("    addr    stack prio refs     state           name time    ");
//			commands_printf("-------------------------------------------------------------");
//			tp = chRegFirstThread();
//			do {
//				commands_printf("%.8lx %.8lx %4lu %4lu %9s %14s %lu",
//						(uint32_t)tp, (uint32_t)tp->p_ctx.r13,
//						(uint32_t)tp->p_prio, (uint32_t)(tp->p_refs - 1),
//						states[tp->p_state], tp->p_name, (uint32_t)tp->p_time);
//				tp = chRegNextThread(tp);
//			} while (tp != NULL);
//}

void get_data_IMU(unsigned char *tx_data, unsigned int *index) {

	int16_t XaccelRaw, YaccelRaw, ZaccelRaw, XgyroRaw, YgyroRaw, ZgyroRaw;
	MPUgetMotion6(&XaccelRaw, &YaccelRaw, &ZaccelRaw, &XgyroRaw, &YgyroRaw, &ZgyroRaw);

	buffer_append_int16(tx_data, XaccelRaw, index);
	buffer_append_int16(tx_data, YaccelRaw, index);
	buffer_append_int16(tx_data, ZaccelRaw, index);

	buffer_append_int16(tx_data, XgyroRaw, index);
	buffer_append_int16(tx_data, YgyroRaw, index);
	buffer_append_int16(tx_data, ZgyroRaw, index);
}
