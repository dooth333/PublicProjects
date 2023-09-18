#include "stm32f10x.h"                  // Device header
#include "PWM.h"
u8 Motor_flag = 0;
void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15| GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);  
}

void Motor_Open(void)
{
	Motor_flag = 1;
	GPIO_SetBits(GPIOC,GPIO_Pin_15);
	GPIO_ResetBits(GPIOC,GPIO_Pin_14);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
}

void Motor_Close(void)
{
	Motor_flag = 0;
	GPIO_SetBits(GPIOC,GPIO_Pin_15);
	GPIO_ResetBits(GPIOC,GPIO_Pin_14);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}


void Motor_Turn(void)
{
	if(Motor_flag == 0)
	{
		Motor_Open();
	}else if(Motor_flag == 1)
	{
		Motor_Close();
	}
}
