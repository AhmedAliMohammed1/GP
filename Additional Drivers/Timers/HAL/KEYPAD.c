/*
 * KEYPAD.c
 *
 *  Created on: Aug 2, 2023
 *      Author: Ahmed
 */

#include "KEYPAD.h"
PIN_config PIN={R0,OUTPUT_PP,SPEED_2};
unsigned char ROWs[]={R0,R1,R2,R3};
unsigned char COL_s[]={C0,C1,C2};

void KEYPAD_init(){
	MCAL_GPIO_init(KEYPAD_PORT, &PIN);
	PIN.PIN_number=R1;	MCAL_GPIO_init(KEYPAD_PORT, &PIN);
	PIN.PIN_number=R2;	MCAL_GPIO_init(KEYPAD_PORT, &PIN);
	PIN.PIN_number=R3;	MCAL_GPIO_init(KEYPAD_PORT, &PIN);
	PIN.PIN_number=C0;
	PIN.MODE=INPUT_PU; MCAL_GPIO_init(KEYPAD_PORT, &PIN);
	PIN.PIN_number=C1; MCAL_GPIO_init(KEYPAD_PORT, &PIN);
	PIN.PIN_number=C2; MCAL_GPIO_init(KEYPAD_PORT, &PIN);
	MCAL_write_PORT(KEYPAD_PORT,0xFF);
}
unsigned char Get_Pressed_KEY(void){
	int i,j;
	for(i=0;i<Row_N;i++){

	MCAL_write_PIN(KEYPAD_PORT, ROWs[0], LOGIC_LOW);
	MCAL_write_PIN(KEYPAD_PORT, ROWs[1], LOGIC_LOW);
	MCAL_write_PIN(KEYPAD_PORT, ROWs[2], LOGIC_LOW);
	MCAL_write_PIN(KEYPAD_PORT, ROWs[3], LOGIC_LOW);
//			dms(200);
	MCAL_write_PIN(KEYPAD_PORT, ROWs[i], LOGIC_HIGH);
//	wait_ms(30);
	for(j=0;j<Col_N;j++){

		if(MCAL_Read_PIN(KEYPAD_PORT, COL_s[j])){
			while(MCAL_Read_PIN(KEYPAD_PORT, COL_s[j]));
			switch(i){
			case 0:
				if (j==0) return '*';
				if (j==1) return 0;
				if (j==2) return '#';
				break;
			case 1:
				if (j==0) return 7;
				if (j==1) return 8;
				if (j==2) return 9;

				break;
			case 2:
				if (j==0) return 4;
				if (j==1) return 5;
				if (j==2) return 6;
				break;
			case 3:
				if (j==0) return 1;
				if (j==1) return 2;
				if (j==2) return 3;
				break;
			default:
				break;
			}
		}
	}

	}
	return 'N';

}
