#ifndef __RELAY_H
#define __RELAY_H

#define GPIO_relay_1 GPIO_Pin_13
#define GPIO_relay_2 GPIO_Pin_14
#define GPIO_GPIOx_relay GPIOC
#define GPIO_Periph_relay RCC_APB2Periph_GPIOC

void relay_Init(void);
void relay1_ON(void);
void relay1_OFF(void);
void relay1_Turn(void);
void relay2_ON(void);
void relay2_OFF(void);
void relay2_Turn(void);

#endif

