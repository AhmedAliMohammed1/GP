#include "LUNA_LIDAR.h"
#include "USART_Driver.h"
uint16_t LUNA_dis=0;
uint16_t LUNA_AMP=0;
uint16_t LUNA_TEMP=0;
uint8_t LUNA_CheckSum=0;
void LUNA_CallBack(){
	static uint8_t x=0;


		if(x==0){
			if(MCAL_USART_ReciveData(LUNA_UART_INSTANT)==0x59){
				x++;

			}
		}else if(x==1){
			if(MCAL_USART_ReciveData(LUNA_UART_INSTANT)==0x59)
				x++;

		}else if(x==2){
			x++;
			LUNA_dis=0;
			LUNA_dis=MCAL_USART_ReciveData(LUNA_UART_INSTANT);
		}else if(x==3){
			x++;
			LUNA_dis=((LUNA_dis) |(MCAL_USART_ReciveData(LUNA_UART_INSTANT)<<8));

		}else if(x==4){
			x++;
			LUNA_AMP=0;
			LUNA_AMP=MCAL_USART_ReciveData(LUNA_UART_INSTANT);
		}else if(x==5){
			x++;
			LUNA_AMP=((LUNA_AMP) |(MCAL_USART_ReciveData(LUNA_UART_INSTANT)<<8));
		}else if(x==6){
			x++;
			LUNA_TEMP=0;
			LUNA_TEMP=MCAL_USART_ReciveData(LUNA_UART_INSTANT);
		}else if(x==7){
			x++;
			LUNA_TEMP=((LUNA_TEMP) |(MCAL_USART_ReciveData(LUNA_UART_INSTANT)<<8));
		}else if(x==8){
			LUNA_CheckSum=MCAL_USART_ReciveData(LUNA_UART_INSTANT);
			x=0;
		}




}

void LUNA_ENABLE(){
	//	if(LUNA_UART_INSTANT==USART1){
	//		NVIC_ISER1 |=(1<<(USART1_IRQ-32));
	//	}else if(LUNA_UART_INSTANT==USART2){
	//
	//		NVIC_ISER1 |=(1<<(USART2_IRQ-32));
	//
	//	}
	//	else if(LUNA_UART_INSTANT==USART3){
	//		NVIC_ISER1 |=(1<<(USART3_IRQ-32));
	//	}
	NVIC_ISER1 |=(1<<(USART3_IRQ-32));

}
void LUNA_Disable(){
	//	if(LUNA_UART_INSTANT==USART1){
	//		NVIC_ICER1 |=(1<<(USART1_IRQ-32));
	//	}else if(LUNA_UART_INSTANT==USART2){
	//
	//		NVIC_ICER1 |=(1<<(USART2_IRQ-32));
	//
	//	}
	//	else if(LUNA_UART_INSTANT==USART3){
	//		NVIC_ICER1 |=(1<<(USART3_IRQ-32));
	//	}
	NVIC_ICER1 |=(1<<(USART3_IRQ-32));
	NVIC_ICER1 &=~(1<<(USART3_IRQ-32));
	NVIC_ISER1 |=(1<<(USART1_IRQ-32));

}

void LUNA_INIT(LUNA_MODES mode,OUTPUT_FORMAT format)
{
	/*bude raete 9600*/
	USART_Config_t PIN ={115200,EGHIT_BITS,Parity_DISABLE,Interrupt,Disabled,Asynchronous,ONE_STOP_BIT,LUNA_CallBack};
	MCAL_USART_init(LUNA_UART_INSTANT, &PIN);
	//	LUNA_Disable();
	MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x08);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x06);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);	MCAL_USART_SendData(LUNA_UART_INSTANT,0xC2);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x01);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x00); MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
	switch (mode){
	case CONTIOUS_RANGING_MODE:
		MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x06);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x03);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x64);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
		break;
	case TRIGER_MODE :
		/*frequancy ==0*/
		MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x06);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x03);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x00); MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);	MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
		/*triger mode*/
		MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x04);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x04);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
		break;
	case ON_OFF_MODE :
		MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x04);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x3B);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
		break;
	}
	switch (format)
	{
	case BYTE_9_CM:
		MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x01);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
		break;
	case PLX :
		MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x02);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
		break;
	case BYTE_9_MM :
		MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x06);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
		break;
	case BYTE_32:
		MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x07);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
		break;
	case ID_0 :
		MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x08);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
		break;
	case BYTE_8_CM :
		MCAL_USART_SendData(LUNA_UART_INSTANT,0x5A);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x05);  MCAL_USART_SendData(LUNA_UART_INSTANT,0x09);   MCAL_USART_SendData(LUNA_UART_INSTANT,0x00);
		break;
	}
}


void LUNA_dist(){
	uint32_t temp_data=0;
	if(MCAL_USART_ReciveData(LUNA_UART_INSTANT) == 0x59){
		if(MCAL_USART_ReciveData(LUNA_UART_INSTANT) == 0x59){
			for(uint8_t data_counter=0;data_counter<4;data_counter++){
				temp_data =(temp_data<<8) |(MCAL_USART_ReciveData(LUNA_UART_INSTANT));
			}
		}
	}
	LUNA_dis=(temp_data &0xFFFF0000) >>16;
	LUNA_AMP=(temp_data &0x0000FFFF);


}







//	 uint8_t x=0;
//	while( x <=6){
//		while(MCAL_USART_ReciveData(LUNA_UART_INSTANT) == 0x59);
//	 if(x==0){
//		x++;
//		LUNA_dis=0;
//		LUNA_dis=MCAL_USART_ReciveData(LUNA_UART_INSTANT);
//	}else if(x==1){
//		x++;
//		LUNA_dis=((LUNA_dis) |(MCAL_USART_ReciveData(LUNA_UART_INSTANT)<<8));
//
//	}else if(x==2){
//		x++;
//		LUNA_AMP=0;
//		LUNA_AMP=MCAL_USART_ReciveData(LUNA_UART_INSTANT);
//	}else if(x==3){
//		x++;
//		LUNA_AMP=((LUNA_AMP) |(MCAL_USART_ReciveData(LUNA_UART_INSTANT)<<8));
//	}else if(x==4){
//		x++;
//		LUNA_TEMP=0;
//		LUNA_TEMP=MCAL_USART_ReciveData(LUNA_UART_INSTANT);
//	}else if(x==5){
//		LUNA_TEMP=((LUNA_TEMP) |(MCAL_USART_ReciveData(LUNA_UART_INSTANT)<<8));
//	}else if(x==6){
//		LUNA_CheckSum=MCAL_USART_ReciveData(LUNA_UART_INSTANT);
//		x++;
//
////		x=0;
//	}
//	}
