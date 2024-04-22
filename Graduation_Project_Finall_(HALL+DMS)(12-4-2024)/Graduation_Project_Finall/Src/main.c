/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
/*#############################################################################################################################


#     ____ ____      _    ____  _   _   _  _____ ___ ___  _   _      ____  ____   ___      _ _____ ____ _____
#    / ___|  _ \    / \  |  _ \| | | | / \|_   _|_ _/ _ \| \ | |    |  _ \|  _ \ / _ \    | | ____/ ___|_   _|
#   | |  _| |_) |  / _ \ | | | | | | |/ _ \ | |  | | | | |  \| |    | |_) | |_) | | | |_  | |  _|| |     | |
#   | |_| |  _ <  / ___ \| |_| | |_| / ___ \| |  | | |_| | |\  |    |  __/|  _ <| |_| | |_| | |__| |___  | |
#    \____|_| \_\/_/   \_\____/ \___/_/   \_\_| |___\___/|_| \_|    |_|   |_| \_\\___/ \___/|_____\____| |_|

#    _____ ____ ___ _____ ____   ___  _   _ ___ ____ ____             ____ ____      _    _____ _____ _____ ____  ____
#   | ____/ ___/ _ \_   _|  _ \ / _ \| \ | |_ _/ ___/ ___|           / ___|  _ \    / \  |  ___|_   _| ____|  _ \/ ___|
#   |  _|| |  | | | || | | |_) | | | |  \| || | |   \___ \          | |   | |_) |  / _ \ | |_    | | |  _| | |_) \___ \
#   | |__| |__| |_| || | |  _ <| |_| | |\  || | |___ ___) |         | |___|  _ <  / ___ \|  _|   | | | |___|  _ < ___) |
#   |_____\____\___/ |_| |_| \_\\___/|_| \_|___\____|____/           \____|_| \_\/_/   \_\_|     |_| |_____|_| \_\____/


 */
#include "main.h"

/**================================================================
 * @Fn- Error_Handller
 * @brief - this fun shall to go in infinte loop if there is any thing wrong
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void Error_Handller(){
	while(1);
}

/**================================================================
 * @Fn- Sys_Clk_init
 * @brief - this fun shall to select the system clock accourding to datasheet
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void Sys_Clk_init(){
	// system speed 36Mhz
	RCC->CFGR |=(0b0101 <<18); //1111: PLL input clock x 16
	//	RCC->CFGR |=(0b100<<8); //100: HCLK divided by 2
	//	RCC->CFGR |=(1 <<16); //PLL entry clock source
	//	RCC->CR|=(1<<16); //HSE clock enable

	RCC->CR|=(1<<24); //PLL ON
	RCC->CFGR |=(0b10 <<0); //10: PLL selected as system clock


}





/********************* HALL EFFECT *****************/
/**================================================================
 * @Fn- HALL_EFFECT_TIMER_ENABLE
 * @brief - this fun shall to enable and disable global variable every 1 sec to control other handler
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void HALL_EFFECT_TIMER_ENABLE(){
	HALL_TIMER_EN ^=1;

}
/**================================================================
 * @Fn- HALL_EFFECT_HANDLLER
 * @brief - this fun shall to get final speed of vichle using hall effect sensor and HALL_EFFECT_TIMER_ENABLE to calulate the time
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note- this fun called every rissing edege from hall effect sensor
 * and update the HALL_EFFECT_KM_H every 1sec and caluclate it from HALL_EFFECT_N_PULSES
 */
void HALL_EFFECT_HANDLLER(){
	if(HALL_TIMER_EN){
		HALL_EFFECT_COUNTER++;
	}else{
		if(HALL_EFFECT_COUNTER){
			HALL_EFFECT_N_PULSES=HALL_EFFECT_COUNTER;
			HALL_EFFECT_RPS=((HALL_EFFECT_N_PULSES*HALL_EFFECT_TIME_CONVERSION)/HALL_EFFECT_REV_PER_PULSES);
			HALL_EFFECT_RPM=HALL_EFFECT_RPS *60;
			//		_TIM1_delay_ms(1);
			HALL_EFFECT_KM_H=((HALL_EFFECT_RPM*3*PI*MOTOR_SHAFT_RADIUS)/(2500000));
			_TIM1_delay_ms(1);
			HALL_EFFECT_COUNTER=0;
		}
	}

}
/**================================================================
 * @Fn- HALL_EFECT_Init
 * @brief - this fun shall to init the hall effect EXTI and the timer that calulate the time
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void HALL_EFECT_Init(){
	{
		GP_TIMERx_config GP_sitting={(MCAL_GET_H_CLCK()/1000) // to get tick every 1ms
				,1000 //to get interrupt every 1SEC
				,0,0,INT_EN,NORMAL,HALL_EFFECT_TIMER_ENABLE};
		GP_TIMERx_NORMAL_config GP_sitting_NORMA={Up};
		GP_TIMx_start(HALL_EFFECT_TIMx_instant,&GP_sitting,&GP_sitting_NORMA);
	}


	{
		EXTI_config_t HALL_EFFECT_SITTING={HALL_EFFECT_EXTI_LINE,RISEING,ENABLE,HALL_EFFECT_HANDLLER};
		MCAL_EXTI_init(&HALL_EFFECT_SITTING);

	}
}

/************DMS TASK*************/
/************DMS TASK*************/
/************DMS TASK*************/
/************DMS TASK*************/
/************DMS TASK*************/

/**================================================================
 * @Fn- DMS_Handller_TASK
 * @brief - this TASK shall to take the DMS sensors read and take action depending on it
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void DMS_Handller_TASK(){


	while(1){
		DMS_DATA=DMS_read();
		if(DMS_DATA==0){
			DMS__one_COUNTER=0;
			if(  DMS__zero_COUNTER==0){
				MCAL_USART_SendData(TSR_UART_INSTANT, DMS_TAKE_ACTION);
				DMS__zero_COUNTER++;
			}

		}else{
			DMS__zero_COUNTER=0;
			if(DMS__one_COUNTER==0){
				MCAL_USART_SendData(TSR_UART_INSTANT, DMS_Release_ACTION);
				DMS__one_COUNTER++;
			}
		}







	}
}



/***********************************/
/***********************************/
/***********************************/
/***********************************/
/***********************************/
/***********************************/














/************ACC TASK*************/
/************ACC TASK*************/
/************ACC TASK*************/
/************ACC TASK*************/
/************ACC TASK*************/





/**================================================================
 * @Fn- ACC_CONVERT_ADC_TODICMAL
 * @brief - this fun shall to ADC value and convert it to Digital value to send it to DAC
 * @param [in] - ACC_THROTTEL_ (ADC value)
 * @param [out] - ACC_DICIMAL_VAL (Disimal Value)
 * @retval -
 * Note-
 */


uint8_t ACC_CONVERT_ADC_TODICMAL(uint8_t ACC_THROTTEL_){
	uint8_t ACC_DICIMAL_VAL=((((ACC_THROTTEL_-ACC_TROTTEL_MIN_ADC_VAL)*(ACC_DAC_MAX_DECIMAL-ACC_DAC_MIN_DECIMAL))/(ACC_TROTTEL_Max_ADC_VAL-ACC_TROTTEL_MIN_ADC_VAL))+ACC_DAC_MIN_DECIMAL);

	return ACC_DICIMAL_VAL;

}
/**================================================================
 * @Fn- ACC_ADC_CallBack
 * @brief - this fun shall to read the ADC value if the ADC work with interrupt
 * @param [in] - void
 * @param [out] - void
 * @retval -
 * Note- the ADC must work as interrupt otherwise this fun will not work
 */
void ACC_ADC_CallBack(){
	ADC_read(ADC1,ACC_THROTTEL_CHx,&ACC_THROTTEL_DATA);

}
/**================================================================
 * @Fn- ACC_throtel_init
 * @brief - this fun shall to init the ACC( INIT ADC,ACC GPIO PIN)
 * @param [in] - void
 * @param [out] - void
 * @retval -
 * Note-
 */
void ACC_throtel_init(){
	ADC_Analog_WDG AWDG={0,0,0,0};
	ADC_CONFIG config={ACC_THROTTEL_CHx,ADC_Continuous_conversion,ADC_1_5_cycles,ADC_Polling,&AWDG,ACC_ADC_CallBack};
	ADC_init(ADC1,&config);
	//	ADC_interrupt_Enable(ADC1);
	PIN_config PINx={ACC_BOTTON_PIN,INPUT_PD,0};
	MCAL_GPIO_init(ACC_BOTTON_PORT, &PINx);

}
/**================================================================
 * @Fn- ACC_throtel_init
 * @brief - this fun shall to init the DAC
 * @param [in] - void
 * @param [out] - void
 * @retval -
 * Note-
 */
void ACC_DAC_init(){
	PIN_config PINx={ACC_DAC_0,OUTPUT_PP,SPEED_10};
	MCAL_GPIO_init(GPIOA, &PINx);
	PINx=(PIN_config){ACC_DAC_1,OUTPUT_PP,SPEED_10};
	MCAL_GPIO_init(GPIOB, &PINx);
	PINx=(PIN_config){ACC_DAC_2,OUTPUT_PP,SPEED_10};
	MCAL_GPIO_init(GPIOB, &PINx);
	PINx=(PIN_config){ACC_DAC_3,OUTPUT_PP,SPEED_10};
	MCAL_GPIO_init(GPIOB, &PINx);
	PINx=(PIN_config){ACC_DAC_4,OUTPUT_PP,SPEED_10};
	MCAL_GPIO_init(GPIOB, &PINx);
	PINx=(PIN_config){ACC_DAC_5,OUTPUT_PP,SPEED_10};
	MCAL_GPIO_init(GPIOB, &PINx);
	PINx=(PIN_config){ACC_DAC_6,OUTPUT_PP,SPEED_10};
	MCAL_GPIO_init(GPIOB, &PINx);
	PINx=(PIN_config){ACC_DAC_7,OUTPUT_PP,SPEED_10};
	MCAL_GPIO_init(GPIOB, &PINx);

}



/**================================================================
 * @Fn- ACC_throtel_init
 * @brief - this fun shall to send the data to the DAC to get the analog volt
 * @param [in] - decimal_val the disimal value
 * @param [out] - void
 * @retval -
 * Note- the DAC designed is 8-bit dac so the value should be between 0-255
 * and we need the volt not be less 0.8 so decimal_val sould be between 64-255
 */

void ACC_FROM_ADC_TO_DAC(uint16_t decimal_val){

	//	uint16_t PWM_V=(uint16_t)(((ADC_VAL-ACC_TROTTEL_MIN_ADC_VAL)*100)/(ACC_TROTTEL_Max_ADC_VAL_shifted));
	/*MY CLOCK IS 28Mhz so i the prescaler will be 27
	 * and i need to proudce and it will make tick every 1us and i need 3KHZ PWM so the ARR= will be 333.33
	 * */
	//	PWM_V=((PWM_V*35)/100);
	MCAL_write_PIN(GPIOA, ACC_DAC_0, ((decimal_val >>0) &1));
	MCAL_write_PIN(GPIOB, ACC_DAC_1, ((decimal_val >>1) &1));
	MCAL_write_PIN(GPIOB, ACC_DAC_2, ((decimal_val >>2) &1));
	MCAL_write_PIN(GPIOB, ACC_DAC_3, ((decimal_val >>3) &1));
	MCAL_write_PIN(GPIOB, ACC_DAC_4, ((decimal_val >>4) &1));
	MCAL_write_PIN(GPIOB, ACC_DAC_5, ((decimal_val >>5) &1));
	MCAL_write_PIN(GPIOB, ACC_DAC_6, ((decimal_val >>6) &1));
	MCAL_write_PIN(GPIOB, ACC_DAC_7, ((decimal_val >>7) &1));

}

/**================================================================
 * @Fn- ACC_Handller_TASK
 * @brief - this task shall to get the distance form luna lidar and start
 * change the state of the veichle
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void ACC_Handller_TASK(){
	while(1){

		//      ACC_AMP=500;
		if((LUNA_AMP>=100) && (LUNA_AMP<=65535) ){
			if(LUNA_dis ==0x00){
				if(GR_DMS_FLAG_send != DMS_EYES_CLOSED_FORCE_STOP)
					ACC_ACTION=ACC_CAR_GO;
				else
					ACC_ACTION=ACC_CAR_STOP;

			}else if((LUNA_dis <= ACC_distance_stop) ||(GR_DMS_FLAG_send == DMS_EYES_CLOSED_FORCE_STOP) ||((GR_DMS_FLAG_send ==DMS_EYES_CLOSED) && (DMS_DATA==0))){
				// here should send CAN fram to atmega to stop the motor
				ACC_ACTION=ACC_CAR_STOP;

			}else if((LUNA_dis > ACC_distance_stop) &&(LUNA_dis <ACC_distance_slowdown)){
				ACC_ACTION=ACC_CAR_SLOW_DOWN;


			}else{
				ACC_ACTION=ACC_CAR_GO;

			}


		}
		// if the Signal strength indicator not strong dequeue its disance value
		else{
			if(LUNA_dis ==0x00){
				if(GR_DMS_FLAG_send != DMS_EYES_CLOSED_FORCE_STOP)
					ACC_ACTION=ACC_CAR_GO;
				else
					ACC_ACTION=ACC_CAR_STOP;

			}
		}
	}
}




/**================================================================
 * @Fn- ACC_throttel_Handller_TASK
 * @brief - this task shall to SEND the volt to the motor drive
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note- ACC_DICIMAL_VAL is a global variable and update every 1ms from ACC_STATE_READ_TASK
 */

void ACC_throttel_Handller_TASK(){
	uint8_t ACC_counter=0;
	uint16_t ADC_SAVED=0;
	while(1){

		if(ACC_ST==ACC_ON){
			if(ACC_counter ==0){
				ADC_SAVED=ACC_CONVERT_ADC_TODICMAL(ACC_THROTTEL_DATA);
				ACC_counter++;
			}
			if(ADC_SAVED<ACC_DICIMAL_VAL){
				ACC_FROM_ADC_TO_DAC(ACC_DICIMAL_VAL);
			}else{

				if(ACC_ACTION ==ACC_CAR_STOP){
					ACC_FROM_ADC_TO_DAC(ACC_DAC_MIN_DECIMAL);
				}else if(ACC_ACTION ==ACC_CAR_SLOW_DOWN){

					ACC_FROM_ADC_TO_DAC((ADC_SAVED/2));
				}else if(ACC_ACTION ==ACC_CAR_GO){
					ACC_FROM_ADC_TO_DAC(ADC_SAVED);

				}
			}


		}else if(ACC_ST==ACC_OFF){
			ACC_counter=0;
			if(ACC_ACTION ==ACC_CAR_STOP){
				ACC_FROM_ADC_TO_DAC(ACC_DAC_MIN_DECIMAL);
			}else if(ACC_ACTION ==ACC_CAR_SLOW_DOWN){
				ACC_FROM_ADC_TO_DAC((ACC_DICIMAL_VAL/2));
			}else if(ACC_ACTION ==ACC_CAR_GO){
				ACC_FROM_ADC_TO_DAC(ACC_DICIMAL_VAL);
			}
		}

	}
}
/**================================================================
 * @Fn- ACC_throttel_Handller_TASK
 * @brief - this task shall to read the state of ACC_BOTTON_PIN
 * and read THROTTEL_DATA and convert it to DICIMAL_VAL
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */

void ACC_STATE_READ_TASK(){
	while(1){

		//		LUNA_dist();
		if(MCAL_Read_PIN(ACC_BOTTON_PORT, ACC_BOTTON_PIN)){
			_TIM1_delay_ms(30);
			if(MCAL_Read_PIN(ACC_BOTTON_PORT, ACC_BOTTON_PIN)){
				ACC_ST=1;


			}
		}else{
			ACC_ST=0;

		}
		ADC_read(ADC1,ACC_THROTTEL_CHx,&ACC_THROTTEL_DATA);
		if(ACC_THROTTEL_DATA<ACC_TROTTEL_MIN_ADC_VAL){
			ACC_DICIMAL_VAL=64;
		}else if(ACC_THROTTEL_DATA>ACC_TROTTEL_Max_ADC_VAL){
			ACC_DICIMAL_VAL=255;
		}

		else{
			//		uint32_t step1=((uint32_t)(ACC_THROTTEL_DATA-ACC_TROTTEL_MIN_ADC_VAL)*(ACC_DAC_MAX_DECIMAL-ACC_DAC_MIN_DECIMAL)); //884.3
			//		uint32_t step2=(ACC_TROTTEL_Max_ADC_VAL-ACC_TROTTEL_MIN_ADC_VAL);//1539
			//		uint32_t step3=(step1/step2);
			//		ACC_DICIMAL_VAL=step3+ACC_DAC_MIN_DECIMAL;
			ACC_DICIMAL_VAL=((((ACC_THROTTEL_DATA-ACC_TROTTEL_MIN_ADC_VAL)*(ACC_DAC_MAX_DECIMAL-ACC_DAC_MIN_DECIMAL))/(ACC_TROTTEL_Max_ADC_VAL-ACC_TROTTEL_MIN_ADC_VAL))+ACC_DAC_MIN_DECIMAL);
		}


		if(HALL_EFFECT_KM_H <=10){
			ACC_distance_stop=Distance_SET;
			ACC_distance_slowdown=MAX_Distance_SET;
		}else if(HALL_EFFECT_KM_H >10 && HALL_EFFECT_KM_H<=30){
			ACC_distance_stop=500;
			ACC_distance_slowdown=700;
		}else if(HALL_EFFECT_KM_H > 30){
			ACC_distance_stop=850;
			ACC_distance_slowdown=900;
		}
	}
}
/***********************************/
/***********************************/
/***********************************/
/***********************************/
/***********************************/
/***********************************/












/************TSR TASK*************/
/************TSR TASK*************/
/************TSR TASK*************/
/************TSR TASK*************/






/**================================================================
 * @Fn- TFT_Handller_TASK
 * @brief - this task shall to print various things to the TFT
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note- it must to change the Priority of this task while sending the data to TFT screen to make sure
 * that there is no data corruption
 */
void TFT_Handller_TASK(){
	while(1){
		//	  if(GR_TSR_FLAG_OLED_send !=0x99){
		vTaskPrioritySet(TSR_Handller_TASK_Handle,4);
		TFT_send_ACC_image(HALL_EFFECT_KM_H);
		TFT_send_TSR_image(GR_TSR_FLAG_OLED_send);
		TFT_cruise_control_ICON_Print(ACC_ST);
		TFT_HOD_ICON_Print(DMS_DATA);
		vTaskPrioritySet(TSR_Handller_TASK_Handle,2);


		//	  }
	}
}

/**================================================================
 * @Fn- TSR_call_Back
 * @brief - this task shall to get the flags PC using TSR_UART_INSTANT
 * to send the actions to other tasks
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void TSR_call_Back(void){
	PC_Uart_Flag=  MCAL_USART_ReciveData(TSR_UART_INSTANT);



	switch(PC_Uart_Flag){
	case '#':
		TSR_START_Flag=1;
		TSR_END_Flag=0;
		break;
	case '*':
		TSR_END_Flag=1;
		break;
	case 0x2F:
		FACE_START_Flag=1;
		FACE_END_Flag=0;
		break;
	case 0x2B:
		FACE_END_Flag=1;
		break;

	case '@':
		DMS_START_OF_FRAME=1;
		DMS_END_OF_FRAME=0;
		break;
	case '&':
		DMS_END_OF_FRAME=1;
		break;

	}

	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////

	if (FACE_START_Flag){
		if(PC_Counter ==0)
			PC_Uart_Flag=0;

		if(FACE_END_Flag ==0){
			GR_FACE_FLAG_ = (GR_FACE_FLAG_<<8)| PC_Uart_Flag;
			PC_Counter++;
			/*
			 * 0x0000 | 0x2F =0x
			 *
			 * */

		}else{
			GR_FACE_FLAG_ &=0x0F0F;
			GR_FACE_FLAG_send = ((GR_FACE_FLAG_ &0x0F00)>>4) |((GR_FACE_FLAG_&0x000F));
			GR_FACE_FLAG_=0;

			///////////////
			FACE_START_Flag=0;
			FACE_END_Flag=0;
			PC_Counter=0;
		}
	}
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	if(TSR_START_Flag){
		if(PC_Counter ==0)
			PC_Uart_Flag=0;

		if(TSR_END_Flag ==0){
			GR_TSR_FLAG_OLED = (GR_TSR_FLAG_OLED<<8)| PC_Uart_Flag;
			PC_Counter++;


		}else{
			GR_TSR_FLAG_OLED &=0x0F0F;
			GR_TSR_FLAG_OLED_send = ((GR_TSR_FLAG_OLED &0x0F00)>>4) |((GR_TSR_FLAG_OLED&0x000F));
			GR_TSR_FLAG_OLED=0;
			///////////////
			TSR_END_Flag=0;
			TSR_START_Flag=0;
			PC_Counter=0;


		}
	}
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////
	if(DMS_START_OF_FRAME){
		if(PC_Counter ==0)
			PC_Uart_Flag=0;

		if(DMS_END_OF_FRAME ==0){
			GR_DMS_FLAG_ = (GR_DMS_FLAG_<<8)| PC_Uart_Flag;
			PC_Counter++;


		}else{
			GR_DMS_FLAG_ &=0x0F0F;
			GR_DMS_FLAG_send = ((GR_DMS_FLAG_ &0x0F00)>>4) |((GR_DMS_FLAG_&0x000F));
			GR_DMS_FLAG_=0;
			///////////////
			DMS_START_OF_FRAME=0;
			DMS_END_OF_FRAME=0;
			PC_Counter=0;


		}
	}










}


/**================================================================
 * @Fn- TSR_init
 * @brief - this fun shall to init TSR
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void TSR_init(void){
	USART_Config_t UART1_CON={115200,EGHIT_BITS,Parity_DISABLE,Interrupt,ONE_STOP_BIT,Disabled,Asynchronous,TSR_call_Back};
	MCAL_USART_init(TSR_UART_INSTANT, &UART1_CON);
}

/***********************************/
/***********************************/
/***********************************/
/***********************************/
/***********************************/
/***********************************/









/************FACE ID TASK*************/
/************FACE ID TASK*************/
/************FACE ID TASK*************/
/**================================================================
 * @Fn- CAR_ON_Handler
 * @brief - this fun shall to  off the car depending on EXTI when detecting the FALLING edge from the switch
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void CAR_ON_Handler(){
	CAR_login_counter=0;
	if((MCAL_Read_PIN(CONTACT_BOTTON_PORT, CONTACT_BOTTON_PIN)==0) ){
		_TIM1_delay_ms(30); //depouncing delay
		if((MCAL_Read_PIN(CONTACT_BOTTON_PORT, CONTACT_BOTTON_PIN)==0) ){

			if(CAR_ON_counter ==1 &&GR_FACE_FLAG_send !=0x99&&GR_FACE_FLAG_send !=0x00){

				CAR_ON_counter=0;
				GR_FACE_FLAG_send=0;
				CAR_login_counter=0;
				DMS__zero_COUNTER=0;
				DMS__one_COUNTER=0;
				//UART SEND
				TFT_SET_BACKGROUND(0,159,0,127,0xff,0xff,0xff);
				//
				ACC_FROM_ADC_TO_DAC(ACC_DAC_MIN_DECIMAL);
				MCAL_USART_SendData(TSR_UART_INSTANT,CAR_OFF_FLAG);
				_TIM1_delay_ms(30);

				vTaskResume(FACE_ID_TASK_Handle);
				//				vTaskPrioritySet(FACE_ID_TASK_Handle,5);

			}
		}

	}


}
/**================================================================
 * @Fn- CAR_ON_init
 * @brief - this fun shall to init the swtich that control the car on off
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void CAR_ON_init(){
	EXTI_config_t CAR_BOTTON_SITTING={EXT1PB1,FALLING,ENABLE,CAR_ON_Handler};
	MCAL_EXTI_init(&CAR_BOTTON_SITTING);
	PIN_config pin={CONTACT_BOTTON_PIN,INPUT_PD};
	MCAL_GPIO_init(CONTACT_BOTTON_PORT, &pin);
}
/**================================================================
 * @Fn- FACE_ID_TASK
 * @brief - this task shall to control the on and off the car depending on the FACE ID and Mobile APP
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void FACE_ID_TASK(){
	while(1){
		//		_TIM1_delay_ms(500);
		if((MCAL_Read_PIN(CONTACT_BOTTON_PORT, CONTACT_BOTTON_PIN)==1) ){
			_TIM1_delay_ms(30); //depouncing delay
			if((MCAL_Read_PIN(CONTACT_BOTTON_PORT, CONTACT_BOTTON_PIN)==1) ){
				//UART SEND

				if(CAR_login_counter==0){
					MCAL_USART_SendData(TSR_UART_INSTANT,CAR_ON_FLAG);
					CAR_login_counter++;
				}

				if(GR_FACE_FLAG_send !=0x99 && GR_FACE_FLAG_send !=0x00){
					CAR_ON_counter=1;
					CAR_login_counter=0;

					TFT_Welcome_ICON_Print();
					TFT_SPEED_ICON_Print();
					TFT_KM_H_ICON_Print();
					vTaskSuspend(FACE_ID_TASK_Handle);
					//					vTaskPrioritySet(FACE_ID_TASK_Handle,1);


				}
			}
		}else{
			//			this will happen in CAR_ON_Handler because of falling edge
		}

	}
}


/***********************************/
/***********************************/
/***********************************/
/***********************************/
/***********************************/
/***********************************/






/**================================================================
 * @Fn- HW_init
 * @brief - this fun shall to all hardware and software periphrals
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */


void HW_init(){
	Sys_Clk_init();
	_TIM1_delay_ms(100);
	////////////*********TFT_init***************//////////////////
	TFT_init(RGB_5_6_5);
	_TIM1_delay_ms(100);

	////////////*********TSR init***************//////////////////
	TSR_init();
	_TIM1_delay_ms(100);

	////////////*********ACC_throtel_init*********//////////////////
	ACC_throtel_init();
	_TIM1_delay_ms(100);

	////////////*********DAC init***************//////////////////
	ACC_DAC_init();
	_TIM1_delay_ms(100);

	////////////*********DMS_init***************//////////////////
	DMS_init();
	_TIM1_delay_ms(100);

	////////////*********CAR_ON_init***************//////////////////
	CAR_ON_init();
	_TIM1_delay_ms(100);
	////////////*********HALL_EFECT_Init***************//////////////////

	HALL_EFECT_Init();
	_TIM1_delay_ms(100);
	////////////*********LUNA_INIT***************//////////////////
	LUNA_INIT(CONTIOUS_RANGING_MODE,BYTE_9_CM);
	_TIM1_delay_ms(100);

}
int main(void)
{
	//	_TIM1_delay_s(2);
	HW_init();

	///////////////////////////
	if(xTaskCreate(ACC_throttel_Handller_TASK,"ACC_throttel_Handller_TASK",256,NULL,2,NULL)!=pdPASS ){
		Error_Handller();
	}

	if(xTaskCreate(ACC_Handller_TASK,"ACC_Handller_TASK",256,NULL,2,NULL)!=pdPASS ){
		Error_Handller();
	}


	if(xTaskCreate(ACC_STATE_READ_TASK,"BOTTON_READ",256,NULL,2,&ACC_STATE_READ_TASK_Handle)!=pdPASS ){
		Error_Handller();
	}
	///////////////////////

	if(xTaskCreate(TFT_Handller_TASK,"TFT_Handller_TASK",256,NULL,2,&TSR_Handller_TASK_Handle)!=pdPASS ){
		Error_Handller();
	}

	///////////////////////

	if(xTaskCreate(DMS_Handller_TASK,"DMS_Handller_TASK",256,NULL,2,NULL)!=pdPASS ){
		Error_Handller();
	}


	///////////////////////
	if(xTaskCreate(FACE_ID_TASK,"FACE_ID_TASK",256,NULL,5,&FACE_ID_TASK_Handle)!=pdPASS ){
		Error_Handller();
	}


	//    MCAL_USART_SendData(TSR_UART_INSTANT, 'D');

	vTaskStartScheduler();

	for(;;);
}
