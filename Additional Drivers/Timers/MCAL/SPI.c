/*
 * SPI.c
 *
 *  Created on: Aug 15, 2023
 *      Author: Ahmed
 */

#include "SPI.h"
SPI_Config_t G_P_Config_t[2]={0}; // index 0 for SPI0 index 1 for SPI1

void MCAL_SPI_init(SPI_Reg * SPIx,SPI_Config_t *Config){
	// make a global backup for the configuration of the SPI
	if(SPIx == SPI1){ G_P_Config_t[0]= *Config; 	RCC->APB2ENR |=(1<<12); }
	else if(SPIx == SPI2){ G_P_Config_t[1]= *Config;RCC->APB1ENR |=(1<<14); }
	//1. Set the DFF bit to define 8- or 16-bit data frame format
	SPIx->SPI_CR1.Bit_Name.DFF = Config->DATA;
		/*2. Select the CPOL and CPHA bits to define one of the four relationships between the
		data transfer and the serial clock (see Figure 240). For correct data transfer, the CPOL
		and CPHA bits must be configured in the same way in the slave device and the master
		device*/
	SPIx->SPI_CR1.Bit_Name.CPOL = Config->POL;
	SPIx->SPI_CR1.Bit_Name.CPHA = Config->PHA;
		/*3. The frame format (MSB-first or LSB-first depending on the value of the LSBFIRST bit in
		the SPI_CR1 register) must be the same as the master device.*/
	SPIx->SPI_CR1.Bit_Name.LSBFIRST = Config->FRAME;
	/*4. In Hardware mode (refer to Slave select (NSS) pin management), the NSS pin must be
		connected to a low level signal during the complete byte transmit sequence. In NSS
		software mode, set the SSM bit and clear the SSI bit in the SPI_CR1 register.*/
	if(Config->NSS_SELC ==SW) 	SPIx->SPI_CR1.Bit_Name.SSM = 1;
	else if(Config->NSS_SELC ==HW_OUT ){ SPIx->SPI_CR1.Bit_Name.SSM = 0; SPIx->SPI_CR2.Bit_Name.SSOE =1;}
	else if(Config->NSS_SELC ==HW_IN ){ SPIx->SPI_CR1.Bit_Name.SSM = 0; SPIx->SPI_CR2.Bit_Name.SSOE =0;}
	//5. Clear the MSTR bit and set the SPE bit (both in the SPI_CR1 register) to assign the pins to alternate functions.
	SPIx->SPI_CR1.Bit_Name.MSTR = Config->M_S;
	//6. Select the BR[2:0] bits to define the serial clock baud rate (see SPI_CR1 register)
	SPIx->SPI_CR1.Bit_Name.BR = Config->BAUD_R;

	// 7.check if the interrupt is enabled or not
	if(Config->IN_EN ==interrupt_EN){

		if(SPIx == SPI1)    	NVIC_ISER1 |=(1<< (SPI1_IRQ-32));
		else if(SPIx == SPI2)   NVIC_ISER1 |=(1<< (SPI2_IRQ-32));
}
	// set the SPE bit
	 MCAL_SET_GPIO(SPIx);
	 SPIx->SPI_CR1.Bit_Name.SPE =Config->SP_EN;




}
void MCAL_SPI_Deinit(SPI_Reg *SPIx){
	if(SPIx == SPI1)   {	NVIC_ICER1 |=(1<< (SPI1_IRQ-32));	RCC->APB2RSTR |=(1<<12); }
	else if(SPIx == SPI2) {NVIC_ICER1 |=(1<< (SPI2_IRQ-32));	RCC->APB1RSTR |=(1<<14); }
}


uint8_t MCAL_SPI_SendData(SPI_Reg *SPIx,uint8_t data){
	SPI_Config_t *L_P_config_t=NULL;
	if(SPIx == SPI1) L_P_config_t =&G_P_Config_t[0];
	else if(SPIx == SPI2) L_P_config_t =&G_P_Config_t[1];
	// check if the configuration is polling or interrupt
	if(L_P_config_t->IN_EN ==interrupt_EN){ // do nothing the cpu will jump to isr
		SPIx->SPI_CR2.Bit_Name.TXEIE = 1;

	}else{
		while(!SPIx->SPI_SR.Bit_Name.TXE);
	}
	SPIx->DR_reg.ALL_REG=(uint8_t)data;

	return SPIx->DR_reg.ALL_REG;

}
void MCAL_SPI_ReciveData(SPI_Reg *SPIx,uint8_t *data){
	SPI_Config_t *L_P_config_t=NULL;
	if(SPIx == SPI1) L_P_config_t =&G_P_Config_t[0];
	else if(SPIx == SPI2) L_P_config_t =&G_P_Config_t[1];
	// check if the configuration is polling or interrupt
	SPIx->DR_reg.ALL_REG=0x00;

	if(L_P_config_t->IN_EN ==interrupt_EN){ // do nothing the cpu will jump to isr
		SPIx->SPI_CR2.Bit_Name.RXNEIE = 1;
	}else{
		while(!SPIx->SPI_SR.Bit_Name.RXNE);
	}
	(*data)=(SPIx->DR_reg.ALL_REG &0xFF);


}

void MCAL_SET_GPIO(SPI_Reg *SPIx){
	SPI_Config_t *L_P_config_t=NULL;
	PIN_config SPI_PIN_CONFIG;
	if(SPIx == SPI1) {
		L_P_config_t =&G_P_Config_t[0];
		RCC->APB2ENR|=(1<<2); // ENABLE CLOCK FOR PROTA
		//PA4 SPI1_NSS
		if(L_P_config_t ->NSS_SELC ==SW){ SPI_PIN_CONFIG=(PIN_config) {PIN_4,OUTPUT_PP,SPEED_10};  		SPI1->SPI_CR1.Bit_Name.SSI=1;}//Not used. Can be used as a GPIO
		else if(L_P_config_t ->NSS_SELC ==HW_OUT) SPI_PIN_CONFIG=(PIN_config) {PIN_4,OUTPUT_AF_PP,SPEED_10}; //Alternate function push-pull
		else if(L_P_config_t ->NSS_SELC ==HW_IN) SPI_PIN_CONFIG=(PIN_config) {PIN_4,INPUT_FI,0}; //Input floating/ Input pull-up / Input pull-down
		MCAL_GPIO_init(GPIOA, &SPI_PIN_CONFIG);
		//PA5 SPI1_SCK
		if(L_P_config_t ->M_S ==Master) SPI_PIN_CONFIG=(PIN_config) {PIN_5,OUTPUT_AF_PP,SPEED_10};
		else if(L_P_config_t ->M_S ==Slave) SPI_PIN_CONFIG=(PIN_config) {PIN_5,INPUT_FI,0};
		MCAL_GPIO_init(GPIOA, &SPI_PIN_CONFIG);
		//PA6 SPI1_MISO
		if(L_P_config_t ->M_S ==Master) SPI_PIN_CONFIG=(PIN_config) {PIN_6,INPUT_FI,0};
		else if(L_P_config_t ->M_S ==Slave) SPI_PIN_CONFIG=(PIN_config) {PIN_6,OUTPUT_AF_PP,SPEED_10};
		MCAL_GPIO_init(GPIOA, &SPI_PIN_CONFIG);
		//PA7 SPI1_MOSI
		if(L_P_config_t ->M_S ==Master) SPI_PIN_CONFIG=(PIN_config) {PIN_7,OUTPUT_AF_PP,SPEED_10};
		else if(L_P_config_t ->M_S ==Slave) SPI_PIN_CONFIG=(PIN_config) {PIN_7,INPUT_FI,0};
		MCAL_GPIO_init(GPIOA, &SPI_PIN_CONFIG);

	}
	else if(SPIx == SPI2){
		L_P_config_t =&G_P_Config_t[1];
		RCC->APB2ENR|=(1<<3); // ENABLE CLOCK FOR PROTA
		//PB12 SPI2_NSS
		if(L_P_config_t ->NSS_SELC ==SW) SPI_PIN_CONFIG=(PIN_config) {PIN_12,OUTPUT_AF_PP,SPEED_10}; //Not used. Can be used as a GPIO
			else if(L_P_config_t ->NSS_SELC ==HW_OUT) SPI_PIN_CONFIG=(PIN_config) {PIN_12,OUTPUT_AF_PP,SPEED_10}; //Alternate function push-pull
			else if(L_P_config_t ->NSS_SELC ==HW_IN) SPI_PIN_CONFIG=(PIN_config) {PIN_12,INPUT_FI,0}; //Input floating/ Input pull-up / Input pull-down
			MCAL_GPIO_init(GPIOA, &SPI_PIN_CONFIG);
		//PB13 SPI2_SCK
			//PA5 SPI1_SCK
				if(L_P_config_t ->M_S ==Master) SPI_PIN_CONFIG=(PIN_config) {PIN_13,OUTPUT_AF_PP,SPEED_10};
				else if(L_P_config_t ->M_S ==Slave) SPI_PIN_CONFIG=(PIN_config) {PIN_13,INPUT_FI,0};
				MCAL_GPIO_init(GPIOA, &SPI_PIN_CONFIG);
		//PB14 SPI2_MISO
				if(L_P_config_t ->M_S ==Master) SPI_PIN_CONFIG=(PIN_config) {PIN_14,INPUT_FI,0};
					else if(L_P_config_t ->M_S ==Slave) SPI_PIN_CONFIG=(PIN_config) {PIN_14,OUTPUT_AF_PP,SPEED_10};
					MCAL_GPIO_init(GPIOA, &SPI_PIN_CONFIG);
		//PB15 SPI2_MOSI
					if(L_P_config_t ->M_S ==Master) SPI_PIN_CONFIG=(PIN_config) {PIN_15,OUTPUT_AF_PP,SPEED_10};
							else if(L_P_config_t ->M_S ==Slave) SPI_PIN_CONFIG=(PIN_config) {PIN_15,INPUT_FI,0};
							MCAL_GPIO_init(GPIOA, &SPI_PIN_CONFIG);
	}



}


void SPI1_IRQHandler(void){
	Flag_source flagv2;
	get_flag_source(&flagv2,SPI1);
	G_P_Config_t[0].P_CallBack(flagv2);
}
void get_flag_source(Flag_source *flag,SPI_Reg* SPIx){

	if(SPIx->SPI_SR.Bit_Name.RXNE){
			flag->TXE_FLAG=0;
			flag->RXNE_FLAG=1;
			SPIx->SPI_CR2.Bit_Name.RXNEIE=0;
		}else if(SPIx->SPI_SR.Bit_Name.TXE){
		flag->TXE_FLAG=1;
		flag->RXNE_FLAG=0;
		SPIx->SPI_CR2.Bit_Name.TXEIE=0;
	}
}
