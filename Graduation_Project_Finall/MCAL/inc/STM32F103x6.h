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
#define NULL (0)

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
#define CAN1_BASE 	0x40006400
#define ADC1_BASE	0x40012400
#define ADC2_BASE	0x40012800




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



/*****************CAN******************/



/*****************CAN_MCR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_MCR_Bit_Name{
		volatile uint32_t INRQ:1;
		volatile uint32_t SLEEP:1;
		volatile uint32_t TXFP:1;
		volatile uint32_t RFLM:1;
		volatile uint32_t NART:1;
		volatile uint32_t AWUM:1;
		volatile uint32_t ABOM:1;
		volatile uint32_t TTCM:1;
		volatile uint32_t Reserved:7;
		volatile uint32_t RESET:1;
		volatile uint32_t DBF:1;
	}Bit_Name;
}CAN_MCR;
/*****************CAN_MSR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_MSR_Bit_Name{
		volatile uint32_t INAK:1;
		volatile uint32_t SLAK:1;
		volatile uint32_t ERRI:1;
		volatile uint32_t WKUI:1;
		volatile uint32_t SLAKI:1;
		volatile uint32_t Reserved:3;
		volatile uint32_t TXM:1;
		volatile uint32_t RXM:1;
		volatile uint32_t RX:1;

	}Bit_Name;
}CAN_MSR;
/*****************CAN_TSR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_TSR_Bit_Name{
		volatile uint32_t RQCP0:1;
		volatile uint32_t TXOK0:1;
		volatile uint32_t ALST0:1;
		volatile uint32_t TERR0:1;
		volatile uint32_t :3;
		volatile uint32_t ABRQ0:1;
		volatile uint32_t RQCP1:1;
		volatile uint32_t TXOK1:1;
		volatile uint32_t ALST1:1;
		volatile uint32_t TERR1:1;
		volatile uint32_t :3;
		volatile uint32_t ABRQ1:1;
		volatile uint32_t RQCP2:1;
		volatile uint32_t TXOK2:1;
		volatile uint32_t ALST2:1;
		volatile uint32_t TERR2:1;
		volatile uint32_t :3;
		volatile uint32_t ABRQ2:1;
		volatile uint32_t CODE:2;
		volatile uint32_t TME:3;
		volatile uint32_t LOW:3;
	}Bit_Name;
}CAN_TSR;
/*****************CAN_RF0R******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_RF0R_Bit_Name{
		volatile uint32_t FMP0:2;
		volatile uint32_t :1;
		volatile uint32_t FULL0:1;
		volatile uint32_t FOVR0:1;
		volatile uint32_t RFOM0:1;
	}Bit_Name;
}CAN_RF0R;
/*****************CAN_RF1R******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_RF1R_Bit_Name{
		volatile uint32_t FMP1:2;
		volatile uint32_t :1;
		volatile uint32_t FULL1:1;
		volatile uint32_t FOVR1:1;
		volatile uint32_t RFOM1:1;
	}Bit_Name;
}CAN_RF1R;
/*****************CAN_IER******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_IER_Bit_Name{
		volatile uint32_t TMEIE:1;
		volatile uint32_t FMPIE0:1;
		volatile uint32_t FFIE0:1;
		volatile uint32_t FOVIE0:1;
		volatile uint32_t FMPIE1:1;
		volatile uint32_t FFIE1:1;
		volatile uint32_t FOVIE1:1;
		volatile uint32_t :1;
		volatile uint32_t EWGIE:1;
		volatile uint32_t EPVIE:1;
		volatile uint32_t BOFIE:1;
		volatile uint32_t LECIE:1;
		volatile uint32_t :3;
		volatile uint32_t ERRIE:1;
		volatile uint32_t WKUIE:1;
		volatile uint32_t SLKIE:1;

	}Bit_Name;
}CAN_IER;
/*****************CAN_ESR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_ESR_Bit_Name{
		volatile uint32_t EWGF:1;
		volatile uint32_t EPVF:1;
		volatile uint32_t BOFF:1;
		volatile uint32_t :1;
		volatile uint32_t LEC:3;
		volatile uint32_t :9;
		volatile uint32_t TEC:8;
		volatile uint32_t REC:8;
	}Bit_Name;
}CAN_ESR;
/*****************CAN_BTR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_BTR_Bit_Name{
		volatile uint32_t BRP:10;
		volatile uint32_t :6;
		volatile uint32_t TS1:4;
		volatile uint32_t TS2:3;
		volatile uint32_t :1;
		volatile uint32_t SJW:2;
		volatile uint32_t :4;
		volatile uint32_t LBKM:1;
		volatile uint32_t SILM:1;

	}Bit_Name;
}CAN_BTR;
/*****************CAN_TIxR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_TIxR_Bit_Name{
		volatile uint32_t TXRQ:1;
		volatile uint32_t RTR:1;
		volatile uint32_t IDE:1;
		volatile uint32_t EXID:18;
		volatile uint32_t STID:11;

	}Bit_Name;
}CAN_TIxR;
/*****************CAN_TDTxR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_TDTxR_Bit_Name{
		volatile uint32_t DLC:4;
		volatile uint32_t :4;
		volatile uint32_t TGT:1;
		volatile uint32_t :7;
		volatile uint32_t TIME:16;
	}Bit_Name;
}CAN_TDTxR;
/*****************CAN_TDLxR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_TDLxR_Bit_Name{
		volatile uint32_t DATA0:8;
		volatile uint32_t DATA1:8;
		volatile uint32_t DATA2:8;
		volatile uint32_t DATA3:8;
	}Bit_Name;
}CAN_TDLxR;
/*****************CAN_TDHxR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_TDHxR_Bit_Name{
		volatile uint32_t DATA4:8;
		volatile uint32_t DATA5:8;
		volatile uint32_t DATA6:8;
		volatile uint32_t DATA7:8;
	}Bit_Name;
}CAN_TDHxR;
/*****************CAN_RIxR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_RIxR_Bit_Name{
		volatile uint32_t :1;
		volatile uint32_t RTR:1;
		volatile uint32_t IDE:1;
		volatile uint32_t EXID:18;
		volatile uint32_t STID:11;
	}Bit_Name;
}CAN_RIxR;
/*****************CAN_RDTxR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_RDTxR_Bit_Name{
		volatile uint32_t DLC:4;
		volatile uint32_t :4;
		volatile uint32_t FMI:8;
		volatile uint32_t TIME:16;
	}Bit_Name;
}CAN_RDTxR;
/*****************CAN_RDLxR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_RDLxR_Bit_Name{
		volatile uint32_t DATA0:8;
		volatile uint32_t DATA1:8;
		volatile uint32_t DATA2:8;
		volatile uint32_t DATA3:8;
	}Bit_Name;
}CAN_RDLxR;
/*****************CAN_RDHxR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_RDHxR_Bit_Name{
		volatile uint32_t DATA4:8;
		volatile uint32_t DATA5:8;
		volatile uint32_t DATA6:8;
		volatile uint32_t DATA7:8;
	}Bit_Name;
}CAN_RDHxR;
/*****************CCAN_FMR******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_FMR_Bit_Name{
		volatile uint32_t FINIT:1;
		volatile uint32_t :7;
		volatile uint32_t CAN2SB:6;
	}Bit_Name;
}CAN_FMR;
/*****************CAN_FM1R******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_FM1R_Bit_Name{
		volatile uint32_t FBM:28;
	}Bit_Name;
}CAN_FM1R;
/*****************CAN_FS1R******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_FS1R_Bit_Name{
		volatile uint32_t FSC:28;
	}Bit_Name;
}CAN_FS1R;
/*****************CAN_FFA1R******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_FFA1R_Bit_Name{
		volatile uint32_t FFA:28;
	}Bit_Name;
}CAN_FFA1R;
/*****************CAN_FA1R******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_FA1R_Bit_Name{
		volatile uint32_t FACT:28;
	}Bit_Name;
}CAN_FA1R;
/*****************CAN_FxR1******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_FxR1_Bit_Name{
		volatile uint32_t FB:32;
	}Bit_Name;
}CAN_FxR1;
/*****************CAN_FxR2******************/

typedef union{
	volatile uint32_t ALL_Bits;
	struct CAN_FxR2_Bit_Name{
		volatile uint32_t FB:32;
	}Bit_Name;
}CAN_FxR2;
/*****************CAN_Final_Struct******************/
typedef struct{
	volatile CAN_MCR MCR;
	volatile CAN_MSR MSR;
	volatile CAN_TSR TSR;
	volatile CAN_RF0R RF0R;
	volatile CAN_RF1R RF1R;
	volatile CAN_IER  IER;
	volatile CAN_ESR ESR;
	volatile CAN_BTR BTR;
	//0x020- 0x17F Reserved
	volatile uint64_t  Reserved1;
	volatile uint64_t  Reserved2;
	volatile uint64_t  Reserved3;
	volatile uint64_t  Reserved4;
	volatile uint64_t  Reserved5;
	volatile uint64_t  Reserved6;
	volatile uint64_t  Reserved7;
	volatile uint64_t  Reserved8;
	volatile uint64_t  Reserved9;
	volatile uint64_t  Reserved10;
	volatile uint64_t  Reserved11;
	volatile uint64_t  Reserved12;
	volatile uint64_t  Reserved13;
	volatile uint64_t  Reserved14;
	volatile uint64_t  Reserved15;
	volatile uint64_t  Reserved16;
	volatile uint64_t  Reserved17;
	volatile uint64_t  Reserved18;
	volatile uint64_t  Reserved19;
	volatile uint64_t  Reserved20;
	volatile uint64_t  Reserved21;
	volatile uint64_t  Reserved22;
	volatile uint64_t  Reserved23;
	volatile uint64_t  Reserved24;
	volatile uint64_t  Reserved25;
	volatile uint64_t  Reserved26;
	volatile uint64_t  Reserved27;
	volatile uint64_t  Reserved28;
	volatile uint64_t  Reserved29;
	volatile uint64_t  Reserved30;
	volatile uint64_t  Reserved31;
	volatile uint64_t  Reserved32;
	volatile uint64_t  Reserved33;
	volatile uint64_t  Reserved34;
	volatile uint64_t  Reserved35;
	volatile uint64_t  Reserved36;
	volatile uint64_t  Reserved37;
	volatile uint64_t  Reserved38;
	volatile uint64_t  Reserved39;
	volatile uint64_t  Reserved40;
	volatile uint64_t  Reserved41;
	volatile uint64_t  Reserved42;
	volatile uint64_t  Reserved43;
	volatile uint64_t  Reserved44;
	// 0x180 CAN_TI0R
	// index 0
	volatile CAN_TIxR TI0R;
	volatile CAN_TDTxR TDT0R;
	volatile CAN_TDLxR TDL0R;
	volatile CAN_TDHxR TDH0R;
	// index 1
	volatile CAN_TIxR TI1R;
	volatile CAN_TDTxR TDT1R;
	volatile CAN_TDLxR TDL1R;
	volatile CAN_TDHxR TDH1R;
	// index 2
	volatile CAN_TIxR TI2R;
	volatile CAN_TDTxR TDT2R;
	volatile CAN_TDLxR TDL2R;
	volatile CAN_TDHxR TDH2R;
	// 0x1B0 CAN_RI0R
	// index 0
	volatile CAN_RIxR RI0R;
	volatile CAN_RDTxR RDT0R;
	volatile CAN_RDLxR RDL0R;
	volatile CAN_RDHxR RDH0R;
	// index 1
	volatile CAN_RIxR RI1R;
	volatile CAN_RDTxR RDT1R;
	volatile CAN_RDLxR RDL1R;
	volatile CAN_RDHxR RDH1R;
	//0x1D0-0x1FF Reserved

	volatile uint64_t  Reserved45;
	volatile uint64_t  Reserved46;
	volatile uint64_t  Reserved47;
	volatile uint64_t  Reserved48;
	volatile uint64_t  Reserved49;
	volatile uint64_t  Reserved50;

	volatile CAN_FMR FMR;
	volatile CAN_FM1R FM1R;
	volatile uint32_t Reserved51;
	volatile CAN_FS1R FS1R;
	volatile uint32_t Reserved52;
	volatile CAN_FFA1R FFA1R;
	volatile uint32_t Reserved53;
	volatile CAN_FA1R FA1R;
	volatile uint32_t Reserved54;
	volatile uint64_t  Reserved55;
	volatile uint64_t  Reserved56;
	volatile uint64_t  Reserved57;
	// filter 0-13 [r1,r2]
	//index 0
	volatile CAN_FxR1 F0R1;
	volatile CAN_FxR2 F0R2;
	//index 1
	volatile CAN_FxR1 F1R1;
	volatile CAN_FxR2 F1R2;

	//index 2
	volatile CAN_FxR1 F2R1;
	volatile CAN_FxR2 F2R2;

	//index 3
	volatile CAN_FxR1 F3R1;
	volatile CAN_FxR2 F3R2;
	//index 4
	volatile CAN_FxR1 F4R1;
	volatile CAN_FxR2 F4R2;
	//index 5
	volatile CAN_FxR1 F5R1;
	volatile CAN_FxR2 F5R2;

	//index 6
	volatile CAN_FxR1 F6R1;
	volatile CAN_FxR2 F6R2;

	//index7
	volatile CAN_FxR1 F7R1;
	volatile CAN_FxR2 F7R2;

	//index 8
	volatile CAN_FxR1 F8R1;
	volatile CAN_FxR2 F8R2;
	//index 9
	volatile CAN_FxR1 F9R1;
	volatile CAN_FxR2 F9R2;

	//index 10
	volatile CAN_FxR1 F10R1;
	volatile CAN_FxR2 F10R2;
	//index 11
	volatile CAN_FxR1 F11R1;
	volatile CAN_FxR2 F11R2;
	//index 12
	volatile CAN_FxR1 F12R1;
	volatile CAN_FxR2 F12R2;
	//index 13
	volatile CAN_FxR1 F13R1;
	volatile CAN_FxR2 F13R2;













}CANx_REG;
/*****************ADC******************/

/*****************ADC_SR******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_SR_Bit_Name{
		volatile uint32_t AWD:1;
		volatile uint32_t EOC:1;
		volatile uint32_t JEOC:1;
		volatile uint32_t JSTRT:1;
		volatile uint32_t STRT:1;

	}Bit_Name;
}ADC_SR;
/*****************ADC_CR1******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_CR1_Bit_Name{
		volatile uint32_t AWDCH:5;
		volatile uint32_t EOCIE:1;
		volatile uint32_t AWDIE:1;
		volatile uint32_t JEOCIE:1;
		volatile uint32_t SCAN:1;
		volatile uint32_t AWDSGL:1;
		volatile uint32_t JAUTO:1;
		volatile uint32_t DISCEN:1;
		volatile uint32_t JDISCEN:1;
		volatile uint32_t DISCNUM:3;
		volatile uint32_t DUALMOD:4;
		volatile uint32_t :2;
		volatile uint32_t JAWDEN:1;
		volatile uint32_t AWDEN:1;



	}Bit_Name;
}ADC_CR1;
/*****************ADC_CR2******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_CR2_Bit_Name{
		volatile uint32_t ADON:1;
		volatile uint32_t CONT:1;
		volatile uint32_t CAL:1;
		volatile uint32_t RSTCAL:1;
		volatile uint32_t :4;
		volatile uint32_t DMA:1;
		volatile uint32_t :2;
		volatile uint32_t ALIGN:1;
		volatile uint32_t JEXTSEL:1;
		volatile uint32_t JEXTTRIG:1;
		volatile uint32_t :1;
		volatile uint32_t EXTSEL:3;
		volatile uint32_t EXTTRIG:1;
		volatile uint32_t JSWSTART:1;
		volatile uint32_t SWSTART:1;
		volatile uint32_t TSVREFE:1;


	}Bit_Name;
}ADC_CR2;
/*****************ADC_SMPR2******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_SMPR2_Bit_Name{
		volatile uint32_t SMP0:3;
		volatile uint32_t SMP1:3;
		volatile uint32_t SMP2:3;
		volatile uint32_t SMP3:3;
		volatile uint32_t SMP4:3;
		volatile uint32_t SMP5:3;
		volatile uint32_t SMP6:3;
		volatile uint32_t SMP7:3;
		volatile uint32_t SMP8:3;
		volatile uint32_t SMP9:3;



	}Bit_Name;
}ADC_SMPR2;
/*****************ADC_SMPR1******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_SMPR1_Bit_Name{
		volatile uint32_t SMP10:3;
		volatile uint32_t SMP11:3;
		volatile uint32_t SMP12:3;
		volatile uint32_t SMP13:3;
		volatile uint32_t SMP14:3;
		volatile uint32_t SMP15:3;
		volatile uint32_t SMP16:3;
		volatile uint32_t SMP17:3;
	}Bit_Name;
}ADC_SMPR1;

/*****************ADC_JOFR1******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_JOFR1_Bit_Name{
		volatile uint32_t JOFFSET1:12;

	}Bit_Name;
}ADC_JOFR1;

/*****************ADC_JOFR2******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_JOFR2_Bit_Name{
		volatile uint32_t JOFFSET2:12;

	}Bit_Name;
}ADC_JOFR2;
/*****************ADC_JOFR3******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_JOFR3_Bit_Name{
		volatile uint32_t JOFFSET3:12;

	}Bit_Name;
}ADC_JOFR3;
/*****************ADC_JOFR4******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_JOFR4_Bit_Name{
		volatile uint32_t JOFFSET4:12;

	}Bit_Name;
}ADC_JOFR4;

/*****************ADC_HTR******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_HTR_Bit_Name{
		volatile uint32_t HT:12;

	}Bit_Name;
}ADC_HTR;
/*****************ADC_LTR******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_LTR_Bit_Name{
		volatile uint32_t LT:12;

	}Bit_Name;
}ADC_LTR;

/*****************ADC_SQR1******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_SQR1_Bit_Name{
		volatile uint32_t SQ13:5;
		volatile uint32_t SQ14:5;
		volatile uint32_t SQ15:5;
		volatile uint32_t SQ16:5;
		volatile uint32_t L:4;

	}Bit_Name;
}ADC_SQR1;
/*****************ADC_SQR2******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_SQR2_Bit_Name{
		volatile uint32_t SQ7:5;
		volatile uint32_t SQ8:5;
		volatile uint32_t SQ9:5;
		volatile uint32_t SQ10:5;
		volatile uint32_t SQ11:5;
		volatile uint32_t SQ12:5;
	}Bit_Name;
}ADC_SQR2;
/*****************ADC_SQR3******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_SQR3_Bit_Name{
		volatile uint32_t SQ1:5;
		volatile uint32_t SQ2:5;
		volatile uint32_t SQ3:5;
		volatile uint32_t SQ4:5;
		volatile uint32_t SQ5:5;
		volatile uint32_t SQ6:5;
	}Bit_Name;
}ADC_SQR3;
/*****************ADC_JSQR******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_JSQR_Bit_Name{
		volatile uint32_t JSQ1:5;
		volatile uint32_t JSQ2:5;
		volatile uint32_t JSQ3:5;
		volatile uint32_t JSQ4:5;
		volatile uint32_t JL:4;

	}Bit_Name;
}ADC_JSQR;
/*****************ADC_JDR1******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_JDR1_Bit_Name{
		volatile uint32_t JDATA:16;

	}Bit_Name;
}ADC_JDR1;
/*****************ADC_JDR2******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_JDR2_Bit_Name{
		volatile uint32_t JDATA:16;

	}Bit_Name;
}ADC_JDR2;
/*****************ADC_JDR3******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_JDR3_Bit_Name{
		volatile uint32_t JDATA:16;

	}Bit_Name;
}ADC_JDR3;
/*****************ADC_JDR4******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_JDR4_Bit_Name{
		volatile uint32_t JDATA:16;

	}Bit_Name;
}ADC_JDR4;
/*****************ADC_DR******************/
typedef union{
	volatile uint32_t ALL_Bits;
	struct ADC_DR_Bit_Name{
		volatile uint32_t Regular_DATA:16;
		volatile uint32_t ADC2DATA:16;


	}Bit_Name;
}ADC_DR;


/*****************ADC_FINAL_STRUCT******************/
typedef struct{
	ADC_SR		SR;
	ADC_CR1		CR1;
	ADC_CR2		CR2;
	ADC_SMPR1	SMPR1;
	ADC_SMPR2	SMPR2;
	ADC_JOFR1	JOFR1 ;
	ADC_JOFR2	JOFR2;
	ADC_JOFR3	JOFR3;
	ADC_JOFR4	JOFR4;
	ADC_HTR		HTR;
	ADC_LTR		LTR;
	ADC_SQR1	SQR1;
	ADC_SQR2	SQR2;
	ADC_SQR3	SQR3;
	ADC_JSQR	JSQR;
	ADC_JDR1	JDR1;
	ADC_JDR2	JDR2;
	ADC_JDR3	JDR3;
	ADC_JDR4	JDR4;
	ADC_DR		DR;


}ADCx_REG;


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
#define CAN1		((CANx_REG *)(CAN1_BASE))
#define ADC1		((ADCx_REG*)ADC1_BASE)
#define ADC2		((ADCx_REG*)ADC2_BASE)

//-*-*-*-*-*-*-*-*-*-*-*-
//clock enable Macros:
//-*-*-*-*-*-*-*-*-*-*-*
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*


#endif /* INC_STM32F103X6_H_ */
