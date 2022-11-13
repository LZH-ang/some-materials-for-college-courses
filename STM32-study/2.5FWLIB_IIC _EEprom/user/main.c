#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_iic_eeprom.h"


int main(void)
{
	uint8_t		I2c_Buf_Write[256];
	LED_Init();
	USART_Config();
	I2C_Config();
	LED_RED;
	Usart_SendString( DEBUG_USARTx, "	Hello STM32!\n");
	printf("	stm32给爷爬!\n\r");//使用printf的文件要用ANSI编码方式
	I2c_Buf_Write[0] = 9;I2c_Buf_Write[7] = 8;I2c_Buf_Write[8] = 7;
	printf("写入的数据:0x%02X\n\r",I2c_Buf_Write[0]);

	I2C_EEPROM_ByteW(EEP_Firstpage, I2c_Buf_Write);
	EEPROM_INFO("\n    写成功\n\r");
	EEPROM_ACK_POLL();
	I2c_Buf_Write[0] = I2C_EEPROM_ByteR(EEP_Firstpage);
	EEPROM_INFO("\n    读成功:%d\n\r",I2c_Buf_Write[0]);
	
	I2C_EEPROM_PageW(EEP_Firstpage, I2c_Buf_Write, 9);
	EEPROM_INFO("\n    写成功\n\r");
	EEPROM_ACK_POLL();
	I2c_Buf_Write[0] = I2C_EEPROM_ByteR(EEPROM_page(0));
	EEPROM_INFO("\n    读成功:%d\n\r",I2c_Buf_Write[0]);
	
	LED_BLUE; 
  //EEPROM 读写测试
	if(I2C_Test() ==1)
	{
			LED_GREEN;
	}
	else
	{
			LED_RED;
	}
	
	while(1)
	{
		
	}
}
