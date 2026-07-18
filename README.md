# STM32 FreeRTOS 智能小车

基于 STM32F103C8T6 微控制器和 FreeRTOS 实时操作系统开发的智能小车项目，采用 CMSIS-RTOS V2 封装层，通过消息队列和互斥量实现任务间通信与数据同步。小车支持手动遥控、自动避障、自动循迹三种工作模式，可通过串口指令或板载按键切换。

## 技术栈

MCU 为 STM32F103C8T6（Cortex-M3 内核，主频 72MHz），使用 STM32CubeMX 生成工程并基于 HAL 库开发。RTOS 层采用 FreeRTOS ，CMSIS-RTOS V2 作为上层封装接口。外设方面涉及 USART 中断通信、I2C 驱动 OLED、PWM 控制电机和舵机、定时器输入捕获实现超声波测距。硬件驱动包括 HC-SR04 超声波模块、SG90 舵机、SSD1306 OLED（双缓冲机制）、红外循迹传感器和有源蜂鸣器。

## 系统架构

系统设计了 5 个 RTOS 任务。CmdTask 优先级为 High，栈大小 256 words，阻塞于消息队列接收，负责串口命令的解析与分发。ContralTask 优先级为 Normal，栈大小 512 words，以 20ms 为周期运行，是避障和循迹控制的主循环。OLEDDisplayTask 优先级为 Low，栈大小 348 words，500ms 周期刷新屏幕状态。KeyScanTask 优先级为 Low，栈大小 128 words，20ms 周期扫描按键并实现状态机式的模式切换。defaultTask 为 CubeMX 生成的默认占位任务，不承担实际业务。

任务间通信主要依靠消息队列和互斥量两种机制。USART1 接收中断中调用 osMessageQueuePut（0 超时），将数据送入 UartCmdQueue，CmdTask 通过 osMessageQueueGet 阻塞式获取数据，实现了中断与任务的解耦。共享变量 mode、CarSpeed、BuzzerEnable、distanceMM 均通过 StartMutex 互斥量保护读写，利用优先级继承机制规避优先级反转问题。此外，由于 SysTick 被 FreeRTOS 占用，项目将 HAL 库的系统时基迁移到了 TIM1，通过 HAL_IncTick 实现两者互不干扰。

## 硬件资源映射

电机方向控制使用 PA4 到 PA7 四个引脚，电机 PWM 由 TIM2 的 CH3 和 CH4 通道输出。舵机 PWM 使用 TIM3 CH3（PB0），频率为标准舵机信号的 50Hz。超声波测距依靠 TIM4 输入捕获功能，Trig 引脚为 PB12。循迹模块使用 PB5、PB6、PB7、PB9 四路红外传感器。OLED 屏幕通过 I2C2（PB10/PB11）驱动。按键检测使用 PA8，蜂鸣器控制引脚为 PB1，串口通信使用 USART1（PA9/PA10）。

## 串口指令集

指令 A 切换为避障模式，指令 B 切换为循迹模式，指令 0 切换为手动模式。手动模式下，指令 1 为停止，2 为前进，3 为后退，4 为左转，5 为右转，6 为原地左旋，7 为原地右旋，8 为加速，9 为减速。指令 K 打开蜂鸣器，指令 G 关闭蜂鸣器。

## 自动避障演示



https://github.com/user-attachments/assets/777adf0c-1577-4d92-a424-2fcca4f09d70



## 寻迹功能演示


https://github.com/user-attachments/assets/659313ef-a694-412e-af96-dc9d77df03aa

