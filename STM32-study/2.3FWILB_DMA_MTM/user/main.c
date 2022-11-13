#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_dma.h"


int main(void)
{
	uint8_t TransferStatus;
	LED_Init();
	DMA_Config();
	
	while(DMA_GetFlagStatus(DMA_FLAG_TC)==RESET);
	TransferStatus=Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
	if(TransferStatus){LED_GREEN;}
	else {LED_RED;}
	
	while(1)
	{
		
	}
}
