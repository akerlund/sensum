/*
 * rx_requests.h
 *
 *  Created on: Aug 5, 2017
 *      Author: freakuency
 */

#ifndef RX_REQUESTS_H_
#define RX_REQUESTS_H_

void get_chibi_status(void);
void get_data_IMU(unsigned char *tx_data, unsigned int *index);

#endif /* RX_REQUESTS_H_ */
