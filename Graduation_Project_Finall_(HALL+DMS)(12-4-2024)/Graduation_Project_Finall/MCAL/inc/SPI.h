/*
 * SPI.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Ahmed
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_
//-----------------------------
//Includes
//-----------------------------
#include "STM32F103x6.h"
#include "GPIO_Driver.h"
#include <stdint.h>
//-----------------------------
//User type definitions (structures,enum,unions)
//-----------------------------
typedef enum { //Bit 11 DFF: Data frame format
	SPI_8_BITS,SPI_16_BITS
}DATA_size;
typedef enum { // Bit 9 SSM: Software slave management
	SW,HW_OUT,HW_IN
}NSS_SELECT_MANGMENT;
typedef enum { //Bit 7 LSBFIRST: Frame format
	MSB,LSB
}Frame_format;
typedef enum { //Bit 6 SPE: SPI enable
	disabled,enabled
}SPI_enable;
typedef enum { //Bits 5:3 BR[2:0]: Baud rate control
	F_CPU_2,F_CPU_4,F_CPU_8,F_CPU_16,F_CPU_32,F_CPU_64,F_CPU_128,F_CPU_256
}Baud_rate_control;
typedef enum { //Bit 2 MSTR: Master selection
	Slave,Master
}Master_selection;
typedef enum { //Bit1 CPOL: Clock polarity
	idle_0,idle_1
}Clock_polarity;
typedef enum { //Bit 0 CPHA: Clock phase
	 first_clock, //0: The first clock transition is the first data capture edge
	 second_clock //1: The second clock transition is the first data capture edge
}Clock_phase;
typedef enum {
	interrupt_DS,interrupt_EN
}interrupt_enable;
#define SPI1_IRQ 35
#define SPI2_IRQ 36

#define USART3_IRQ 39
typedef struct{
	uint8_t TXE_FLAG:1;
	uint8_t RXNE_FLAG:1;

}Flag_source;

typedef struct{
	SPI_enable SP_EN;
	Master_selection M_S;
	DATA_size DATA;
	Frame_format FRAME;
	NSS_SELECT_MANGMENT NSS_SELC;
	Baud_rate_control BAUD_R;
	Clock_polarity POL;
	Clock_phase PHA;
	interrupt_enable IN_EN;
	void (* P_CallBack)(Flag_source fLAG);
}SPI_Config_t;

/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */
void MCAL_SPI_init(SPI_Reg * SPIx,SPI_Config_t *Config);
void MCAL_SPI_Deinit(SPI_Reg *SPIx);
uint8_t MCAL_SPI_SendData(SPI_Reg *SPIx,uint8_t data);
void MCAL_SPI_ReciveData(SPI_Reg *SPIx,uint8_t *data);
#endif /* INC_SPI_H_ */
