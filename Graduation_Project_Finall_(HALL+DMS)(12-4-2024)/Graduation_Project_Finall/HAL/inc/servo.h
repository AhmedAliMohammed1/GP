/*
 * servo.h
 *
 *  Created on: Nov 2, 2023
 *      Author: medoo
 */

#ifndef INC_SERVO_H_
#define INC_SERVO_H_
#include "GP_Timers.h"

void servo_degree(GP_TIMx_REG* TIMx,uint8_t degree,uint8_t position);

#endif /* INC_SERVO_H_ */
