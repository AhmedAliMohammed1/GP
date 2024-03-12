/*
 * DMS.c
 *
 *  Created on: Mar 6, 2024
 *      Author: medoo
 */

#include "DMS.h"


void DMS_init(){
	PIN_config PINx={TOUCH1,INPUT_FI,0};
	MCAL_GPIO_init(DMS_PORT, &PINx);
	 PINx=(PIN_config){TOUCH2,INPUT_FI,0};
	MCAL_GPIO_init(DMS_PORT, &PINx);
	 PINx=(PIN_config){TOUCH3,INPUT_FI,0};
	MCAL_GPIO_init(DMS_PORT, &PINx);
	 PINx=(PIN_config){TOUCH4,INPUT_FI,0};
	MCAL_GPIO_init(DMS_PORT, &PINx);
}


uint8_t DMS_read(){
	if((MCAL_Read_PIN(DMS_PORT, TOUCH1)) || (MCAL_Read_PIN(DMS_PORT, TOUCH2)) ||(MCAL_Read_PIN(DMS_PORT, TOUCH3)) || (MCAL_Read_PIN(DMS_PORT, TOUCH4))){
		return 1;
	}
	return 0;
}
