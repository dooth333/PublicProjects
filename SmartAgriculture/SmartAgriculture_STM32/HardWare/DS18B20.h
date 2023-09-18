#ifndef _DS18B20_H
#define _DS18B20_H

#define GPIO_DS18B20 GPIO_Pin_5
void DS18B20_GPIO_Config(void);
uint8_t DS18B20_Rst(void);
uint8_t DS18B20_Rst(void);
float DS18B20_GetTemp_SkipRom ( void );

#endif
