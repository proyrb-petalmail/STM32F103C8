#include "Timer.h"

void Timer_General_Config(const GeneralTimer timer, const GeneralConfig*const config) {
	switch(timer) {
		case Timer2:
			TIM2->PSC = config->factor - 1;//设置分频器的输出频率
			TIM2->ARR = config->threshold - 1;//设置计数器的阈值或重装值
			if(config->direction == Up) {
				TIM2->CR1 &= ~0x0010;//设置计数方向为向上计数
			}
			else if(config->direction == Up) {
				TIM2->CR1 |= 0x0010;//设置计数方向为向下计数
			}
			break;
		case Timer3:
			TIM3->PSC = config->factor - 1;//设置分频器的输出频率
			TIM3->ARR = config->threshold - 1;//设置计数器的阈值或重装值
			if(config->direction == Up) {
				TIM3->CR1 &= ~0x0010;//设置计数方向为向上计数
			}
			else if(config->direction == Up) {
				TIM3->CR1 |= 0x0010;//设置计数方向为向下计数
			}
			break;
		case Timer4:
			TIM4->PSC = config->factor - 1;//设置分频器的输出频率
			TIM4->ARR = config->threshold - 1;//设置计数器的阈值或重装值
			if(config->direction == Up) {
				TIM4->CR1 &= ~0x0010;//设置计数方向为向上计数
			}
			else if(config->direction == Up) {
				TIM5->CR1 |= 0x0010;//设置计数方向为向下计数
			}
			break;
		default:
			break;
	}
}

void Timer_General_Control(const GeneralTimer timer, const GeneralControl*const control) {
	switch(timer) {
		case Timer2:
			RCC->APB1ENR |= 0x00000001;//启动对应通用定时器TIM2的时钟
			TIM2->DIER = 0x0001;//允许触发和更新中断
			if(control->enable == True) {
				TIM2->CR1 = 0x0001;//启动计数器
			}
			else {
				TIM2->CR1 &= ~0x0001;//停止计数器
			}
			break;
		case Timer3:
			RCC->APB1ENR |= 0x00000002;//启动对应通用定时器TIM3的时钟
			TIM3->DIER = 0x0001;//允许触发和更新中断
			if(control->enable == True) {
				TIM3->CR1 |= 0x0001;//启动计数器
			}
			else {
				TIM3->CR1 &= ~0x0001;//停止计数器
			}
			break;
		case Timer4:
			RCC->APB1ENR |= 0x00000004;//启动对应通用定时器TIM4的时钟
			TIM4->DIER = 0x0001;//允许触发和更新中断
			if(control->enable == True) {
				TIM4->CR1 |= 0x0001;//启动计数器
			}
			else {
				TIM4->CR1 &= ~0x0001;//停止计数器
			}
			break;
		default:
			break;
	}
}
