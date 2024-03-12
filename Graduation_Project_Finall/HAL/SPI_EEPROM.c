/*
 * SPI_EEPROM.c
 *
 *  Created on: Sep 15, 2023
 *      Author: medoo
 */


#include "SPI_EEPROM.h"
void Start_TX_RX(Flag_source flag){
	if(flag.RXNE_FLAG){

	}
}
 SPI_Config_t SPI_config_v ={enabled,Master,SPI_8_BITS,MSB,SW,F_CPU_8,idle_0,first_clock,interrupt_DS,Start_TX_RX};


 uint8_t EEPROM_readStatus(void) {
 	uint8_t	 data=0;
 	MCAL_write_PIN(GPIOA, PIN_4, 0); //PA4
 	MCAL_SPI_SendData(SPI1, RDSR_Instruction);
 	MCAL_SPI_ReciveData(SPI1,&data);

 	MCAL_write_PIN(GPIOA, PIN_4, 1); //PA4
 return (data );


 }

void SPI_EEPROM_init(SPI_Reg *SPIx){
	MCAL_SPI_init(SPI1,&SPI_config_v);
	dms(10);

	MCAL_write_PIN(GPIOA, PIN_4, 0); //PA4
	MCAL_SPI_SendData(SPI1, WRDI_Instruction);
	MCAL_write_PIN(GPIOA, PIN_4, 1);
	while((EEPROM_readStatus()& (1<<0)));

}



/*  Write Sequence
 * 1. CS low
 * 2. Send WREN instruction
 * 3. CS high
 * 4. CS low
 * 5. Send WRITE instruction
 * 6. Send 16 Bit-address with the first MSB of the address being a “don’t care”
 * 7. Up to 64 bytes of data can be
		sent to the device before a write cycle is necessary.
		The only restriction is that all of the bytes must reside
		in the same page.

 *
 *   */
void SPI_EEPROM_WRITE(SPI_Reg *SPIx,uint16_t addr,uint8_t *data,uint8_t data_len){

	MCAL_write_PIN(GPIOA, PIN_4, 0); //PA4
	MCAL_SPI_SendData(SPI1, WREN_Instruction);
	MCAL_write_PIN(GPIOA, PIN_4, 1);
//	dms(30);
	/****************/
	MCAL_write_PIN(GPIOA, PIN_4, 0);
	MCAL_SPI_SendData(SPI1, WRITE_Instruction);
	MCAL_SPI_SendData(SPI1, (uint8_t)(addr>>8));
	MCAL_SPI_SendData(SPI1,(uint8_t) (addr &0xFF));
	for(int i=0;(i<data_len) &&(data_len <=64);i++){
		MCAL_SPI_SendData(SPI1,((uint8_t)(*data++)));

	}

	MCAL_write_PIN(GPIOA, PIN_4, 1);
	while((EEPROM_readStatus()& (1<<0)));

//	MCAL_write_PIN(GPIOA, PIN_4, 0);
////	MCAL_SPI_SendData(SPI1, 0x00);
//	MCAL_write_PIN(GPIOA, PIN_4, 1);
////


}




/* Read  Sequence
 * 	1. CS low
 * 	2. Send READ instruction
 * 	3. Send Send 16 Bit-address with the first MSB of the address being a “don’t care”
 * 	4. the data stored in the memory at the selected address is shifted out on the
		SO pin.
 *	5. The internal Address Pointer is
		automatically incremented to the next higher address
		after each byte of data is shifted out
 *	6. When the highest
		address is reached (7FFFh), the address counter rolls
		over to address 0000h
 *	7. The read operation is terminated by raising the CS pin
 *
 * */


void SPI_EEPROM_READ(SPI_Reg *SPIx,uint16_t addr,uint8_t *data,uint8_t data_len){

	/****************/

	MCAL_write_PIN(GPIOA, PIN_4, 0); //PA4
	MCAL_SPI_SendData(SPI1, READ_Instruction);
	MCAL_SPI_SendData(SPI1, (uint8_t)(addr<<8));
	MCAL_SPI_SendData(SPI1,(uint8_t) (addr &0xFF));
	for(uint8_t i=0;i<data_len;i++){
		MCAL_SPI_ReciveData(SPI1,data++);
	}
	MCAL_write_PIN(GPIOA, PIN_4, 1); //PA4


}










