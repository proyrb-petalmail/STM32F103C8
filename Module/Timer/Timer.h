#ifndef __TIMER_H
#define __TIMER_H

/* 此模块目前只适用于STM32F103C系列的单片机 */

#include "StandardLib.h"
#include "stm32f10x.h"

typedef enum {
	Timer2,//对应通用定时器TIM2
	Timer3,//对应通用定时器TIM3
	Timer4,//对应通用定时器TIM4
} GeneralTimer;//定义使用哪个通用定时器

typedef enum {
	Up,//对应向上计数
	Down,//对应向下计数
} CountDirection;//定义计数方向

typedef struct {
	uint16_t factor;//定义分频比例
	uint16_t threshold;//定义阈值或重装值
	CountDirection direction;//定义计数方向
} GeneralConfig;//定义使用哪个通用定时器

typedef Bool TimerEnable;//定义是否启动计数器

typedef struct {
	TimerEnable enable;//定义是否启动计数器
} GeneralControl;//定义使用哪个通用定时器

void Timer_General_Config(const GeneralTimer timer, const GeneralConfig*const config);
void Timer_General_Control(const GeneralTimer timer, const GeneralControl*const control);

#endif /* __TIMER_H */
