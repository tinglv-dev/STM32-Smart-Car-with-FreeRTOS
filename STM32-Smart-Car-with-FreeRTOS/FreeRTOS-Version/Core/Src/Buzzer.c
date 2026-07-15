#include "Buzzer.h"

uint8_t BuzzerEnable = 0 ;

void Buzzer_Once(void)
{
	if(BuzzerEnable == 1)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET);
		osDelay (pdMS_TO_TICKS(100));
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);
	}
}

void Buzzer_Twice(void)
{
	Buzzer_Once();
	osDelay (pdMS_TO_TICKS(100));
	Buzzer_Once();
}
