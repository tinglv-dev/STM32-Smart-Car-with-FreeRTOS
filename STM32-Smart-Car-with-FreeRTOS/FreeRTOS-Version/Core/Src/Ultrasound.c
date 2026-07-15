#include "Ultrasound.h"
#include "tim.h"

float Ultrasound_GetDistance(void)
	{
      //1.让计数器CNT归零
	  __HAL_TIM_SET_COUNTER(&htim4,0);
	  
	  //2.清除cc3\cc4标志位
	  __HAL_TIM_CLEAR_FLAG(&htim4,TIM_FLAG_CC3);
	  __HAL_TIM_CLEAR_FLAG(&htim4,TIM_FLAG_CC4);
	  
	  //3.启动输入捕获
	  HAL_TIM_IC_Start(&htim4,TIM_CHANNEL_3);
	  HAL_TIM_IC_Start(&htim4,TIM_CHANNEL_4);
	  
	  //4.向Trig发送脉冲
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
	  
	  for(volatile uint32_t i=0;i<720;i++);
	  
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
	  
	  //5.等待测量结果
	  uint8_t success  = 0;
	  uint32_t expireTime = HAL_GetTick()+50;
	  
	  while(expireTime > HAL_GetTick())
	  {
	    uint32_t cc3Flag = __HAL_TIM_GET_FLAG(&htim4,TIM_FLAG_CC3);
	    uint32_t cc4Flag = __HAL_TIM_GET_FLAG(&htim4,TIM_FLAG_CC4);
		  
		if(cc3Flag && cc4Flag)
		{
			success = 1;
			break;
		}
		osDelay (1);
	  }
	  
	  //6.关闭定时器
      HAL_TIM_IC_Stop(&htim4,TIM_CHANNEL_3);
	    HAL_TIM_IC_Stop(&htim4,TIM_CHANNEL_4);
	  
	  //计算测量结果
	  if(success == 1)
	  {
		  uint16_t cc3 = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_3);
		  uint16_t cc4 = __HAL_TIM_GET_COMPARE(&htim4, TIM_CHANNEL_4);
		  
		  float pulseWidth = (cc4-cc3) * 1e-6f ;
		  float distance = 340.0f * pulseWidth / 2.0f ;
		  return distance;
		  
	  }
	  return 0;
  } 
