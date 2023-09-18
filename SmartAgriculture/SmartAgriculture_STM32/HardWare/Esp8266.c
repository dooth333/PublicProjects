#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Delay.h"

void Esp8266_Init(void){
	
	Serial_SendString("AT+CIPMUX=1\r\n");
	Delay_ms(1000);
	Serial_SendString("AT+CIPSERVER=1,8080\r\n");
		
}
