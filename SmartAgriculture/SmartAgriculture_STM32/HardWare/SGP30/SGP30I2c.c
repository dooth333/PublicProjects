#include "SGP30i2c.h"
#include "Delay.h"

 
//��ʼ��IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11); 	//PB10,PB11 �����
}

//SDA PB11
//SCL PB10

void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     	//sda�����
	SDA_DATA(1);	
	SCL_OUT(1);  	  
	Delay_us(20);

	SDA_DATA(0);	//START:when CLK is high,DATA change form high to low 
	Delay_us(20);
	SCL_OUT(0); 	//ǯסI2C���ߣ�׼�����ͻ�������� 
}	
  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();		//sda�����
	SCL_OUT(0);  
	SDA_DATA(0);	//STOP:when CLK is high DATA change form low to high
 	Delay_us(20);
 	SCL_OUT(1);  
	SDA_DATA(1);	//����I2C���߽����ź�
	Delay_us(20);
}  

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      		//SDA����Ϊ����  
	SDA_DATA(1);
	Delay_us(10);
	SCL_OUT(1);  	   
	Delay_us(10);
	while(SDA_IO_IN)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			//printf("no ack!\r\n");
			IIC_Stop();
			return 1;
		}
	}
	SCL_OUT(0);  		//ʱ�����0 	
	return 0;  
} 

//����ACKӦ��
void IIC_Ack(void)
{
	SCL_OUT(0);  	
	SDA_OUT();
	SDA_DATA(0);
	Delay_us(20);
	SCL_OUT(1); 
	Delay_us(20);
	SCL_OUT(0); 
} 

//������ACKӦ��		    
void IIC_NAck(void)
{
	SCL_OUT(0); 
	SDA_OUT();
	SDA_DATA(1);
	Delay_us(20);
	SCL_OUT(1); 
	Delay_us(20);
	SCL_OUT(0); 
}		
			 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 
	SCL_OUT(0); 	    	//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
			if((txd&0x80)>>7)
				SDA_DATA(1); 
			else
				SDA_DATA(0); 
			txd<<=1; 	  
			Delay_us(20);   
			SCL_OUT(1); 
			Delay_us(20); 
			SCL_OUT(0); 	
			Delay_us(20);
    }	
	Delay_us(20);
		
} 	    

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u16 IIC_Read_Byte(u8 ack)
{
		u8 i;
		u16 receive=0;
		SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        SCL_OUT(0);  
        Delay_us(20);
        SCL_OUT(1); 
        receive<<=1;
        if(SDA_IO_IN)	
					receive++;   
				Delay_us(20); 
				//printf("%d,%d ",i,receive);
    }		
		//printf("\n");
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}



