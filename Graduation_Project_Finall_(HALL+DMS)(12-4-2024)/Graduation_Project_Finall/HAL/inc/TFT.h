/*
 * TFT.h
 *
 *  Created on: Feb 3, 2024
 *      Author: medoo
 */

#ifndef INC_TFT_H_
#define INC_TFT_H_

/********includes*******/
#include "GPIO_Driver.h"
#include "Timer1_8.h"
#include "SPI.h"
//#include "TFT_signs.h"

/********Defines*******/
#define TFT_SPI_inistant SPI1
#define TFT_PORT GPIOA
#define TFT_RESET_PIN PIN_2
#define TFT_A0_PIN PIN_3
#define TFT_CS_PIN PIN_4
#define TFT_Sleep_Out_MODE 0x11
#define TFT_Display_On_MODE 0x29
#define TFT_Pixel_Format_MODE 0x3A
#define TFT_SET_Column_MODE 0x2A
#define TFT_SET_Row_MODE 0x2B
#define TFT_Memory_Write_MODE 0x2C
#define TFT_Software_Reset_MODE 0x1
#define TFT_Memory_Access_Control 0x36



#define TFT_width 320
#define TFT_height 480

#define NO_PARKING_SIGN_FLAG	0x7
#define NO_WAITING_SIGN_FLAG	0x8
#define _100_KM_SIGN_FLAG		0x9
#define _120_KM_SIGN_FLAG		0x10
#define _20_KM_SIGN_FLAG		0x11
#define _30_KM_SIGN_FLAG		0x12
#define _40_KM_SIGN_FLAG		0x13
#define _50_KM_SIGN_FLAG		0x14
#define _70_KM_SIGN_FLAG		0x16
#define _80_KM_SIGN_FLAG		0x17
#define _90_KM_SIGN_FLAG		0x18
#define STOP_SIGN_FLAG			0x19

/********enums*******/
typedef enum{
	RGB_4_4_4=0x33,RGB_5_6_5=0x55,RGB_6_6_6=0x66
}RGB_fromat;
typedef enum{default_option,X_ROTATE,Y_ROTATE}IMAGE_option;

/********Fun*******/
void TFT_init(RGB_fromat RGB);
void TFT_send_command(uint8_t command);
void TFT_send_data(uint8_t data);
uint8_t TFT_send_TSR_image(uint8_t image_flag);
void TFT_SEND_Image(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2,uint16_t* image);
void TFT_SET_BACKGROUND(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2,uint8_t r,uint8_t g,uint8_t b);
void TFT_MAKE_option(IMAGE_option OPTION);
void TFT_KM_H_ICON_Print();
void TFT_SPEED_ICON_Print();
void TFT_send_ACC_image(uint8_t NUMBER);
void TFT_cruise_control_ICON_Print(uint8_t on_off);
void TFT_HOD_ICON_Print(uint8_t on_off);
void TFT_Welcome_ICON_Print();
/********Defines*******/

#endif /* INC_TFT_H_ */
