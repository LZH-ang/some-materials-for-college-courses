#include "bsp_led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_LED;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//开启多个时钟用"|"	
	
	GPIO_LED.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_LED.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_LED.GPIO_Pin = LED_R;
	GPIO_Init(GPIOB, &GPIO_LED);
	GPIO_LED.GPIO_Pin = LED_G;
	GPIO_Init(GPIOB, &GPIO_LED);
	
	GPIO_LED.GPIO_Pin = LED_B;
	GPIO_Init(GPIOB, &GPIO_LED);
	
	LED_R_OFF;
//	LED_R_ON;
	LED_G_OFF;
//	LED_G_ON;
	LED_B_OFF;
//	LED_B_ON;
}

void delay_ms(uint16_t time)
{    
   uint16_t i=0;  
   while(time--)
   {
      i=12000;  //自己定义
      while(i--);    
   }
}
