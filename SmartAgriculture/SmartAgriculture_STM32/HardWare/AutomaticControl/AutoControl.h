#ifndef __AUTOCONTROPL_H
#define __AUTOCONTROPL_H
#define Free_Value 1000

extern uint8_t AutoControl_mode;

struct ENV_Struct
{
	uint16_t ENV_free;//报警计时
	uint32_t  ENV_value;
	uint32_t ENV_MaxValue;//最大阈值
	uint16_t ENV_MiniValue;//最小阈值
};
extern struct ENV_Struct tempControl;//温度控制结构体
extern struct ENV_Struct lightControl;//温度控制结构体
extern struct ENV_Struct soilHumControl;//土壤湿度控制结构体
extern struct ENV_Struct Co2Control;//土壤湿度控制结构体

void Control_Init(void);
void Control_Execute(void);

#endif