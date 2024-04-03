/*
 * LUNA_LIDAR.h
 *
 * Created: 18/07/45 02:12:09 ص
 *  Author: hp
 */ 


#ifndef LUNA_LIDAR_H_
#define LUNA_LIDAR_H_
#include <stdint.h>
#define LUNA_UART_INSTANT USART3
#define Distance_SET 300
#define MAX_Distance_SET 500

typedef enum
{
	CONTIOUS_RANGING_MODE,
	TRIGER_MODE,
	ON_OFF_MODE,
	}LUNA_MODES;
	
typedef enum
{
	BYTE_9_CM,
	PLX,
	BYTE_9_MM,
	BYTE_32,
	ID_0,
	BYTE_8_CM,
	
	}OUTPUT_FORMAT;
	
void LUNA_INIT(LUNA_MODES mode,OUTPUT_FORMAT format);

void LUNA_dist(void);
void LUNA_ENABLE();
void LUNA_Disable();
#endif /* LUNA_LIDAR_H_ */
