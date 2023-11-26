/*
 * RCC.h
 *
 *  Created on: Aug 8, 2023
 *      Author: Ahmed
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_
#include "stdint.h"
#include "STM32F103x6.h"
#define HSI_CLOCK 8000000UL
#define HSE_CLOCK 16000000UL
#define PLL_CLOCK 16000000UL


uint32_t MCAL_GET_SYS_CLCK();
uint32_t MCAL_GET_H_CLCK();
uint32_t MCAL_GET_PCLCK1();
uint32_t MCAL_GET_PCLCK2();


#endif /* INC_RCC_H_ */
