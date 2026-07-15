# STM32 Smart Car with FreeRTOS

基于 STM32F103C8T6 的智能小车控制系统。

## 项目简介

本项目基于 STM32 HAL 库开发，实现智能小车的多种控制功能。

项目经历了从裸机开发到 FreeRTOS 多任务管理的改进过程，主要用于学习 STM32 外设驱动、任务调度以及嵌入式系统设计。

## Hardware

- MCU: STM32F103C8T6
- Motor Driver: TB6612
- Bluetooth Module: HC-05
- Ultrasonic Sensor: HC-SR04
- OLED Display
- Servo Motor

## Features

### Bare Metal Version

实现功能：

- 蓝牙遥控
- 自动循迹
- 超声波避障
- 蜂鸣器提示
- 舵机控制
- OLED显示


### FreeRTOS Version

基于 FreeRTOS 实现多任务管理：

- Motor Control Task
- Bluetooth Communication Task
- Ultrasonic Detection Task
- OLED Display Task

使用：

- Task
- Queue
- Mutex

实现任务之间的数据通信和资源管理。

## Development Environment

- STM32CubeMX
- Keil MDK
- STM32 HAL Library
- FreeRTOS

## Project Structure
