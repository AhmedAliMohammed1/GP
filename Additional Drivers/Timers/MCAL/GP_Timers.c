/*
 * GP_Timers.c
 *
 *  Created on: Oct 30, 2023
 *      Author: medoo
 */

/*
 * Timer1_8.c
 *
 *  Created on: Oct 13, 2023
 *      Author: medoo
 */


#include "GP_Timers.h"
GP_TIMERx_config g_GP_Sitting[3];
GP_TIMx_REG* g_GP_TIMX;
GP_TIMERx_ICU_config g_GP_ICU_MEM[3];
/**================================================================
 * @Fn- MCAL_SET_GP_TIMx_GPIO
 * @brief - this fun shall to goes in infinte loop if any error happen
 * @param [in] - void
 * @param [out] - Void
 * @retval -
 * Note-
 */
void GP_ERROR_HANDLER(){
	while(1);
}
/**================================================================
 * @Fn- MCAL_SET_GP_TIMx_GPIO
 * @brief - this fun shall to set the GPIO pins for ICU/PWM
 * @param [in] - TIM[1 OR 2 OR 3] and the sitting
 * @param [out] - Void
 * @retval -
 * Note-
 */
void MCAL_SET_GP_TIMx_GPIO(GP_TIMx_REG* TIMx,GP_TIMER_Mode MODE,uint8_t CHx){
	PIN_config pin;
	if(TIMx ==TIM2){
		switch (MODE) {
		case NORMAL:

			break;
		case PWM://Alternate function push-pull
			switch(CHx){
			case 1:// chanel 1 TIM2(PA0)
				pin=(PIN_config){PIN_0,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOA, &pin);
				break;
			case 2:// chanel 2 TIM2(PA1)
				pin=(PIN_config){PIN_1,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOA, &pin);
				break;
			case 3:// chanel 3 TIM2(PA2)
				pin=(PIN_config){PIN_2,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOA, &pin);

				break;
			case 4:// chanel 4 TIM2(PA3)
				pin=(PIN_config){PIN_3,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOA, &pin);
				break;
			default:
				ERROR_HANDLER();
			}
			break;
			case ICU:
				switch(CHx){
				case 1:
					pin=(PIN_config){PIN_0,INPUT_FI,0};
					MCAL_GPIO_init(GPIOA, &pin);
					break;
				case 2:
					pin=(PIN_config){PIN_1,INPUT_FI,0};
					MCAL_GPIO_init(GPIOA, &pin);

					break;
				case 3:
					pin=(PIN_config){PIN_2,INPUT_FI,0};
					MCAL_GPIO_init(GPIOA, &pin);

					break;
				case 4:
					pin=(PIN_config){PIN_3,INPUT_FI,0};
					MCAL_GPIO_init(GPIOA, &pin);
					break;
				default:
					ERROR_HANDLER();
				}
				break;
				default:
					break;
		}

	}else if(TIMx ==TIM3){
		switch (MODE) {
		case NORMAL:

			break;
		case PWM://Alternate function push-pull
			switch(CHx){
			case 1:// chanel 1 TIM3(PA6)
				pin=(PIN_config){PIN_6,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOA, &pin);

				break;
			case 2:// chanel 2 TIM3(PA7)
				pin=(PIN_config){PIN_7,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOA, &pin);
				break;
			case 3:// chanel 3 TIM3(PB0)
				pin=(PIN_config){PIN_0,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOB, &pin);

				break;
			case 4:// chanel 4 TIM3(PB1)
				pin=(PIN_config){PIN_1,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOB, &pin);
				break;
			default:
				ERROR_HANDLER();
			}
			break;
			case ICU:
				switch(CHx){
				case 1:
					pin=(PIN_config){PIN_6,INPUT_FI,0};
					MCAL_GPIO_init(GPIOA, &pin);
					break;
				case 2:
					pin=(PIN_config){PIN_7,INPUT_FI,0};
					MCAL_GPIO_init(GPIOA, &pin);
					break;
				case 3:
					pin=(PIN_config){PIN_0,INPUT_FI,0};
					MCAL_GPIO_init(GPIOB, &pin);

					break;
				case 4:
					pin=(PIN_config){PIN_1,INPUT_FI,0};
					MCAL_GPIO_init(GPIOB, &pin);
					break;
				default:
					ERROR_HANDLER();
				}
				break;
				default:
					break;
		}



	}else if(TIMx ==TIM4){
		switch (MODE) {
		case NORMAL:

			break;
		case PWM://Alternate function push-pull
			switch(CHx){
			case 1:// chanel 1 TIM4(PB6)
				pin=(PIN_config){PIN_6,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOB, &pin);

				break;
			case 2:// chanel 2 TIM4(PB7)
				pin=(PIN_config){PIN_7,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOB, &pin);
				break;
			case 3:// chanel 3 TIM4(PB8)
				pin=(PIN_config){PIN_8,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOB, &pin);

				break;
			case 4:// chanel 4 TIM4(PB9)
				pin=(PIN_config){PIN_9,OUTPUT_AF_PP,SPEED_10};
				MCAL_GPIO_init(GPIOB, &pin);
				break;
			default:
				ERROR_HANDLER();
			}
			break;
			case ICU:
				switch(CHx){
				case 1:
					pin=(PIN_config){PIN_6,INPUT_FI,0};
					MCAL_GPIO_init(GPIOB, &pin);
					break;
				case 2:
					pin=(PIN_config){PIN_7,INPUT_FI,0};
					MCAL_GPIO_init(GPIOB, &pin);
					break;
				case 3:
					pin=(PIN_config){PIN_8,INPUT_FI,0};
					MCAL_GPIO_init(GPIOB, &pin);

					break;
				case 4:
					pin=(PIN_config){PIN_9,INPUT_FI,0};
					MCAL_GPIO_init(GPIOB, &pin);
					break;
				default:
					ERROR_HANDLER();
				}
				break;
				default:
					break;
		}
		//////////



	}
}
/**================================================================
 * @Fn- GP_TIMx_start
 * @brief - this fun shall to start normal/compare mode
 * @param [in] - TIM[1 OR 2 OR 3] and the sitting
 * @param [out] - Void
 * @retval -
 * Note-
 */
void GP_TIMx_start(GP_TIMx_REG* TIMx,GP_TIMERx_config* Sitting,GP_TIMERx_NORMAL_config* NORMAL_SITTING){

	if(Sitting->mode==NORMAL){
		g_GP_TIMX=TIMx;
		if(TIMx== TIM2){RCC->APB1ENR|=(1<<0);			g_GP_Sitting[0]=(* Sitting);	}
		else if(TIMx== TIM3) {RCC->APB1ENR|=(1<<1);	g_GP_Sitting[1]=(* Sitting);	}
		else if(TIMx== TIM4) {RCC->APB1ENR|=(1<<2);		g_GP_Sitting[2]=(* Sitting);}
		GP_TIMx_Deint(TIMx);

		// 2.select the pre vale
		TIMx->PSC=Sitting->TIME_PSC;

		TIMx->ARR=Sitting->TIME_ARR;

		TIMx->RCR=Sitting->TIME_RCR;

		if(Sitting->TIME_RCR)
			TIMx->CR1.BIT_NAME.ARPE=1;

		//1.Select the mode CMS[1:0]
		switch(NORMAL_SITTING->NORMAL_MODE){
		case Up:
			TIMx->CR1.BIT_NAME.CMS=0b00; //00: Edge-aligned mode. The counter counts up or down depending on the direction bit (DIR).
			TIMx->CR1.BIT_NAME.DIR=0; //0: Counter used as upcounter
			break;
		case DOWN:
			TIMx->CR1.BIT_NAME.CMS=0b00; //00: Edge-aligned mode. The counter counts up or down depending on the direction bit (DIR).
			TIMx->CR1.BIT_NAME.DIR=1; //1: Counter used as downcounter
			break;
		case Up_Down:
			TIMx->CR1.BIT_NAME.CMS=0b11;
			/*11: Center-aligned mode 3. The counter counts up and down alternatively. Output compare
		interrupt flags of channels configured in output (CCxS=00 in TIMx_CCMRx register) are set
		both when the counter is counting up or down*/
			break;
		default:
			GP_ERROR_HANDLER();
			break;
		}
		MCAL_SET_GP_TIMx_GPIO(TIMx,NORMAL,0);
		TIMx->CR1.BIT_NAME.CEN=1;

		if(Sitting->INT_EN_DIS==INT_EN){
			TIMx->DIER.BIT_NAME.UIE=1;
			if(TIMx== TIM2) 	NVIC_ISER0|=(1<<28);
			else if(TIMx== TIM3) NVIC_ISER0|=(1<<29);
			else if(TIMx== TIM4) NVIC_ISER0|=(1<<30);

		}else{
			while(!TIMx->SR.BIT_NAME.UIF);
			TIMx->SR.BIT_NAME.UIF=0;
		}
	}else{
		GP_ERROR_HANDLER();
	}
}
/**================================================================
 * @Fn- MCAL_SET_GP_TIMx_GPIO
 * @brief - this fun shall to produce PWM or make high value after T of time
 * @param [in] - TIM[1 OR 2 OR 3] and the sitting of global timer and PWM Or CTC sitting
 * @param [out] - WAVE
 * @retval -
 * Note-
 */
void GP_TIMx__CTC_start(GP_TIMx_REG* TIMx,GP_TIMERx_config* Sitting,GP_TIMERx_CTC_config* CTC_Sitting){

	if(Sitting->mode==PWM ||Sitting->mode==CTC ){
		g_GP_TIMX=TIMx;
		if(TIMx== TIM2){RCC->APB1ENR|=(1<<0);			g_GP_Sitting[0]=(* Sitting);	}
		else if(TIMx== TIM3) {RCC->APB1ENR|=(1<<1);	g_GP_Sitting[1]=(* Sitting);	}
		else if(TIMx== TIM4) {RCC->APB1ENR|=(1<<2);		g_GP_Sitting[2]=(* Sitting);}
		GP_TIMx_Deint(TIMx);
		// 2.select the pre vale
		TIMx->PSC=Sitting->TIME_PSC;

		TIMx->ARR=Sitting->TIME_ARR;

		TIMx->RCR=Sitting->TIME_RCR;

		if(Sitting->TIME_RCR)
			TIMx->CR1.BIT_NAME.ARPE=1;


		/*
		 * Procedure:
1. Select the counter clock (internal, external, prescaler). Done
2. Write the desired data in the TIMx_ARR and TIMx_CCRx registers.
3. Set the CCxIE bit if an interrupt request is to be generated.
4. Select the output mode. For example:
– Write OCxM = 011 to toggle OCx output pin when CNT matches CCRx
– Write OCxPE = 0 to disable preload register
– Write CCxP = 0 to select active high polarity
– Write CCxE = 1 to enable the output
5. Enable the counter by setting the CEN bit in the TIMx_CR1 register.*/
		switch(CTC_Sitting->CTC_MODE){
		// IN CASE I NEED TO SWITCH TO FROZEN
		case Frozen:
			switch(CTC_Sitting->CHx_num){
			case 1:
				TIMx->CCMR1.Compare_BIT_NAME.OC1M=Frozen;
				MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,1);

				break;
			case 2:
				TIMx->CCMR1.Compare_BIT_NAME.OC2M=Frozen;
				MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,2);

				break;
			case 3:
				TIMx->CCMR2.Compare_BIT_NAME.OC3M=Frozen;
				MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,3);

				break;
			case 4:
				TIMx->CCMR2.Compare_BIT_NAME.OC4M=Frozen;
				MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,4);

				break;
			default:
				GP_ERROR_HANDLER();
				break;

			}
			break;

			case active:
				switch(CTC_Sitting->CHx_num){
				case 1:
					TIMx->CCR1=Sitting->TIME_CCR;
					TIMx->CCMR1.Compare_BIT_NAME.OC1M=active;
					//if the preload > 0 so enable the OC1PE
					if(Sitting->TIME_RCR){
						TIMx->CCMR1.Compare_BIT_NAME.OC1PE=1;
					}else{
						TIMx->CCMR1.Compare_BIT_NAME.OC1PE=0;
					}
					TIMx->CCER.BIT_NAME.CC1P=CTC_Sitting->CTC_POL;
					//			CC1S	  00: CC1 channel is configured as output
					TIMx->CCMR1.Compare_BIT_NAME.CC1S=0;
					//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

					TIMx->CCER.BIT_NAME.CC1E=1;
					MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,1);

					break;
				case 2:
					TIMx->CCR2=Sitting->TIME_CCR;
					TIMx->CCMR1.Compare_BIT_NAME.OC2M=active;
					//if the preload > 0 so enable the OC1PE
					if(Sitting->TIME_RCR){
						TIMx->CCMR1.Compare_BIT_NAME.OC2PE=1;
					}else{
						TIMx->CCMR1.Compare_BIT_NAME.OC2PE=0;
					}
					TIMx->CCER.BIT_NAME.CC2P=CTC_Sitting->CTC_POL;
					//			CC1S	  00: CC1 channel is configured as output
					TIMx->CCMR1.Compare_BIT_NAME.CC2S=0;
					//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

					TIMx->CCER.BIT_NAME.CC2E=1;
					MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,2);

					break;
				case 3:
					TIMx->CCR3=Sitting->TIME_CCR;
					TIMx->CCMR2.Compare_BIT_NAME.OC3M=active;
					//if the preload > 0 so enable the OC1PE
					if(Sitting->TIME_RCR){
						TIMx->CCMR2.Compare_BIT_NAME.OC3PE=1;
					}else{
						TIMx->CCMR2.Compare_BIT_NAME.OC3PE=0;
					}
					TIMx->CCER.BIT_NAME.CC3P=CTC_Sitting->CTC_POL;
					//			CC1S	  00: CC1 channel is configured as output
					TIMx->CCMR2.Compare_BIT_NAME.CC3S=0;
					//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

					TIMx->CCER.BIT_NAME.CC3E=1;
					MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,3);

					break;
				case 4:
					TIMx->CCR4=Sitting->TIME_CCR;
					TIMx->CCMR2.Compare_BIT_NAME.OC4M=active;
					//if the preload > 0 so enable the OC1PE
					if(Sitting->TIME_RCR){
						TIMx->CCMR2.Compare_BIT_NAME.OC4PE=1;
					}else{
						TIMx->CCMR2.Compare_BIT_NAME.OC4PE=0;
					}
					TIMx->CCER.BIT_NAME.CC4P=CTC_Sitting->CTC_POL;
					//			CC1S	  00: CC1 channel is configured as output
					TIMx->CCMR2.Compare_BIT_NAME.CC4S=0;
					//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

					TIMx->CCER.BIT_NAME.CC4E=1;
					MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,4);

					break;
				default:
					GP_ERROR_HANDLER();
					break;

				}
				break;





				case inactive:
					switch(CTC_Sitting->CHx_num){
					case 1:
						TIMx->CCR1=Sitting->TIME_CCR;
						TIMx->CCMR1.Compare_BIT_NAME.OC1M=inactive;
						//if the preload > 0 so enable the OC1PE
						if(Sitting->TIME_RCR){
							TIMx->CCMR1.Compare_BIT_NAME.OC1PE=1;
						}else{
							TIMx->CCMR1.Compare_BIT_NAME.OC1PE=0;
						}
						TIMx->CCER.BIT_NAME.CC1P=CTC_Sitting->CTC_POL;
						//			CC1S	  00: CC1 channel is configured as output
						TIMx->CCMR1.Compare_BIT_NAME.CC1S=0;
						//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

						TIMx->CCER.BIT_NAME.CC1E=1;
						MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,1);

						break;
					case 2:
						TIMx->CCR2=Sitting->TIME_CCR;
						TIMx->CCMR1.Compare_BIT_NAME.OC2M=inactive;
						//if the preload > 0 so enable the OC1PE
						if(Sitting->TIME_RCR){
							TIMx->CCMR1.Compare_BIT_NAME.OC2PE=1;
						}else{
							TIMx->CCMR1.Compare_BIT_NAME.OC2PE=0;
						}
						TIMx->CCER.BIT_NAME.CC2P=CTC_Sitting->CTC_POL;
						//			CC1S	  00: CC1 channel is configured as output
						TIMx->CCMR1.Compare_BIT_NAME.CC2S=0;
						//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

						TIMx->CCER.BIT_NAME.CC2E=1;
						MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,2);

						break;
					case 3:
						TIMx->CCR3=Sitting->TIME_CCR;
						TIMx->CCMR2.Compare_BIT_NAME.OC3M=inactive;
						//if the preload > 0 so enable the OC1PE
						if(Sitting->TIME_RCR){
							TIMx->CCMR2.Compare_BIT_NAME.OC3PE=1;
						}else{
							TIMx->CCMR2.Compare_BIT_NAME.OC3PE=0;
						}
						TIMx->CCER.BIT_NAME.CC3P=CTC_Sitting->CTC_POL;
						//			CC1S	  00: CC1 channel is configured as output
						TIMx->CCMR2.Compare_BIT_NAME.CC3S=0;
						//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

						TIMx->CCER.BIT_NAME.CC3E=1;
						MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,3);

						break;
					case 4:
						TIMx->CCR4=Sitting->TIME_CCR;
						TIMx->CCMR2.Compare_BIT_NAME.OC4M=inactive;
						//if the preload > 0 so enable the OC1PE
						if(Sitting->TIME_RCR){
							TIMx->CCMR2.Compare_BIT_NAME.OC4PE=1;
						}else{
							TIMx->CCMR2.Compare_BIT_NAME.OC4PE=0;
						}
						TIMx->CCER.BIT_NAME.CC4P=CTC_Sitting->CTC_POL;
						//			CC1S	  00: CC1 channel is configured as output
						TIMx->CCMR2.Compare_BIT_NAME.CC4S=0;
						//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

						TIMx->CCER.BIT_NAME.CC4E=1;
						MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,4);

						break;
					default:
						GP_ERROR_HANDLER();
						break;

					}
					break;
					case Toggle:
						switch(CTC_Sitting->CHx_num){
						case 1:
							TIMx->CCR1=Sitting->TIME_CCR;
							TIMx->CCMR1.Compare_BIT_NAME.OC1M=Toggle;
							//if the preload > 0 so enable the OC1PE
							if(Sitting->TIME_RCR){
								TIMx->CCMR1.Compare_BIT_NAME.OC1PE=1;
							}else{
								TIMx->CCMR1.Compare_BIT_NAME.OC1PE=0;
							}
							TIMx->CCER.BIT_NAME.CC1P=CTC_Sitting->CTC_POL;
							//			CC1S	  00: CC1 channel is configured as output
							TIMx->CCMR1.Compare_BIT_NAME.CC1S=0;
							//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

							TIMx->CCER.BIT_NAME.CC1E=1;
							MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,1);

							break;
						case 2:
							TIMx->CCR2=Sitting->TIME_CCR;
							TIMx->CCMR1.Compare_BIT_NAME.OC2M=Toggle;
							//if the preload > 0 so enable the OC1PE
							if(Sitting->TIME_RCR){
								TIMx->CCMR1.Compare_BIT_NAME.OC2PE=1;
							}else{
								TIMx->CCMR1.Compare_BIT_NAME.OC2PE=0;
							}
							TIMx->CCER.BIT_NAME.CC2P=CTC_Sitting->CTC_POL;
							//			CC1S	  00: CC1 channel is configured as output
							TIMx->CCMR1.Compare_BIT_NAME.CC2S=0;
							//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

							TIMx->CCER.BIT_NAME.CC2E=1;
							MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,2);

							break;
						case 3:
							TIMx->CCR3=Sitting->TIME_CCR;
							TIMx->CCMR2.Compare_BIT_NAME.OC3M=Toggle;
							//if the preload > 0 so enable the OC1PE
							if(Sitting->TIME_RCR){
								TIMx->CCMR2.Compare_BIT_NAME.OC3PE=1;
							}else{
								TIMx->CCMR2.Compare_BIT_NAME.OC3PE=0;
							}
							TIMx->CCER.BIT_NAME.CC3P=CTC_Sitting->CTC_POL;
							//			CC1S	  00: CC1 channel is configured as output
							TIMx->CCMR2.Compare_BIT_NAME.CC3S=0;
							//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

							TIMx->CCER.BIT_NAME.CC3E=1;
							MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,3);

							break;
						case 4:
							TIMx->CCR4=Sitting->TIME_CCR;
							TIMx->CCMR2.Compare_BIT_NAME.OC4M=Toggle;
							//if the preload > 0 so enable the OC1PE
							if(Sitting->TIME_RCR){
								TIMx->CCMR2.Compare_BIT_NAME.OC4PE=1;
							}else{
								TIMx->CCMR2.Compare_BIT_NAME.OC4PE=0;
							}
							TIMx->CCER.BIT_NAME.CC4P=CTC_Sitting->CTC_POL;
							//			CC1S	  00: CC1 channel is configured as output
							TIMx->CCMR2.Compare_BIT_NAME.CC4S=0;
							//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

							TIMx->CCER.BIT_NAME.CC4E=1;
							MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,4);

							break;
						default:
							GP_ERROR_HANDLER();
							break;

						}
						break;
						case PWM_AH:
							switch(CTC_Sitting->CHx_num){
							case 1:
								TIMx->CCR1=Sitting->TIME_CCR;
								TIMx->CCMR1.Compare_BIT_NAME.OC1M=PWM_AH;
								//if the preload > 0 so enable the OC1PE
								if(Sitting->TIME_RCR){
									TIMx->CCMR1.Compare_BIT_NAME.OC1PE=1;
								}else{
									TIMx->CCMR1.Compare_BIT_NAME.OC1PE=0;
								}
								TIMx->CCER.BIT_NAME.CC1P=CTC_Sitting->CTC_POL;
								//			CC1S	  00: CC1 channel is configured as output
								TIMx->CCMR1.Compare_BIT_NAME.CC1S=0;
								//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

								TIMx->CCER.BIT_NAME.CC1E=1;
								MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,1);

								break;
							case 2:
								TIMx->CCR2=Sitting->TIME_CCR;
								TIMx->CCMR1.Compare_BIT_NAME.OC2M=PWM_AH;
								//if the preload > 0 so enable the OC1PE
								if(Sitting->TIME_RCR){
									TIMx->CCMR1.Compare_BIT_NAME.OC2PE=1;
								}else{
									TIMx->CCMR1.Compare_BIT_NAME.OC2PE=0;
								}
								TIMx->CCER.BIT_NAME.CC2P=CTC_Sitting->CTC_POL;
								//			CC1S	  00: CC1 channel is configured as output
								TIMx->CCMR1.Compare_BIT_NAME.CC2S=0;
								//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

								TIMx->CCER.BIT_NAME.CC2E=1;
								MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,2);

								break;
							case 3:
								TIMx->CCR3=Sitting->TIME_CCR;
								TIMx->CCMR2.Compare_BIT_NAME.OC3M=PWM_AH;
								//if the preload > 0 so enable the OC1PE
								if(Sitting->TIME_RCR){
									TIMx->CCMR2.Compare_BIT_NAME.OC3PE=1;
								}else{
									TIMx->CCMR2.Compare_BIT_NAME.OC3PE=0;
								}
								TIMx->CCER.BIT_NAME.CC3P=CTC_Sitting->CTC_POL;
								//			CC1S	  00: CC1 channel is configured as output
								TIMx->CCMR2.Compare_BIT_NAME.CC3S=0;
								//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

								TIMx->CCER.BIT_NAME.CC3E=1;
								MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,3);

								break;
							case 4:
								TIMx->CCR4=Sitting->TIME_CCR;
								TIMx->CCMR2.Compare_BIT_NAME.OC4M=PWM_AH;
								//if the preload > 0 so enable the OC1PE
								if(Sitting->TIME_RCR){
									TIMx->CCMR2.Compare_BIT_NAME.OC4PE=1;
								}else{
									TIMx->CCMR2.Compare_BIT_NAME.OC4PE=0;
								}
								TIMx->CCER.BIT_NAME.CC4P=CTC_Sitting->CTC_POL;
								//			CC1S	  00: CC1 channel is configured as output
								TIMx->CCMR2.Compare_BIT_NAME.CC4S=0;
								//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

								TIMx->CCER.BIT_NAME.CC4E=1;
								MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,4);

								break;
							default:
								GP_ERROR_HANDLER();
								break;

							}
							break;
							case PWM_AL:
								switch(CTC_Sitting->CHx_num){
								case 1:
									TIMx->CCR1=Sitting->TIME_CCR;
									TIMx->CCMR1.Compare_BIT_NAME.OC1M=PWM_AL;
									//if the preload > 0 so enable the OC1PE
									if(Sitting->TIME_RCR){
										TIMx->CCMR1.Compare_BIT_NAME.OC1PE=1;
									}else{
										TIMx->CCMR1.Compare_BIT_NAME.OC1PE=0;
									}
									TIMx->CCER.BIT_NAME.CC1P=CTC_Sitting->CTC_POL;
									//			CC1S	  00: CC1 channel is configured as output
									TIMx->CCMR1.Compare_BIT_NAME.CC1S=0;
									//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

									TIMx->CCER.BIT_NAME.CC1E=1;
									MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,1);

									break;
								case 2:
									TIMx->CCR2=Sitting->TIME_CCR;
									TIMx->CCMR1.Compare_BIT_NAME.OC2M=PWM_AL;
									//if the preload > 0 so enable the OC1PE
									if(Sitting->TIME_RCR){
										TIMx->CCMR1.Compare_BIT_NAME.OC2PE=1;
									}else{
										TIMx->CCMR1.Compare_BIT_NAME.OC2PE=0;
									}
									TIMx->CCER.BIT_NAME.CC2P=CTC_Sitting->CTC_POL;
									//			CC1S	  00: CC1 channel is configured as output
									TIMx->CCMR1.Compare_BIT_NAME.CC2S=0;
									//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

									TIMx->CCER.BIT_NAME.CC2E=1;
									MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,2);

									break;
								case 3:
									TIMx->CCR3=Sitting->TIME_CCR;
									TIMx->CCMR2.Compare_BIT_NAME.OC3M=PWM_AL;
									//if the preload > 0 so enable the OC1PE
									if(Sitting->TIME_RCR){
										TIMx->CCMR2.Compare_BIT_NAME.OC3PE=1;
									}else{
										TIMx->CCMR2.Compare_BIT_NAME.OC3PE=0;
									}
									TIMx->CCER.BIT_NAME.CC3P=CTC_Sitting->CTC_POL;
									//			CC1S	  00: CC1 channel is configured as output
									TIMx->CCMR2.Compare_BIT_NAME.CC3S=0;
									//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

									TIMx->CCER.BIT_NAME.CC3E=1;
									MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,3);

									break;
								case 4:
									TIMx->CCR4=Sitting->TIME_CCR;
									TIMx->CCMR2.Compare_BIT_NAME.OC4M=PWM_AL;
									//if the preload > 0 so enable the OC1PE
									if(Sitting->TIME_RCR){
										TIMx->CCMR2.Compare_BIT_NAME.OC4PE=1;
									}else{
										TIMx->CCMR2.Compare_BIT_NAME.OC4PE=0;
									}
									TIMx->CCER.BIT_NAME.CC4P=CTC_Sitting->CTC_POL;
									//			CC1S	  00: CC1 channel is configured as output
									TIMx->CCMR2.Compare_BIT_NAME.CC4S=0;
									//Note: CCxS bits are writable only when the channel is OFF (CC2E = 0 in TIMx_CCER).**************

									TIMx->CCER.BIT_NAME.CC4E=1;
									MCAL_SET_GP_TIMx_GPIO(TIMx,PWM,4);

									break;
								default:
									GP_ERROR_HANDLER();
									break;

								}
								break;

								default:
									GP_ERROR_HANDLER();
									break;
		}
		TIMx->CR1.BIT_NAME.CEN=1;

		if(Sitting->INT_EN_DIS==INT_EN){
			switch (CTC_Sitting->CHx_num) {
			case 1:
				TIMx->DIER.BIT_NAME.CC1IE=1;

				break;
			case 2:
				TIMx->DIER.BIT_NAME.CC2IE=1;

				break;
			case 3:
				TIMx->DIER.BIT_NAME.CC3IE=1;

				break;
			case 4:
				TIMx->DIER.BIT_NAME.CC4IE=1;

				break;
			default:
				GP_ERROR_HANDLER();
				break;
			}
			if(TIMx== TIM2) 	NVIC_ISER0|=(1<<28);
			else if(TIMx== TIM3) NVIC_ISER0|=(1<<29);
			else if(TIMx== TIM4) NVIC_ISER0|=(1<<30);

		}else{
			switch (CTC_Sitting->CHx_num) {
			case 1:
				while(!TIMx->SR.BIT_NAME.CC1IF);
				TIMx->SR.BIT_NAME.CC1IF=0;
				break;
			case 2:
				while(!TIMx->SR.BIT_NAME.UIF);

				while(!TIMx->SR.BIT_NAME.CC2IF);
				TIMx->SR.BIT_NAME.CC2IF=0;
				TIMx->SR.BIT_NAME.UIF=0;

				break;
			case 3:
				while(!TIMx->SR.BIT_NAME.CC3IF);
				TIMx->SR.BIT_NAME.CC3IF=0;
				break;
			case 4:
				while(!TIMx->SR.BIT_NAME.CC4IF);
				TIMx->SR.BIT_NAME.CC4IF=0;
				break;
			default:
				GP_ERROR_HANDLER();
				break;
			}

		}
	}else{
		GP_ERROR_HANDLER();
	}
}
////////////////////////////////




void GP_TIMx_ICU_init(GP_TIMx_REG* TIMx,GP_TIMERx_config* Sitting,GP_TIMERx_ICU_config* ICU_sitting){
	if(Sitting->mode==ICU ){
		g_GP_TIMX=TIMx;

		if(TIMx== TIM2)			{RCC->APB1ENR|=(1<<0);		g_GP_Sitting[0]=(* Sitting);	g_GP_ICU_MEM[0]=(*ICU_sitting);	}
		else if(TIMx== TIM3)	{RCC->APB1ENR|=(1<<1);		g_GP_Sitting[1]=(* Sitting);	g_GP_ICU_MEM[0]=(*ICU_sitting);	}
		else if(TIMx== TIM4)	{RCC->APB1ENR|=(1<<2);		g_GP_Sitting[2]=(* Sitting);	g_GP_ICU_MEM[0]=(*ICU_sitting);	}


		//	// 2.select the pre vale
		//	TIMx->PSC=Sitting->TIME_PSC;
		//
		TIMx->ARR=65535; // to make the counter reach the max value (2^16)-1
		switch(ICU_sitting->CHx_num){
		case 1:
			//1.Bits 1:0 CC1S: Capture/Compare 1 Selection
			TIMx->CCMR1.input_NAME.CC1S=0b01;
			//2. Bits 3:2 IC1PSC: Input capture 1 prescaler
			//00: no prescaler, capture is done each time an edge is detected on the capture input
			TIMx->CCMR1.input_NAME.IC1PSC=0;

			// 3. Bit 1 CC1P: Capture/Compare 1 output polarit
			//0: non-inverted: capture is done on a rising edge of IC1. When used as external trigger, IC1 is non-inverted.
			TIMx->CCER.BIT_NAME.CC1P=ICU_sitting->EDGE_SELECT;

			TIMx->CCER.BIT_NAME.CC1E=1;
			break;
		case 2:
			//1.Bits 1:0 CC1S: Capture/Compare 1 Selection
			TIMx->CCMR1.input_NAME.CC2S=0b01;
			//2. Bits 3:2 IC1PSC: Input capture 1 prescaler
			//00: no prescaler, capture is done each time an edge is detected on the capture input
			TIMx->CCMR1.input_NAME.IC2PSC=0;

			// 3. Bit 1 CC1P: Capture/Compare 1 output polarit
			//0: non-inverted: capture is done on a rising edge of IC1. When used as external trigger, IC1 is non-inverted.
			TIMx->CCER.BIT_NAME.CC2P=ICU_sitting->EDGE_SELECT;

			TIMx->CCER.BIT_NAME.CC2E=1;
			break;
		case 3:
			//1.Bits 1:0 CC1S: Capture/Compare 1 Selection
			TIMx->CCMR2.input_NAME.CC3S=0b01;
			//2. Bits 3:2 IC1PSC: Input capture 1 prescaler
			//00: no prescaler, capture is done each time an edge is detected on the capture input
			TIMx->CCMR2.input_NAME.IC3PSC=0;

			// 3. Bit 1 CC1P: Capture/Compare 1 output polarit
			//0: non-inverted: capture is done on a rising edge of IC1. When used as external trigger, IC1 is non-inverted.
			TIMx->CCER.BIT_NAME.CC3P=ICU_sitting->EDGE_SELECT;

			TIMx->CCER.BIT_NAME.CC3E=1;
			break;
		case 4:
			//1.Bits 1:0 CC1S: Capture/Compare 1 Selection
			TIMx->CCMR2.input_NAME.CC4S=0b01;
			//2. Bits 3:2 IC1PSC: Input capture 1 prescaler
			//00: no prescaler, capture is done each time an edge is detected on the capture input
			TIMx->CCMR2.input_NAME.IC4PSC=0;

			// 3. Bit 1 CC1P: Capture/Compare 1 output polarit
			//0: non-inverted: capture is done on a rising edge of IC1. When used as external trigger, IC1 is non-inverted.
			TIMx->CCER.BIT_NAME.CC4P=ICU_sitting->EDGE_SELECT;

			TIMx->CCER.BIT_NAME.CC4E=1;
			break;
		default:
			GP_ERROR_HANDLER();
			break;

		}
		TIMx->CCMR1.input_NAME.IC1F=0b0011;//fSAMPLING=fCK_INT, N=8 //THIS CONSTANT FILTER



		if(Sitting->INT_EN_DIS == INT_EN){
			switch (ICU_sitting->CHx_num) {
			case 1:
				TIMx->DIER.BIT_NAME.CC1IE=1;

				break;
			case 2:
				TIMx->DIER.BIT_NAME.CC2IE=1;

				break;
			case 3:
				TIMx->DIER.BIT_NAME.CC3IE=1;

				break;
			case 4:
				TIMx->DIER.BIT_NAME.CC4IE=1;

				break;
			default:
				GP_ERROR_HANDLER();
				break;
			}
			if(TIMx== TIM2) 	NVIC_ISER0|=(1<<28);
			else if(TIMx== TIM3) NVIC_ISER0|=(1<<29);
			else if(TIMx== TIM4) NVIC_ISER0|=(1<<30);

		}

		TIMx->CR1.BIT_NAME.CEN=1;

	}else{
		GP_ERROR_HANDLER();
	}
}
/////////////////////////////////////////////

void GP_TIMx_Icu_setEdgeDetectionType (GP_TIMx_REG* TIMx,GP_TIMER_ICU_Edge_Selection dir){
	if(TIMx== TIM2) {
		switch(g_GP_ICU_MEM[0].CHx_num){
			case 1:
				if (dir ==RISSING){
					TIMx->CCER.BIT_NAME.CC1P=0;
				}else if(dir == FALLING){
					TIMx->CCER.BIT_NAME.CC1P=1;

				}
				break;
			case 2:
				if (dir ==RISSING){
					TIMx->CCER.BIT_NAME.CC2P=0;
				}else if(dir == FALLING){
					TIMx->CCER.BIT_NAME.CC2P=1;

				}
				break;
			case 3:
				if (dir ==RISSING){
					TIMx->CCER.BIT_NAME.CC3P=0;
				}else if(dir == FALLING){
					TIMx->CCER.BIT_NAME.CC3P=1;

				}
				break;
			case 4:
				if (dir ==RISSING){
					TIMx->CCER.BIT_NAME.CC4P=0;
				}else if(dir == FALLING){
					TIMx->CCER.BIT_NAME.CC4P=1;

				}
				break;
			default:
				GP_ERROR_HANDLER();
				break;
			}

	}
	else if(TIMx== TIM3){
		switch(g_GP_ICU_MEM[1].CHx_num){
					case 1:
						if (dir ==RISSING){
							TIMx->CCER.BIT_NAME.CC1P=0;
						}else if(dir == FALLING){
							TIMx->CCER.BIT_NAME.CC1P=1;

						}
						break;
					case 2:
						if (dir ==RISSING){
							TIMx->CCER.BIT_NAME.CC2P=0;
						}else if(dir == FALLING){
							TIMx->CCER.BIT_NAME.CC2P=1;

						}
						break;
					case 3:
						if (dir ==RISSING){
							TIMx->CCER.BIT_NAME.CC3P=0;
						}else if(dir == FALLING){
							TIMx->CCER.BIT_NAME.CC3P=1;

						}
						break;
					case 4:
						if (dir ==RISSING){
							TIMx->CCER.BIT_NAME.CC4P=0;
						}else if(dir == FALLING){
							TIMx->CCER.BIT_NAME.CC4P=1;

						}
						break;
					default:
						GP_ERROR_HANDLER();
						break;
					}

	}
	else if(TIMx== TIM4) {
		switch(g_GP_ICU_MEM[2].CHx_num){
					case 1:
						if (dir ==RISSING){
							TIMx->CCER.BIT_NAME.CC1P=0;
						}else if(dir == FALLING){
							TIMx->CCER.BIT_NAME.CC1P=1;

						}
						break;
					case 2:
						if (dir ==RISSING){
							TIMx->CCER.BIT_NAME.CC2P=0;
						}else if(dir == FALLING){
							TIMx->CCER.BIT_NAME.CC2P=1;

						}
						break;
					case 3:
						if (dir ==RISSING){
							TIMx->CCER.BIT_NAME.CC3P=0;
						}else if(dir == FALLING){
							TIMx->CCER.BIT_NAME.CC3P=1;

						}
						break;
					case 4:
						if (dir ==RISSING){
							TIMx->CCER.BIT_NAME.CC4P=0;
						}else if(dir == FALLING){
							TIMx->CCER.BIT_NAME.CC4P=1;

						}
						break;
					default:
						GP_ERROR_HANDLER();
						break;
					}

	}



}


uint16_t GP_TIMx_getTime(GP_TIMx_REG* TIMx,uint8_t CHx){
	switch (CHx) {
	case 1:
		return TIM1->CCR1;
		break;
	case 2:
		return TIM1->CCR2;
		break;
	case 3:
		return TIM1->CCR3;
		break;
	case 4:
		return TIM1->CCR4;
		break;
	default:
		GP_ERROR_HANDLER();
		break;
		return 0; //ملهاش لزمه

	}
	return 0; //ملهاش لزمه

}

void GP_TIMX_Clear(GP_TIMx_REG* TIMx){

	TIMx->CNT=0;
}
void GP_TIMx_Deint(GP_TIMx_REG* TIMx){
	TIMx->CR1.ALL_BITS=0;
	TIMx->ARR=0;
	TIMx->CCER.ALL_BITS=0;
	TIMx->CCMR1.ALL_BITS=0;
	TIMx->CCMR2.ALL_BITS=0;
	TIMx->CCR1=0;
	TIMx->CCR2=0;
	TIMx->CCR3=0;
	TIMx->CCR4=0;
	TIMx->CNT=0;
	TIMx->CR2.ALL_BITS=0;
	TIMx->PSC=0;
	if(TIMx== TIM2)			{RCC->APB1RSTR|=(1<<0);		RCC->APB1RSTR&=~(1<<0);	}
			else if(TIMx== TIM3)	{RCC->APB1RSTR|=(1<<1);		RCC->APB1RSTR&=~(1<<1);	}
			else if(TIMx== TIM4)	{RCC->APB1RSTR|=(1<<2);		RCC->APB1RSTR&=~(1<<2);	}
}

void TIM2_IRQHandler(){
	GP_TIMx_ERROR_src *ERROR;
	if(TIM2->SR.BIT_NAME.UIF){
			ERROR->UIF=1;
			TIM2->SR.BIT_NAME.UIF=0;
		}

		else if(TIM2->SR.BIT_NAME.CC1IF){
			ERROR->CC1IF=1;
			TIM2->SR.BIT_NAME.CC1IF=0;


		}
		else if(TIM2->SR.BIT_NAME.CC2IF){
			ERROR->CC2IF=1;
			TIM2->SR.BIT_NAME.CC2IF=0;

		}
		else if(TIM2->SR.BIT_NAME.CC3IF){
			ERROR->CC3IF=1;
			TIM2->SR.BIT_NAME.CC3IF=0;

		}
		else if(TIM2->SR.BIT_NAME.CC4IF){
			ERROR->CC4IF=1;
			TIM2->SR.BIT_NAME.CC4IF=0;

		}
	g_GP_Sitting[0].f_callback(ERROR);

}
void TIM3_IRQHandler(){
	GP_TIMx_ERROR_src *ERROR;
	if(TIM3->SR.BIT_NAME.UIF){
		ERROR->UIF=1;
		TIM3->SR.BIT_NAME.UIF=0;
	}

	else if(TIM3->SR.BIT_NAME.CC1IF){
		ERROR->CC1IF=1;
		TIM3->SR.BIT_NAME.CC1IF=0;


	}
	else if(TIM3->SR.BIT_NAME.CC2IF){
		ERROR->CC2IF=1;
		TIM3->SR.BIT_NAME.CC2IF=0;

	}
	else if(TIM3->SR.BIT_NAME.CC3IF){
		ERROR->CC3IF=1;
		TIM3->SR.BIT_NAME.CC3IF=0;

	}
	else if(TIM3->SR.BIT_NAME.CC4IF){
		ERROR->CC4IF=1;
		TIM3->SR.BIT_NAME.CC4IF=0;

	}
	g_GP_Sitting[1].f_callback(ERROR);


}void TIM4_IRQHandler(){
	volatile  GP_TIMx_ERROR_src *ERROR;
	if(TIM4->SR.BIT_NAME.UIF){
			ERROR->UIF=1;
			TIM4->SR.BIT_NAME.UIF=0;
		}

		else if(TIM4->SR.BIT_NAME.CC1IF){
			ERROR->CC1IF=1;
			TIM4->SR.BIT_NAME.CC1IF=0;


		}
		else if(TIM4->SR.BIT_NAME.CC2IF){
			ERROR->CC2IF=1;
			TIM4->SR.BIT_NAME.CC2IF=0;
			ERROR->UIF=1;

		}
		else if(TIM4->SR.BIT_NAME.CC3IF){
			ERROR->CC3IF=1;
			TIM4->SR.BIT_NAME.CC3IF=0;

		}
		else if(TIM4->SR.BIT_NAME.CC4IF){
			ERROR->CC4IF=1;
			TIM4->SR.BIT_NAME.CC4IF=0;

		}
	g_GP_Sitting[2].f_callback(ERROR);


}


void _delay_us(GP_TIMx_REG* TIMx ,uint16_t delay){
	uint16_t PRE_scal=(F_CPU/1000000UL);
	if(PRE_scal!=1) PRE_scal--; //The counter clock frequency CK_CNT is equal to fCK_PSC / (PSC[15:0] + 1).
	GP_TIMERx_config l_t_delay={PRE_scal,delay,0,0,INT_DIS,NORMAL,NULL};
	GP_TIMERx_NORMAL_config NORMAL_SIT={Up};
	GP_TIMx_start(TIMx,&l_t_delay,&NORMAL_SIT);

}


void _delay_ms(GP_TIMx_REG* TIMx ,uint16_t delay){
	for(uint32_t i=0;i<delay;i++)
	_delay_us(TIMx,1000);
}
void _delay_s(GP_TIMx_REG* TIMx ,uint16_t delay){
	for(uint32_t i=0;i<delay;i++)
	_delay_ms(TIMx,1000);
}



