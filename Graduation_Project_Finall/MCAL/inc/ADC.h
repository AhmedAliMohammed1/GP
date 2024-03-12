/*
 * ADC.h
 *
 *  Created on: Feb 15, 2024
 *      Author: medoo
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

/***********includes***********/
#include "STM32F103x6.h"
#include "GPIO_Driver.h"
#include "Timer1_8.h"
#include "RCC.h"
/***********defines***********/

/***********Enums***********/
typedef enum{ADC_OK,ADC_error}ADC_return;
typedef enum{ADC_Single_conversion,ADC_Continuous_conversion}ADC_mode;
typedef enum{ADC_Polling,ADC_interrupt}ADC_Mechanism;
typedef enum{
	ADC_1_5_cycles,ADC_7_5_cycles,ADC_13_5_cycles,ADC_28_5_cycles,ADC_41_5_cycles,
	ADC_55_5_cycles,ADC_71_5_cycles,ADC_239_5_cycles
}ADC_sample_time;

/***********Struct***********/
typedef struct{
	uint32_t N:4; //number of chanels should be in the sequence
	uint32_t CH_1:4; //CH1 in sequence
	uint32_t CH_2:4;//CH2 in sequence ...
	uint32_t CH_3:4;
	uint32_t CH_4:4;
	uint32_t CH_5:4;
	uint32_t CH_6:4;
	uint32_t CH_7:4;
	uint32_t CH_8:4;
	uint32_t sequence_Enable:1; //Discontinuous mode

}ADC_sequence;
typedef struct{
	uint16_t AWGD_Enable:1;
	uint16_t  AWGD_CH:5; //number of chanhel that i want to enable the ADC watchdog
	uint16_t ADC_LTRV; //low threshold voltage
	uint16_t ADC_HTRV;//high threshold voltage

}ADC_Analog_WDG;
typedef struct{
	uint8_t CHx_num;/*
					ADC12_IN0 --> PA0
					ADC12_IN1 --> PA1
					ADC12_IN2 --> PA2
					ADC12_IN3 --> PA3
					ADC12_IN4 --> PA4
					ADC12_IN5 --> PA5
					ADC12_IN6 --> PA6
					ADC12_IN7 --> PA7
					ADC12_IN8 --> PB0
					ADC12_IN9 --> PB1
					ADC12_IN14 --> PC4
					ADC12_IN15 --> PC5
	 	 	 	 	 */
	ADC_mode mode; // refer to @ADC_mode
	ADC_sample_time SPT; /*Tconv = Sampling time + 12.5 cycles
							Example:
						With an ADCCLK = 14 MHz and a sampling time of 1.5 cycles:
						Tconv = 1.5 + 12.5 = 14 cycles = 1 μs
						STM32F103xx performance line devices: 1 μs at 56 MHz (1.17 μs at 72 MHz)*/
	ADC_Mechanism IE; // refer to ADC_Mechanism
//	ADC_sequence *sequence; //
	ADC_Analog_WDG *AWDG;
	void(*g_ADC_callback)();

}ADC_CONFIG;
/***********APIs***********/
ADC_return ADC_init(ADCx_REG *ADCx,ADC_CONFIG *config);
void ADC_interrupt_Enable(ADCx_REG *ADCx);
void ADC_read(ADCx_REG *ADCx,uint8_t CH_num,uint16_t *data); //MAKE SURE THAT THE DATA IS ARRAY
void ADC_interrupt_Enable(ADCx_REG *ADCx);
#endif /* INC_ADC_H_ */
