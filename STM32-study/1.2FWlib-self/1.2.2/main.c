
#include "stm32f10x.h" // Device header
#include "stm32f10x_gpio.h"

//????LED
//??λ |= 
//???? &=~ 
void delay_ms(uint16_t time);
int main(void)
{
#if 0
	RCC->APB2ENR |= (1<<3);//????APB2ʱ??
	//PB5?˿????üĴ???????????????10MHz
	GPIOB->CRL &=~(0X0F<<(4*5));
	GPIOB->CRL |= (1<<(4*5));
	GPIOB->CRL &=~(0X0F<<(4*0));
	GPIOB->CRL |= (1<<(4*0));
	GPIOB->CRL &=~(0X0F<<(4*1));
	GPIOB->CRL |= (1<<(4*1));
	GPIOB->ODR |= (1<<0);
	GPIOB->ODR |= (1<<1);
	GPIOB->ODR |= (1<<5);
	while(1)
	{	
		//?˿??????Ĵ???
		GPIOB->ODR &=~(1<<0);
		delay_ms(100);
		GPIOB->ODR |= (1<<0);

		GPIOB->BRR |= (1<<1);
		delay_ms(100);
		GPIOB->BSRR |= (1<<1);

		GPIOB->BRR |= (1<<5);
		delay_ms(100);
		GPIOB->BSRR |= (1<<5);
	}
#elif 1
	
	
	GPIO_Init_Def		GPIO_InitStructure;
	RCC->APB2ENR |= (1<<3);//????APB2ʱ??
	GPIOB->CRL &=~(0X0F<<(4*5));
	GPIOB->CRL &=~(0X0F<<(4*0));
	GPIOB->CRL &=~(0X0F<<(4*1));
	GPIOB->ODR |= (1<<5);
	GPIOB->ODR |= (1<<0);
	GPIOB->ODR |= (1<<1);
	//?˿????üĴ???????????????10MHz
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	delay_ms(100);
	while(1)
	{	
		//?˿??????Ĵ???

		GPIOB->ODR &=~ (1<<5);
		delay_ms(100);
		GPIOB->ODR |= (1<<5);

		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		delay_ms(100);
		GPIO_SetBits(GPIOB,GPIO_Pin_0);

		GPIO_ResetBits(GPIOB,GPIO_Pin_1);
		delay_ms(100);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
	}

#endif
}
void delay_ms(uint16_t time)
{    
   uint16_t i=0;  
   while(time--)
   {
      i=12000;  //?Լ?????
      while(i--);    
   }
}
void SystemInit(void)
{
	//space
}
