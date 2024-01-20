#include "Led.h"

static uint32_t Periph = RCC_APB2Periph_GPIOA; //定义并初始化当前使用的外设
static uint16_t Pin = GPIO_Pin_All; //定义并初始化当前使用的引脚

void Led_Init(const uint32_t RCC_APB2Periph, const uint16_t GPIO_Pin) {
	if((RCC_APB2Periph != RCC_APB2Periph_GPIOA) && (RCC_APB2Periph != RCC_APB2Periph_GPIOB)) {
		return; //不允许使用其他类型的外围设备
	}
	Periph = RCC_APB2Periph; //记录当前使用的外围设备
	Pin = GPIO_Pin; //记录当前使用的引脚
	GPIO_InitTypeDef GPIO_Structure; //声明用于初始化GPIO端口的结构体
	GPIO_Structure.GPIO_Pin = GPIO_Pin; //使用引脚
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz; //使用50MHz输出速度
	GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP; //使用推挽输出
	RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE); //使能指定外围设备的时钟
	switch(RCC_APB2Periph) {
		case RCC_APB2Periph_GPIOA:
			GPIO_Init(GPIOA, &GPIO_Structure); //初始化GPIOA端口
			break;
		case RCC_APB2Periph_GPIOB:
			GPIO_Init(GPIOB, &GPIO_Structure); //初始化GPIOB端口
			break;
	}
	Led_Dark(GPIO_Pin); //默认熄灭Led
}

void Led_Light(const uint16_t GPIO_Pin) {
	switch(Periph) {
		case RCC_APB2Periph_GPIOA:
#ifdef LEN
			GPIO_Write(GPIOA, GPIO_ReadInputData(GPIOA) & ~(GPIO_Pin & Pin)); //读取GPIOA端口的输入数据并向GPIOA端口写入数值
#else
			GPIO_Write(GPIOA, GPIO_ReadInputData(GPIOA) | (GPIO_Pin & Pin)); //读取GPIOA端口的输入数据并向GPIOA端口写入数值
#endif
			break;
		case RCC_APB2Periph_GPIOB:
#ifdef LEN
			GPIO_Write(GPIOB, GPIO_ReadInputData(GPIOB) & ~(GPIO_Pin & Pin)); //读取GPIOB端口的输入数据并向GPIOB端口写入数值
#else
			GPIO_Write(GPIOB, GPIO_ReadInputData(GPIOB) | (GPIO_Pin & Pin)); //读取GPIOB端口的输入数据并向GPIOB端口写入数值
#endif
			break;
	}
}

void Led_Dark(const uint16_t GPIO_Pin) {
	switch(Periph) {
		case RCC_APB2Periph_GPIOA:
#ifdef LEN
			GPIO_Write(GPIOA, GPIO_ReadInputData(GPIOA) | (GPIO_Pin & Pin)); //读取GPIOA端口的输入数据并向GPIOA端口写入数值
#else
			GPIO_Write(GPIOA, GPIO_ReadInputData(GPIOA) & ~(GPIO_Pin & Pin)); //读取GPIOA端口的输入数据并向GPIOA端口写入数值
#endif
			break;
		case RCC_APB2Periph_GPIOB:
#ifdef LEN
			GPIO_Write(GPIOB, GPIO_ReadInputData(GPIOB) | (GPIO_Pin & Pin)); //读取GPIOB端口的输入数据并向GPIOB端口写入数值
#else
			GPIO_Write(GPIOB, GPIO_ReadInputData(GPIOB) & ~(GPIO_Pin & Pin)); //读取GPIOB端口的输入数据并向GPIOB端口写入数值
#endif
			break;
	}
}
