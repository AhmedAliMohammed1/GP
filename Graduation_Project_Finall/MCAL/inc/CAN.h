/*
 * CAN.h
 *
 *  Created on: Feb 12, 2024
 *      Author: medoo
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_
/***********includes***********/
#include "STM32F103x6.h"
#include "GPIO_Driver.h"
#include "RCC.h"
/***********defines***********/
#define ON	1
#define OFF	0

/***********Enums***********/
typedef enum {CAN_OK,CAN_ERROR}CAN_retrun;
typedef enum {SLEEP,ITIALIZATION,NORMAL}CAN_state;
typedef enum {CAN_1MB,CAN_500KB,CAN_250KB,CAN_100KB}CAN_SPEED;
typedef enum {CAN_NORMAL,CAN_Silent,CAN_Loop_back,CAN_Silent_Loop_back}CAN_MODE;
typedef enum {CAN_POLLING,CAN_interrupt}CAN_Mechanism;

typedef enum {CAN_MASK,CAN_ID}CAN_Filteration_Mechanism;
typedef enum {CAN_16_bit_scale,CAN_32_bit_scale}CAN_Filteration_SCALE;

/***********Struct***********/
typedef struct{
	uint32_t Receive_counter:8;
	uint32_t Transmit_counter:8;
	uint32_t Error_src:3; /*000: No Error
							001: Stuff Error
							010: Form Error
							011: Acknowledgment Error
							100: Bit recessive Error
							101: Bit dominant Error
							110: CRC Error
							111: Set by software*/
	uint32_t Bus_off_flag:1; /*The bus-off state is entered on
								TEC overflow, greater than 255,*/
	uint32_t Error_passive_flag:1; /*(Receive Error
									Counter or Transmit Error Counter>127).*/
	uint32_t Error_warning:1; /*(Receive Error Counter or Transmit Error Counter≥96)*/



}CAN_ERROR_SRC;

typedef struct{
	uint8_t FB_num; //must be from 0-13
	CAN_Filteration_Mechanism FM;
	CAN_Filteration_SCALE FS;
	uint16_t ID; //Identifier List and used in mask mode as comparator
	uint16_t MASK_ID;//Identifier Mask and used in id mode as second id

}CAN_Filter_x_Bank;
typedef struct{
	uint8_t ABO; /* Automatic bus-off management
           This bit controls the behavior of the CAN hardware on leaving the Bus-Off state*/

	uint8_t NAT; /* No automatic retransmission
	           This bit controls the behavior of the CAN hardware on leaving the Bus-Off state*/
	uint8_t RFL; /*Receive FIFO locked mode locked on overrun mangment ON 1 , OFF0*/
	CAN_SPEED SPEED; // refer to @CAN_SPEED
	CAN_MODE MODE;// refer to @CAN_MODE
	CAN_Mechanism IE;// refer to @CAN_Mechanism
	void(*g_f_callback)(void);
}CAN_config;
typedef struct{
	uint8_t RTR:1;
	uint8_t IDE:1;
	uint16_t STID;
	uint8_t DLC;
	uint8_t FMI; //Filter match index
	uint8_t data[8];



}CAN_frame;


/***********APIs***********/
CAN_retrun MCAL_CAN_init(CAN_config *CANx);
CAN_retrun MCAL_CAN_TX(uint16_t ID,uint8_t DLC,uint8_t *data,uint8_t RTR);
CAN_retrun MCAL_CAN_ADD_Filter(CAN_Filter_x_Bank *FBx);
CAN_retrun MCAL_CAN_RX(CAN_frame *frame);


#endif /* INC_CAN_H_ */
