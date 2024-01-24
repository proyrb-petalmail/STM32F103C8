#include "Exception.h"

static PriorityType priorityType;//定义处理异常的优先级类型

/* 自定义处理异常的回调函数 */
static void (*Timer2Callback)(void) = Null;//定义并初始化处理Timer2异常的回调函数
static void (*Timer3Callback)(void) = Null;//定义并初始化处理Timer3异常的回调函数
static void (*Timer4Callback)(void) = Null;//定义并初始化处理Timer4异常的回调函数

/* 该初始化函数一般在一个程序生命周期内只允许调用一次 */
void Exception_Initialize(const PriorityType type) {
	priorityType = type;
	NVIC_SetPriorityGrouping(type);//设置优先级分组
}

void Exception_Config(const ExceptionConfig*const config) {
	switch(config->exceptionExit) {
		case TIM2_IRQn:
			Timer2Callback = (void*)config->callback;//保存回调函数地址
			break;
		case TIM3_IRQn:
			Timer3Callback = (void*)config->callback;//保存回调函数地址
			break;
		case TIM4_IRQn:
			Timer4Callback = (void*)config->callback;//保存回调函数地址
			break;
		default:
			break;
	}
	NVIC_SetPriority(
		config->exceptionExit,
		NVIC_EncodePriority(priorityType, config->grabLevel, config->respondLevel)
	);//设置该异常通道的优先级
}

void Exception_Control(const ExceptionControl*const control) {
	if(control->enable == True) {
		NVIC_EnableIRQ(control->exceptionExit);//允许该异常通道触发
	}
	else {
		NVIC_DisableIRQ(control->exceptionExit);//不允许该异常通道触发
	}
	if(control->trigger == True) {
		NVIC_SetPendingIRQ(control->exceptionExit);//触发该异常通道
	}
	else {
		NVIC_ClearPendingIRQ(control->exceptionExit);//清除该异常通道的触发态
	}
}

void TIM2_IRQHandler(void) {
	Timer2Callback();//跳转到自定义的回调函数进行处理
	TIM2->SR &= ~0x0001;//清除中断标志位
}

void TIM3_IRQHandler(void) {
	Timer3Callback();//跳转到自定义的回调函数进行处理
	TIM3->SR &= ~0x0001;//清除中断标志位
}

void TIM4_IRQHandler(void) {
	Timer4Callback();//跳转到自定义的回调函数进行处理
	TIM4->SR &= ~0x0001;//清除中断标志位
}