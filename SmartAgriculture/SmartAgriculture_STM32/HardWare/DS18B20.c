#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "DS18B20.h"

void DS18B20_GPIO_Config(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_DS18B20;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
}

void DS18B20_Mode_Out_PP(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_DS18B20;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
}

void DS18B20_Mode_IPU(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_DS18B20;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
}


uint8_t DS18B20_Rst(void)
{
    DS18B20_GPIO_Config ();
		GPIO_SetBits(GPIOA,GPIO_DS18B20);
    DS18B20_Mode_Out_PP();

		GPIO_ResetBits(GPIOA,GPIO_DS18B20);
    GPIO_ResetBits(GPIOA,GPIO_DS18B20);
    Delay_us(750);
    GPIO_SetBits(GPIOA,GPIO_DS18B20);
    DS18B20_Mode_IPU();
    Delay_us(70);
    if(GPIO_ReadOutputDataBit(GPIOA,GPIO_DS18B20) == 0)
    {
        Delay_us(240);
        if(GPIO_ReadOutputDataBit(GPIOA,GPIO_DS18B20) == 1)
            return 0;
    }
    else 
        return 1;
}

void DS18B20_WriteByte(uint8_t dat)
{
    uint8_t tem = 0,i = 0;
    DS18B20_Mode_Out_PP();
    for(i = 0; i < 8;i++)
    {
        tem = dat & 0x01;
        dat = dat >> 1;
        if(tem == 0)
        {
            GPIO_ResetBits(GPIOA,GPIO_DS18B20);
            Delay_us(70);
            GPIO_SetBits(GPIOA,GPIO_DS18B20);
            Delay_us(5);
        }
        if(tem == 1)
        {
            GPIO_ResetBits(GPIOA,GPIO_DS18B20);
            Delay_us(5);
            GPIO_SetBits(GPIOA,GPIO_DS18B20);
            Delay_us(60);
        }
    }
}




uint8_t DS18B20_ReadByte(void)
{
    uint8_t dat = 0,num = 0,i = 0;
    for(i = 0; i < 8;i++)
    {
        uint8_t num = 0;
        DS18B20_Mode_Out_PP();
        GPIO_ResetBits(GPIOA,GPIO_DS18B20);
        Delay_us(15);
        DS18B20_Mode_IPU();
        if(GPIO_ReadOutputDataBit(GPIOA,GPIO_DS18B20) == 0)
            num = 0;
        else
            num = 1;
        Delay_us(50);
        dat = (num << i) | dat;
    }
    return dat;
}

static void DS18B20_SkipRom ( void )
{
	DS18B20_Rst();	   	 
	DS18B20_WriteByte(0XCC);
}

float DS18B20_GetTemp_SkipRom ( void )
{
    uint8_t tem_h, tem_l;
    short s_tem;
    float f_tem;

    DS18B20_SkipRom ();
    DS18B20_WriteByte(0X44);		//启动温度转换。

    DS18B20_SkipRom ();
    DS18B20_WriteByte(0XBE);		

    tem_l = DS18B20_ReadByte();		 
    tem_h = DS18B20_ReadByte(); 

    s_tem = tem_h << 8;
    s_tem = s_tem | tem_l;

//    if( s_tem < 0 )		
//        f_tem = (~s_tem + 1) * 0.0625;	
//    else
//        f_tem = s_tem * 0.0625;
		f_tem = s_tem * 0.0625;
    return f_tem; 	
}


