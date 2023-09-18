#include "stm32f10x.h"                  // Device header
#include "relay.h"

/**
  * @brief  继电器初始化
  * @param  None
  * @retval None
  */
void relay_Init(void)
{
	RCC_APB2PeriphClockCmd(GPIO_Periph_relay,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_relay_1 | GPIO_relay_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_GPIOx_relay, &GPIO_InitStructure);
	GPIO_SetBits(GPIO_GPIOx_relay,GPIO_relay_1 | GPIO_relay_2);
}

/**
  * @brief  继电器1开,风扇
  * @param  None
  * @retval None
  */
void relay1_ON(void)
{
	GPIO_ResetBits(GPIO_GPIOx_relay,GPIO_relay_1);
}

/**
  * @brief  继电器1关,风扇
  * @param  None
  * @retval None
  */
void relay1_OFF(void)
{
	GPIO_SetBits(GPIO_GPIOx_relay,GPIO_relay_1);
}

/**
  * @brief  继电器1转换,风扇
  * @param  None
  * @retval None
  */
void relay1_Turn(void)
{
	if(GPIO_ReadInputDataBit(GPIO_GPIOx_relay,GPIO_relay_1)  == 0)
	{
		GPIO_SetBits(GPIO_GPIOx_relay,GPIO_relay_1);
	}
	else
	{
		GPIO_ResetBits(GPIO_GPIOx_relay,GPIO_relay_1);
	}
	
}


/**
  * @brief  继电器2开,水泵
  * @param  None
  * @retval None
  */
void relay2_ON(void)
{
	GPIO_ResetBits(GPIO_GPIOx_relay,GPIO_relay_2);
}

/**
  * @brief  继电器2关,水泵
  * @param  None
  * @retval None
  */
void relay2_OFF(void)
{
	GPIO_SetBits(GPIO_GPIOx_relay,GPIO_relay_2);
}


/**
  * @brief  继电器2转换,水泵
  * @param  None
  * @retval None
  */
void relay2_Turn(void)
{
	if(GPIO_ReadInputDataBit(GPIO_GPIOx_relay,GPIO_relay_2)  == 0)
	{
		GPIO_SetBits(GPIO_GPIOx_relay,GPIO_relay_2);
	}
	else
	{
		GPIO_ResetBits(GPIO_GPIOx_relay,GPIO_relay_2);
	}
	
}