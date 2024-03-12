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

#define TFT_width 320
#define TFT_height 480

#define NO_PARKING_SIGN_FLAG	7
#define NO_WAITING_SIGN_FLAG	8
#define _100_KM_SIGN_FLAG		9
#define _120_KM_SIGN_FLAG		10
#define _20_KM_SIGN_FLAG		11
#define _30_KM_SIGN_FLAG		12
#define _40_KM_SIGN_FLAG		13
#define _50_KM_SIGN_FLAG		14
#define _70_KM_SIGN_FLAG		16
#define _80_KM_SIGN_FLAG		17
#define _90_KM_SIGN_FLAG		18
#define STOP_SIGN_FLAG			19

/********enums*******/
typedef enum{
	RGB_4_4_4=0x33,RGB_5_6_5=0x55,RGB_6_6_6=0x66
}RGB_fromat;


/********Fun*******/
void TFT_init(RGB_fromat RGB);
void TFT_send_command(uint8_t command);
void TFT_send_data(uint8_t data);
void TFT_send_image(uint8_t image_flag);
void send_frame();
void send_frame1();
void TFT_saveData(I2C_REG * I2Cx,uint16_t *data,uint32_t len,uint16_t add);
void TFT_ReadData(I2C_REG * I2Cx,uint16_t *data,uint32_t len,uint16_t add);
void TFT_send_image_v2(uint16_t *image);
/********Defines*******/

#endif /* INC_TFT_H_ */
