#ifndef _SERVO_H_
#define _SERVO_H_
extern u8 Servo_flag;
void Servo_Init(void);
void Servo_setAngle(float Angle);
void Servo_open(void);
void Servo_close(void);
void Servo_Turn(void);
#endif
