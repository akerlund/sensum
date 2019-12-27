/*
 * ssd1331.h
 *
 *  Created on: Aug 8, 2017
 *      Author: freakuency
 */

#ifndef SSD1331_H_
#define SSD1331_H_

// SSD1331 Commands.

#define SSD1331_CMD_PHASEPERIOD      0x12
#define SSD1331_CMD_DRAWLINE         0x21
#define SSD1331_CMD_DRAWRECT         0x22
#define SSD1331_CMD_COPY             0x23
#define SSD1331_CMD_DIM_WINDOW       0x24
#define SSD1331_CMD_CLEAR_WINDOW     0x25
#define SSD1331_CMD_FILL             0x26
#define SSD1331_CMD_SETCOLUMN        0x15
#define SSD1331_CMD_SETROW           0x75
#define SSD1331_CMD_CONTRASTA        0x81
#define SSD1331_CMD_CONTRASTB        0x82
#define SSD1331_CMD_CONTRASTC        0x83
#define SSD1331_CMD_MASTERCURRENT    0x87
#define SSD1331_CMD_SETREMAP         0xA0
#define SSD1331_CMD_STARTLINE        0xA1
#define SSD1331_CMD_DISPLAYOFFSET    0xA2
#define SSD1331_CMD_NORMALDISPLAY    0xA4
#define SSD1331_CMD_DISPLAYALLON     0xA5
#define SSD1331_CMD_DISPLAYALLOFF    0xA6
#define SSD1331_CMD_INVERTDISPLAY    0xA7
#define SSD1331_CMD_SETMULTIPLEX     0xA8
#define SSD1331_CMD_SETMASTER        0xAD
#define SSD1331_CMD_DISPLAYOFF       0xAE
#define SSD1331_CMD_DISPLAYON        0xAF
#define SSD1331_CMD_POWERMODE        0xB0
#define SSD1331_CMD_PRECHARGE        0xB1
#define SSD1331_CMD_CLOCKDIV         0xB3
#define SSD1331_CMD_GRAYSCALE        0xB8
#define SSD1331_CMD_PRECHARGEA       0x8A
#define SSD1331_CMD_PRECHARGEB       0x8B
#define SSD1331_CMD_PRECHARGEC       0x8C
#define SSD1331_CMD_PRECHARGELEVEL   0xBB
#define SSD1331_CMD_VCOMH            0xBE



// Basic Color definitions.
#define	COLOR_BLACK                         (uint16_t)(0x0000)
#define	COLOR_BLUE                          (uint16_t)(0x001F)
#define	COLOR_RED                           (uint16_t)(0xF800)
#define	COLOR_GREEN                         (uint16_t)(0x07E0)
#define COLOR_CYAN                          (uint16_t)(0x07FF)
#define COLOR_MAGENTA                       (uint16_t)(0xF81F)
#define COLOR_YELLOW                        (uint16_t)(0xFFE0)
#define COLOR_WHITE                         (uint16_t)(0xFFFF)

// Grayscale Values.
#define COLOR_GRAY_15                       (uint16_t)(0x0861)    //  15  15  15
#define COLOR_GRAY_30                       (uint16_t)(0x18E3)    //  30  30  30
#define COLOR_GRAY_50                       (uint16_t)(0x3186)    //  50  50  50
#define COLOR_GRAY_80                       (uint16_t)(0x528A)    //  80  80  80
#define COLOR_GRAY_128                      (uint16_t)(0x8410)    // 128 128 128
#define COLOR_GRAY_200                      (uint16_t)(0xCE59)    // 200 200 200
#define COLOR_GRAY_225                      (uint16_t)(0xE71C)    // 225 225 225

void SPI_write_byte(int8_t tx_data);
void ssd1331_write_command(int8_t tx_data);
void ssd1331_write_data(int8_t tx_data);

void ssd1331_initialize(void);
void ssd1331_reset(void);

void ssd1331_set_cursor(uint8_t x, uint8_t y);
void ssd1331_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color);
void ssd1331_fill_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t pencolor, uint16_t fillcolor);
void ssd1331_copy(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void ssd1331_dim_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void ssd1331_clear_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

void ssd1331_test(void);

#endif /* SSD1331_H_ */
