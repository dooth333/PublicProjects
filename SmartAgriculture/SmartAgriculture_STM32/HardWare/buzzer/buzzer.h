#ifndef __BUZZER_H
#define __BUZZER_H

#define GPIO_BUZZER GPIO_Pin_12

extern u8 Buzzer_flag;	//��������״̬��0�졢1��
void Buzzer_Init(void);
void Buzzer_OFF(void);
void Buzzer_ON(void);
void Buzzer_Turn(void);

#endif