/*
 * USART_Driver.h
 *
 *  Created on: Aug 8, 2023
 *      Author: Ahmed
 */

#ifndef INC_USART_DRIVER_H_
#define INC_USART_DRIVER_H_
//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "stdint.h"
#include "RCC.h"
#include "GPIO_Driver.h"
//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef enum{
	EGHIT_BITS,NINE_BITS
}Data_Size;
typedef enum{
	Parity_DISABLE,Even_PARTY=2,Odd_PARTY
}Parity_control;
typedef enum{
	POLLING,Interrupt,DMA
}Mechanism_control;

typedef enum{
	//The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5.
	ONE_STOP_BIT,HALF_STOP_BIT,TWO_STOP_BIT,ONE_HALF_STOP_BIT
}STOP_control;
typedef enum{
	Disabled,RTSE,CTSE,BOTH
}Hardware_Flow_control;

typedef enum{
	Asynchronous,Synchronous
}MODE_control;
typedef struct {
	uint32_t Baud_Rate;
	Data_Size Word;
	Parity_control Parity;
	Mechanism_control MEC;
	STOP_control STOP;
	Hardware_Flow_control HW;
	MODE_control MODE;
	void (* P_Call_Back)(void);
}USART_Config_t;


//-----------------------------
//Macros Configuration References
//-----------------------------
#define USART1_IRQ 37
#define USART2_IRQ 38
#define USART3_IRQ 39

#define RTS_EN (1<<8)
#define CTS_EN (1<<9)
#define USARTDIV(F_CLK,BUAD_RATE)		(uint32_t)(F_CLK /(16* BUAD_RATE))
#define USARTDIV_100(F_CLK,BUAD_RATE)	(uint32_t)((25*F_CLK) /(4*BUAD_RATE))
#define Mantissa(F_CLK,BUAD_RATE)		(uint32_t)(USARTDIV(F_CLK,BUAD_RATE))
#define Mantissa_100(F_CLK,BUAD_RATE)  (uint32_t)((USARTDIV(F_CLK,BUAD_RATE)) *100)
#define DIV_Fraction(F_CLK,BUAD_RATE)  (uint32_t)((( (USARTDIV_100(F_CLK,BUAD_RATE)) -  (Mantissa_100(F_CLK,BUAD_RATE)) )*16)/100)
#define BRR(F_CLK,BUAD_RATE)			(( (Mantissa(F_CLK,BUAD_RATE)) <<4) | ((DIV_Fraction(F_CLK,BUAD_RATE))&0xF) )
#define UART_STATUS_CHECK(UART_inistant) (UART_inistant->SR &(1<<5))



/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 *
 */
void MCAL_USART_init(USART_REG *USARTx,USART_Config_t *PIN);
void MCAL_USART_Deinit(USART_REG *USARTx);

void MCAL_USART_SendData(USART_REG *USARTx,uint8_t data);
uint16_t MCAL_USART_ReciveData(USART_REG *USARTx);




#endif /* INC_USART_DRIVER_H_ */
