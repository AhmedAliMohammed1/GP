/*
 * LCD.h
 *
 *  Created on: Jul 25, 2023
 *      Author: Ahmed
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

/*
 * LCD.c
 *
 *  Created on: Jul 25, 2023
 *      Author: Ahmed
 */
#include "STM32F103x6.h"
#include "GPIO_Driver.h"
#include "GP_Timers.h"
#define DATA_PORT	GPIOA
#define CTRL_PORT GPIOA
#define RS	PIN_0
#define EN	PIN_1
#define D0 PIN_9
#define D1 PIN_8
#define D2 PIN_7
#define D3 PIN_6
#define D4 PIN_2
#define D5 PIN_3
#define D6 PIN_4
#define D7 PIN_5
//#define EIGHT_BIT_MODE
#define GET_BIT(REG,num) ((REG>>num) &1)
#define FOUR_BIT_MODE
/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80
#define LCD_SET_CURSOR_LOCATION_2nd          0xC0

void LCD_sendCommand( usint8_t command);
void LCD_sendCharcter(usint8_t data);
void LCD_init();
void LCD_sendString(char *data);
void LCD_moveCURSER(unsigned char row,unsigned char col);
void LCD_clearScreen();
void LCD_intgerToString(unsigned int num);
#endif /* LCD_H_ */




