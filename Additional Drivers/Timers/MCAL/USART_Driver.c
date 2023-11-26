/*
 * USART_Driver.c
 *
 *  Created on: Aug 8, 2023
 *      Author: Ahmed
 */
#include "USART_Driver.h"
USART_Config_t G_P_config[3];
void MCAL_USART_init(USART_REG *USARTx,USART_Config_t *PIN){
	if(USARTx==USART1){ // MAKE A BACKUP AND ENABLE THE CLOCK
		G_P_config[0]=*PIN;
		RCC->APB2ENR |=(1<<14);
	}else if(USARTx==USART2){
		G_P_config[1]=*PIN;
		RCC->APB1ENR |=(1<<17);
}else if(USARTx==USART3){
		G_P_config[2]=*PIN;
		RCC->APB1ENR |=(1<<18);


	}
	// 1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
	USARTx->CR1 |=(1<<13);
	//2. Program the M bit in USART_CR1 to define the word length.
	USARTx->CR1 |=(PIN->Word<<12);
	//3. Program the number of stop bits in USART_CR2
	USARTx->CR2 |=(PIN->STOP<<12);
	if(PIN->MODE ==Asynchronous){
		//	6. Set the TE bit in USART_CR1 to send an idle frame as first transmission
		USARTx->CR1 |=(1<<3);
		//	7. Set the RE bit in USART_CR1 to send an idle frame as first transmission
		USARTx->CR1 |=(1<<2);
	}else{ // will modified later

	}
	//	8. Set the CTSE&RTSE bit in USART_CR3 to enable CTS&RTS hardware flow control

	switch( PIN->HW ){
	case Disabled:
		USARTx->CR3 &=~(RTS_EN |CTS_EN);
		break;
	case RTSE:
		USARTx->CR3 |=RTS_EN;
		break;
	case CTSE:
		USARTx->CR3 |=CTS_EN;
		break;
	case BOTH:
		USARTx->CR3 |=CTS_EN |RTS_EN;
		break;

	}
	//	9. Set the PCE &PS bit in USART_CR1 to send an idle frame as first transmission
	USARTx->CR1 |=(PIN->Parity<<9);
	if(PIN->MEC ==Interrupt){



		//ENABLE NVIC 	ISER1 32-63
		if(USARTx==USART1){

			NVIC_ISER1 |=(1<<(USART1_IRQ-32));
		}
		else if(USARTx==USART2){
			NVIC_ISER1 |=(1<<(USART2_IRQ-32));

		}
		else if(USARTx==USART3){
			NVIC_ISER1 |=(1<<(USART3_IRQ-32));

		}
		//Bit 7 TXEIE: TXE interrupt enable				//		Bit 5 RXNEIE: RXNE interrupt enable

				USARTx->CR1 |=(1<<5) ;
		}
	if(USARTx==USART1){ // MAKE A BACKUP AND ENABLE THE CLOCK
				USARTx->BRR=BRR(MCAL_GET_PCLCK2(),PIN->Baud_Rate);
			}else if(USARTx==USART2){
				USARTx->BRR=	BRR(MCAL_GET_PCLCK1(),PIN->Baud_Rate);

		}else if(USARTx==USART3){
			USARTx->BRR=	BRR(MCAL_GET_PCLCK1(),PIN->Baud_Rate);
		}
	SET_GPIO(USARTx);
	}


void MCAL_USART_Deinit(USART_REG *USARTx){
	if(USARTx==USART1){
		RCC	->APB2RSTR |=(1<<14);
		NVIC_ICER1 |=(1<<(USART1_IRQ-32));
	}			else if(USARTx==USART2){

		RCC	->APB1RSTR |=(1<<17);
		NVIC_ICER1 |=(1<<(USART2_IRQ-32));

	}
	else if(USARTx==USART3){
		RCC	->APB1RSTR |=(1<<18);
		NVIC_ICER1 |=(1<<(USART3_IRQ-32));
	}
	}

void MCAL_USART_SendData(USART_REG *USARTx,uint8_t data){
	USART_Config_t * L_P_config_pin=NULL;
	if(USARTx==USART1){
		L_P_config_pin=&G_P_config[0];
	}		else if(USARTx==USART2){
		L_P_config_pin=&G_P_config[1];
	}
	else if(USARTx==USART3){
		L_P_config_pin=&G_P_config[2];
	}

	if(L_P_config_pin->MEC ==POLLING){
		while(!(USARTx->SR & (1<<7)));
	}else if(L_P_config_pin->MEC ==Interrupt){ // Do nothing the cpu will jump to isr

	}else if(L_P_config_pin->MEC ==DMA){ // will modified later

	}

	// check if the word size if 9B or 8B
	if(L_P_config_pin->Word ==NINE_BITS)
	{
		USARTx->DR =(data & 0x1FF);
	}else{
		USARTx->DR =(data & 0xFF);

	}

}
uint16_t MCAL_USART_ReciveData(USART_REG *USARTx){
	USART_Config_t * L_P_config_pin=NULL;
	if(USARTx==USART1){
		L_P_config_pin=&G_P_config[0];
	}		else if(USARTx==USART2){
		L_P_config_pin=&G_P_config[1];
	}
	else if(USARTx==USART3){
		L_P_config_pin=&G_P_config[2];
	}

		if(L_P_config_pin->MEC ==POLLING){
			while(!(USARTx->SR & (1<<5)));
		}else if(L_P_config_pin->MEC ==Interrupt){ // Do nothing the cpu will jump to isr

		}else if(L_P_config_pin->MEC ==DMA){ // will modified later

		}
		if(L_P_config_pin->Parity ==Parity_DISABLE){
			return USARTx->DR;
		}else{
			return (USARTx->DR &0xFF);

		}

}

void SET_GPIO(USART_REG *USARTx){
	PIN_config GPIO={PIN_9,OUTPUT_AF_PP,SPEED_2}; // CONFIGRATION OF TX PIN
	if(USARTx==USART1){
		RCC->APB2ENR |=(1<<2); // Enable Colck to write on GPIOA
		MCAL_GPIO_init(GPIOA, &GPIO);
		GPIO =(PIN_config) {PIN_10,INPUT_FI,0}; //CONFIGRATION OF RX PIN
		MCAL_GPIO_init(GPIOA, &GPIO);

	}
	else if(USARTx==USART2){
		RCC->APB2ENR |=(1<<2); // Enable Colck to write on GPIOA

		GPIO=(PIN_config){PIN_2,OUTPUT_AF_PP,SPEED_2};// CONFIGRATION OF TX PIN
		MCAL_GPIO_init(GPIOA, &GPIO);
		GPIO =(PIN_config) {PIN_3,INPUT_FI,0}; //CONFIGRATION OF RX PIN
		MCAL_GPIO_init(GPIOA, &GPIO);
	}
	else if(USARTx==USART3){
		RCC->APB2ENR |=(1<<3); // Enable Colck to write on GPIOA

		GPIO=(PIN_config){PIN_10,OUTPUT_AF_PP,SPEED_2};// CONFIGRATION OF TX PIN
		MCAL_GPIO_init(GPIOB, &GPIO);
		GPIO =(PIN_config) {PIN_11,INPUT_FI,0}; //CONFIGRATION OF RX PIN
		MCAL_GPIO_init(GPIOB, &GPIO);
		}
}
void USART1_IRQHandler(void){
	G_P_config[0].P_Call_Back();
}
void USART2_IRQHandler(void){
	G_P_config[1].P_Call_Back();
}void USART3_IRQHandler(void){
	G_P_config[2].P_Call_Back();
}

