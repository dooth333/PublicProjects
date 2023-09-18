#include "SGP30.h"
#include "delay.h"

u16 Co2 = 0,TVOC = 0;
u32 dat;
//**********************************��������****************************

//��ʼ��IIC�ӿ�
void SGP30_Init(void)
{
	IIC_Init();
	SGP30_ad_write(0x20,0x03);
//	SGP30_ad_write(0x20,0x61);
//	SGP30_ad_write(0x01,0x00);
}

void SGP30_ad_write(u8 a, u8 b)
{
  	IIC_Start();
  	IIC_Send_Byte(SGP30_write); //����������ַ+дָ��
		IIC_Wait_Ack();
  	IIC_Send_Byte(a);		//���Ϳ����ֽ�
		IIC_Wait_Ack();
		IIC_Send_Byte(b);
		IIC_Wait_Ack();
		IIC_Stop();
		Delay_ms(100);
}

u32 SGP30_ad_read(void)
{
  	u32 dat;
		u8 crc;
  	IIC_Start();
  	IIC_Send_Byte(SGP30_read); //����������ַ+��ָ��
		IIC_Wait_Ack();
  	dat = IIC_Read_Byte(1);
		dat <<= 8;
		dat += IIC_Read_Byte(1);
		crc = IIC_Read_Byte(1); //crc���ݣ���ȥ
	  crc = crc;  //Ϊ�˲��ó��ֱ��뾯��
		dat <<= 8;
		dat += IIC_Read_Byte(1);
		dat <<= 8;
		dat += IIC_Read_Byte(0);
  	IIC_Stop();
  	return(dat);
}


void SGP30_getValue(void)
{
	SGP30_ad_write(0x20,0x08);
	dat = SGP30_ad_read();
	Co2 = (dat & 0xffff0000) >> 16;
	TVOC = dat & 0x0000ffff;	
}
