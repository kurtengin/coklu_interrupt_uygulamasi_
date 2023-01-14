
/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_Initstructure;
EXTI_InitTypeDef EXTI_Initstructure;  //EXT. INT.
NVIC_InitTypeDef NVIC_Initstructure;

void Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); // led
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //button

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  //ext. int. port enable

	//led

	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 | GPIO_Pin_0 |  GPIO_Pin_1 ;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_Initstructure);

	//BUTTON1

	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_1;   //PA1
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_Initstructure);

	//BUTTON2
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_2;   //PA2
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_Initstructure);


	//EXT. INT.

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource2);

	//BUTTON 1
	EXTI_Initstructure.EXTI_Line=EXTI_Line1;
	EXTI_Initstructure.EXTI_LineCmd=ENABLE;
	EXTI_Initstructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_Initstructure);

	//BUTTON2
	EXTI_Initstructure.EXTI_Line=EXTI_Line2;
	EXTI_Initstructure.EXTI_LineCmd=ENABLE;
	EXTI_Initstructure.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_Initstructure);

	//NVIC

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	//BUTTON1
	NVIC_Initstructure.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_Initstructure);

	//BUTTON2
	NVIC_Initstructure.NVIC_IRQChannel=EXTI2_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_Initstructure);

}

void delay(uint32_t time){

	while(time--);

}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		//öncelikli

		int i=0;
		do{

			GPIO_ToggleBits(GPIOD, GPIO_Pin_1);
			delay(160000000);

			i++;

		}while(i<5);

		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
		{

			int i=0;
			do{

				GPIO_ToggleBits(GPIOD, GPIO_Pin_0);
				delay(160000000);

				i++;

			}while(i<5);

			EXTI_ClearITPendingBit(EXTI_Line2);
		}

}

int main(void)
{
	Config();

	while(1)

	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	}

}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
