#ifndef __BUTTON_H
#define __BUTTON_H

#include "stm32f10x.h" //包含设备头文件

#define LEN //定义低电平表示按下Button

#define RECORD_CAP 5 //定义记录的容量

static uint16_t Record[RECORD_CAP]; //定义固定容量的记录
static uint16_t* RecordHead; //定义记录的指针

void Button_Init(const uint32_t RCC_APB2Periph, const uint16_t GPIO_Pin); //初始化Button模块
void Button_Record(void); //记录按钮状态
uint16_t Button_Value(void); //获取当前按钮的组合键值

#endif /* __BUTTON_H */
