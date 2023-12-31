/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
#include "GPIO_Driver.h"
#include "LCD.h"
#include "RCC.h"
uint32_t sec_s;
uint8_t g_edgeCount = 0;
uint16_t g_timeHigh = 0;


void servo_degree(GP_TIMx_REG* TIMx,uint8_t degree,uint8_t position){
	/* F_CPU is 8Mhz and if i make the prescaler 8 i will get tick every 1 us so i will make the ARR reg 20000us(20ms)
	 * (50 hz of the servo and change the degree (1 to 2 ms change the degree*/
	uint32_t deg=0;
	switch(position){
	case '-':
		deg=((100000+556*(90-degree))/100);
		break;
	case '+':
		deg=((150000+556*degree)/100);

		break;
	default:
		deg=((150000+556*degree)/100);

		break;
	}
	GP_TIMERx_config Sitting=(GP_TIMERx_config){7,20000,0,deg,INT_DIS,PWM,NULL};
	GP_TIMERx_CTC_config CTC_Sitting={2,PWM_AH,ACTIVE_L};

	GP_TIMx__CTC_start(TIM3, &Sitting, &CTC_Sitting);
}


















void main(void){
	PIN_config PIN={PIN_0,OUTPUT_PP,SPEED_10};
	MCAL_GPIO_init(GPIOA, &PIN);
	while(1){
		MCAL_write_PIN(GPIOA, PIN_0, 1);
		servo_degree(TIM3,55,'+');

		_delay_ms(TIM2, 500);
		MCAL_write_PIN(GPIOA, PIN_0, 0);
		servo_degree(TIM3,86,'-');


		_delay_ms(TIM2, 500);

	}


}

