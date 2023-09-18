#ifndef __LED_H
#define __LED_H

#define GPIO_LED1 GPIO_Pin_0
#define GPIO_LED2 GPIO_Pin_6


void LED_Init(void);
void LED1_OFF(void);
void LED1_ON(void);
void LED1_Turn(void);
void LED2_Turn(void);
void LED2_OFF(void);
void LED2_ON(void);

#endif





