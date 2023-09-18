#ifndef __OLED_H
#define __OLED_H
#include "stdbool.h"
#include "u8g2.h"
/*引脚配置*/
#define OLED_SCL_GPIO GPIOB
#define OLED_SCL_Pin GPIO_Pin_8
#define OLED_SCL_Clock RCC_APB2Periph_GPIOB
#define OLED_W_SCL(x)		GPIO_WriteBit(OLED_SCL_GPIO, OLED_SCL_Pin, (BitAction)(x))

#define OLED_SDA_GPIO GPIOB
#define OLED_SDA_Pin GPIO_Pin_9
#define OLED_SDA_Clock RCC_APB2Periph_GPIOB
#define OLED_W_SDA(x)		GPIO_WriteBit(OLED_SDA_GPIO, OLED_SDA_Pin, (BitAction)(x))

#define SPEED 4//16的因数
#define ICON_SPEED 12
#define ICON_SPACE 48//图标间隔，speed倍数


extern u8g2_t u8g2;


void OLED_I2C_Init(void);
void u8g2Init(void);

bool move(int16_t* a,int16_t* a_trg);
bool move_icon(int16_t* a,int16_t* a_trg);
bool move_width(uint8_t* a,uint8_t* a_trg,uint8_t select,uint8_t id);
bool move_bar(uint8_t* a,uint8_t* a_trg);
void disappear(void);
void logo_ui_show(void);
void pid_ui_show(void);
void select_ui_show(void);
void about_ui_show(void);
void logo_proc(void);
void select_proc(void);
void about_proc(void);
void chart_ui_show(void);
void chart_proc(void);
void pid_proc(void);
void ui_proc(void);

#endif
