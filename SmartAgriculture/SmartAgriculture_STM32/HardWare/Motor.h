#ifndef _MOTOR_H_
#define _MOTOR_H_
extern u8 Motor_flag;
void Motor_Init(void);
void Motor_SetSpeed(int8_t speed);
void Motor_Open(void);
void Motor_Close(void);
void Motor_Turn(void);
#endif
