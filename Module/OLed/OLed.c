#include "OLed.h"

static uint32_t Periph = RCC_APB2Periph_GPIOA; //定义并初始化当前使用的外设
static uint16_t Pin_SCL = GPIO_Pin_All; //定义并初始化当前使用的引脚
static uint16_t Pin_SDA = GPIO_Pin_All; //定义并初始化当前使用的引脚

/*引脚初始化*/
void OLed_I2C_Init(void) {
	GPIO_InitTypeDef GPIO_Structure; //声明用于初始化GPIO端口的结构体
	GPIO_Structure.GPIO_Pin = Pin_SCL | Pin_SDA; //使用引脚
	GPIO_Structure.GPIO_Speed = GPIO_Speed_50MHz; //使用50MHz输出速度
	GPIO_Structure.GPIO_Mode = GPIO_Mode_Out_PP; //使用推挽输出
	RCC_APB2PeriphClockCmd(Periph, ENABLE); //使能外设时钟
	switch(Periph) {
		case RCC_APB2Periph_GPIOA:
			GPIO_Init(GPIOA, &GPIO_Structure); //初始化GPIOA端口
			GPIO_WriteBit(GPIOA, Pin_SCL, (BitAction)(1));
			GPIO_WriteBit(GPIOA, Pin_SDA, (BitAction)(1));
			break;
		case RCC_APB2Periph_GPIOB:
			GPIO_Init(GPIOB, &GPIO_Structure); //初始化GPIOB端口
			GPIO_WriteBit(GPIOB, Pin_SCL, (BitAction)(1));
			GPIO_WriteBit(GPIOB, Pin_SDA, (BitAction)(1));
			break;
	}
}

/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void OLed_I2C_Start(void) {
	switch(Periph) {
		case RCC_APB2Periph_GPIOA:
			GPIO_WriteBit(GPIOA, Pin_SDA, (BitAction)(1));
			GPIO_WriteBit(GPIOA, Pin_SCL, (BitAction)(1));
			GPIO_WriteBit(GPIOA, Pin_SDA, (BitAction)(0));
			GPIO_WriteBit(GPIOA, Pin_SCL, (BitAction)(0));
			break;
		case RCC_APB2Periph_GPIOB:
			GPIO_WriteBit(GPIOB, Pin_SDA, (BitAction)(1));
			GPIO_WriteBit(GPIOB, Pin_SCL, (BitAction)(1));
			GPIO_WriteBit(GPIOB, Pin_SDA, (BitAction)(0));
			GPIO_WriteBit(GPIOB, Pin_SCL, (BitAction)(0));
			break;
	}
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void OLed_I2C_Stop(void) {
	switch(Periph) {
		case RCC_APB2Periph_GPIOA:
			GPIO_WriteBit(GPIOA, Pin_SDA, (BitAction)(0));
			GPIO_WriteBit(GPIOA, Pin_SCL, (BitAction)(1));
			GPIO_WriteBit(GPIOA, Pin_SDA, (BitAction)(1));
			break;
		case RCC_APB2Periph_GPIOB:
			GPIO_WriteBit(GPIOB, Pin_SDA, (BitAction)(0));
			GPIO_WriteBit(GPIOB, Pin_SCL, (BitAction)(1));
			GPIO_WriteBit(GPIOB, Pin_SDA, (BitAction)(1));
			break;
	}
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void OLed_I2C_SendByte(uint8_t Byte) {
	switch(Periph) {
		case RCC_APB2Periph_GPIOA:
			for (uint8_t i = 0; i < 8; i++) {
				GPIO_WriteBit(GPIOA, Pin_SDA, (BitAction)(Byte & (0x80 >> i)));
				GPIO_WriteBit(GPIOA, Pin_SCL, (BitAction)(1));
				GPIO_WriteBit(GPIOA, Pin_SCL, (BitAction)(0));
			}
			GPIO_WriteBit(GPIOA, Pin_SCL, (BitAction)(1)); //额外的一个时钟，不处理应答信号
			GPIO_WriteBit(GPIOA, Pin_SCL, (BitAction)(0));
			break;
		case RCC_APB2Periph_GPIOB:
			for (uint8_t i = 0; i < 8; i++) {
				GPIO_WriteBit(GPIOB, Pin_SDA, (BitAction)(Byte & (0x80 >> i)));
				GPIO_WriteBit(GPIOB, Pin_SCL, (BitAction)(1));
				GPIO_WriteBit(GPIOB, Pin_SCL, (BitAction)(0));
			}
			GPIO_WriteBit(GPIOB, Pin_SCL, (BitAction)(1)); //额外的一个时钟，不处理应答信号
			GPIO_WriteBit(GPIOB, Pin_SCL, (BitAction)(0));
			break;
	}
}

/**
  * @brief  OLed写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void OLed_WriteCommand(uint8_t Command) {
	OLed_I2C_Start();
	OLed_I2C_SendByte(0x78);	 //从机地址
	OLed_I2C_SendByte(0x00); //写命令
	OLed_I2C_SendByte(Command); 
	OLed_I2C_Stop();
}

/**
  * @brief  OLed写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void OLed_WriteData(uint8_t Data) {
	OLed_I2C_Start();
	OLed_I2C_SendByte(0x78); //从机地址
	OLed_I2C_SendByte(0x40); //写数据
	OLed_I2C_SendByte(Data);
	OLed_I2C_Stop();
}

/**
  * @brief  OLed设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLed_SetCursor(uint8_t Y, uint8_t X) {
	OLed_WriteCommand(0xB0 | Y); //设置Y位置
	OLed_WriteCommand(0x10 | ((X & 0xF0) >> 4)); //设置X位置高4位
	OLed_WriteCommand(0x00 | (X & 0x0F)); //设置X位置低4位
}

/**
  * @brief  OLed清屏
  * @param  无
  * @retval 无
  */
void OLed_Clear(void) {
	for (uint8_t j = 0; j < 8; j++) {
		OLed_SetCursor(j, 0);
		for(uint8_t i = 0; i < 128; i++) {
			OLed_WriteData(0x00);
		}
	}
}

/**
  * @brief  OLed显示一个字符
  * @param  Line 行位置，范围：1~4
  * @param  Column 列位置，范围：1~16
  * @param  Char 要显示的一个字符，范围：ASCII可见字符
  * @retval 无
  */
void OLed_ShowChar(uint8_t Line, uint8_t Column, char Char) {
	OLed_SetCursor((Line - 1) * 2, (Column - 1) * 8); //设置光标位置在上半部分
	for (uint8_t i = 0; i < 8; i++) {
		OLed_WriteData(OLed_F8x16[Char - ' '][i]); //显示上半部分内容
	}
	OLed_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8); //设置光标位置在下半部分
	for (uint8_t i = 0; i < 8; i++) {
		OLed_WriteData(OLed_F8x16[Char - ' '][i + 8]); //显示下半部分内容
	}
}

/**
  * @brief  OLed显示字符串
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @retval 无
  */
void OLed_ShowString(uint8_t Line, uint8_t Column, char *String) {
	for (uint8_t i = 0; String[i] != '\0'; i++) {
		OLed_ShowChar(Line, Column + i, String[i]);
	}
}

/**
  * @brief  OLed次方函数
  * @retval 返回值等于X的Y次方
  */
uint32_t OLed_Pow(uint32_t X, uint32_t Y) {
	uint32_t Result = 1;
	while (Y--) {
		Result *= X;
	}
	return Result;
}

/**
  * @brief  OLed显示数字（十进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLed_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length) {
	for (uint8_t i = 0; i < Length; i++) {
		OLed_ShowChar(Line, Column + i, Number / OLed_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLed显示数字（十进制，带符号数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLed_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length) {
	uint32_t Number1;
	if (Number >= 0) {
		OLed_ShowChar(Line, Column, '+');
		Number1 = Number;
	}
	else {
		OLed_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for (uint8_t i = 0; i < Length; i++) {
		OLed_ShowChar(Line, Column + i + 1, Number1 / OLed_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLed显示数字（十六进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval 无
  */
void OLed_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length) {
	uint8_t SingleNumber;
	for (uint8_t i = 0; i < Length; i++) {
		SingleNumber = Number / OLed_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10) {
			OLed_ShowChar(Line, Column + i, SingleNumber + '0');
		}
		else {
			OLed_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
  * @brief  OLed显示数字（二进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void OLed_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length) {
	for (uint8_t i = 0; i < Length; i++) {
		OLed_ShowChar(Line, Column + i, Number / OLed_Pow(2, Length - i - 1) % 2 + '0');
	}
}

/**
  * @brief  OLed初始化
  * @param  无
  * @retval 无
  */
void OLed_Init(const uint32_t RCC_APB2Periph, const uint16_t GPIO_Pin_SCL, const uint16_t GPIO_Pin_SDA) {
	if((RCC_APB2Periph != RCC_APB2Periph_GPIOA) && (RCC_APB2Periph != RCC_APB2Periph_GPIOB)) {
		return; //不允许使用其他类型的外围设备
	}
	Periph = RCC_APB2Periph;
	Pin_SCL = GPIO_Pin_SCL;
	Pin_SDA = GPIO_Pin_SDA;
	
	//上电延时
	for (uint32_t i = 0; i < 1000; i++) {
		for (uint32_t j = 0; j < 1000; j++);
	}
	
	OLed_I2C_Init(); //端口初始化
	
	OLed_WriteCommand(0xAE); //关闭显示
	
	OLed_WriteCommand(0xD5); //设置显示时钟分频比/振荡器频率
	OLed_WriteCommand(0x80);
	
	OLed_WriteCommand(0xA8); //设置多路复用率
	OLed_WriteCommand(0x3F);
	
	OLed_WriteCommand(0xD3); //设置显示偏移
	OLed_WriteCommand(0x00);
	
	OLed_WriteCommand(0x40); //设置显示开始行
	
	OLed_WriteCommand(0xA1); //设置左右方向，0xA1正常 0xA0左右反置
	
	OLed_WriteCommand(0xC8); //设置上下方向，0xC8正常 0xC0上下反置

	OLed_WriteCommand(0xDA); //设置COM引脚硬件配置
	OLed_WriteCommand(0x12);
	
	OLed_WriteCommand(0x81); //设置对比度控制
	OLed_WriteCommand(0xCF);

	OLed_WriteCommand(0xD9); //设置预充电周期
	OLed_WriteCommand(0xF1);

	OLed_WriteCommand(0xDB); //设置VCOMH取消选择级别
	OLed_WriteCommand(0x30);

	OLed_WriteCommand(0xA4); //设置整个显示打开/关闭

	OLed_WriteCommand(0xA6); //设置正常/倒转显示

	OLed_WriteCommand(0x8D); //设置充电泵
	OLed_WriteCommand(0x14);

	OLed_WriteCommand(0xAF); //开启显示
		
	OLed_Clear(); //OLed清屏
}
