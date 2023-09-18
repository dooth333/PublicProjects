#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Servo.h"
u8 Servo_flag = 0;//舵机的状态，1：开门、0：关门
/**
  * @brief 初始化舵机
  * @param  None
  * @retval None
  */
void Servo_Init(void)
{
	PWM_Init();
	Servo_close();
}

/**
  * @brief  旋转特定角度
  * @param  角度
  * @retval None
  */
void Servo_setAngle(float Angle)
{
	PWM_SetCompare2(Angle / 180 * 2000 + 500);
}

/**
  * @brief  开门
  * @param  None
  * @retval None
  */
void Servo_open()
{
	Servo_setAngle(0);
	Servo_flag = 1;
}

/**
  * @brief 关门 
  * @param  None
  * @retval None
  */
void Servo_close()
{
	Servo_setAngle(90);
	Servo_flag = 0;
}

/**
  * @brief 开关状态转换
  * @param  None
  * @retval None
  */
void Servo_Turn()
{
	if(Servo_flag == 0)
	{
		Servo_open();
	}
	else
	{
		Servo_close();
	}
}
