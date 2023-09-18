#include "stm32f10x.h"                  // Device header
#include "buzzer.h"


u8 Buzzer_flag = 0;	//蜂鸣器的状态，0响、1关

/**
  * @brief  Buzzer初始化
  * @param  None
  * @retval None
  */
void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_BUZZER;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_BUZZER);
}

/**Buzzer开
  * @param  None
  * @retval None
  */
void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_BUZZER);
	Buzzer_flag = 1;
}

/**
  * @brief  Buzzer关
  * @param  None
  * @retval None
  */
void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_BUZZER);
	Buzzer_flag = 0;
}


/**
  * @brief  Buzzer转换
  * @param  None
  * @retval None
  */
void Buzzer_Turn(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_BUZZER)  == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_BUZZER);
		Buzzer_flag = 0;
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_BUZZER);
		Buzzer_flag = 0;
	}
	
}