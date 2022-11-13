#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"


int main(void)
{
	// 来到这里的时候，系统的时钟已经被配置成72M。
//	LED_Init();
	
//	uint8_t array[] = {0xff,0xee,0xdd,0xcc,0xbb,0xaa,0x99,0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11,0x00};
	USART_Config();
//	Usart_SendHalfWord( DEBUG_USARTx, 0xcccc);
//	Usart_SendArray( DEBUG_USARTx, array, 16);
	Usart_SendByte( DEBUG_USARTx, 0xcc);
	Usart_SendHalfWord( DEBUG_USARTx, 0x8888);
//	Usart_SendString( DEBUG_USARTx, "\nHello World!\n");
//	printf("\nstm32给爷爬\n");//使用printf的文件要用ANSI编码方式
	
	while(1)
	{
		
//		LED_RED;delay_ms(500);
//		LED_YELLOW;delay_ms(500);
//		LED_BLUE;delay_ms(500);
//		LED_GREEN;delay_ms(500);
//		LED_CYAN;delay_ms(500);
//		LED_PURPLE;delay_ms(500);
	}
}
