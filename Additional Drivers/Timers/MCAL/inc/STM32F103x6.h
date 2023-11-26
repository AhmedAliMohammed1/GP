/*
 * STM32F103x6.h
 *
 *  Created on: Jul 24, 2023
 *      Author: Ahmed
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_
//-----------------------------
//Includes
//-----------------------------
#include <Platform_Types.h>
#include <stdint.h>
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define FLASH_MEMORY_BASE 	0x08000000UL
#define SYS_MEMORY_BASE 	0x1FFFF000UL
#define SRAM_MEMORY_BASE 	0x20000000UL
#define NULL ((void *) 0)

//-----------------------------
//Base addresses for  AHB BUS Peripherals
//-----------------------------
#define RCC_BASE 0x40021000
//-----------------------------
//Base addresses for  APB1 BUS Peripherals

//-----------------------------
#define SPI2_BASE	0x40003800
#define SPI3_BASE	0x40003C00
#define I2C1_BASE	0x40005400
#define I2C2_BASE	0x40005800


//-----------------------------
//Base addresses for  APB2 BUS Peripherals
//-----------------------------
#define GPIOA_BASE 	0x40010800
#define GPIOB_BASE 	0x40010C00
#define GPIOC_BASE 	0x40011000
#define GPIOD_BASE 	0x40011400
#define GPIOE_BASE 	0x40011800
#define GPIOF_BASE 	0x40011C00
#define GPIOG_BASE 	0x40012000
#define EXTI_BASE  	0x40010400
#define AFIO_BASE  	0x40010000
#define USART1_BASE	0x40013800
#define USART2_BASE 0x40004400
#define USART3_BASE 0x40004800
#define SPI1_BASE	0x40013000
#define TIMER1_BASE 0x40012C00
#define TIMER2_BASE 0x40000000
#define TIMER3_BASE 0x40000400
#define TIMER4_BASE 0x40000800

#define SysTick_BASE  0xE000E010
#define NVIC_BASE 	0xE000E100
#define NVIC_ISER0 *((vusint32_t *) (NVIC_BASE+0x00))
#define NVIC_ISER1 *((vusint32_t *) (NVIC_BASE+0x04))
#define NVIC_ISER2 *((vusint32_t *) (NVIC_BASE+0x08))
#define NVIC_ICER0 *((vusint32_t *) (NVIC_BASE+0x080))
#define NVIC_ICER1 *((vusint32_t *) (NVIC_BASE+0x084))
#define NVIC_ICER2 *((vusint32_t *) (NVIC_BASE+0x088))

#define STK_LOAD *((vusint32_t *) (SysTick_BASE+0x04))
#define STK_VALUE *((vusint32_t *) (SysTick_BASE+0x04))
#define STK_CTRL *((vusint32_t * )(SysTick_BASE+0x00))

//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral register:
//-*-*-*-*-*-*-*-*-*-*-*
typedef struct {
	vusint32_t CRL;
	vusint32_t CRH;
	vusint32_t IDR;
	vusint32_t ODR;
	vusint32_t BSRR;
	vusint32_t BRR;
	vusint32_t LCKR;
}GPIOx_REG;
typedef struct {
	vusint32_t EVCR;
	vusint32_t MAPR;
	vusint32_t EXTICR[4];
	usint32_t RESERVED;
	vusint32_t MAPR2;
}AFIOx_REG;
typedef struct {
	vusint32_t IMR;
	vusint32_t EMR;
	vusint32_t RTSR;
	vusint32_t FTSR;
	vusint32_t SWIER;
	vusint32_t PR;
}EXTI_REG;
typedef struct{
	vusint32_t CR;
	vusint32_t CFGR;
	vusint32_t CIR;
	vusint32_t APB2RSTR;
	vusint32_t APB1RSTR;
	vusint32_t AHBENR;
	vusint32_t APB2ENR;
	vusint32_t APB1ENR;
	vusint32_t BDCR;
	vusint32_t CSR;
	vusint32_t AHBSTR;
	vusint32_t CFGR2;
}RCC_REG;
typedef struct{
	vusint32_t SR;
	vusint32_t DR;
	vusint32_t BRR;
	vusint32_t CR1;
	vusint32_t CR2;
	vusint32_t CR3;
	vusint32_t GTPR;

}USART_REG;
typedef union{
	vusint32_t ALL_REG;
	struct 	CR1_BITS{
		vusint32_t CPHA:1;
		vusint32_t CPOL:1;
		vusint32_t MSTR:1;
		vusint32_t BR:3;
		vusint32_t SPE:1;
		vusint32_t LSBFIRST:1;
		vusint32_t SSI:1;
		vusint32_t SSM:1;
		vusint32_t RXONLY:1;
		vusint32_t DFF:1;
		vusint32_t CRCNEXT:1;
		vusint32_t CRCEN:1;
		vusint32_t BIDIOE:1;
		vusint32_t BIDIMODE:1;
		//		vusint32_t Reserved:16;
	}Bit_Name;
}CR1;
typedef union{
	vusint32_t ALL_REG;
	struct 	CR2_BITS{
		vusint32_t RXDMAEN:1;
		vusint32_t TXDMAEN:1;
		vusint32_t SSOE:1;
		vusint32_t Reserved:2;
		vusint32_t ERRIE:1;
		vusint32_t RXNEIE:1;
		vusint32_t TXEIE:1;
		//		vusint32_t Reserved1:24;

	}Bit_Name;
}CR2;
typedef union{
	vusint32_t ALL_REG;
	struct 	SR_BITS{
		vusint32_t RXNE:1;
		vusint32_t TXE:1;
		vusint32_t CHSIDE:1;
		vusint32_t UDR:1;
		vusint32_t CRCERR:1;
		vusint32_t MODF:1;
		vusint32_t OVR:1;
		vusint32_t BSY:1;
		//		vusint32_t Reserved:24;

	}Bit_Name;
}SR;
typedef union{
	vusint32_t ALL_REG;
	struct 	DR_BITS{
		vusint32_t DR0:1;
		vusint32_t DR1:1;
		vusint32_t DR2:1;
		vusint32_t DR3:1;
		vusint32_t DR4:1;
		vusint32_t DR5:1;
		vusint32_t DR6:1;
		vusint32_t DR7:1;
		vusint32_t DR8:1;
		vusint32_t DR9:1;
		vusint32_t DR10:1;
		vusint32_t DR11:1;
		vusint32_t DR12:1;
		vusint32_t DR13:1;
		vusint32_t DR14:1;
		vusint32_t DR15:1;
		//		vusint32_t Reserved:16;
	}Bit_Name;
}DR;
typedef struct {
	volatile CR1 SPI_CR1;
	volatile CR2 SPI_CR2;
	volatile SR SPI_SR;
	volatile DR DR_reg;
	vusint32_t CRCPR;
	vusint32_t RXCRCR;
	vusint32_t TXCRCR;
	vusint32_t I2SCFGR;
	vusint32_t I2SPR;

}SPI_Reg;
/////////////////////////I2C////////////////////////////
typedef union{
	vusint32_t ALL_REG;
	struct 	I2C_CR1_BITS{
		vusint32_t PE:1;
		vusint32_t SMBUS:1;
		vusint32_t :1;
		vusint32_t SMBTYPE:1;
		vusint32_t ENARP:1;
		vusint32_t ENPEC:1;
		vusint32_t ENGC:1;
		vusint32_t NOSTRETCH:1;
		vusint32_t START:1;
		vusint32_t STOP:1;
		vusint32_t ACK:1;
		vusint32_t POS:1;
		vusint32_t PEC:1;
		vusint32_t ALERT:1;
		vusint32_t :1;
		vusint32_t SWRST:1;
		//		vusint32_t Reserved:16;
	}Bit_Name;
}I2C_CR1;
//////////////////////
typedef union{
	vusint32_t ALL_REG;
	struct 	I2C_CR2_BITS{
		vusint32_t FREQ:6;
		vusint32_t :2;
		vusint32_t ITERREN:1;
		vusint32_t ITEVTEN:1;
		vusint32_t ITBUFEN:1;
		vusint32_t DMAEN:1;
		vusint32_t LAST:1;

	}Bit_Name;
}I2C_CR2;
////////////////////////////////
typedef union{
	vusint32_t ALL_REG;
	struct 	I2C_OAR1_BITS{
		vusint32_t ADD0:1;
		vusint32_t ADD:7;
		vusint32_t ADD_10_BIT:2;
		vusint32_t :5;
		vusint32_t ADDMODE:1;

		//		vusint32_t Reserved:16;
	}Bit_Name;
}I2C_OAR1;
///////////////////////////////
typedef union{
	vusint32_t ALL_REG;
	struct 	I2C_OAR2_BITS{
		vusint32_t ENDUAL:1;
		vusint32_t ADD2:7;

		//		vusint32_t Reserved:16;
	}Bit_Name;
}I2C_OAR2;
/////////////////////
typedef union{
	vusint32_t ALL_REG;
	struct 	I2C_DR_BITS{
		vusint32_t DR0:1;
		vusint32_t DR1:1;
		vusint32_t DR2:1;
		vusint32_t DR3:1;
		vusint32_t DR4:1;
		vusint32_t DR5:1;
		vusint32_t DR6:1;
		vusint32_t DR7:1;

		//		vusint32_t Reserved:16;
	}Bit_Name;
}I2C_DR;
////////////////////////////////////
typedef union{
	vusint32_t ALL_REG;
	struct 	I2C_SR1_BITS{
		vusint32_t SB:1;
		vusint32_t ADDR:1;
		vusint32_t BTF:1;
		vusint32_t ADD10:1;
		vusint32_t STOPF:1;
		vusint32_t :1;
		vusint32_t RxNE:1;
		vusint32_t TxE:1;
		vusint32_t BERR:1;
		vusint32_t ARLO:1;
		vusint32_t AF:1;
		vusint32_t OVR:1;
		vusint32_t PECERR:1;
		vusint32_t :1;
		vusint32_t TIMEOUT:1;
		vusint32_t SMBALERT:1;
		//		vusint32_t Reserved:16;
	}Bit_Name;
}I2C_SR1;
///////////////////////////////
typedef union{
	vusint32_t ALL_REG;
	struct 	I2C_SR2_BITS{
		vusint32_t MSL:1;
		vusint32_t BUSY:1;
		vusint32_t TRA:1;
		vusint32_t :1;
		vusint32_t GENCALL:1;
		vusint32_t SMBDEFAULT:1;
		vusint32_t SMBHOST:1;
		vusint32_t DUALF:1;
		vusint32_t PEC:8;

		//		vusint32_t Reserved:16;
	}Bit_Name;
}I2C_SR2;
///////////////////////////
typedef union{
	vusint32_t ALL_REG;
	struct 	I2C_CCR_BITS{
		vusint32_t CCR:12;
		vusint32_t :2;
		vusint32_t DUTY:1;
		vusint32_t F_S:1;

		//		vusint32_t Reserved:16;
	}Bit_Name;
}I2C_CCR;
/////////////////////////////
typedef union{
	vusint32_t ALL_REG;
	struct 	I2C_TRISE_BITS{
		vusint32_t TRISE:6;

		//		vusint32_t Reserved:16;
	}Bit_Name;
}I2C_TRISE;
//////////////// I2C STRUCT //////////////////
typedef struct {
	volatile I2C_CR1 CR1;
	volatile I2C_CR2 CR2;
	volatile I2C_OAR1 OAR1;
	volatile I2C_OAR2 OAR2;
	volatile I2C_DR DR;
	volatile I2C_SR1 SR1;
	volatile I2C_SR2 SR2;
	volatile I2C_CCR CCR;
	volatile I2C_TRISE TRISE;
}I2C_REG;


////////////// TIMERS 1&8 /////////////////
typedef union {
	vusint32_t ALL_BITS;
	struct AD_TIMx_CR1_BITS{
		vusint32_t CEN:1;
		vusint32_t UDIS:1;
		vusint32_t URS:1;
		vusint32_t OPM:1;
		vusint32_t DIR:1;
		vusint32_t CMS:2;
		vusint32_t ARPE:1;
		vusint32_t CKD:2;
		vusint32_t :22;



	}BIT_NAME;
}AD_TIMx_CR1;
typedef union {
	vusint32_t ALL_BITS;
	struct AD_TIMx_CR2_BITS{
		vusint32_t CCPC:1;
		vusint32_t :1;
		vusint32_t CCUS:1;
		vusint32_t CCDS:1;
		vusint32_t MMS:3;
		vusint32_t TI1S:1;
		vusint32_t OIS1:1;
		vusint32_t OIS1N:1;
		vusint32_t OIS2:1;
		vusint32_t OIS2N:1;
		vusint32_t OIS3:1;
		vusint32_t OIS3N:1;
		vusint32_t OIS4:1;
		vusint32_t :17;



	}BIT_NAME;
}AD_TIMx_CR2;
typedef union {
	vusint32_t ALL_BITS;
	struct SMCR_BITS{
		vusint32_t SMS:3;
		vusint32_t :1;
		vusint32_t TS:3;
		vusint32_t MSM:1;
		vusint32_t ETF:4;
		vusint32_t ETPS:2;
		vusint32_t ECE:1;
		vusint32_t ETP:1;
		vusint32_t :16;



	}BIT_NAME;
}AD_TIMx_SMCR;
typedef union {
	vusint32_t ALL_BITS;
	struct DIER_BITS{
		vusint32_t UIE:1;
		vusint32_t CC1IE:1;
		vusint32_t CC2IE:1;
		vusint32_t CC3IE:1;
		vusint32_t CC4IE:1;
		vusint32_t COMIE:1;
		vusint32_t TIE:1;
		vusint32_t BIE:1;
		vusint32_t UDE:1;
		vusint32_t CC1DE:1;
		vusint32_t CC2DE:1;
		vusint32_t CC3DE:1;
		vusint32_t CC4DE:1;
		vusint32_t COMDE:1;
		vusint32_t TDE:1;
		vusint32_t :17;



	}BIT_NAME;
}AD_TIMx_DIER;
typedef union {
	vusint32_t ALL_BITS;
	struct AD_TIMx_SR_BITS{
		vusint32_t UIF:1;
		vusint32_t CC1IF:1;
		vusint32_t CC2IF:1;
		vusint32_t CC3IF:1;
		vusint32_t CC4IF:1;
		vusint32_t COMIF:1;
		vusint32_t TIF:1;
		vusint32_t BIF:1;
		vusint32_t :1;
		vusint32_t CC1OF:1;
		vusint32_t CC2OF:1;
		vusint32_t CC3OF:1;
		vusint32_t CC4OF:1;
		vusint32_t :19;



	}BIT_NAME;
}AD_TIMx_SR;

typedef union {
	vusint32_t ALL_BITS;
	struct EGR_BITS{
		vusint32_t UG:1;
		vusint32_t CC1G:1;
		vusint32_t CC2G:1;
		vusint32_t CC3G:1;
		vusint32_t CC4G:1;
		vusint32_t COMG:1;
		vusint32_t TG:1;
		vusint32_t BG:1;
		vusint32_t :24;



	}BIT_NAME;
}AD_TIMx_EGR;
typedef union {
	vusint32_t ALL_BITS;
	/////////////////////////////////////  There is two REG share the same mem location (Compare_mode_BITS+input_Capture_BITS)
	struct CCMR1_Compare_mode_BITS{
		vusint32_t CC1S:2;
		vusint32_t OC1FE:1;
		vusint32_t OC1PE:1;
		vusint32_t OC1M:3;
		vusint32_t OC1CE:1;
		vusint32_t CC2S:2;
		vusint32_t OC2FE:1;
		vusint32_t OC2PE:1;
		vusint32_t OC2M:3;
		vusint32_t OC2CE:1;
		vusint32_t :16;



	}Compare_BIT_NAME;
	////////////////////////////////
	struct CCMR1_input_Capture_BITS{
		vusint32_t CC1S:2;
		vusint32_t IC1PSC:2;
		vusint32_t IC1F:4;
		vusint32_t CC2S:2;
		vusint32_t IC2PSC:2;
		vusint32_t IC2F:4;
		vusint32_t :16;



	}input_NAME;
}AD_TIMx_CCMR1;
typedef union {
	vusint32_t ALL_BITS;
	/////////////////////////////////////  There is two REG share the same mem location (Compare_mode_BITS+input_Capture_BITS)
	struct CCMR2_Compare_mode_BITS{
		vusint32_t CC3S:2;
		vusint32_t OC3FE:1;
		vusint32_t OC3PE:1;
		vusint32_t OC3M:3;
		vusint32_t OC3CE:1;
		vusint32_t CC4S:2;
		vusint32_t OC4FE:1;
		vusint32_t OC4PE:1;
		vusint32_t OC4M:3;
		vusint32_t O24CE:1;
		vusint32_t :16;



	}Compare_BIT_NAME;
	////////////////////////////////
	struct CCMR2_input_Capture_BITS{
		vusint32_t CC3S:2;
		vusint32_t IC3PSC:2;
		vusint32_t IC3F:4;
		vusint32_t CC4S:2;
		vusint32_t IC4PSC:2;
		vusint32_t IC4F:4;
		vusint32_t :16;



	}input_NAME;
}AD_TIMx_CCMR2;
typedef union {
	vusint32_t ALL_BITS;
	struct CCER_BITS{
		vusint32_t CC1E:1;
		vusint32_t CC1P:1;
		vusint32_t CC1NE:1;
		vusint32_t CC1NP:1;
		vusint32_t CC2E:1;
		vusint32_t CC2P:1;
		vusint32_t CC2NE:1;
		vusint32_t CC2NP:1;
		//
		vusint32_t CC3E:1;
		vusint32_t CC3P:1;
		vusint32_t CC3NE:1;
		vusint32_t CC3NP:1;
		vusint32_t CC4E:1;
		vusint32_t CC4P:1;

		vusint32_t :18;



	}BIT_NAME;
}AD_TIMx_CCER;
typedef union {
	vusint32_t ALL_BITS;
	struct BDTR_BITS{
		vusint32_t DT:8;
		vusint32_t LOCK:2;
		vusint32_t OSSI:1;
		vusint32_t OSSR:1;
		vusint32_t BKE:1;
		vusint32_t BKP:1;
		vusint32_t AOE:1;
		vusint32_t MOE:1;
		vusint32_t :16;



	}BIT_NAME;
}AD_TIMx_BDTR;
typedef union {
	vusint32_t ALL_BITS;
	struct DCR_BITS{
		vusint32_t DBA:5;
		vusint32_t :3;
		vusint32_t DBL:5;
		vusint32_t :13;

	}BIT_NAME;
}AD_TIMx_DCR;
////////////////////////////////////////


typedef struct{
	volatile	AD_TIMx_CR1 	CR1;
	volatile	AD_TIMx_CR2 	CR2;
	volatile	AD_TIMx_SMCR 	SMCR;
	volatile	AD_TIMx_DIER 	DIER;
	volatile	AD_TIMx_SR 	SR;
	volatile	AD_TIMx_EGR 	EGR;
	volatile	AD_TIMx_CCMR1 	CCMR1;
	volatile	AD_TIMx_CCMR2 	CCMR2;
	volatile	AD_TIMx_CCER 	CCER;
	volatile	uint32_t 	CNT;
	volatile	uint32_t 	PSC;
	volatile	uint32_t 	ARR;
	volatile	uint32_t 	RCR;
	volatile	uint32_t 	CCR1;
	volatile	uint32_t 	CCR2;
	volatile	uint32_t 	CCR3;
	volatile	uint32_t 	CCR4;
	volatile	AD_TIMx_BDTR 	BDTR;
	volatile	AD_TIMx_DCR 	DCR;
	volatile	uint32_t 	DMAR;








}TIM1_8_REG;



///////////////*****************GP_TIMERs****************///////////////////////
/*@GP_TIMx_CR1 specify the CR1 reg from datasheet*/

typedef union {
	vusint32_t ALL_BITS;
	struct GP_TIMx_CR1_BITS{
		vusint32_t CEN:1;
		vusint32_t UDIS:1;
		vusint32_t URS:1;
		vusint32_t OPM:1;
		vusint32_t DIR:1;
		vusint32_t CMS:2;
		vusint32_t ARPE:1;
		vusint32_t CKD:2;
		vusint32_t :22;



	}BIT_NAME;
}GP_TIMx_CR1;
/*@GP_TIMx_CR2 specify the CR2 reg from datasheet*/

typedef union {
	vusint32_t ALL_BITS;
	struct GP_TIMx_CR2_BITS{
		vusint32_t :3;
		vusint32_t CCDS:1;
		vusint32_t MMS:3;
		vusint32_t TI1S:1;
		vusint32_t :24;



	}BIT_NAME;
}GP_TIMx_CR2;
/*@GP_TIMx_SMCR specify the SMCR reg from datasheet*/

typedef union {
	vusint32_t ALL_BITS;
	struct GP_TIMx_SMCR_BITS{
		vusint32_t SMS:3;
		vusint32_t :1;
		vusint32_t TS:3;
		vusint32_t MSM:1;
		vusint32_t ETF:4;
		vusint32_t ETPS:2;
		vusint32_t ECE:1;
		vusint32_t ETP:1;
		vusint32_t :16;



	}BIT_NAME;
}GP_TIMx_SMCR;
/*@GP_TIMx_DIER specify the DIER reg from datasheet*/

typedef union {
	vusint32_t ALL_BITS;
	struct GP_TIMx_DIER_BITS{
		vusint32_t UIE:1;
		vusint32_t CC1IE:1;
		vusint32_t CC2IE:1;
		vusint32_t CC3IE:1;
		vusint32_t CC4IE:1;
		vusint32_t :1;
		vusint32_t TIE:1;
		vusint32_t :1;
		vusint32_t UDE:1;
		vusint32_t CC1DE:1;
		vusint32_t CC2DE:1;
		vusint32_t CC3DE:1;
		vusint32_t CC4DE:1;
		vusint32_t COMDE:1;
		vusint32_t TDE:1;
		vusint32_t :17;



	}BIT_NAME;
}GP_TIMx_DIER;

/*@GP_TIMx_SR specify the SR reg from datasheet*/

typedef union {
	vusint32_t ALL_BITS;
	struct GP_TIMx_SR_BITS{
		vusint32_t UIF:1;
		vusint32_t CC1IF:1;
		vusint32_t CC2IF:1;
		vusint32_t CC3IF:1;
		vusint32_t CC4IF:1;
		vusint32_t :1;
		vusint32_t TIF:1;
		vusint32_t :2;
		vusint32_t CC1OF:1;
		vusint32_t CC2OF:1;
		vusint32_t CC3OF:1;
		vusint32_t CC4OF:1;
		vusint32_t :19;



	}BIT_NAME;
}GP_TIMx_SR;
/*@GP_TIMx_DIER specify the DIER reg from datasheet*/

typedef union {
	vusint32_t ALL_BITS;
	struct GP_TIMx_EGR_BITS{
		vusint32_t UG:1;
		vusint32_t CC1G:1;
		vusint32_t CC2G:1;
		vusint32_t CC3G:1;
		vusint32_t CC4G:1;
		vusint32_t :1;
		vusint32_t TG:1;
		vusint32_t :25;



	}BIT_NAME;
}GP_TIMx_EGR;


typedef union {
	vusint32_t ALL_BITS;
	/////////////////////////////////////  There is two REG share the same mem location (Compare_mode_BITS+input_Capture_BITS)
	struct GP_TIMx_CCMR1_Compare_mode_BITS{
		vusint32_t CC1S:2;
		vusint32_t OC1FE:1;
		vusint32_t OC1PE:1;
		vusint32_t OC1M:3;
		vusint32_t OC1CE:1;
		vusint32_t CC2S:2;
		vusint32_t OC2FE:1;
		vusint32_t OC2PE:1;
		vusint32_t OC2M:3;
		vusint32_t OC2CE:1;
		vusint32_t :16;



	}Compare_BIT_NAME;
	////////////////////////////////
	struct GP_TIMx_CCMR1_input_Capture_BITS{
		vusint32_t CC1S:2;
		vusint32_t IC1PSC:2;
		vusint32_t IC1F:4;
		vusint32_t CC2S:2;
		vusint32_t IC2PSC:2;
		vusint32_t IC2F:4;
		vusint32_t :16;



	}input_NAME;
}GP_TIMx_CCMR1;
typedef union {
	vusint32_t ALL_BITS;
	/////////////////////////////////////  There is two REG share the same mem location (Compare_mode_BITS+input_Capture_BITS)
	struct GP_TIMx_CCMR2_Compare_mode_BITS{
		vusint32_t CC3S:2;
		vusint32_t OC3FE:1;
		vusint32_t OC3PE:1;
		vusint32_t OC3M:3;
		vusint32_t OC3CE:1;
		vusint32_t CC4S:2;
		vusint32_t OC4FE:1;
		vusint32_t OC4PE:1;
		vusint32_t OC4M:3;
		vusint32_t O24CE:1;
		vusint32_t :16;



	}Compare_BIT_NAME;
	////////////////////////////////
	struct GP_TIMx_CCMR2_input_Capture_BITS{
		vusint32_t CC3S:2;
		vusint32_t IC3PSC:2;
		vusint32_t IC3F:4;
		vusint32_t CC4S:2;
		vusint32_t IC4PSC:2;
		vusint32_t IC4F:4;
		vusint32_t :16;



	}input_NAME;
}GP_TIMx_CCMR2;
typedef union {
	vusint32_t ALL_BITS;
	struct GP_TIMx_CCER_BITS{
		vusint32_t CC1E:1;
		vusint32_t CC1P:1;
		vusint32_t :2;
		vusint32_t CC2E:1;
		vusint32_t CC2P:1;
		vusint32_t :2;
		vusint32_t CC3E:1;
		vusint32_t CC3P:1;
		vusint32_t :2;
		vusint32_t CC4E:1;
		vusint32_t CC4P:1;

		vusint32_t :18;



	}BIT_NAME;
}GP_TIMx_CCER;
typedef union {
	vusint32_t ALL_BITS;
	struct GP_TIMx_DCR_BITS{
		vusint32_t DBA:5;
		vusint32_t :3;
		vusint32_t DBL:5;
		vusint32_t :13;

	}BIT_NAME;
}GP_TIMx_DCR;

////////////////////////////////////
typedef struct{
	volatile	GP_TIMx_CR1 	CR1;
	volatile	GP_TIMx_CR2 	CR2;
	volatile	GP_TIMx_SMCR 	SMCR;
	volatile	GP_TIMx_DIER 	DIER;
	volatile	GP_TIMx_SR 		SR;
	volatile	GP_TIMx_EGR 	EGR;
	volatile	GP_TIMx_CCMR1 	CCMR1;
	volatile	GP_TIMx_CCMR2 	CCMR2;
	volatile	GP_TIMx_CCER 	CCER;
	volatile	uint32_t 	CNT;
	volatile	uint32_t 	PSC;
	volatile	uint32_t 	ARR;
	volatile	uint32_t 	RCR;
	volatile	uint32_t 	CCR1;
	volatile	uint32_t 	CCR2;
	volatile	uint32_t 	CCR3;
	volatile	uint32_t 	CCR4;
	volatile	uint32_t 	Reserved;
	volatile	GP_TIMx_DCR 	DCR;
	volatile	uint32_t 	DMAR;








}GP_TIMx_REG;
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*
#define GPIOA		((GPIOx_REG *) GPIOA_BASE)
#define GPIOB		((GPIOx_REG *) GPIOB_BASE)
#define GPIOC		((GPIOx_REG *) GPIOC_BASE)
#define GPIOD		((GPIOx_REG *) GPIOD_BASE)
#define GPIOE		((GPIOx_REG *) GPIOE_BASE)
#define GPIOF		((GPIOx_REG *) GPIOF_BASE)
#define GPIOG		((GPIOx_REG *) GPIOG_BASE)
#define RCC   		((RCC_REG   *)  RCC_BASE )
#define EXTI_REG	((EXTI_REG  *)  EXTI_BASE)
#define AFIO		((AFIOx_REG *) AFIO_BASE )
#define USART1		((USART_REG *) USART1_BASE)
#define USART2		((USART_REG *) USART2_BASE)
#define USART3		((USART_REG *) USART3_BASE)
#define SPI1		((SPI_Reg *) SPI1_BASE)
#define SPI2		((SPI_Reg *) SPI2_BASE)
#define SPI3		((SPI_Reg *) SPI3_BASE)
#define I2C1		((I2C_config_t *) I2C1_BASE)
#define I2C2		((I2C_config_t *) I2C2_BASE)
#define TIM1		((TIM1_8_REG *)TIMER1_BASE)
#define TIM2		((GP_TIMx_REG *)TIMER2_BASE)
#define TIM3		((GP_TIMx_REG *)TIMER3_BASE)
#define TIM4		((GP_TIMx_REG *)TIMER4_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*


#endif /* INC_STM32F103X6_H_ */
