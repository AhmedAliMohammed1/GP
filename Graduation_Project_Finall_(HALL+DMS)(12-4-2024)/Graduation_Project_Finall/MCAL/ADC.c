/*
 * ADC.c
 *
 *  Created on: Feb 15, 2024
 *      Author: medoo
 */

#include "ADC.h"
ADC_CONFIG G_ADC_config[2][16]={0};
void ADC_ERROR_HANDLER(){
	while(1);
}
void ADC_GPIO_CONFIG(uint8_t CHx){
	PIN_config PINx={PIN_0,Analog,0};
	switch(CHx){
	case 0:
		PINx=(PIN_config){PIN_0,Analog,0};
		MCAL_GPIO_init(GPIOA,&PINx);
		break;
	case 1:
		PINx=(PIN_config){PIN_1,Analog,0};
		MCAL_GPIO_init(GPIOA,&PINx);
		break;
	case 2:
		PINx=(PIN_config){PIN_2,Analog,0};
		MCAL_GPIO_init(GPIOA,&PINx);
		break;
	case 3:
		PINx=(PIN_config){PIN_3,Analog,0};
		MCAL_GPIO_init(GPIOA,&PINx);
		break;
	case 4:
		PINx=(PIN_config){PIN_4,Analog,0};
		MCAL_GPIO_init(GPIOA,&PINx);
		break;
	case 5:
		PINx=(PIN_config){PIN_5,Analog,0};
		MCAL_GPIO_init(GPIOA,&PINx);
		break;
	case 6:
		PINx=(PIN_config){PIN_6,Analog,0};
		MCAL_GPIO_init(GPIOA,&PINx);
		break;
	case 7:
		PINx=(PIN_config){PIN_7,Analog,0};
		MCAL_GPIO_init(GPIOA,&PINx);
		break;
	case 8:
		PINx=(PIN_config){PIN_0,Analog,0};
		MCAL_GPIO_init(GPIOB,&PINx);
		break;
	case 9:
		PINx=(PIN_config){PIN_1,Analog,0};
		MCAL_GPIO_init(GPIOB,&PINx);
		break;
	case 14:
		PINx=(PIN_config){PIN_4,Analog,0};
		MCAL_GPIO_init(GPIOC,&PINx);
		break;
	case 15:
		PINx=(PIN_config){PIN_5,Analog,0};
		MCAL_GPIO_init(GPIOC,&PINx);
		break;
	default:
		ADC_ERROR_HANDLER();
		break;

	}



}

ADC_return ADC_init(ADCx_REG *ADCx,ADC_CONFIG *config)
{
	if(config->CHx_num>9 &&config->CHx_num<14)
		return ADC_error;
	//peripheral clock enable
	if(ADCx ==ADC1){
		G_ADC_config[0][config->CHx_num]=*config;
		RCC->APB2ENR |=(1<<9);
	}
	else{
		G_ADC_config[1][config->CHx_num]=*config;
		RCC->APB2ENR |=(1<<10);
	}
	ADC_GPIO_CONFIG(config->CHx_num);

	//The ADC can be powered-on by setting the ADON bit in the ADC_CR2 register
	ADCx->CR2.Bit_Name.ADON=1;
	_TIM1_delay_us(10);
	/*Conversion starts when ADON bit is set for a second time by software after ADC power-up
	time (tSTAB).*/
	ADCx->CR2.Bit_Name.ADON=1;
	//	ADC clock (max 14Mhz)
	// i want to edit the prescaler to ensure the adc clock not more 14Mhz but i assume the my
	//	max clock not more 24 Mhz so the clock will be 12 Mhz

	switch((MCAL_GET_PCLCK2()/1000000UL)){
	case 8: //ADC CLK 4MHZ
		RCC->CFGR&=~(0b11<<14);
		break;
	case 16://ADC CLK 8MHZ
		RCC->CFGR&=~(0b11<<14);
		break;
	case 28://ADC CLK 12MHZ
		RCC->CFGR&=~(0b11<<14);
		break;
	default:
		//the worst case that 72Mhz so i will divde by 6 to ensure that i'm ok
		RCC->CFGR|=(0b10<<14);
		break;
	}
	//It is recommended to perform a calibration after each power-up.
	ADCx->CR2.Bit_Name.CAL=1;
	//Right alignment of data
	ADCx->CR2.Bit_Name.ALIGN=0;

	//ADC sample time register
	/*Tconv = Sampling time + 12.5 cycles
			Example:
		With an ADCCLK = 14 MHz and a sampling time of 1.5 cycles:
		Tconv = 1.5 + 12.5 = 14 cycles = 1 μs
		STM32F103xx performance line devices: 1 μs at 56 MHz (1.17 μs at 72 MHz)*/
	switch(config->CHx_num){
	case 0:
		ADCx->SMPR2.Bit_Name.SMP0=config->SPT;
		break;
	case 1:
		ADCx->SMPR2.Bit_Name.SMP1=config->SPT;

		break;
	case 2:
		ADCx->SMPR2.Bit_Name.SMP2=config->SPT;

		break;
	case 3:
		ADCx->SMPR2.Bit_Name.SMP3=config->SPT;

		break;
	case 4:
		ADCx->SMPR2.Bit_Name.SMP4=config->SPT;

		break;
	case 5:
		ADCx->SMPR2.Bit_Name.SMP5=config->SPT;

		break;
	case 6:
		ADCx->SMPR2.Bit_Name.SMP6=config->SPT;

		break;
	case 7:
		ADCx->SMPR2.Bit_Name.SMP7=config->SPT;

		break;
	case 8:
		ADCx->SMPR2.Bit_Name.SMP8=config->SPT;

		break;
	case 9:
		ADCx->SMPR2.Bit_Name.SMP9=config->SPT;

		break;
	case 14:
		ADCx->SMPR1.Bit_Name.SMP14=config->SPT;

		break;
	case 15:
		ADCx->SMPR1.Bit_Name.SMP15=config->SPT;
		break;
	default:
		ADC_ERROR_HANDLER();
		break;


	}

	switch(config->mode){
	case ADC_Single_conversion:
		/*In Single conversion mode the ADC does one conversion. This mode is started either by
setting the ADON bit in the ADC_CR2 register (for a regular channel only) or by external
trigger (for a regular or injected channel), while the CONT bit is 0.*/
		ADCx->CR2.Bit_Name.CONT=0;
		break;
	case ADC_Continuous_conversion:
		/*In continuous conversion mode ADC starts another conversion as soon as it finishes one.
This mode is started either by external trigger or by setting the ADON bit in the ADC_CR2
register, while the CONT bit is 1. */
		ADCx->CR2.Bit_Name.CONT=1;
		break;

	default:
		ADC_ERROR_HANDLER();
		break;
	}

	if(config->AWDG->AWGD_Enable){
		ADCx->CR1.Bit_Name.AWDEN=1;
		ADCx->CR1.Bit_Name.AWDCH=config->CHx_num;
		if(config->IE ==ADC_interrupt){
			ADCx->CR1.Bit_Name.AWDIE=1;
		}else{
			ADCx->CR1.Bit_Name.AWDIE=0;
		}
		ADCx->CR1.Bit_Name.AWDSGL=1;
	}
	//	if(config->sequence->sequence_Enable){
	//		//Regular channel sequence length
	//		ADCx->SQR1.Bit_Name.L=(config->sequence->N-1);
	//		for(uint8_t i=0;i<config->sequence->N;i++){
	//			switch(i){
	//			case 0:
	//				ADCx->SQR3.Bit_Name.SQ1=config->sequence->CH_1;
	//
	//				break;
	//			case 1:
	//				ADCx->SQR3.Bit_Name.SQ2=config->sequence->CH_2;
	//
	//				break;
	//			case 2:
	//				ADCx->SQR3.Bit_Name.SQ3=config->sequence->CH_3;
	//
	//				break;
	//			case 3:
	//				ADCx->SQR3.Bit_Name.SQ4=config->sequence->CH_4;
	//
	//				break;
	//			case 4:
	//				ADCx->SQR3.Bit_Name.SQ5=config->sequence->CH_5;
	//
	//				break;
	//			case 5:
	//				ADCx->SQR3.Bit_Name.SQ6=config->sequence->CH_6;
	//
	//				break;
	//			case 6:
	//				ADCx->SQR2.Bit_Name.SQ7=config->sequence->CH_8;
	//
	//				break;
	//			case 7:
	//				ADCx->SQR2.Bit_Name.SQ8=config->sequence->CH_8;
	//
	//				break;
	//
	//			}
	//		}
	//	}
	//	else{
	//		ADCx->SQR1.ALL_Bits=0;
	//		ADCx->SQR2.ALL_Bits=0;
	//		ADCx->SQR3.ALL_Bits=0;
	//
	//		ADCx->SQR1.Bit_Name.L=1;
	//		ADCx->SQR3.Bit_Name.SQ1=config->CHx_num;
	//
	//
	//	}

	if(config->IE){
 // this will done when ADC_interrupt_Enable(); calles
	}

	ADCx->CR2.Bit_Name.EXTSEL=0b111; //111: SWSTART
	ADCx->CR2.Bit_Name.SWSTART=1;//1: Starts conversion of regular channels

	return ADC_OK;
}

void ADC_read(ADCx_REG *ADCx,uint8_t CH_num,uint16_t *data){
	ADC_CONFIG *ADC_CONFIG_v=NULL;

	//GET the back up sitting from the global sitting
	if(ADCx ==ADC1){
		ADC_CONFIG_v=&G_ADC_config[0][CH_num];
	}
	else{
		ADC_CONFIG_v=&G_ADC_config[1][CH_num];

	}




	ADCx->SQR1.ALL_Bits=0;
	ADCx->SQR2.ALL_Bits=0;
	ADCx->SQR3.ALL_Bits=0;

	ADCx->SQR3.Bit_Name.SQ1=ADC_CONFIG_v->CHx_num;



	if(ADC_CONFIG_v->mode==ADC_Single_conversion){
		ADCx->CR2.Bit_Name.SWSTART=1;//1: Starts conversion of regular channels
		//		while(ADCx->SR.Bit_Name.STRT==0);
		while(ADCx->SR.Bit_Name.EOC==0);

	}

	if(ADC_CONFIG_v->IE){
		*data=ADCx->DR.Bit_Name.Regular_DATA;
		data++;
	}else{
		//		while(ADCx->SR.Bit_Name.EOC==0);

		for(uint8_t i=0;i<=ADCx->SQR1.Bit_Name.L;i++){
			*data=ADCx->DR.Bit_Name.Regular_DATA;
			data++;
		}
	}

}

void ADC1_2_IRQHandler(){
	if(ADC1->SR.Bit_Name.EOC ==1){

		G_ADC_config[0][(ADC1->SQR3.Bit_Name.SQ1)].g_ADC_callback();
	}else{
		G_ADC_config[1][(ADC2->SQR3.Bit_Name.SQ1)].g_ADC_callback();
	}
}


void ADC_interrupt_Enable(ADCx_REG *ADCx){
	ADCx->CR1.Bit_Name.EOCIE=1;
	NVIC_ISER0 |=(1<<18); //18  settable ADC1_2 ADC1 and ADC2 global interrupt
}
