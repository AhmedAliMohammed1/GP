/*
 * RCC.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Ahmed
 */
#include "RCC.h"
uint8_t APB_Prescaler[]={0,0,0,0,1,2,3,4};
uint8_t AHB_Prescaler[]={0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9};

uint32_t MCAL_GET_SYS_CLCK(){
	switch((RCC->CFGR >>2) &0b11){
	case 0:
		return HSI_CLOCK;
		break;
	case 1:
		return HSE_CLOCK;
		break;
	case 2:
		return PLL_CLOCK;

		break;
	}

}
uint32_t MCAL_GET_H_CLCK(){

	return (MCAL_GET_SYS_CLCK() >> AHB_Prescaler[ (RCC->CFGR >>4) &0xF]) ;
}
uint32_t MCAL_GET_PCLCK1(){
	return (MCAL_GET_H_CLCK() >> AHB_Prescaler[ (RCC->CFGR >>8) &0b111] );

}
uint32_t MCAL_GET_PCLCK2(){
	return (MCAL_GET_H_CLCK() >> AHB_Prescaler[ (RCC->CFGR >>11) &0b111] );

}



