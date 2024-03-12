/*
 * EEPROM.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Ahmed
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_
#include "I2C.h"



void EPPROM_write(I2C_REG * I2Cx,uint8_t *data,uint8_t len,uint16_t add);
void EPPROM_READ(I2C_REG * I2Cx,uint8_t *data,uint8_t len,uint16_t add);


#endif /* INC_EEPROM_H_ */
