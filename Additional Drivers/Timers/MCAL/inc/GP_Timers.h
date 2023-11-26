/*
 * GP_Timers.h
 *
 *  Created on: Oct 30, 2023
 *      Author: medoo
 */

#ifndef INC_GP_TIMERS_H_
#define INC_GP_TIMERS_H_
#include "STM32F103x6.h"
#include "GPIO_Driver.h"
#define F_CPU 8000000UL
/*ENUMS */


/*@GP_TIMER_Mode shall to select the mode of the timer*/
typedef enum{
	NORMAL,PWM,CTC=1,ICU
}GP_TIMER_Mode;
/*@GP_TIMER_Counter_Modes shall to select the mode of the normal mode counter up or down*/
typedef enum{
	Up, /*If the repetition counter is used, the update event (UEV) is generated after upcounting is
		repeated for the number of times programmed in the repetition counter register plus one
		(TIMx_RCR+1). Else the update event is generated at each counter overflow.
	 */
	DOWN,
	Up_Down
	,Compare_output

}GP_TIMER_Counter_Modes;
/*@GP_TIMER_INTERPUT shall to enable or disable the interrupt*/
typedef enum{
	INT_EN,INT_DIS
}GP_TIMER_INTERPUT;
/*@GP_TIMER_ICU_Edge_Selection shall to change the direction of the edge detection*/
typedef enum{
	RISSING,FALLING

}GP_TIMER_ICU_Edge_Selection;
/*@GP_TIMER_Output_Compare_mode shall to Select the mode of the CTC or PWM mode according to OCxM register*/
typedef enum{
	Frozen=0, //disable
	active,  // always high
	inactive, //always low
	Toggle,		//toggle the signal when the CNT reach the ARR
	PWM_AH=6 ,//PWM ACTIVE HIGH
	PWM_AL		//PWM ACTIVE LOW
}GP_TIMER_Output_Compare_mode;
/*@GP_TIMER_Output_Compare_POL shall to select the polarity of the output wave (H/L) */
typedef enum{
	ACTIVE_H,ACTIVE_L
}GP_TIMER_Output_Compare_POL;

////////////////////////*********STRUCT*******///////////////////////////

/*@GP_TIMERx_NORMAL_config shall to make the sitting of the CTC/PWM mode */

typedef struct{
	GP_TIMER_Counter_Modes NORMAL_MODE; //to know what is the mode (CTC(HIGH/LOW))/PWM
}GP_TIMERx_NORMAL_config;
/*@GP_TIMERx_CTC_config shall to make the sitting of the CTC/PWM mode */

typedef struct{
	uint8_t CHx_num; // how many chanels user need to activate in PWM/CTC mode
	GP_TIMER_Output_Compare_mode CTC_MODE; //to know what is the mode (CTC(HIGH/LOW))/PWM
	GP_TIMER_Output_Compare_POL CTC_POL;
}GP_TIMERx_CTC_config;

/*@GP_TIMERx_CTC_config shall to make the sitting of the CTC/PWM mode */
typedef struct{
	uint8_t CHx_num; // how many chanels user need to activate in PWM/CTC mode
	GP_TIMER_ICU_Edge_Selection EDGE_SELECT; //to know what is the mode (CTC(HIGH/LOW))/PWM
}GP_TIMERx_ICU_config;

/*@GP_TIMx_ERROR_src shall to know the interrupt source error */
typedef struct{
	uint8_t UIF:1;
	uint8_t CC1IF:1;
	uint8_t CC2IF:1;
	uint8_t CC3IF:1;
	uint8_t CC4IF:1;

}GP_TIMx_ERROR_src;



/*@GP_TIMERx_config shall to put in it the genaric sitting of any timer in any mode */
typedef struct{
	uint16_t TIME_PSC; //prescaler
	uint16_t TIME_ARR; // = THE TOP VALUE THAT THE COUNTER REACH
	uint16_t TIME_RCR; //preload register
	uint16_t TIME_CCR; //compare register
	GP_TIMER_INTERPUT INT_EN_DIS; //
	GP_TIMER_Mode mode;
	void (*f_callback)(GP_TIMx_ERROR_src* ERROR_SRC);


}GP_TIMERx_config;






/***************APIs***************/
void MCAL_SET_GP_TIMx_GPIO(GP_TIMx_REG* TIMx,GP_TIMER_Mode MODE,uint8_t CHx);
void GP_TIMx_start(GP_TIMx_REG* TIMx,GP_TIMERx_config* Sitting,GP_TIMERx_NORMAL_config* NORMAL_SITTING);
void GP_TIMx__CTC_start(GP_TIMx_REG* TIMx,GP_TIMERx_config* Sitting,GP_TIMERx_CTC_config* CTC_Sitting);
void GP_TIMx_ICU_init(GP_TIMx_REG* TIMx,GP_TIMERx_config* Sitting,GP_TIMERx_ICU_config* ICU_sitting);
void GP_TIMx_Icu_setEdgeDetectionType (GP_TIMx_REG* TIMx,GP_TIMER_ICU_Edge_Selection dir);
uint16_t GP_TIMx_getTime(GP_TIMx_REG* TIMx,uint8_t CHx);
void GP_TIMX_Clear(GP_TIMx_REG* TIMx);
void GP_TIMx_Deint(GP_TIMx_REG* TIMx);
void _delay_us(GP_TIMx_REG* TIMx ,uint16_t delay);
void _delay_ms(GP_TIMx_REG* TIMx ,uint16_t delay);
void _delay_s(GP_TIMx_REG* TIMx ,uint16_t delay);

#endif /* INC_GP_TIMERS_H_ */
