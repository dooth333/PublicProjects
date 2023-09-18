#include "stm32f10x.h"                  // Device header

/**
  * @brief  PWM初始化，使用TIM2的通道2，用于舵机角度转换
  * @param  None
  * @retval None
  */
void PWM_Init(void)
{
//1、RCC开启时钟：
	//把TIM外设和GPIO外设的时钟打开
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
//2、配置时基单元
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 20000-1;//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	//避免刚初始化完就进入中断的问题，即计数从1开始
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	//使能中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
//3、配置输出比较单元
//包括：CCR的值、输出比较模式、极性选择、输出使能
	TIM_OCInitTypeDef TIM_OCInitStructure;
	//先赋初始值就算用不到也可避免突然用的而没有值的错误
	TIM_OCStructInit(&TIM_OCInitStructure);
	//然后更改需要用的值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable ; 
	TIM_OCInitStructure.TIM_Pulse = 0; //CCR
	TIM_OC2Init(TIM2,&TIM_OCInitStructure);

// 4、配置GPIO
//把GPIO对应的GPIO初始化为复用推挽输出
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	TIM_Cmd(TIM2,ENABLE);
}

/**
  * @brief  用于设置舵机角度
  * @param  None
  * @retval None
  */
void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2,Compare);
}

