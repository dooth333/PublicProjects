#include "stm32f10x.h"                  // Device header
#include "AutoControl.h"

//硬件驱动
#include "LED.h"
#include "Timer.h"
#include "buzzer.h"
#include "Servo.h"
#include "relay.h"
#include "SGP30.h"

//0为关闭自动模式，1为开启自动模式
uint8_t AutoControl_mode =0;


struct ENV_Struct tempControl;//温度结构体
struct ENV_Struct lightControl;//光照强度控制结构体
struct ENV_Struct soilHumControl;//土壤湿度控制结构体
struct ENV_Struct Co2Control;//土壤湿度控制结构体

void Control_Init(void)
{
	//温度初始化
	tempControl.ENV_free = 0;
	tempControl.ENV_MaxValue = 26;
	tempControl.ENV_MiniValue = 10;
	
	//土壤湿度初始化
	soilHumControl.ENV_free = 0;
	soilHumControl.ENV_MaxValue = 2100;
	soilHumControl.ENV_MiniValue = 1500;
	
	//光照强度初始化
	lightControl.ENV_free = 0;
	lightControl.ENV_MaxValue = 2600;
	lightControl.ENV_MiniValue = 10;
	
	//二氧化碳初始化
	Co2Control.ENV_free = 0;
	Co2Control.ENV_MaxValue = 600;
	Co2Control.ENV_MiniValue = 10;
	
}


void Control_Execute(void)
{
	//判断是否开启自动模式
	if(AutoControl_mode == 1)
	{
		//光照强度判断
		if(lightControl.ENV_free == 0)
		{
			if(lightControl.ENV_value >= lightControl.ENV_MaxValue)
			{                                                
				LED2_ON();//打开LED2灯
			}
			else
			{
				LED2_OFF();//关闭LED2灯
			}
		}
		else
		{
			lightControl.ENV_free--;
		}
		
		//温度判断
		if(tempControl.ENV_free == 0)
		{
			if(tempControl.ENV_value >= tempControl.ENV_MaxValue)
			{
				relay1_ON();//打开风扇
				Buzzer_ON();
				
			}
			else
			{
				Buzzer_OFF();
				relay1_OFF();//关闭风扇
			}
		}
		else
		{
			tempControl.ENV_free--;
		}
		
		//土壤湿度
		if(soilHumControl.ENV_free == 0)
		{
			if(soilHumControl.ENV_value >= soilHumControl.ENV_MaxValue)
			{
				relay2_ON();//打开水泵
			}
			else
			{
				relay2_OFF();//关闭水泵
			}
		}
		else
		{
			soilHumControl.ENV_free--;
		}
		
		//二氧化碳浓度
		if(Co2Control.ENV_free == 0)
		{
			if(Co2Control.ENV_value >= Co2Control.ENV_MaxValue)
			{
				Servo_open();//打开舵机
				
			}
			else
			{
				Servo_close();//关闭舵机
				
			}
		}
		else
		{
			Co2Control.ENV_free--;
		}
	}
}