#include "stm32f10x.h" //包含驱动模块
#include "Debug.h" //包含Debug模块
#include "Delay.h" //包含Delay模块
#include "Led.h" //包含Led模块
#include "Button.h" //包含Button模块
#include "OLed.h" //包含OLed模块

int main(void) {
	GPIOC_13_Debug(); //点亮GPIOC端口PC13引脚的指示灯
	Led_Init(RCC_APB2Periph_GPIOA, GPIO_Pin_All); //初始化Led模块
	Button_Init(RCC_APB2Periph_GPIOB, GPIO_Pin_1 | GPIO_Pin_11); //初始化Button模块
	OLed_Init(RCC_APB2Periph_GPIOB, GPIO_Pin_5, GPIO_Pin_6); //初始化OLed模块
	
	while(1) {
		Button_Record();
		Delay_ms(20); //延时100ms
		if(Button_Value() == 1) {
			Led_Light(GPIO_Pin_All); //点亮指定引脚上的Led
		}
		else {
			Led_Dark(GPIO_Pin_All); //熄灭指定引脚上的Led
		}
		OLed_ShowBinNum(1, 1, *(Record+((RecordHead-Record+RECORD_CAP-1)%RECORD_CAP)), 16);
	}
}
