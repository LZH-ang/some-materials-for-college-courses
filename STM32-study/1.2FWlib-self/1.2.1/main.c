#include "stm32f10x.h"                  // Device header
//����LED
//��λ |= 
//���� &=~ 
void delay_ms(uint16_t time);
int main(void)
{
	RCC->APB2ENR |= (1<<3);//��APB2ʱ��
	//PB5�˿����üĴ��������������10MHz
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
		//�˿�����Ĵ���
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
}
void delay_ms(uint16_t time)
{    
   uint16_t i=0;  
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
