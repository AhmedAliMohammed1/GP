/*
 * Timer1_8.c
 *
 *  Created on: Oct 13, 2023
 *      Author: medoo
 */


#include "Timer1_8.h"
TIMERx_type g_Sitting;
TIM1_8_REG* g_TIMX;


void MCAL_SET_TIMx_GPIO(TIM1_8_REG* TIMx){
	PIN_config pin={PIN_8,OUTPUT_AF_PP,SPEED_10};
	MCAL_GPIO_init(GPIOA, &pin);
}
void TIMER_1_8_start(TIM1_8_REG* TIMx,TIMERx_type* Sitting){
	g_Sitting=(* Sitting);
	g_TIMX=TIMx;
	if(TIMx== TIM1) RCC->APB2ENR|=(1<<11);



	// 2.select the pre vale
	TIMx->PSC=Sitting->TIME_PSC;

	TIMx->CR1.BIT_NAME.ARPE=1;

	TIMx->ARR=Sitting->TIME_ARR;

		TIMx->RCR=Sitting->TIME_RCR;
	//1.Select the mode CMS[1:0]
	switch(Sitting->mode){
	case TIM1_Up:
		TIMx->CR1.BIT_NAME.CMS=0b00; //00: Edge-aligned mode. The counter counts up or down depending on the direction bit (DIR).
		TIMx->CR1.BIT_NAME.DIR=0; //0: Counter used as upcounter
		break;
	case TIM1_DOWN:
		TIMx->CR1.BIT_NAME.CMS=0b00; //00: Edge-aligned mode. The counter counts up or down depending on the direction bit (DIR).
		TIMx->CR1.BIT_NAME.DIR=1; //1: Counter used as downcounter
		break;
	case TIM1_Up_Down:
		TIMx->CR1.BIT_NAME.CMS=0b11;
		/*11: Center-aligned mode 3. The counter counts up and down alternatively. Output compare
		interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
		both when the counter is counting up or down*/
		break;
	default:
		ERROR_HANDLER();
		break;
	}
	MCAL_SET_TIMx_GPIO(TIMx);
	TIMx->CR1.BIT_NAME.CEN=1;

	if(Sitting->INT_EN_DIS==TIM1_INT_EN){

		TIMx->DIER.BIT_NAME.UIE=1;
		NVIC_ISER0|=(1<<25);


	}else{
		while(!TIMx->SR.BIT_NAME.UIF);
		TIMx->SR.BIT_NAME.UIF=0;
	}

}
void TIMER_1_CTC_start(TIM1_8_REG* TIMx,TIMERx_type* Sitting,Compare_mode_sitting* CTC_Sitting){
	g_Sitting=(* Sitting);
	g_TIMX=TIMx;
	if(TIMx== TIM1) RCC->APB2ENR|=(1<<11);



	// 2.select the pre vale
	TIMx->PSC=Sitting->TIME_PSC;

	TIMx->ARR=Sitting->TIME_ARR;
	//	TIMx->CR1.BIT_NAME.ARPE=1;

		TIMx->RCR=Sitting->TIME_RCR;
	//1.Select the mode CMS[1:0]
	switch(Sitting->mode){
	case TIM1_Compare_output:
		/*
		 * Procedure:
1. Select the counter clock (internal, external, prescaler). Done
2. Write the desired data in the TIMx_ARR and TIMx_CCRx registers.
3. Set the CCxIE bit if an interrupt request is to be generated.
4. Select the output mode. For example:
– Write OCxM = 011 to toggle OCx output pin when CNT matches CCRx
– Write OCxPE = 0 to disable preload register
– Write CCxP = 0 to select active high polarity
– Write CCxE = 1 to enable the output
5. Enable the counter by setting the CEN bit in the TIMx_CR1 register.*/
		TIMx->CCR1=Sitting->TIME_CCR;
		TIMx->CCMR1.Compare_BIT_NAME.OC1M=CTC_Sitting->TIM1_CTC_MD;
		TIMx->CCMR1.Compare_BIT_NAME.OC1PE=CTC_Sitting->TIM1_CTC_PE;
		TIMx->CCER.BIT_NAME.CC1P=CTC_Sitting->TIM1_POL;
		TIMx->BDTR.BIT_NAME.MOE=1;
//		TIMx->BDTR.BIT_NAME.OSSR=1;
//		TIMx->BDTR.BIT_NAME.OSSI=1;

		TIMx->CCER.BIT_NAME.CC1E=1;

		break;

	default:
		ERROR_HANDLER();
		break;
	}
	MCAL_SET_TIMx_GPIO(TIMx);
	TIMx->CR1.BIT_NAME.CEN=1;

	if(Sitting->INT_EN_DIS==TIM1_INT_EN){
		TIMx->DIER.BIT_NAME.CC1IE=1;
		NVIC_ISER0|=(1<<27);
	}else{
		while(!TIMx->SR.BIT_NAME.CC1IF);
		TIMx->SR.BIT_NAME.CC1IF=0;
	}

}
////////////////////////////////




void TIMER_1_ICU_init(TIM1_8_REG* TIMx,TIMERx_type* Sitting){
	g_Sitting=(* Sitting);
	g_TIMX=TIMx;
	if(TIMx== TIM1) RCC->APB2ENR|=(1<<11);
//	// 2.select the pre vale
//	TIMx->PSC=Sitting->TIME_PSC;
//
	TIMx->ARR=65535;
//		TIMx->CR1.BIT_NAME.ARPE=1;
//
//		TIMx->RCR=Sitting->TIME_RCR;
	//1.Bits 1:0 CC1S: Capture/Compare 1 Selection
	TIMx->CCMR1.input_NAME.CC1S=0b01;
	//2. Bits 3:2 IC1PSC: Input capture 1 prescaler
	//00: no prescaler, capture is done each time an edge is detected on the capture input
	TIMx->CCMR1.input_NAME.IC2PSC=0;
	TIMx->CCMR1.input_NAME.IC1F=0b0011;//fSAMPLING=fCK_INT, N=8

	// 3. Bit 1 CC1P: Capture/Compare 1 output polarit
	//0: non-inverted: capture is done on a rising edge of IC1. When used as external trigger, IC1 is non-inverted.
	TIMx->CCER.BIT_NAME.CC1P=0;

	TIMx->CCER.BIT_NAME.CC1E=1;

	if(Sitting->INT_EN_DIS == TIM1_INT_EN){
		TIMx->DIER.BIT_NAME.CC1IE=1;
		NVIC_ISER0|=(1<<27);
	}

	TIMx->CR1.BIT_NAME.CEN=1;


}
/////////////////////////////////////////////

void Icu_setEdgeDetectionType (TIM1_8_REG* TIMx,Edge dir){
	if (dir ==TIM1_RISSING){
		TIMx->CCER.BIT_NAME.CC1P=0;
	}else if(dir == TIM1_FALLING){
		TIMx->CCER.BIT_NAME.CC1P=1;

	}
}


uint16_t TIMER_1_getTime(){
	return TIM1->CCR1;
}

void TIMER_1_Clear(){
	TIM1->CNT=0;
}
void TIMER_1_Deint(){
	RCC->APB2RSTR |=(1<<11);
	RCC->APB2RSTR &=~(1<<11);
	TIM1->ARR=0;
	TIM1->BDTR.ALL_BITS=0;
	TIM1->CCER.ALL_BITS=0;
	TIM1->CCMR1.ALL_BITS=0;
	TIM1->CCMR2.ALL_BITS=0;
	TIM1->CCR1=0;
	TIM1->CCR2=0;
	TIM1->CCR3=0;
	TIM1->CCR4=0;
	TIM1->CNT=0;
	TIM1->CR2.ALL_BITS=0;
	TIM1->PSC=0;

}



void TIM1_UP_IRQHandler(){
	g_Sitting.f_callback();
	g_TIMX->SR.BIT_NAME.UIF=0;

}


void TIM1_CC_IRQHandler(){
	g_Sitting.f_callback();
	g_TIMX->SR.BIT_NAME.CC1IF=0;

}
void TIM1_BRK_IRQHandler(){
	g_Sitting.f_callback();
	g_TIMX->SR.BIT_NAME.UIF=0;

}
void TIM1_TRG_COM_IRQHandler(){
	g_Sitting.f_callback();
	g_TIMX->SR.BIT_NAME.UIF=0;

}

void _TIM1_delay_us(uint16_t delay){
	TIMERx_type l_t_delay={((MCAL_GET_PCLCK2()/1000000)-1),((delay)-1),0,0,TIM1_INT_DIS,TIM1_Up,NULL};
	TIMER_1_8_start(TIM1,&l_t_delay);

}

void _TIM1_delay_ms(uint16_t delay){


		for(uint32_t i=0;i<delay;i++)
			_TIM1_delay_us(1000);

}
void _TIM1_delay_s(uint16_t delay){


		for(uint32_t i=0;i<delay;i++)
			_TIM1_delay_ms(1000);

}
