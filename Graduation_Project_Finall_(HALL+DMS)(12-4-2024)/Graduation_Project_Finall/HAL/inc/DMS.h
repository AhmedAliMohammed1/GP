/*
 * DMS.h
 *
 *  Created on: Mar 6, 2024
 *      Author: medoo
 */

#ifndef INC_DMS_H_
#define INC_DMS_H_

#include "GPIO_Driver.h"
#include "Timer1_8.h"
#define TOUCH1	PIN_1
#define TOUCH2	PIN_12
#define TOUCH3	PIN_11
#define TOUCH4	PIN_8
#define DMS_PORT GPIOA


void DMS_init();
uint8_t DMS_read();
#endif /* INC_DMS_H_ */
