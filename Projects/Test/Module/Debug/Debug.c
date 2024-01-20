#include "Debug.h"

void GPIOC_13_Debug(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能APB2中的GPIOC时钟
	GPIO_InitTypeDef GPIOC_Structure; //声明用于初始化GPIOC端口的结构体
	GPIOC_Structure.GPIO_Pin = GPIO_Pin_13; //使用Pin13引脚
	GPIOC_Structure.GPIO_Speed = GPIO_Speed_50MHz; //使用50MHz输出速度
	GPIOC_Structure.GPIO_Mode = GPIO_Mode_Out_PP; //使用推挽输出
	GPIO_Init(GPIOC, &GPIOC_Structure); //初始化GPIOC端口
	GPIO_ResetBits(GPIOC, GPIO_Pin_13); //将GPIOC端口的13引脚设置为低电平(即点亮PC13的指示灯)
}
