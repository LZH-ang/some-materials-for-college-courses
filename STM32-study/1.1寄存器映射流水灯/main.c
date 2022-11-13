#include "stm32f10x.h"                  // Device header
#define u16 unsigned int
//����LED
//��λ |= 
//���� &=~ 
void delay_ms(u16 time);
int main(void)
{
	RCC_APB2ENR |= (1<<3);//��APB2ʱ��
	//PB5�˿����üĴ��������������10MHz
	GPIOB_CRL &=~(0X0F<<(4*5));
	GPIOB_CRL |= (1<<(4*5));
	GPIOB_CRL &=~(0X0F<<(4*0));
	GPIOB_CRL |= (1<<(4*0));
	GPIOB_CRL &=~(0X0F<<(4*1));
	GPIOB_CRL |= (1<<(4*1));
	GPIOB_ODR |= (1<<0);
	GPIOB_ODR |= (1<<1);
	GPIOB_ODR |= (1<<5);
	while(1)
	{	
		//�˿�����Ĵ���
		GPIOB_ODR &=~(1<<0);
		delay_ms(100);
		GPIOB_ODR |= (1<<0);

		GPIOB_BRR |= (1<<1);
		delay_ms(100);
		GPIOB_BSRR |= (1<<1);

		GPIOB_BRR |= (1<<5);
		delay_ms(100);
		GPIOB_BSRR |= (1<<5);
	}
}
void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //�Լ�����
      while(i--);    
   }
}
void SystemInit(void)
{
	//space
}
