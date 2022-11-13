#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_clkconfig.h"


int main(void)
{
	// 程序来到main函数之前，启动文件：statup_stm32f10x_hd.s已经调用
	// SystemInit()函数把系统时钟初始化成72MHZ
	// SystemInit()在system_stm32f10x.c中定义
	// 如果用户想修改系统时钟，可自行编写程序修改
	
	// 重新设置系统时钟，这时候可以选择使用HSE还是HSI
	
	// 使用HSE时，SYSCLK = 8M * RCC_PLLMul_x, x:[2,3,...16],最高是128M
	//HSE_SetSysClock(RCC_PLLMul_9);
	
	// 使用HSI时，SYSCLK = 4M * RCC_PLLMul_x, x:[2,3,...16],最高是64MH
	HSE_SetSysClock(RCC_PLLMul_9);
	
	// MCO 引脚初始化
	MCO_Init();
	
	// 设置MCO引脚输出时钟，用示波器即可在PA8测量到输出的时钟信号，
	// 我们可以把PLLCLK/2作为MCO引脚的时钟来检测系统时钟是否配置准确
	// MCO引脚输出可以是HSE,HSI,PLLCLK/2,SYSCLK	
	//RCC_MCOConfig(RCC_MCO_HSE);	             	        
	//RCC_MCOConfig(RCC_MCO_HSI);	                   
	//RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);    	
	RCC_MCOConfig(RCC_MCO_SYSCLK);		      
	
	// LED 端口初始化
	LED_Init();
	
	LED_R_OFF;
//	LED_R_ON;
	LED_G_OFF;
//	LED_G_ON;
	LED_B_OFF;
//	LED_B_ON;
	while(1)
	{
		LED_RED;delay_ms(500);
		LED_YELLOW;delay_ms(500);
		LED_BLUE;delay_ms(500);
		LED_GREEN;delay_ms(500);
		LED_CYAN;delay_ms(500);
		LED_PURPLE;delay_ms(500);
	}
}
