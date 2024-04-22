/*
 * I2C.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Ahmed
 */

#include "I2C.h"
I2C_config_t G_P_CONFIG[2]; //INDEX 0 FOR I2C1 ,,,INDEX 1 FOR I2C2
void MCAL_I2C_SET_GPIO(I2C_REG * I2Cx){
	PIN_config I2C_pin;
	if(I2Cx ==I2C1){
		RCC->APB2ENR |=(1<<3);
	//I2C1_SCL PB6
		I2C_pin=(PIN_config){PIN_6,OUTPUT_AF_OD,SPEED_10};
		MCAL_GPIO_init(GPIOB, &I2C_pin);
	//I2C1_SDA PB7
		I2C_pin=(PIN_config){PIN_7,OUTPUT_AF_OD,SPEED_10};
		MCAL_GPIO_init(GPIOB, &I2C_pin);


	}
	else if(I2Cx ==I2C2){
		RCC->APB2ENR |=(1<<3);
		//I2C2_SCL PB10
		I2C_pin=(PIN_config){PIN_10,OUTPUT_AF_OD,SPEED_10};
		MCAL_GPIO_init(GPIOB, &I2C_pin);
		//I2C2_SDA PB11
		I2C_pin=(PIN_config){PIN_11,OUTPUT_AF_OD,SPEED_10};
		MCAL_GPIO_init(GPIOB, &I2C_pin);




}

}
uint16_t GET_flag_status(I2C_REG * I2Cx,EVENT_check EVENT){
	uint16_t	dummy;
	switch(EVENT){
	case EV5:
		dummy= ((uint16_t)I2Cx->SR1.ALL_REG);
	break;
	case EV6:
		dummy= ((uint16_t)I2Cx->SR1.ALL_REG);
		dummy=((uint16_t)I2Cx->SR2.ALL_REG);
		break;
	case EV8_1:
		while(I2Cx->SR1.Bit_Name.TxE);// this EV8_1
		break;
	case EV8:
		while(!I2Cx->SR1.Bit_Name.TxE);// this EV8_1

		break;
	case EV8_2:
		while(!I2Cx->SR1.Bit_Name.TxE);// this EV8_1

		break;


	}
	return dummy;
}

void I2C_init(I2C_REG * I2Cx,I2C_config_t *I2C_config){
	if(I2Cx ==(I2C_REG *)I2C1){G_P_CONFIG[0]=*I2C_config;     RCC->APB1ENR |=(1<<21); } //ENABLE THE CLOCK AND MAKE A BACKUP
	else if(I2Cx ==(I2C_REG *)I2C2){G_P_CONFIG[1]=*I2C_config;     RCC->APB1ENR |=(1<<22);} //ENABLE THE CLOCK AND MAKE A BACKUP

	//1.Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	I2Cx->CR2.Bit_Name.FREQ =FREQ_EQ;
	//2.• Configure the clock control registers (CCR)
	I2Cx->CCR.Bit_Name.F_S=I2C_config->FS; //0: Sm mode I2C ,,1: Fm mode I2C
	I2Cx->CCR.Bit_Name.CCR=CCR_EQ(I2C_config->F_SCL);
	//3.• Configure the rise time register
	I2Cx->TRISE.Bit_Name.TRISE=(FREQ_EQ)+1;
	//4.SET MY OWN SLAVE ADDRESS
	I2Cx->OAR1.Bit_Name.ADD=I2C_config->SLA.Primary_SLA;
	if(I2C_config->SLA.Dual_addressing_EN) 	{ I2Cx->OAR2.Bit_Name.ENDUAL=1;  I2Cx->OAR2.Bit_Name.ADD2=I2C_config->SLA.DUAL_SLA;}
	//5.SET interrupt_EN IF IT ENABLED
	if(I2C_config->interrupt_EN){
		I2Cx->CR2.Bit_Name.ITEVTEN=1;
		I2Cx->CR2.Bit_Name.ITBUFEN=1;
		if(I2Cx ==(I2C_REG *)I2C1){		NVIC_ISER0 |=(1<<(I2C1_EV_IRQ)); NVIC_ISER1 |=(1<<(I2C1_ER-32));  } //ENABLE THE CLOCK AND MAKE A BACKUP
		else if(I2Cx ==(I2C_REG *)I2C2){	NVIC_ISER1 |=(1<<(I2C2_EV-32)); NVIC_ISER1 |=(1<<(I2C2_ER-32)); } //ENABLE THE CLOCK AND MAKE A BACKUP

	}
	MCAL_I2C_SET_GPIO(I2Cx);
	//6.• Program the I2C_CR1 register to enable the peripheral
	I2Cx->CR1.Bit_Name.PE=1;


}
void I2C_Deinit(I2C_REG * I2Cx,I2C_config_t *I2C_config){

	if(I2Cx ==(I2C_REG *)I2C1){	RCC->APB1RSTR|=(1<<21);	NVIC_ICER0 |=(1<<(I2C1_EV_IRQ)); NVIC_ICER1 |=(1<<(I2C1_ER-32));  } //ENABLE THE CLOCK AND MAKE A BACKUP
	else if(I2Cx ==(I2C_REG *)I2C2){RCC->APB1RSTR|=(1<<22);	NVIC_ICER1 |=(1<<(I2C2_EV-32)); NVIC_ICER1 |=(1<<(I2C2_ER-32)); } //ENABLE THE CLOCK AND MAKE A BACKUP

}

void I2C_Start_BIT(I2C_REG * I2Cx){
	// check if the bus is busy or not
	while(I2Cx->SR2.Bit_Name.BUSY); //wait until bus is free – cleared by hardware on detection of a Stop condition.
	I2Cx->CR1.Bit_Name.START=1;
	while(!I2Cx->SR1.Bit_Name.SB);

}
void I2C_REPATED_Start_BIT(I2C_REG * I2Cx){
	// check if the bus is busy or not
	I2Cx->CR1.Bit_Name.START=1;
	while(!I2Cx->SR1.Bit_Name.SB);

}

void I2C_Stop_BIT(I2C_REG * I2Cx){
	I2Cx->CR1.Bit_Name.STOP=1;

}
void I2C_WriteADDRESS(I2C_REG * I2Cx,uint8_t DEV_add,Read_Control RW){
	DEV_add =(DEV_add<<1);
	if(RW==WRITE){
		DEV_add &=~(1<<0);
	}else{
		DEV_add |=(1<<0);

	}
	I2Cx->DR.ALL_REG=DEV_add;
	while(!I2Cx->SR1.Bit_Name.ADDR);


}
void I2C_WriteByte(I2C_REG * I2Cx,uint8_t data){
	while(!I2Cx->SR1.Bit_Name.TxE);// this EV8_1
	I2Cx->DR.ALL_REG=((uint8_t)data);
}
void I2C_ReciveByte(I2C_REG * I2Cx,uint8_t *data){
	while(!I2Cx->SR1.Bit_Name.RxNE);
	*data= ((uint8_t)I2Cx->DR.ALL_REG);
}


void I2C_MASTER_Transsimte(I2C_REG * I2Cx,uint8_t address,uint8_t data,uint8_t len){
	I2C_config_t *L_G_P_CONFIG=NULL;
	if(I2Cx ==I2C1){L_G_P_CONFIG=&G_P_CONFIG[0];  } // MAKE A BACKUP
		else if(I2Cx ==I2C2){L_G_P_CONFIG=&G_P_CONFIG[1]    ;}  // MAKE A BACKUP
	address>>=1;
	I2C_Start_BIT(I2Cx);
	GET_flag_status(I2Cx,EV5);
	I2C_WriteByte(I2Cx,address);
	GET_flag_status(I2Cx,EV6);
	for(int i=0;i<len;i++)
		I2C_WriteByte(I2Cx,data++);
	I2C_Stop_BIT(I2Cx);
}






