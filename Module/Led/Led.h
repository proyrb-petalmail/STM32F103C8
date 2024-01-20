#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h" //包含设备头文件

#define LEN //定义低电平点亮Led

void Led_Init(const uint32_t RCC_APB2Periph, const uint16_t GPIO_Pin); //初始化Led模块
void Led_Light(const uint16_t GPIO_Pin); //点亮指定Led
void Led_Dark(const uint16_t GPIO_Pin); //熄灭指定Led

#endif /* __LED_H */
