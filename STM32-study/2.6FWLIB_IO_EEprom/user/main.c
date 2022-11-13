#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_iic_eeprom.h"

#define  	EEP_Firstpage      0x00
uint8_t		I2c_Buf_Write[256];

int main(void)
{
	LED_Init();
	USART_Config();
//	I2C_EEPROM_CheckOk();
	LED_BLUE;
	Usart_SendString( DEBUG_USARTx, "	Hello STM32!\n");
	printf("	stm32��ү��!\n\r");//ʹ��printf���ļ�Ҫ��ANSI���뷽ʽ

	EEPROM_Erase();
	
	if(EEPROM_Test() == 1)
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

