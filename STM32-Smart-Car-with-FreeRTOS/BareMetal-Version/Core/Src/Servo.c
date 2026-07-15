#include "Servo.h"
#include "tim.h"

void Servo_SetAngle(float Angle)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, Angle / 180 * 2000 + 500 );
}
