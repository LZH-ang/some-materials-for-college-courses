#include "stm32f10x.h"                  // Device header
#define u16 unsigned int
//����LED
//��λ |= 
//���� &=~ 
void delay_ms(u16 time);
int main(void)
{
	*(unsigned int *)0x40021018 |= (1<<3);//��APB2ʱ��

	while(1)
	{
		//PB5�˿����üĴ��������������10MHz
		*(unsigned int *)0X40010C00 &=~(0X0F<<(4*5));//����
		*(unsigned int *)0X40010C00 |= (1<<(4*5));//���������10MHz
		//�˿�����Ĵ���
		*(unsigned int *)0X40010C0C &=~(1<<5);//����͵�ƽ
		delay_ms(100);
		*(unsigned int *)0X40010C00 = 0X44444444;//��λ
		
		//PB0�˿����üĴ��������������10MHz
		*(unsigned int *)0X40010C00 &=~(0X0F<<(4*0));//����
		*(unsigned int *)0X40010C00 |= (1<<(4*0));//���������10MHz
		//�˿�����Ĵ���
		*(unsigned int *)0X40010C0C &=~(1<<0);//����͵�ƽ
		delay_ms(100);
		*(unsigned int *)0X40010C00 = 0X44444444;//��λ
		
		//PB1�˿����üĴ��������������10MHz
		*(unsigned int *)0X40010C00 &=~(0X0F<<(4*1));//����
		*(unsigned int *)0X40010C00 |= (1<<(4*1));//���������10MHz
		//�˿�����Ĵ���
		*(unsigned int *)0X40010C0C &=~(1<<1);//����͵�ƽ	
		delay_ms(100);
		*(unsigned int *)0X40010C00 = 0X44444444;//��λ		
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
