#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_dma.h"


int main(void)
{
	uint16_t i;
	
	LED_Init();
	USART_Config();
	DMA_Config();
	
	LED_RED;
  printf("\r\n USART1 DMA TX ���� \r\n");
  /*��佫Ҫ���͵�����*/
  for(i=0;i<SENDBUFF_SIZE;i++)
  {
    SendBuff[i]	 = 'P';  
  }
	USART_DMACmd(DMA_USART, USART_DMAReq_Tx, ENABLE);
	
	while(DMA_GetFlagStatus(DMAtoUSART_FLAG_TC)==RESET)
	{
		LED_B_ON;
		delay_ms(100);
		LED_B_OFF;
		delay_ms(100);
	}
	LED_GREEN;
	
	while(1)
	{
		
	}
}
