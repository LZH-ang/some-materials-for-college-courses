/**********************************************************************************************/
/*		1) 初始化用来产生中断的 GPIO；																															*/
/*		2) 初始化 EXTI；																																					*/
/*		3) 配置 NVIC；																																						*/
/*		4) 编写中断服务函数；																																			*/
/**********************************************************************************************/
#include "stm32f10x.h"  
#include "bsp_led.h"
#include "bsp_exti.h"

uint8_t LED_flag = 0;

int main(void)
{
	// 来到这里的时候，系统的时钟已经被配置成72M。
	LED_Init();
	KEY_EXTI_Init();
	LED_R_OFF;
//	LED_R_ON;
	LED_G_OFF;
//	LED_G_ON;
	LED_B_OFF;
//	LED_B_ON;
	while(1)
	{
//		LED_flag = Readflag();
		if(LED_flag)
		{
			LEDG_ON;
//			LED_RED;delay_ms(500);
//			LED_YELLOW;delay_ms(500);
//			LED_BLUE;delay_ms(500);
//			LED_GREEN;delay_ms(500);
//			LED_CYAN;delay_ms(500);
//			LED_PURPLE;delay_ms(500);
		}		
		else 
		{
			LED_R_OFF;
			LED_G_OFF;
			LED_B_OFF;
		}		
	}
}

//我不明白为啥还要有stm32f10x_it
void KEY1_IRQHandler(void)								//中断服务函数
{
	if(EXTI_GetITStatus(KEY1_LINE) == SET)	//检测中断标志位
	{
		LED_flag = ~LED_flag;
		EXTI_ClearITPendingBit(KEY1_LINE);		//清除中断挂起
	}
}

