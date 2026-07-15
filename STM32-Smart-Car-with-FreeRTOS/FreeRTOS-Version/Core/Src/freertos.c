/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Car.h"
#include "Buzzer.h"
#include "Track.h"
#include "Avoid.h"
#include "Ultrasound.h"
#include "oled.h"
#include "OLED_Display.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern uint8_t mode;
extern uint8_t CarSpeed;
extern uint8_t BuzzerEnable;
extern uint32_t distanceMM;
extern osMutexId_t StartMutexHandle;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for CmdTask */
osThreadId_t CmdTaskHandle;
const osThreadAttr_t CmdTask_attributes = {
  .name = "CmdTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for ControlTask */
osThreadId_t ControlTaskHandle;
const osThreadAttr_t ControlTask_attributes = {
  .name = "ControlTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for OLEDDisplayTask */
osThreadId_t OLEDDisplayTaskHandle;
const osThreadAttr_t OLEDDisplayTask_attributes = {
  .name = "OLEDDisplayTask",
  .stack_size = 348 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for KeyScanTask */
osThreadId_t KeyScanTaskHandle;
const osThreadAttr_t KeyScanTask_attributes = {
  .name = "KeyScanTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for UartCmdQueue */
osMessageQueueId_t UartCmdQueueHandle;
const osMessageQueueAttr_t UartCmdQueue_attributes = {
  .name = "UartCmdQueue"
};
/* Definitions for StartMutex */
osMutexId_t StartMutexHandle;
const osMutexAttr_t StartMutex_attributes = {
  .name = "StartMutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartCmdTask(void *argument);
void StartControlTask(void *argument);
void StartOLEDDisplayTask(void *argument);
void StartKeyScanTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of StartMutex */
  StartMutexHandle = osMutexNew(&StartMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of UartCmdQueue */
  UartCmdQueueHandle = osMessageQueueNew (8, sizeof(uint8_t), &UartCmdQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of CmdTask */
  CmdTaskHandle = osThreadNew(StartCmdTask, NULL, &CmdTask_attributes);

  /* creation of ControlTask */
  ControlTaskHandle = osThreadNew(StartControlTask, NULL, &ControlTask_attributes);

  /* creation of OLEDDisplayTask */
  OLEDDisplayTaskHandle = osThreadNew(StartOLEDDisplayTask, NULL, &OLEDDisplayTask_attributes);

  /* creation of KeyScanTask */
  KeyScanTaskHandle = osThreadNew(StartKeyScanTask, NULL, &KeyScanTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartCmdTask */
/**
* @brief Function implementing the CmdTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCmdTask */
void StartCmdTask(void *argument)
{
  /* USER CODE BEGIN StartCmdTask */
  /* Infinite loop */
	uint8_t cmd;
for(;;)
{
  osMessageQueueGet(UartCmdQueueHandle, &cmd, NULL, osWaitForever);

  uint8_t curMode;
  uint8_t needStop = 0, needBuzzer = 0;


osMutexAcquire(StartMutexHandle, osWaitForever);

if(cmd == 'A') { mode = 'A'; needStop = 1; needBuzzer = 1; }
if(cmd == 'B') { mode = 'B'; needStop = 1; needBuzzer = 1; }
if(cmd == '0') { mode = '0'; needStop = 1; needBuzzer = 1; }

curMode = mode;  

if(curMode == '0')
{
  if(cmd == '8' && CarSpeed < 90) { CarSpeed = CarSpeed + 20; }
  if(cmd == '9' && CarSpeed > 50) { CarSpeed = CarSpeed - 20; }
}

if(cmd == 'K') { BuzzerEnable = 1; }
if(cmd == 'G') { BuzzerEnable = 0; }

osMutexRelease(StartMutexHandle);

if(needStop) Car_Stop();
if(needBuzzer) Buzzer_Once();

if(curMode == '0')
{
  if(cmd == '1') Car_Stop();
  if(cmd == '2') Go_Ahead();
  if(cmd == '3') Go_Back();
  if(cmd == '4') Turn_Left();
  if(cmd == '5') Turn_Right();
  if(cmd == '6') Self_Left();
  if(cmd == '7') Self_Right();
}
}
  /* USER CODE END StartCmdTask */
}

/* USER CODE BEGIN Header_StartControlTask */
/**
* @brief Function implementing the ControlTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartControlTask */
void StartControlTask(void *argument)
{
  /* USER CODE BEGIN StartControlTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartControlTask */
}

/* USER CODE BEGIN Header_StartOLEDDisplayTask */
/**
* @brief Function implementing the OLEDDisplayTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartOLEDDisplayTask */
void StartOLEDDisplayTask(void *argument)
{
  /* USER CODE BEGIN StartOLEDDisplayTask */
  char buf[24];
  uint8_t mode_local;
  uint8_t speed_local;
  uint8_t buzzer_local;
  uint32_t dist_local;

  for(;;)
  {
    osMutexAcquire(StartMutexHandle, osWaitForever);
    mode_local   = mode;
    speed_local  = CarSpeed;
    buzzer_local = BuzzerEnable;
    dist_local   = distanceMM;
    osMutexRelease(StartMutexHandle);   // ????????,I2C??????

    OLED_NewFrame();

    if (mode_local == 'A')
        OLED_PrintASCIIString(0, 0, "A: Avoid", &afont16x8, OLED_COLOR_NORMAL);
    else if (mode_local == 'B')
        OLED_PrintASCIIString(0, 0, "B: Track", &afont16x8, OLED_COLOR_NORMAL);
    else
        OLED_PrintASCIIString(0, 0, "0: Manual", &afont16x8, OLED_COLOR_NORMAL);

    if (mode_local == 'A')
    {
        sprintf(buf, "Dist: %umm", dist_local);
        OLED_PrintASCIIString(0, 16, buf, &afont16x8, OLED_COLOR_NORMAL);
    }

    sprintf(buf, "Speed: %d", speed_local);
    OLED_PrintASCIIString(0, 32, buf, &afont16x8, OLED_COLOR_NORMAL);

    OLED_PrintASCIIString(0, 48, buzzer_local ? "Buzzer: Open" : "Buzzer: Close", &afont16x8, OLED_COLOR_NORMAL);

    OLED_ShowFrame();   // I2C????,?????

    osDelay(pdMS_TO_TICKS(500));
  }
  /* USER CODE END StartOLEDDisplayTask */
}

/* USER CODE BEGIN Header_StartKeyScanTask */
/**
* @brief Function implementing the KeyScanTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartKeyScanTask */
void StartKeyScanTask(void *argument)
{
  /* USER CODE BEGIN StartKeyScanTask */
  static enum {IDLE, PRESSED} keyState = IDLE;
  static uint32_t pressTick = 0;

  for(;;)
  {
    uint8_t pinVal = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);

    switch(keyState)
    {
      case IDLE:
        if(pinVal == 0)   // ??
        {
          pressTick = osKernelGetTickCount();
          keyState = PRESSED;
        }
        break;

      case PRESSED:
        if(pinVal == 1)   // ??
        {
          if(osKernelGetTickCount() - pressTick > pdMS_TO_TICKS(1000))
          {
            // ???? ? ????
            osMutexAcquire(StartMutexHandle, osWaitForever);
            if(mode == '0') mode = 'A';
            else if(mode == 'A') mode = 'B';
            else mode = '0';
            osMutexRelease(StartMutexHandle);

            Buzzer_Once();   // ?????,??osDelay?????
          }
          keyState = IDLE;
        }
        break;
    }

    osDelay(pdMS_TO_TICKS(20));
  }
  /* USER CODE END StartKeyScanTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
