#ifndef __AD_H
#define __AD_H

extern uint16_t AD_Value[3];
extern uint16_t InfraredSwitch;
void InfraredSwitchConvert(void);
void AD_Init(void);

#endif
