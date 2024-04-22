/*
 * Timer1_8.h
 *
 *  Created on: Oct 13, 2023
 *      Author: medoo
 */

#ifndef INC_TIMER1_8_H_
#define INC_TIMER1_8_H_
#include "STM32F103x6.h"
#include "GPIO_Driver.h"
#include "RCC.h"
typedef enum{
	TIM1_Up, /*If the repetition counter is used, the update event (UEV) is generated after upcounting is
		repeated for the number of times programmed in the repetition counter register plus one
		(TIMx_RCR+1). Else the update event is generated at each counter overflow.
	 	 */
	TIM1_DOWN,
	TIM1_Up_Down
	,TIM1_Compare_output

}Counter_Modes;
typedef enum{
	TIM1_INT_EN,TIM1_INT_DIS
}INTERPUT;
typedef enum{
	TIM1_RISSING,TIM1_FALLING

}Edge;
typedef enum{
	TIM1_Frozen=0,
	TIM1_active,
	TIM1_inactive,
	TIM1_Toggle,
	TIM1_PWM_AH=6 ,//PWM ACTIVE HIGH
	TIM1_PWM_AL
}Output_Compare_mode;
typedef enum{
	CTC_Preload_DIS,CTC_Preload_EN
}Output_Compare_preload_enable;
typedef enum{
	TIM1_ACTIVE_H,TIM1_ACTIVE_L
}Output_Compare_POL;
typedef struct{
	uint16_t TIME_PSC;
	uint16_t TIME_ARR; // = THE TOP VALUE THAT THE COUNTER REACH
	uint16_t TIME_RCR;
	uint16_t TIME_CCR;
	INTERPUT INT_EN_DIS;
	Counter_Modes mode;
	void (*f_callback)(void);


}TIMERx_type;


typedef struct{
	Output_Compare_mode TIM1_CTC_MD;
	Output_Compare_preload_enable TIM1_CTC_PE;
	Output_Compare_POL TIM1_POL;
}Compare_mode_sitting;





void TIMER_1_8_start(TIM1_8_REG* TIMx,TIMERx_type* Sitting);
void TIMER_1_CTC_start(TIM1_8_REG* TIMx,TIMERx_type* Sitting,Compare_mode_sitting* CTC_Sitting);
void Icu_setEdgeDetectionType (TIM1_8_REG* TIMx,Edge dir);
uint16_t TIMER_1_getTime();
void TIMER_1_Clear();
void TIMER_1_Deint();
void _TIM1_delay_us(uint16_t delay);
void _TIM1_delay_ms(uint16_t delay);
void _TIM1_delay_s(uint16_t delay);
#endif /* INC_TIMER1_8_H_ */
