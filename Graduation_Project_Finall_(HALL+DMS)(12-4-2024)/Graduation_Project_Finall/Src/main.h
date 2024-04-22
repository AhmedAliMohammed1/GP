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
#include "Timer1_8.h"
#include "DMS.h"
//////////***********defines***********//////////
#define TSR_UART_INSTANT USART1
#define ACC_TROTTEL_MIN_VOLT 0.85
#define ACC_TROTTEL_Max_VOLT 2
#define ACC_TROTTEL_MIN_ADC_VAL 0x4B0
#define ACC_TROTTEL_Max_ADC_VAL 0x906
#define ACC_DAC_MAX_DECIMAL 255
#define ACC_DAC_MIN_DECIMAL 64
#define ACC_TROTTEL_Max_ADC_VAL_shifted ((ACC_TROTTEL_Max_ADC_VAL)-(ACC_TROTTEL_MIN_ADC_VAL))
#define ACC_PWM_TIMx_INSTANTE TIM2
#define ACC_BOTTON_PORT GPIOB
#define ACC_BOTTON_PIN PIN_0
#define CONTACT_BOTTON_PORT GPIOB
#define CONTACT_BOTTON_PIN PIN_1
#define ACC_THROTTEL_CHx 0
#define ACC_DAC_0 PIN_15
#define ACC_DAC_1 PIN_3
#define ACC_DAC_2 PIN_4
#define ACC_DAC_3 PIN_5
#define ACC_DAC_4 PIN_6
#define ACC_DAC_5 PIN_7
#define ACC_DAC_6 PIN_8
#define ACC_DAC_7 PIN_9
/////////////////////////////
#define CAR_ON_FLAG 0x22
#define CAR_OFF_FLAG 0x33
///////////////////////////////
#define DMS_TAKE_ACTION 0x66
#define DMS_Release_ACTION 0x55
#define DMS_EYES_CLOSED 0x77
#define DMS_EYES_OPEN 0x88
#define DMS_EYES_CLOSED_FORCE_STOP 0x89
/////////////////////////////
////////////////////HALL EFFECT EDIT //////////////////////
#define HALL_EFFECT_TIMx_instant TIM3
#define HALL_EFFECT_EXTI_PIN PIN_12
#define HALL_EFFECT_EXTI_PORT GPIOC
#define HALL_EFFECT_EXTI_LINE EXT12PC12
#define MOTOR_SHAFT_RADIUS 1 //CM
#define  HALL_EFFECT_REV_PER_PULSES 28
#define PI 3141  //PI=3.14159 *1000
#define  HALL_EFFECT_TIME_CONVERSION 1 // TAKE TIME EVERY 1 s
uint8_t HALL_TIMER_EN=0;
uint32_t HALL_EFFECT_COUNTER=0;
uint32_t HALL_EFFECT_N_PULSES=0; //NOTE IN THIS CASE HALL_EFFECT_N_PULSES = HALL_EFFECT_RPS
uint32_t HALL_EFFECT_RPS=0;
uint32_t HALL_EFFECT_RPM=0;
uint32_t HALL_EFFECT_KM_H=0;
//////////////////////////////////////////////////
//////////***********enum***********//////////
typedef enum{ACC_CAR_GO,ACC_CAR_STOP,ACC_CAR_SLOW_DOWN}ACC_ACOTION;
typedef enum{ACC_OFF,ACC_ON}ACC_state;

//////////***********extern***********//////////
extern uint16_t LUNA_dis;
extern uint16_t LUNA_AMP;
extern uint16_t LUNA_TEMP;
extern uint8_t LUNA_CheckSum;
//////////***********Semaphore***********//////////
//SemaphoreHandle_t DMS_Semaphore;

//////////***********Queue***********//////////
//QueueHandle_t TSR__Flags_Queue;
//QueueHandle_t ACC__dis_Queue;
//QueueHandle_t ACC__AMP_Queue;
//QueueHandle_t ACC__ACTION_Queue;
//QueueHandle_t ACC__STATE_Queue;
//////////***********Var***********//////////
uint16_t GR_TSR_FLAG_OLED=0;
uint8_t GR_TSR_FLAG_OLED_send=0;
uint8_t GR_TSR_FLAG_OLED_FINAL=0;
uint8_t PC_Counter=0;
uint8_t PC_Uart_Flag=0;
/////////////////////////////
uint8_t TSR_START_Flag=0; //'#'
uint8_t TSR_END_Flag=0; //'*'
////////////////////////////
uint8_t FACE_START_Flag=0; //'-'
uint8_t FACE_END_Flag=0;// '+'
uint16_t GR_FACE_FLAG_=0;
uint8_t GR_FACE_FLAG_send=0;
////////////////////////////
ACC_state ACC_ST=ACC_OFF;
ACC_ACOTION ACC_ACTION=ACC_CAR_STOP;

uint16_t ACC_THROTTEL_DATA=0x00;
uint8_t  ACC_DICIMAL_VAL=0;
uint16_t ACC_distance_stop=Distance_SET,ACC_distance_slowdown=MAX_Distance_SET;
////////////////////////////
uint8_t CAR_ON_counter=0;
uint8_t CAR_login_counter=0;
////////////////////////////

uint8_t DMS__zero_COUNTER=0,DMS__one_COUNTER=0,DMS_DATA=0;
uint8_t DMS_START_OF_FRAME=0; //'#'
uint8_t DMS_END_OF_FRAME=0; //'*'
uint16_t GR_DMS_FLAG_=0;
uint8_t GR_DMS_FLAG_send=0;
/*****************************************/

/////////////////////////////
TaskHandle_t FACE_ID_TASK_Handle;
TaskHandle_t TSR_Handller_TASK_Handle;
TaskHandle_t ACC_STATE_READ_TASK_Handle;





#endif /* MAIN_H_ */
