#include "Avoid.h"
#include "Car.h"
#include "Ultrasound.h"
#include "Servo.h"
#include "Buzzer.h"

static float g_lastDistance = 0;

void Avoid_Run(void)
  {
      Go_Ahead();
	  osDelay (pdMS_TO_TICKS(100));
	  float a  = Ultrasound_GetDistance();
		g_lastDistance = a; 
	  if(a < 0.4)
	  {
		  Buzzer_Twice();
		  Car_Stop ();
		  Servo_SetAngle (180);
		  osDelay (pdMS_TO_TICKS(1000));
		  float b = Ultrasound_GetDistance();
		  if(b > 0.4)
		  {
			  Servo_SetAngle (90);
			  osDelay (pdMS_TO_TICKS(1000));
			  Turn_Left();
			  osDelay (pdMS_TO_TICKS(1000));
			  Go_Ahead();
		  }
		  else
			  {
				  Servo_SetAngle (0);
				  osDelay (pdMS_TO_TICKS(1000));
				  float c = Ultrasound_GetDistance();
				  if(c > 0.4)
				  {
					  Servo_SetAngle (90);
					  osDelay (pdMS_TO_TICKS(1000));
					  Turn_Right();
			          osDelay (pdMS_TO_TICKS(1000));
			          Go_Ahead();
				  }
				  else
				  {
					  Servo_SetAngle (90);
					  Go_Back();
					  osDelay (pdMS_TO_TICKS(2000));
					  Self_Left();
					  osDelay (pdMS_TO_TICKS(1000));
					  Go_Ahead();
				  }
				  
			  }
	  }
  }
float Avoid_GetLastDistance(void)
{
    return g_lastDistance;
}
