#include "Track.h"
#include "Car.h"

void Track_Run(void)
{
	if( HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_5 )== GPIO_PIN_RESET  &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_6 )== GPIO_PIN_RESET  &&
    	HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_7 )== GPIO_PIN_RESET  &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_9 )== GPIO_PIN_RESET  )
	{
		Go_Ahead();
	}
	else if( HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_5 )== GPIO_PIN_SET &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_6 )== GPIO_PIN_SET &&
    	HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_7 )== GPIO_PIN_SET &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_9 )== GPIO_PIN_SET )
	{
		Car_Stop();
	}
	else if( HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_5 )== GPIO_PIN_RESET  &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_6 )== GPIO_PIN_RESET  &&
    	HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_7 )== GPIO_PIN_RESET  &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_9 )== GPIO_PIN_SET )
	{
		Turn_Right();
	}
	else if( HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_5 )== GPIO_PIN_RESET  &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_6 )== GPIO_PIN_RESET  &&
    	HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_7 )== GPIO_PIN_SET &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_9 )== GPIO_PIN_SET )
	{
		Self_Right();
	}
	else if( HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_5 )== GPIO_PIN_RESET  &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_6 )== GPIO_PIN_RESET  &&
    	HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_7 )== GPIO_PIN_SET &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_9 )== GPIO_PIN_RESET  )
	{
		Self_Right();
	}
	else if( HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_5 )== GPIO_PIN_SET &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_6 )== GPIO_PIN_RESET  &&
    	HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_7 )== GPIO_PIN_RESET  &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_9 )== GPIO_PIN_RESET  )
	{
		Turn_Left();
	}
	else if( HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_5 )== GPIO_PIN_SET &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_6 )== GPIO_PIN_SET &&
    	HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_7 )== GPIO_PIN_RESET  &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_9 )== GPIO_PIN_RESET  )
	{
		Self_Left();
	}
	else if( HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_5 )== GPIO_PIN_RESET  &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_6 )== GPIO_PIN_SET &&
    	HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_7 )== GPIO_PIN_RESET  &&
		HAL_GPIO_ReadPin(GPIOB ,GPIO_PIN_9 )== GPIO_PIN_RESET  )
	{
		Self_Left();
	}
}

