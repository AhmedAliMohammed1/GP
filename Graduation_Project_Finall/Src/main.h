/*
 * main.h
 *
 *  Created on: Jan 31, 2024
 *      Author: medoo
 */

#ifndef MAIN_H_
#define MAIN_H_
//////////***********includes***********//////////
#include <stdint.h>
#include "FreeRTOS.h"
#include "USART_Driver.h"
#include "LUNA_LIDAR.h"
#include "semphr.h"
#include "task.h"
#include "queue.h"
#include "ADC.h"
#include "TFT.h"
#include "GP_Timers.h"
#include "GPIO_Driver.h"
#include "EXTI_Driver.h"
//////////***********defines***********//////////
#define TSR_UART_INSTANT USART1
#define ACC_TROTTEL_MIN_VOLT 0.85
#define ACC_TROTTEL_Max_VOLT 2
#define ACC_TROTTEL_MIN_ADC_VAL 0x41F
#define ACC_TROTTEL_Max_ADC_VAL 0xA22
#define ACC_TROTTEL_Max_ADC_VAL_shifted ((ACC_TROTTEL_Max_ADC_VAL)-(ACC_TROTTEL_MIN_ADC_VAL))
#define ACC_PWM_TIMx_INSTANTE TIM2
#define ACC_BOTTON_PORT GPIOB
#define ACC_BOTTON_PIN PIN_1
#define ACC_THROTTEL_CHx 0
#define ACC_DAC_0 PIN_15
#define ACC_DAC_1 PIN_3
#define ACC_DAC_2 PIN_4
#define ACC_DAC_3 PIN_5
#define ACC_DAC_4 PIN_6
#define ACC_DAC_5 PIN_7
#define ACC_DAC_6 PIN_8
#define ACC_DAC_7 PIN_9
#define CAR_ON_FLAG 0xEE
#define CAR_OFF_FLAG 0xEF
#define DMS_TAKE_ACTION 0x66
#define DMS_Release_ACTION 0x55

//////////***********enum***********//////////
typedef enum{ACC_CAR_GO,ACC_CAR_STOP,ACC_CAR_SLOW_DOWN}ACC_ACOTION;
typedef enum{ACC_OFF,ACC_ON}ACC_state;

//////////***********extern***********//////////
extern uint16_t LUNA_dis;
extern uint16_t LUNA_AMP;
extern uint16_t LUNA_TEMP;
extern uint8_t LUNA_CheckSum;
//////////***********Semaphore***********//////////
SemaphoreHandle_t DMS_Semaphore;

//////////***********Queue***********//////////
QueueHandle_t TSR__Flags_Queue;
QueueHandle_t ACC__dis_Queue;
QueueHandle_t ACC__AMP_Queue;
QueueHandle_t ACC__ACTION_Queue;
QueueHandle_t ACC__STATE_Queue;
//////////***********Var***********//////////
uint16_t GR_TSR_FLAG_OLED=0;
uint8_t GR_TSR_FLAG_OLED_send=0;
uint8_t GR_TSR_FLAG_OLED_FINAL=0;
uint8_t PC_Counter=0;
uint8_t PC_Uart_Flag=0;
/////////////////////////////
uint8_t TSR_START_Flag='#'; //'#'
uint8_t TSR_END_Flag='*'; //'*'
////////////////////////////
uint8_t FACE_START_Flag='/'; //'-'
uint8_t FACE_END_Flag='+';// '+'
uint16_t GR_FACE_FLAG_=0;
uint8_t GR_FACE_FLAG_send=0;
////////////////////////////
ACC_state ACC_ST=ACC_OFF;
ACC_ACOTION ACC_ACTION=ACC_CAR_STOP;
/*****************************************/
uint16_t ACC_dis=0;
uint16_t ACC_AMP=0;
/////////////////////////////
TaskHandle_t FACE_ID_TASK_Handle;
uint8_t CAR_ON_counter=0;
uint8_t CAR_login_counter=0;

#endif /* MAIN_H_ */
