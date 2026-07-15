#include "Car.h"
#include "Motor.h"

uint8_t CarSpeed = 70 ;

void Go_Ahead(){
	Motor_SetLeftSpeed(-CarSpeed);
	Motor_SetRightSpeed(CarSpeed);
}
void Go_Back(){
	Motor_SetLeftSpeed(50);
	Motor_SetRightSpeed(-50);
}
void Turn_Left(){
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(CarSpeed);
}
void Turn_Right(){
	Motor_SetRightSpeed(0);
	Motor_SetLeftSpeed(-CarSpeed);
	
}
void Self_Left(){
	Motor_SetLeftSpeed(CarSpeed);  
	Motor_SetRightSpeed(CarSpeed);
}
void Self_Right(){
	Motor_SetLeftSpeed(-CarSpeed);
	Motor_SetRightSpeed(-CarSpeed);
}
void Car_Stop(){
	Motor_SetLeftSpeed(0);
	Motor_SetRightSpeed(0);
}
