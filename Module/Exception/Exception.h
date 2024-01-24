#ifndef __EXCEPTION_H
#define __EXCEPTION_H

/* 此模块目前只适用于STM32F103C系列的单片机 */

#include "StandardLib.h"
#include "stm32f10x.h"

/* 优先级分组情况：
 * 0b011的分组为“0bxxxx.”，表示4位抢占优先级，0位响应优先级
 * 0b100的分组为“0bxxx.y”，表示3位抢占优先级，1位响应优先级
 * 0b101的分组为“0bxx.yy”，表示2位抢占优先级，2位响应优先级
 * 0b110的分组为“0bx.yyy”，表示1位抢占优先级，3位响应优先级
 * 0b111的分组为“0b.yyyy”，表示0位抢占优先级，4位响应优先级*/
typedef enum {
	G4_S0 = 0b011,
	G3_S1 = 0b100,
	G2_S2 = 0b101,
	G1_S3 = 0b110,
	G0_S4 = 0b111,
} PriorityType;//定义异常通道优先级类型

typedef IRQn_Type ExceptionExit;//重定义中断类型为异常通道

typedef struct {
	ExceptionExit exceptionExit;//定义要控制的异常通道
	uint32_t grabLevel;//定义抢占优先级
	uint32_t respondLevel;//定义响应优先级
	uint32_t callback;//定义处理异常的回调函数地址
} ExceptionConfig;//定义异常通道的控制方式

typedef struct {
	ExceptionExit exceptionExit;//定义要控制的异常通道
	Bool enable;//True表示该异常通道允许触发
	Bool trigger;//True表示触发该异常通道
} ExceptionControl;//定义异常通道的控制方式

void Exception_Initialize(const PriorityType type);
void Exception_Config(const ExceptionConfig*const config);
void Exception_Control(const ExceptionControl*const control);

#endif /* __EXCEPTION_H */
