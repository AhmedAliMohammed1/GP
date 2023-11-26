/*
 * EEPROM.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Ahmed
 */

#include "EEPROM.h"

void EPPROM_write(I2C_REG * I2Cx,uint8_t *data,uint8_t len,uint16_t add){
	uint8_t address=0x2A;
	I2C_Start_BIT(I2Cx);
	GET_flag_status(I2Cx,EV5);
	I2C_WriteADDRESS(I2Cx,address,WRITE);
	GET_flag_status(I2Cx,EV6);
	//////////////////////////
	I2C_WriteByte(I2Cx,((uint8_t)(add>>8)));
	//////////////////////////
	I2C_WriteByte(I2Cx,((uint8_t)add));
	//////////////////////////
	for(int i=0;i<len;i++){
		GET_flag_status(I2Cx,EV8);
		I2C_WriteByte(I2Cx,*data++);

	}
	GET_flag_status(I2Cx,EV8_2);
	I2C_Stop_BIT(I2Cx);
}
void EPPROM_READ(I2C_REG * I2Cx,uint8_t *data,uint8_t len,uint16_t add){
	uint8_t address=0x2A;
	I2C_Start_BIT(I2Cx);
	GET_flag_status(I2Cx,EV5);
	I2C_WriteADDRESS(I2Cx,address,WRITE);
	GET_flag_status(I2Cx,EV6);
	//////////////////////////
	I2C_WriteByte(I2Cx,((uint8_t)(add>>8)));
	//////////////////////////
	I2C_WriteByte(I2Cx,((uint8_t)add));
	//////////////////////////
	I2C_REPATED_Start_BIT(I2Cx);
	GET_flag_status(I2Cx,EV5);
	I2C_WriteADDRESS(I2Cx,address,READ);
	GET_flag_status(I2Cx,EV6);
	I2Cx->CR1.Bit_Name.ACK=1;
/////////////////////////////////////////
	for(int i=0;i<len;i++,*data++)
		I2C_ReciveByte(I2Cx,data);


	/// send NACK
	I2Cx->CR1.Bit_Name.ACK=0;



	I2C_Stop_BIT(I2Cx);
}
