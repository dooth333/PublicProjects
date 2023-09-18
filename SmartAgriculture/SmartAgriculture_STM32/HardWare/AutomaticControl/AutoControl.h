#ifndef __AUTOCONTROPL_H
#define __AUTOCONTROPL_H
#define Free_Value 1000

extern uint8_t AutoControl_mode;

struct ENV_Struct
{
	uint16_t ENV_free;//������ʱ
	uint32_t  ENV_value;
	uint32_t ENV_MaxValue;//�����ֵ
	uint16_t ENV_MiniValue;//��С��ֵ
};
extern struct ENV_Struct tempControl;//�¶ȿ��ƽṹ��
extern struct ENV_Struct lightControl;//�¶ȿ��ƽṹ��
extern struct ENV_Struct soilHumControl;//����ʪ�ȿ��ƽṹ��
extern struct ENV_Struct Co2Control;//����ʪ�ȿ��ƽṹ��

void Control_Init(void);
void Control_Execute(void);

#endif