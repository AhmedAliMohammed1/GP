/*
 * SPI_EEPROM.h
 *
 *  Created on: Sep 15, 2023
 *      Author: medoo
 */

#ifndef INC_SPI_EEPROM_H_
#define INC_SPI_EEPROM_H_
#include "SPI.h"
#include "Timer.h"
/* defines*/
#define  READ_Instruction		0b00000011
#define  WRITE_Instruction		0b00000010
#define  WRDI_Instruction		0b00000100
#define  WREN_Instruction		0b00000110
#define  RDSR_Instruction		0b00000101
#define  WRSR_Instruction		0b00000001





/*************APIs**************/


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
void SPI_EEPROM_init(SPI_Reg *SPIx);
void SPI_EEPROM_WRITE(SPI_Reg *SPIx,uint16_t addr,uint8_t *data,uint8_t data_len);

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
void SPI_EEPROM_READ(SPI_Reg *SPIx,uint16_t addr,uint8_t *data,uint8_t data_len);


#endif /* INC_SPI_EEPROM_H_ */
