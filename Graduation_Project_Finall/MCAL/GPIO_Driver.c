/*
 * GPIO_Driver.c
 *
 *  Created on: Jul 24, 2023
 *      Author: Ahmed
 */


#include "GPIO_Driver.h"
usint16_t Get_PIN_Positon(usint16_t pin){
	usint16_t positon = (pin<8) ? (4*pin) :((pin-8)*4)   ;
return positon;
}
void MCAL_GPIO_init(GPIOx_REG* GPIOx,PIN_config* PINx){
	if(GPIOx ==GPIOA) RCC->APB2ENR |=(1<<2);
	else if(GPIOx ==GPIOB)RCC->APB2ENR |=(1<<3);
		else if(GPIOx ==GPIOC)RCC->APB2ENR |=(1<<4);
		else if(GPIOx ==GPIOD)RCC->APB2ENR |=(1<<5);
		else if(GPIOx ==GPIOE)RCC->APB2ENR |=(1<<6);

	vusint32_t *CONFIG=(PINx->PIN_number < 8) ? &GPIOx->CRL : &GPIOx->CRH ;
	*(CONFIG) &=~(0xF <<Get_PIN_Positon(PINx->PIN_number));
	// CNF0[1:0] MODE0[1:0] CLEAR

	if(PINx->MODE == Analog ||PINx->MODE == INPUT_FI ||PINx->MODE == INPUT_PU ||PINx->MODE == INPUT_PD ){
		if(PINx->MODE == INPUT_PD){
			*(CONFIG) |=((INPUT_PU << 2 ) << Get_PIN_Positon(PINx->PIN_number) );
			GPIOx->ODR &=~(1<< PINx->PIN_number);;
		}

		else if(PINx->MODE == INPUT_PU){
			*(CONFIG) |=((INPUT_PU << 2  ) << Get_PIN_Positon(PINx->PIN_number) );
			GPIOx->ODR |=(1<< PINx->PIN_number);;

		}else{
			*(CONFIG) |=((PINx->MODE << 2  ) << Get_PIN_Positon(PINx->PIN_number) );

		}

	}else{
		*(CONFIG) |=((((PINx->MODE -4 ) <<2) | PINx->SPEED ) << Get_PIN_Positon(PINx->PIN_number) );

	}

}
void MCAL_GPIO_Deinit(GPIOx_REG* GPIOx){
	if(GPIOx == GPIOA){
		RCC->APB2RSTR |=(1<<2);
		RCC->APB2RSTR &=~(1<<2);

	}else	if(GPIOx == GPIOB){
		RCC->APB2RSTR |=(1<<3);
		RCC->APB2RSTR &=~(1<<3);

	}else	if(GPIOx == GPIOC){
		RCC->APB2RSTR |=(1<<4);
		RCC->APB2RSTR &=~(1<<4);

	}else	if(GPIOx == GPIOD){
		RCC->APB2RSTR |=(1<<5);
		RCC->APB2RSTR &=~(1<<5);

	}else	if(GPIOx == GPIOE){
		RCC->APB2RSTR |=(1<<6);
		RCC->APB2RSTR &=~(1<<6);

	}


}
void MCAL_write_PIN(GPIOx_REG* GPIOx,vusint16_t PIN_Number,vusint8_t value){
	if(value == LOGIC_HIGH){
		GPIOx->ODR |=(1<<PIN_Number);
	}else{
		GPIOx->ODR &=~(1<<PIN_Number);

	}



}

void MCAL_write_PORT(GPIOx_REG* GPIOX,vusint16_t value){
	GPIOX->ODR=value;


}
usint16_t MCAL_Read_PIN(GPIOx_REG* GPIOx,vusint16_t PIN_Number){

	return ((GPIOx->IDR>>PIN_Number) & 1);

}
usint16_t MCAL_Read_PORT(GPIOx_REG* GPIOx){
	return (GPIOx->IDR);
}
void MCAL_TOGGLE_PIN(GPIOx_REG* GPIOx,vusint16_t PIN_Number){
	GPIOx->ODR ^=(1<<PIN_Number);
}


usint8_t MCAL_LOCK_PIN(GPIOx_REG* GPIOx,vusint16_t PIN_Number){
	usint8_t lock=0;
	GPIOx->LCKR =(0x1000) |(1<<PIN_Number);
//	LOCK key writing sequenc
//	Write 1
	GPIOx->LCKR =(0x1000) |(1<<PIN_Number);

//	Write 0
	GPIOx->LCKR =(0x0000) |(1<<PIN_Number);

//	Write 1
	GPIOx->LCKR =(0x1000) |(1<<PIN_Number);

//	Read 0
	if(!(GPIOx->LCKR & 1<<16))
		lock =0;
//	Read 1 (this read is optional but confirms that the lock is active)
	if((GPIOx->LCKR & 1<<16))
		lock =1;

	return lock;
}

void MCAL_SET_PORT_DIR(GPIOx_REG *GPIOx,PORT_config PORT){
	if(PORT==PORT_INPUT){
		GPIOx->CRH =0x44444444;
		GPIOx->CRL=0x44444444;
	}else{
		GPIOx->CRH=0x22222222;
		GPIOx->CRL=0x22222222;

	}

}
