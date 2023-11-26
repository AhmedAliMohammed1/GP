/*
 * Sorce_Motor.c
 *
 *  Created on: Nov 12, 2021
 *      Author: Mostafa Mahmoud Elshiekh
 */

#include "Servo_Motor.h"





//B8 SERVO1
void Servo1_Entry_Gate_Init(void)
{
	/*SERVO MOTOR 1*/
	PIN_config PinCinfg;
	PinCinfg.PIN_number=PIN_8;
	PinCinfg.MODE = OUTPUT_PP;
	PinCinfg.SPEED =SPEED_10;
	MCAL_GPIO_init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo1_Entry_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo1 Enter gate up +90
		MCAL_write_PIN(GPIOB, PIN_8, 1);
		dus(500);
		MCAL_write_PIN(GPIOB, PIN_8, 0);
	}
	if(Direction==Down)
	{
		//servo1 Enter gate down -90
		MCAL_write_PIN(GPIOB, PIN_8, 1);
		dus(1488);
		MCAL_write_PIN(GPIOB, PIN_8, 0);
	}


}

//B9 SERVO2
void Servo2_Exit_Gate_Init(void)
{
	/*SERVO MOTOR 2*/
	PIN_config PinCinfg;
	PinCinfg.PIN_number=PIN_9;
	PinCinfg.MODE = OUTPUT_PP;
	PinCinfg.SPEED =SPEED_10;
	MCAL_GPIO_init(GPIOB, &PinCinfg);
}

//Direction Up or Down
void Servo2_Exit_Gate(uint8_t Direction)
{
	if(Direction == UP)
	{
		//servo2 Exit gate up +90
		PIN_config PinCinfg;
		MCAL_write_PIN(GPIOB, PIN_9, 1);
		dus(500);
		MCAL_write_PIN(GPIOB, PIN_9, 0);
	}

	if(Direction == Down)
	{
		//servo2 Exit gate down -90
		MCAL_write_PIN(GPIOB, PIN_9, 1);
		dus(1488);
		MCAL_write_PIN(GPIOB, PIN_9, 0);
	}

}
