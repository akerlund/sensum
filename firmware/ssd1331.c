/*
 * ssd1331.c
 *
 *  Created on: Aug 8, 2017
 *      Author: freakuency
 */

#include "ch.h"
#include "hal.h"

#include "ssd1331.h"

#define LINE_ssd1331_RESET PAL_LINE(GPIOB,10U)
#define LINE_ssd1331_DC    PAL_LINE(GPIOB,11U)

#define ssd1331_HEIGHT 64
#define ssd1331_WIDTH  96

	static const SPIConfig spi2cfg2 = {
		NULL,
		/* HW dependent part.*/
		GPIOB,
		12,
		  SPI_CR1_BR_0 | SPI_CR1_CPOL | SPI_CR1_CPHA,/* CR1 register.*/
		0
	};

void SPI_write_byte(int8_t tx_data) {
//	spiSelect(&SPID2);
//	spiSend(&SPID2, 1, tx_data);
//	spiUnselect(&SPID2);

    spiAcquireBus(&SPID2);              /* Acquire ownership of the bus.    */
    //palSetPad(GPIOD, GPIOD_LED5);       /* LED ON.                          */
    spiStart(&SPID2, &spi2cfg2);       /* Setup transfer parameters.       */
    spiSelect(&SPID2);                  /* Slave Select assertion.          */
    //spiExchange(&SPID2, 512,
                //txbuf, rxbuf);          /* Atomic transfer operations.      */

                spiSend(&SPID2, 1, &tx_data);
    spiUnselect(&SPID2);                /* Slave Select de-assertion.       */
    spiReleaseBus(&SPID2);              /* Ownership release.               */
}

void ssd1331_write_command(int8_t tx_data){
	palClearLine(PAL_LINE(GPIOB,11U));
	SPI_write_byte(tx_data);
	palClearLine(PAL_LINE(GPIOB,11U));
	chThdSleepMilliseconds(5);
}

void ssd1331_write_data(int8_t tx_data){
//	palSetLine(LINE_ssd1331_DC);
//	SPI_write_byte(tx_data);
//	palClearLine(LINE_ssd1331_DC);
	palSetLine(PAL_LINE(GPIOB,11U));
	SPI_write_byte(tx_data);
	palClearLine(PAL_LINE(GPIOB,11U));
}

void ssd1331_reset( ){
	palClearLine(LINE_ssd1331_RESET);
	chThdSleepMilliseconds(100);
	palSetLine(LINE_ssd1331_RESET);
}



void ssd1331_initialize( ){

    ssd1331_reset( );

    // Initialization Sequence
    ssd1331_write_command(SSD1331_CMD_DISPLAYOFF);      // 0xAE
    ssd1331_write_command(SSD1331_CMD_SETREMAP);        // 0xA0, horizontal address increment mode.
    ssd1331_write_command(0x72);                        // RGB Color
    //ssd1331_write_command(0x76);                        // BGR Color
    ssd1331_write_command(SSD1331_CMD_STARTLINE);       // 0xA1
    ssd1331_write_command(0x0);
    ssd1331_write_command(SSD1331_CMD_DISPLAYOFFSET);   // 0xA2
    ssd1331_write_command(0x0);
    ssd1331_write_command(SSD1331_CMD_NORMALDISPLAY);   // 0xA4
    ssd1331_write_command(SSD1331_CMD_SETMULTIPLEX);    // 0xA8
    ssd1331_write_command(0x3F);                        // 0x3F 1/64 duty
    ssd1331_write_command(SSD1331_CMD_SETMASTER);       // 0xAD
    ssd1331_write_command(0x8E);
    ssd1331_write_command(SSD1331_CMD_POWERMODE);       // 0xB0
    ssd1331_write_command(0x0B);
    ssd1331_write_command(SSD1331_CMD_PRECHARGE);       // 0xB1
    ssd1331_write_command(0x31);
    ssd1331_write_command(SSD1331_CMD_CLOCKDIV);        // 0xB3
    ssd1331_write_command(0xF0);                        // 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)
    ssd1331_write_command(SSD1331_CMD_PRECHARGEA);      // 0x8A
    ssd1331_write_command(0x64);
    ssd1331_write_command(SSD1331_CMD_PRECHARGEB);      // 0x8B
    ssd1331_write_command(0x78);
    ssd1331_write_command(SSD1331_CMD_PRECHARGEA);      // 0x8C
    ssd1331_write_command(0x64);
    ssd1331_write_command(SSD1331_CMD_PRECHARGELEVEL);  // 0xBB
    ssd1331_write_command(0x3A);
    ssd1331_write_command(SSD1331_CMD_VCOMH);           // 0xBE
    ssd1331_write_command(0x3E);
    ssd1331_write_command(SSD1331_CMD_MASTERCURRENT);   // 0x87
    ssd1331_write_command(0x06);
    ssd1331_write_command(SSD1331_CMD_CONTRASTA);       // 0x81
    ssd1331_write_command(0x91);
    ssd1331_write_command(SSD1331_CMD_CONTRASTB);       // 0x82
    ssd1331_write_command(0x50);
    ssd1331_write_command(SSD1331_CMD_CONTRASTC);       // 0x83
    ssd1331_write_command(0x7D);
//    ssd1331_write_command(SSD1331_CMD_GRAYSCALE);       // 0x83
//    ssd1331_write_command(0x01);
//    ssd1331_write_command(0x03);
//    ssd1331_write_command(0x05);
//    ssd1331_write_command(0x07);
//    ssd1331_write_command(0x0A);
//    ssd1331_write_command(0x0D);
//    ssd1331_write_command(0x10);
//    ssd1331_write_command(0x13);
//    ssd1331_write_command(0x16);
//    ssd1331_write_command(0x19);
//    ssd1331_write_command(0x1C);
//    ssd1331_write_command(0x20);
//    ssd1331_write_command(0x24);
//    ssd1331_write_command(0x28);
//    ssd1331_write_command(0x2C);
//    ssd1331_write_command(0x30);
//    ssd1331_write_command(0x34);
//    ssd1331_write_command(0x38);
//    ssd1331_write_command(0x3C);
//    ssd1331_write_command(0x40);
//    ssd1331_write_command(0x44);
//    ssd1331_write_command(0x48);
//    ssd1331_write_command(0x4C);
//    ssd1331_write_command(0x50);
//    ssd1331_write_command(0x54);
//    ssd1331_write_command(0x58);
//    ssd1331_write_command(0x5C);
//    ssd1331_write_command(0x60);
//    ssd1331_write_command(0x64);
//    ssd1331_write_command(0x68);
//    ssd1331_write_command(0x6C);
//    ssd1331_write_command(0x70);
//    ssd1331_write_command(SSD1331_CMD_NORMALDISPLAY);       // 0xAF
    ssd1331_write_command(SSD1331_CMD_DISPLAYON);       // 0xAF

    //ssd1331_clear_window(0,0,95,63);

    //ssd1331_fill_rectangle(0,0,95,63,COLOR_BLACK,COLOR_BLACK);

    ssd1331_fill_rectangle(0,0,95,63,COLOR_WHITE,COLOR_BLACK);







//    ssd1331_fill_rectangle(0,0,95,63,COLOR_RED,COLOR_RED);
//    ssd1331_clear_window(0,0,95,63);
//

    ssd1331_fill_rectangle(0,0,15,15,COLOR_WHITE,COLOR_RED);
    ssd1331_fill_rectangle(0,32,15,47,COLOR_WHITE,COLOR_BLUE);

    ssd1331_fill_rectangle(16,16,31,31,COLOR_WHITE,COLOR_GREEN);
    ssd1331_fill_rectangle(32,32,47,47,COLOR_WHITE,COLOR_BLUE);
    ssd1331_fill_rectangle(48,48,63,63,COLOR_WHITE,COLOR_RED);


    //ssd1331_fill_rectangle(0,0,95,63,COLOR_BLACK,COLOR_BLACK);
//
//    ssd1331_test( );
    //ssd1331_fill_rectangle(40,40,50,50,COLOR_WHITE,COLOR_GREEN);
    //ssd1331_fill_rectangle(0,0,63,94,COLOR_BLACK,COLOR_BLACK);
    //ssd1331_fill_rectangle(0,0,95,63,COLOR_BLACK,COLOR_BLACK);
}

void ssd1331_set_cursor(uint8_t x, uint8_t y) {

    if ((x >= ssd1331_WIDTH) || (y >= ssd1331_HEIGHT)) {
        return;
    }

    ssd1331_write_command(SSD1331_CMD_SETCOLUMN); // Followed by start address and end address.
    ssd1331_write_command(x);
    ssd1331_write_command(ssd1331_WIDTH-1);

    ssd1331_write_command(SSD1331_CMD_SETROW);
    ssd1331_write_command(y);
    ssd1331_write_command(ssd1331_HEIGHT-1);
}

void ssd1331_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color) {

    // Checking rotation.
    uint16_t temp_xy;
    if (x1 < x0) {
        temp_xy = x1;
        x1 = x0;
        x0 = temp_xy;
    }
    if (y1 < y0) {
        temp_xy = y1;
        y1 = y0;
        y0 = temp_xy;
    }

    // Checking boundary.
    if ((x0 >= ssd1331_WIDTH)  || (x1 >= ssd1331_WIDTH) || (y0 >= ssd1331_HEIGHT) || (y1 >= ssd1331_HEIGHT)) {
        return;
    }

    // Write.
    ssd1331_write_command(SSD1331_CMD_DRAWLINE);
    ssd1331_write_command(x0);
    ssd1331_write_command(y0);
    ssd1331_write_command(x1);
    ssd1331_write_command(y1);
    ssd1331_write_command((uint8_t)((color >> 11) << 1));
    ssd1331_write_command((uint8_t)((color >> 5) & 0x3F));
    ssd1331_write_command((uint8_t)((color << 1) & 0x3F));
}

void ssd1331_fill_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t pencolor, uint16_t fillcolor) {

    if ((x0 >= ssd1331_WIDTH)  || (x1 >= ssd1331_WIDTH) || (y0 >= ssd1331_HEIGHT) || (y1 >= ssd1331_HEIGHT)) {
        return;
    }

    ssd1331_write_command(SSD1331_CMD_FILL);
    ssd1331_write_command(0x01);
    ssd1331_write_command(SSD1331_CMD_DRAWRECT);
    ssd1331_write_command(x0);
    ssd1331_write_command(y0);
    ssd1331_write_command(x1);
    ssd1331_write_command(y1);
    ssd1331_write_command((pencolor >> 11) << 1);
    ssd1331_write_command((pencolor >> 5) & 0x3F);
    ssd1331_write_command((pencolor << 1)& 0x3F);
    ssd1331_write_command((fillcolor >> 11) << 1);
    ssd1331_write_command((fillcolor >> 5) & 0x3F);
    ssd1331_write_command((fillcolor << 1)& 0x3F);
}

//void ssd1331_copy(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
///*	The following example illustrates the copy procedure.
//	1. Enter the “copy mode” by execute the command 23h
//	2. Set the starting column coordinates, Column 1. E.g., 00h.
//	3. Set the starting row coordinates, Row 1. E.g., 00h.
//	4. Set the finishing column coordinates, Column 2. E.g., 05h
//	5. Set the finishing row coordinates, Row 2. E.g., 05h
//	6. Set the new column coordinates, Column 3. E.g., 03h
//	7. Set the new row coordinates, Row 3. E.g., 03h */
//
//}
//
//void ssd1331_dim_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
///*	This command will dim the window area specify by starting point (Row 1, Column 1) and the ending point
//	(Row 2, Column 2). After the execution of this command, the selected window area will become darker as
//	follow.*/
//}
//
void ssd1331_clear_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
/*	This command sets the window area specify by starting point (Row 1, Column 1) and the ending point (Row 2,
	Column 2) to clear the window display. The graphic display data RAM content of the specified window area
	will be set to zero. */
	ssd1331_write_command(SSD1331_CMD_CLEAR_WINDOW);
	ssd1331_write_command(x0);
	ssd1331_write_command(y0);
	ssd1331_write_command(x1);
	ssd1331_write_command(y1);
}


void ssd1331_fill_pixel(uint8_t x, uint8_t y, uint16_t color) {

    if ((x >= ssd1331_WIDTH) || (y >= ssd1331_HEIGHT)) {
        return;
    }

    ssd1331_set_cursor(x, y);
    ssd1331_write_command(color >> 8);
    ssd1331_write_command(color);
}

void ssd1331_test( ) {

    ssd1331_set_cursor(0, 0);
    static uint16_t temp = 0;
    int i,j;
    for( i = 0; i < 96; i++) {
        for( j = 0; j < 64; j++) {
//
            ssd1331_write_data((uint8_t)COLOR_WHITE>>8);
            ssd1331_write_data((uint8_t)COLOR_WHITE);

        	//temp += (i+j);
        	//ssd1331_write_data(temp);
//            if(i > 55) {
//                ssd1331_write_data((uint8_t)COLOR_WHITE>>8);
//                ssd1331_write_data((uint8_t)COLOR_WHITE);
//            } else if(i>47) {
//                ssd1331_write_data((uint8_t)COLOR_BLUE>>8);
//                ssd1331_write_data((uint8_t)COLOR_BLUE);
//            } else if(i>39) {
//                ssd1331_write_data((uint8_t)COLOR_GREEN>>8);
//                ssd1331_write_data((uint8_t)COLOR_GREEN);
//            } else if(i>31) {
//                ssd1331_write_data((uint8_t)COLOR_CYAN>>8);
//                ssd1331_write_data((uint8_t)COLOR_CYAN);
//            } else if(i>23) {
//                ssd1331_write_data((uint8_t)COLOR_RED>>8);
//                ssd1331_write_data((uint8_t)COLOR_RED);
//            } else if(i>15) {
//                ssd1331_write_data((uint8_t)COLOR_MAGENTA>>8);
//                ssd1331_write_data((uint8_t)COLOR_MAGENTA);
//            } else if(i>7) {
//                ssd1331_write_data((uint8_t)COLOR_YELLOW>>8);
//                ssd1331_write_data((uint8_t)COLOR_YELLOW);
//            } else {
//                ssd1331_write_data((uint8_t)COLOR_YELLOW>>8);
//                ssd1331_write_data((uint8_t)COLOR_YELLOW);
//            }
        }
    }
}
