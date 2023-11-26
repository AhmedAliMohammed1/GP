/*
 * EXTI_Driver.c
 *
 *  Created on: Aug 3, 2023
 *      Author: Ahmed
 */

#include "EXTI_Driver.h"

void (*g_P_CALLBACK_f[15])();
void NVIC_ENABLE(usint8_t irq){
	switch(irq){
	case 0:
		NVIC_EXTI0_EN;
		break;
	case 1:
		NVIC_EXTI1_EN;
		break;
	case 2:
		NVIC_EXTI2_EN;
		break;
	case 3:
		NVIC_EXTI3_EN;
		break;
	case 4:
		NVIC_EXTI4_EN;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_EXTI9_EN;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_EXTI15_EN;
break;

	}
}
void NVIC_DISABLE(usint8_t irq){
	switch(irq){
	case 0:
		NVIC_EXTI0_D;
		break;
	case 1:
		NVIC_EXTI1_D;
		break;
	case 2:
		NVIC_EXTI2_D;
		break;
	case 3:
		NVIC_EXTI3_D;
		break;
	case 4:
		NVIC_EXTI4_D;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_EXTI9_D;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_EXTI15_D;
break;

	}
}
	void MCAL_EXTI_init(EXTI_config_t *EXTI){
		usint8_t AFIO_EXTICR = (EXTI->EXTI_PIN.EXI_LINE /4);
		usint8_t EXTI_position = (EXTI->EXTI_PIN.EXI_LINE %4)*4;

		// MAKE THE PIN INPUT FLOATING
		PIN_config pin={EXTI->EXTI_PIN.PIN,INPUT_FI};
		MCAL_GPIO_init(EXTI->EXTI_PIN.GIPO, &pin);
		//UPDATE THE ALTERNATIVE FUNC
		AFIO->EXTICR[AFIO_EXTICR] &=~(0xF <<EXTI_position);
		AFIO->EXTICR[AFIO_EXTICR] |=(PORT_Detector(EXTI->EXTI_PIN.GIPO)<<EXTI_position);
		//MAKE THE SIGNAL RISING OR FALLING OR BOTH
		if(EXTI->EXT_TRIGGER ==FALLING){
			EXTI_REG->FTSR |=(1<<EXTI->EXTI_PIN.EXI_LINE);
		}else if(EXTI->EXT_TRIGGER ==RISEING){
			EXTI_REG->RTSR |=(1<<EXTI->EXTI_PIN.EXI_LINE);

		}else if(EXTI->EXT_TRIGGER ==FALLING_RISEING){
			EXTI_REG->FTSR |=(1<<EXTI->EXTI_PIN.EXI_LINE);
			EXTI_REG->RTSR |=(1<<EXTI->EXTI_PIN.EXI_LINE);


		}
		//Update Call Back Func
		g_P_CALLBACK_f[EXTI->EXTI_PIN.EXI_LINE]=EXTI->P_CallBack;
		//ENABLE THE Interrupt MASK AND NVIC
		if(EXTI->EXT_EN ==ENABLE){
		EXTI_REG->IMR|=(1<<EXTI->EXTI_PIN.EXI_LINE);
		NVIC_ENABLE(EXTI->EXTI_PIN.EXI_LINE);
		}
		else{
			EXTI_REG->IMR&=~(1<<EXTI->EXTI_PIN.EXI_LINE);
			NVIC_DISABLE(EXTI->EXTI_PIN.EXI_LINE	);
		}

	}
	void EXTI0_IRQHandler(){
		g_P_CALLBACK_f[0]();
		EXTI_REG->PR|=(1<<0);
	}
	void EXTI1_IRQHandler(){
		g_P_CALLBACK_f[1]();
		EXTI_REG->PR|=(1<<1);

	}
	void EXTI2_IRQHandler(){
		g_P_CALLBACK_f[2]();
		EXTI_REG->PR|=(1<<2);

	}
	void EXTI3_IRQHandler(){
		g_P_CALLBACK_f[3]();
		EXTI_REG->PR|=(1<<3);

	}
	void EXTI4_IRQHandler(){
		g_P_CALLBACK_f[4]();
		EXTI_REG->PR|=(1<<4);

	}
	void EXTI9_5_IRQHandler(){
		if(EXTI_REG->PR &(1<<5)){EXTI_REG->PR|=(1<<5); 		g_P_CALLBACK_f[5]();}
		if(EXTI_REG->PR &(1<<6)){EXTI_REG->PR|=(1<<6); 		g_P_CALLBACK_f[6]();}
		if(EXTI_REG->PR &(1<<7)){EXTI_REG->PR|=(1<<7); 		g_P_CALLBACK_f[7]();}
		if(EXTI_REG->PR &(1<<8)){EXTI_REG->PR|=(1<<8); 		g_P_CALLBACK_f[8]();}
		if(EXTI_REG->PR &(1<<9)){EXTI_REG->PR|=(1<<9); 		g_P_CALLBACK_f[9]();}
	}
	void EXTI15_10_IRQHandler(){
		if(EXTI_REG->PR &(1<<10)){EXTI_REG->PR|=(1<<10); 		g_P_CALLBACK_f[10]();}
		if(EXTI_REG->PR &(1<<11)){EXTI_REG->PR|=(1<<11); 		g_P_CALLBACK_f[11]();}
		if(EXTI_REG->PR &(1<<12)){EXTI_REG->PR|=(1<<12); 		g_P_CALLBACK_f[12]();}
		if(EXTI_REG->PR &(1<<13)){EXTI_REG->PR|=(1<<13); 		g_P_CALLBACK_f[13]();}
		if(EXTI_REG->PR &(1<<14)){EXTI_REG->PR|=(1<<14); 		g_P_CALLBACK_f[14]();}
		if(EXTI_REG->PR &(1<<15)){EXTI_REG->PR|=(1<<15); 		g_P_CALLBACK_f[15]();}

	}
