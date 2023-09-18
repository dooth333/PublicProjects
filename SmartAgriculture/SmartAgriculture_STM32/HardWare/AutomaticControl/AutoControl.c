#include "stm32f10x.h"                  // Device header
#include "AutoControl.h"

//Ӳ������
#include "LED.h"
#include "Timer.h"
#include "buzzer.h"
#include "Servo.h"
#include "relay.h"
#include "SGP30.h"

//0Ϊ�ر��Զ�ģʽ��1Ϊ�����Զ�ģʽ
uint8_t AutoControl_mode =0;


struct ENV_Struct tempControl;//�¶Ƚṹ��
struct ENV_Struct lightControl;//����ǿ�ȿ��ƽṹ��
struct ENV_Struct soilHumControl;//����ʪ�ȿ��ƽṹ��
struct ENV_Struct Co2Control;//����ʪ�ȿ��ƽṹ��

void Control_Init(void)
{
	//�¶ȳ�ʼ��
	tempControl.ENV_free = 0;
	tempControl.ENV_MaxValue = 26;
	tempControl.ENV_MiniValue = 10;
	
	//����ʪ�ȳ�ʼ��
	soilHumControl.ENV_free = 0;
	soilHumControl.ENV_MaxValue = 2100;
	soilHumControl.ENV_MiniValue = 1500;
	
	//����ǿ�ȳ�ʼ��
	lightControl.ENV_free = 0;
	lightControl.ENV_MaxValue = 2600;
	lightControl.ENV_MiniValue = 10;
	
	//������̼��ʼ��
	Co2Control.ENV_free = 0;
	Co2Control.ENV_MaxValue = 600;
	Co2Control.ENV_MiniValue = 10;
	
}


void Control_Execute(void)
{
	//�ж��Ƿ����Զ�ģʽ
	if(AutoControl_mode == 1)
	{
		//����ǿ���ж�
		if(lightControl.ENV_free == 0)
		{
			if(lightControl.ENV_value >= lightControl.ENV_MaxValue)
			{                                                
				LED2_ON();//��LED2��
			}
			else
			{
				LED2_OFF();//�ر�LED2��
			}
		}
		else
		{
			lightControl.ENV_free--;
		}
		
		//�¶��ж�
		if(tempControl.ENV_free == 0)
		{
			if(tempControl.ENV_value >= tempControl.ENV_MaxValue)
			{
				relay1_ON();//�򿪷���
				Buzzer_ON();
				
			}
			else
			{
				Buzzer_OFF();
				relay1_OFF();//�رշ���
			}
		}
		else
		{
			tempControl.ENV_free--;
		}
		
		//����ʪ��
		if(soilHumControl.ENV_free == 0)
		{
			if(soilHumControl.ENV_value >= soilHumControl.ENV_MaxValue)
			{
				relay2_ON();//��ˮ��
			}
			else
			{
				relay2_OFF();//�ر�ˮ��
			}
		}
		else
		{
			soilHumControl.ENV_free--;
		}
		
		//������̼Ũ��
		if(Co2Control.ENV_free == 0)
		{
			if(Co2Control.ENV_value >= Co2Control.ENV_MaxValue)
			{
				Servo_open();//�򿪶��
				
			}
			else
			{
				Servo_close();//�رն��
				
			}
		}
		else
		{
			Co2Control.ENV_free--;
		}
	}
}