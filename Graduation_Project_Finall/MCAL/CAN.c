/*
 * CAN.c
 *
 *  Created on: Feb 12, 2024
 *      Author: medoo
 */


#include "CAN.h"
CAN_config CAN_SITTING={0};
void ERROR_HANDLER(){
	while(1);
}
void MCAL_CAN_SET_GPIO(){
	PIN_config PINx={PIN_12,OUTPUT_AF_PP,SPEED_10}; //CAN_TX
	MCAL_GPIO_init(GPIOA, &PINx);
	PINx=(PIN_config){PIN_11,INPUT_FI,0}; //CAN_RX
	MCAL_GPIO_init(GPIOA, &PINx);

}
CAN_retrun MCAL_CAN_init(CAN_config *CANx){
	CAN_SITTING =(*CANx);
	//Make the Can State ITIALIZATION
	RCC->APB1ENR|=(1<<25);
	MCAL_CAN_SET_GPIO();
	if((CAN1->MSR.Bit_Name.INAK ==0) &&(CAN1->MSR.Bit_Name.SLAK ==1) ){
		//this mean the state of can is sleep
		CAN1->MCR.Bit_Name.SLEEP=0;
		CAN1->MCR.Bit_Name.INRQ=1;
		while(!((CAN1->MSR.Bit_Name.INAK ==1) &&(CAN1->MSR.Bit_Name.SLAK ==0)));
	}
	//Automatic bus-off management
	if(CANx->ABO){
		CAN1->MCR.Bit_Name.ABOM=1;
	}else{
		CAN1->MCR.Bit_Name.ABOM=0;
	}
	//No automatic retransmission
	if(CANx->NAT){
		CAN1->MCR.Bit_Name.NART=1;
	}else{
		CAN1->MCR.Bit_Name.NART=0;
	}

	//Transmit FIFO priority by the identifier of the message
	CAN1->MCR.Bit_Name.TXFP=0;
	//Receive FIFO locked mode Receive FIFO locked against overrun. Once a receive FIFO
	//is full the next incoming message will be discarded.
	if(CANx->RFL){
		CAN1->MCR.Bit_Name.RFLM=1;
	}else{
		CAN1->MCR.Bit_Name.RFLM=0;

	}

	//from http://www.bittiming.can-wiki.info/ we can get the CAN1->BTR
	switch(MCAL_GET_PCLCK1()){
	case 8000000UL:
		switch(CANx->SPEED){
		case CAN_1MB:
			CAN1->BTR.ALL_Bits=0x00050000;
			break;
		case CAN_500KB:
			CAN1->BTR.ALL_Bits=0x001c0000;
			break;
		case CAN_250KB:
			CAN1->BTR.ALL_Bits=0x001c0001;
			break;
		case CAN_100KB:
			CAN1->BTR.ALL_Bits=0x001c0004;
			break;

		}
		break;
		case 24000000UL:
			switch(CANx->SPEED){
			case CAN_1MB:
				CAN1->BTR.ALL_Bits=0x00090001;
				break;
			case CAN_500KB:
				CAN1->BTR.ALL_Bits=0x001c0002;
				break;
			case CAN_250KB:
				CAN1->BTR.ALL_Bits=0x001c0005;
				break;
			case CAN_100KB:
				CAN1->BTR.ALL_Bits=0x001c000e;
				break;

			}

			break;
			default:
				break;

	}

	switch(CANx->MODE){
	case CAN_NORMAL:
		CAN1->BTR.Bit_Name.SILM=0;
		CAN1->BTR.Bit_Name.LBKM=0;

		break;
	case CAN_Silent:
		CAN1->BTR.Bit_Name.SILM=1;
		CAN1->BTR.Bit_Name.LBKM=0;
		break;
	case CAN_Loop_back:
		CAN1->BTR.Bit_Name.SILM=0;
		CAN1->BTR.Bit_Name.LBKM=1;
		break;
	case CAN_Silent_Loop_back:
		CAN1->BTR.Bit_Name.SILM=1;
		CAN1->BTR.Bit_Name.LBKM=1;
		break;
	default:
		ERROR_HANDLER();
		break;

	}

	if(CANx->IE){
		CAN1->IER.Bit_Name.FMPIE0=1;
		CAN1->IER.Bit_Name.FMPIE1=1;
		NVIC_ISER0|=(1<<20) |(1<<21);
	}else{
		CAN1->IER.Bit_Name.FMPIE0=0;
		CAN1->IER.Bit_Name.FMPIE1=0;
		NVIC_ICER0|=(1<<20) |(1<<21);
	}

	CAN1->IER.Bit_Name.BOFIE=1;
	CAN1->IER.Bit_Name.ERRIE=1;
	NVIC_ISER0|=(1<<22);
	//Make the Can State Normal
	if((CAN1->MSR.Bit_Name.INAK ==1) &&(CAN1->MSR.Bit_Name.SLAK ==0) ){
		//this mean the state of can is sleep
		CAN1->MCR.Bit_Name.SLEEP=0;
		CAN1->MCR.Bit_Name.INRQ=0;
		while(CAN1->MSR.Bit_Name.INAK ==1);
	}


	return CAN_OK;
}


CAN_retrun MCAL_CAN_TX(uint16_t ID,uint8_t DLC,uint8_t *data,uint8_t RTR){
	//first check if any mailboxes free
	if((CAN1->TSR.Bit_Name.TME)&0b001){


		CAN1->TI0R.Bit_Name.STID=ID;
		CAN1->TI0R.Bit_Name.IDE=0;
		CAN1->TI0R.Bit_Name.RTR=RTR;
		CAN1->TDT0R.Bit_Name.DLC=DLC;
		CAN1->TDT0R.Bit_Name.TGT=0;
		CAN1->TDL0R.ALL_Bits=0;
		CAN1->TDH0R.ALL_Bits=0;
		for(uint8_t i=0;i<DLC;i++){
			if(i<4){
				CAN1->TDL0R.ALL_Bits |= (CAN1->TDL0R.ALL_Bits ) | ((*data)<<(i*8));
			}else{
				CAN1->TDH0R.ALL_Bits |= (CAN1->TDH0R.ALL_Bits ) | ((*data)<<((i-4)*8));
			}
			data++;

		}
		CAN1->TI0R.Bit_Name.TXRQ=1;
		//			while(CAN1->TI0R.Bit_Name.TXRQ);
		//			while( !((CAN1->TSR.Bit_Name.RQCP0)&&(CAN1->TSR.Bit_Name.TXOK0)&&((CAN1->TSR.Bit_Name.TME)&0b001)));
	}

	else if((CAN1->TSR.Bit_Name.TME)&0b010){

		CAN1->TI1R.Bit_Name.STID=ID;
		CAN1->TI1R.Bit_Name.IDE=0;
		CAN1->TDT1R.Bit_Name.DLC=DLC;
		CAN1->TDL1R.ALL_Bits=0;
		CAN1->TDH1R.ALL_Bits=0;
		for(uint8_t i=0;i<DLC;i++){
			if(i<4){
				CAN1->TDL1R.ALL_Bits |= (CAN1->TDL1R.ALL_Bits ) | ((*data)<<(i*8));
			}else{
				CAN1->TDH1R.ALL_Bits |= (CAN1->TDH1R.ALL_Bits ) | ((*data)<<((i-4)*8));
			}
			data++;
		}
		CAN1->TI1R.Bit_Name.TXRQ=1;
		//			while(CAN1->TI1R.Bit_Name.TXRQ);

		//			while( !((CAN1->TSR.Bit_Name.RQCP1)&&(CAN1->TSR.Bit_Name.TXOK1)&&((CAN1->TSR.Bit_Name.TME)&0b010)));

	}
	else if((CAN1->TSR.Bit_Name.TME)&0b100){
		CAN1->TI2R.Bit_Name.STID=ID;
		CAN1->TI2R.Bit_Name.IDE=0;
		CAN1->TDT2R.Bit_Name.DLC=DLC;
		CAN1->TDL2R.ALL_Bits=0;
		CAN1->TDH2R.ALL_Bits=0;
		for(uint8_t i=0;i<DLC;i++){
			if(i<4){
				CAN1->TDL2R.ALL_Bits |= (CAN1->TDL2R.ALL_Bits ) | ((*data)<<(i*8));
			}else{
				CAN1->TDH2R.ALL_Bits |= (CAN1->TDH2R.ALL_Bits ) | ((*data)<<((i-4)*8));
			}
			data++;

		}
		CAN1->TI2R.Bit_Name.TXRQ=1;
		//			while(CAN1->TI2R.Bit_Name.TXRQ);

		//			while( !((CAN1->TSR.Bit_Name.RQCP2)&&(CAN1->TSR.Bit_Name.TXOK2)&&((CAN1->TSR.Bit_Name.TME)&0b100)));


	}else{
		return	CAN_ERROR;
	}
	return CAN_OK;

}


CAN_retrun MCAL_CAN_ADD_Filter(CAN_Filter_x_Bank *FBx){
	CAN1->FA1R.Bit_Name.FACT=0;
	CAN1->FMR.Bit_Name.FINIT=1; //1: Initialization mode for the filters.
	CAN1->FS1R.ALL_Bits|=((FBx->FS)<<(FBx->FB_num)); //0: Dual 16-bit scale configuration
	//													1: Single 32-bit scale configuration
	CAN1->FM1R.ALL_Bits|=((FBx->FM)<<(FBx->FB_num));/*Mode of the registers of Filter x.
					0: Two 32-bit registers of filter bank x are in Identifier Mask mode.
					1: Two 32-bit registers of filter bank x are in Identifier List mod*/

	if(FBx->FB_num <7){
		CAN1->FFA1R.ALL_Bits&=~(1<<FBx->FB_num); //0: Filter assigned to FIFO 0
	}else{
		CAN1->FFA1R.ALL_Bits|=(1<<FBx->FB_num); //1: Filter assigned to FIFO 1

	}
	if(FBx->FS){
		if(FBx->FM){
			switch(FBx->FB_num){
			case 0:
				CAN1->F0R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F0R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 1:
				CAN1->F1R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F1R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 2:
				CAN1->F2R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F2R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 3:
				CAN1->F3R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F3R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;

			case 4:
				CAN1->F4R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F4R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 5:
				CAN1->F5R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F5R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 6:
				CAN1->F6R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F6R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 7:
				CAN1->F7R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F7R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 8:
				CAN1->F8R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F8R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 9:
				CAN1->F9R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F9R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 10:
				CAN1->F10R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F10R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 11:
				CAN1->F11R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F11R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 12:
				CAN1->F12R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F12R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 13:
				CAN1->F13R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F13R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			}

		}else{
			switch(FBx->FB_num){
			case 0:
				CAN1->F0R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F0R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 1:
				CAN1->F1R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F1R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 2:
				CAN1->F2R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F2R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 3:
				CAN1->F3R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F3R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;

			case 4:
				CAN1->F4R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F4R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 5:
				CAN1->F5R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F5R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 6:
				CAN1->F6R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F6R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 7:
				CAN1->F7R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F7R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 8:
				CAN1->F8R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F8R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 9:
				CAN1->F9R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F9R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 10:
				CAN1->F10R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F10R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 11:
				CAN1->F11R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F11R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 12:
				CAN1->F12R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F12R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			case 13:
				CAN1->F13R1.ALL_Bits=(FBx->ID<<21);
				CAN1->F13R2.ALL_Bits=(FBx->MASK_ID<<21);
				break;
			}

		}
	}else{
		if(FBx->FM){
			switch(FBx->FB_num){
			case 0:
				CAN1->F0R2.ALL_Bits=(FBx->MASK_ID<<5);
				CAN1->F0R1.ALL_Bits=(FBx->ID<<5);
				break;
			case 1:
				CAN1->F1R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F1R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 2:
				CAN1->F2R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F2R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 3:
				CAN1->F3R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F3R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;

			case 4:
				CAN1->F4R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F4R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 5:
				CAN1->F5R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F5R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 6:
				CAN1->F6R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F6R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 7:
				CAN1->F7R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F7R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 8:
				CAN1->F8R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F8R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 9:
				CAN1->F9R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F9R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 10:
				CAN1->F10R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F10R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 11:
				CAN1->F11R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F11R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 12:
				CAN1->F12R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F12R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 13:
				CAN1->F13R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F13R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			}

		}else{
			switch(FBx->FB_num){
			case 0:
				CAN1->F0R2.ALL_Bits=(FBx->MASK_ID<<5);
				CAN1->F0R1.ALL_Bits=(FBx->ID<<5);
				break;
			case 1:
				CAN1->F1R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F1R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 2:
				CAN1->F2R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F2R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 3:
				CAN1->F3R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F3R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;

			case 4:
				CAN1->F4R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F4R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 5:
				CAN1->F5R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F5R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 6:
				CAN1->F6R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F6R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 7:
				CAN1->F7R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F7R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 8:
				CAN1->F8R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F8R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 9:
				CAN1->F9R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F9R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 10:
				CAN1->F10R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F10R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 11:
				CAN1->F11R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F11R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 12:
				CAN1->F12R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F12R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			case 13:
				CAN1->F13R1.ALL_Bits=(FBx->ID<<5);
				CAN1->F13R2.ALL_Bits=(FBx->MASK_ID<<5);
				break;
			}

		}


	}

	CAN1->FMR.Bit_Name.FINIT=0; //1: Initialization mode for the filters.
	CAN1->FA1R.ALL_Bits|=(1<<FBx->FB_num);
	return CAN_OK;
}
CAN_retrun MCAL_CAN_RX(CAN_frame *frame){

	if(CAN_SITTING.IE){
		if(CAN1->RF0R.Bit_Name.FMP0){
						if(CAN1->RF0R.Bit_Name.FOVR0)
									CAN1->RF0R.Bit_Name.FOVR0=1;
						if(CAN1->RF0R.Bit_Name.FULL0)
									CAN1->RF0R.Bit_Name.FULL0=1;


						frame->DLC=CAN1->RDT0R.Bit_Name.DLC;
						frame->FMI=CAN1->RDT0R.Bit_Name.FMI;
						frame->STID=CAN1->RI0R.Bit_Name.STID;
						frame->IDE=CAN1->RI0R.Bit_Name.IDE;
						frame->RTR=CAN1->RI0R.Bit_Name.RTR;
						for(uint8_t i=0;i<frame->DLC;i++){
							if(i<4){
								frame->data[i]=(CAN1->RDL0R.ALL_Bits>>(8*i));
							}else{
								frame->data[i]=(CAN1->RDH0R.ALL_Bits>>((i-4)*8));

							}
						}

						CAN1->RF0R.Bit_Name.RFOM0=1;

					}else if(CAN1->RF1R.Bit_Name.FMP1){

						//check if the fifo is full or not
						if(CAN1->RF1R.Bit_Name.FOVR1)
									CAN1->RF1R.Bit_Name.FOVR1=1;
						if(CAN1->RF1R.Bit_Name.FULL1)
									CAN1->RF1R.Bit_Name.FULL1=1;
						frame->DLC=CAN1->RDT1R.Bit_Name.DLC;
						frame->FMI=CAN1->RDT1R.Bit_Name.FMI;
						frame->STID=CAN1->RI1R.Bit_Name.STID;
						frame->IDE=CAN1->RI1R.Bit_Name.IDE;
						frame->RTR=CAN1->RI1R.Bit_Name.RTR;
						for(uint8_t i=0;i<frame->DLC;i++){
							if(i<4){
								frame->data[i]=(CAN1->RDL1R.ALL_Bits>>(8*i));
							}else{
								frame->data[i]=(CAN1->RDH1R.ALL_Bits>>((i-4)*8));

							}
						}


						CAN1->RF1R.Bit_Name.RFOM1=1;

					}
	}else{

		//wait here until you got a frame
		while((CAN1->RF0R.Bit_Name.FMP0==0b00)&&(CAN1->RF1R.Bit_Name.FMP1==0b00));

			//check if the fifo is full or not

			if(CAN1->RF0R.Bit_Name.FMP0){
				if(CAN1->RF0R.Bit_Name.FOVR0)
							CAN1->RF0R.Bit_Name.FOVR0=1;
				if(CAN1->RF0R.Bit_Name.FULL0)
							CAN1->RF0R.Bit_Name.FULL0=1;


				frame->DLC=CAN1->RDT0R.Bit_Name.DLC;
				frame->FMI=CAN1->RDT0R.Bit_Name.FMI;
				frame->STID=CAN1->RI0R.Bit_Name.STID;
				frame->IDE=CAN1->RI0R.Bit_Name.IDE;
				frame->RTR=CAN1->RI0R.Bit_Name.RTR;
				for(uint8_t i=0;i<frame->DLC;i++){
					if(i<4){
						frame->data[i]=(CAN1->RDL0R.ALL_Bits>>(8*i));
					}else{
						frame->data[i]=(CAN1->RDH0R.ALL_Bits>>((i-4)*8));

					}
				}

				CAN1->RF0R.Bit_Name.RFOM0=1;

			}else if(CAN1->RF1R.Bit_Name.FMP1){

				//check if the fifo is full or not
				if(CAN1->RF1R.Bit_Name.FOVR1)
							CAN1->RF1R.Bit_Name.FOVR1=1;
				if(CAN1->RF1R.Bit_Name.FULL1)
							CAN1->RF1R.Bit_Name.FULL1=1;
				frame->DLC=CAN1->RDT1R.Bit_Name.DLC;
				frame->FMI=CAN1->RDT1R.Bit_Name.FMI;
				frame->STID=CAN1->RI1R.Bit_Name.STID;
				frame->IDE=CAN1->RI1R.Bit_Name.IDE;
				frame->RTR=CAN1->RI1R.Bit_Name.RTR;
				for(uint8_t i=0;i<frame->DLC;i++){
					if(i<4){
						frame->data[i]=(CAN1->RDL1R.ALL_Bits>>(8*i));
					}else{
						frame->data[i]=(CAN1->RDH1R.ALL_Bits>>((i-4)*8));

					}
				}


				CAN1->RF1R.Bit_Name.RFOM1=1;

			}
		}



	return CAN_OK;

}

void MCAL_CAN_RESET(){
	RCC->APB1RSTR|=(1<<25);
	RCC->APB1RSTR&=~(1<<25);

}

void USB_LP_CAN_RX0_IRQHandler(){
	CAN_SITTING.g_f_callback();
}
void CAN_RX1_IRQHandler(){
	CAN_SITTING.g_f_callback();
}

void CAN_SCE_IRQHandler(){
	MCAL_CAN_RESET();
	MCAL_CAN_init(&CAN_SITTING);
}
