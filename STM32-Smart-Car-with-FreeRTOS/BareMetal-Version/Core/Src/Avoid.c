#include "Avoid.h"
#include "Car.h"
#include "Ultrasound.h"
#include "Servo.h"
#include "Buzzer.h"

void Avoid_Run(void)
  {
      Go_Ahead();
	  HAL_Delay (100); 
	  float a  = Ultrasound_GetDistance();
	  if(a < 0.2)
	  {
		  Buzzer_Twice();
		  Car_Stop ();
		  Servo_SetAngle (180);
		  HAL_Delay (1000);
		  float b = Ultrasound_GetDistance();
		  if(b > 0.2)
		  {
			  Servo_SetAngle (90);
			  HAL_Delay (1000);
			  Turn_Left();
			  HAL_Delay (1000);
			  Go_Ahead();
		  }
		  else
			  {
				  Servo_SetAngle (0);
				  HAL_Delay (1000);
				  float c = Ultrasound_GetDistance();
				  if(c > 0.2)
				  {
					  Servo_SetAngle (90);
					  HAL_Delay (1000);
					  Turn_Right();
			          HAL_Delay (1000);
			          Go_Ahead();
				  }
				  else
				  {
					  Servo_SetAngle (90);
					  Go_Back();
					  HAL_Delay (2000);
					  Self_Left();
					  HAL_Delay (1000);
					  Go_Ahead();
				  }
				  
			  }
		  
	  }
  }
