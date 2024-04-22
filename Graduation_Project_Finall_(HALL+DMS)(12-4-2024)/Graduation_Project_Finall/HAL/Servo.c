/*
 * Servo.c
 *
 *  Created on: Nov 2, 2023
 *      Author: medoo
 */
#include"servo.h"


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
	GP_TIMERx_config Sitting=(GP_TIMERx_config){7,20000,0,deg,INT_DIS,PWM,NULL}; //you  need to calculate the freq and config the 50hz to the servo
	GP_TIMERx_CTC_config CTC_Sitting={2,PWM_AH,ACTIVE_L};

	GP_TIMx__CTC_start(TIM3, &Sitting, &CTC_Sitting);
}
