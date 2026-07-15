#ifndef __BUZZER_H
#define __BUZZER_H

#include "freertos.h"
#include "main.h"
extern uint8_t BuzzerEnable;
void Buzzer_Once(void);
void Buzzer_Twice(void);

#endif
