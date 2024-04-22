/*
 * I2C.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Ahmed
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_
/* ***************** INC ********************/
#include "STM32F103x6.h"
#include <stdint.h>
#include "RCC.h"
#include "GPIO_Driver.h"
/* ***************** DEFINES ********************/
#define I2C1_EV_IRQ 31
#define I2C1_ER 	32
#define I2C2_EV 	33
#define I2C2_ER 	34
#define FREQ_EQ  (MCAL_GET_PCLCK1()/1000000)
#define CCR_EQ(F_SCL) (MCAL_GET_PCLCK1() /(2*(F_SCL)))
////////////////////
#define F_100Khz 100000UL
#define F_400Khz 400000
//////////////////////////

///****************EVENTS**////////////////
/* ***************** USER DATA TYPES ********************/
typedef enum{
	DISABLE,ENABLE
}Control_PE;
typedef enum{
	READ,WRITE
}Read_Control;
typedef enum{
	Sm,Fm
}F_S_Control;
typedef struct{
	uint8_t Primary_SLA;
	Control_PE  Dual_addressing_EN;
	uint8_t DUAL_SLA;

}SLAVE_ADD;
typedef struct{
	uint8_t RxNE:1;
	uint8_t TxE:1;
	uint8_t BERR:1;
	uint8_t ARLO:1;

}ERROR_check;
typedef struct{
	Control_PE EN;
	SLAVE_ADD SLA;
	F_S_Control FS;
	uint32_t F_SCL; // from @defines
	Control_PE interrupt_EN;
	void (* P_callback)(ERROR_check ERR);

}I2C_config_t;
typedef enum{
	 EV5,
	 EV6,
	 EV8_1,
	 EV8,
	 EV8_2

}EVENT_check;




/* ***************** APIs ********************/
void I2C_init(I2C_REG * I2Cx,I2C_config_t *I2C_config);
void I2C_Deinit(I2C_REG * I2Cx,I2C_config_t *I2C_config);

void I2C_Start_BIT(I2C_REG * I2Cx);
void I2C_Stop_BIT(I2C_REG * I2Cx);

void I2C_WriteByte(I2C_REG * I2Cx,uint8_t data);
void I2C_ReciveByte(I2C_REG * I2Cx,uint8_t *data);

void I2C_MASTER_Transsimte(I2C_REG * I2Cx,uint8_t address,uint8_t data,uint8_t len);
void I2C_MASTER_Recive(I2C_REG * I2Cx,uint8_t address,uint8_t *data);

uint16_t GET_flag_status(I2C_REG * I2Cx,EVENT_check EVENT);
void I2C_WriteADDRESS(I2C_REG * I2Cx,uint8_t DEV_add,Read_Control RW);
void I2C_REPATED_Start_BIT(I2C_REG * I2Cx);



#endif /* INC_I2C_H_ */
