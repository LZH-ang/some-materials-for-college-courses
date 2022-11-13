#include "stm32f10x.h"                  // Device header
#define u16 unsigned int
//点亮LED
//置位 |= 
//清零 &=~ 
void delay_ms(u16 time);
int main(void)
{
	*(unsigned int *)0x40021018 |= (1<<3);//打开APB2时钟

	while(1)
	{
		//PB5端口配置寄存器：推挽输出，10MHz
		*(unsigned int *)0X40010C00 &=~(0X0F<<(4*5));//清零
		*(unsigned int *)0X40010C00 |= (1<<(4*5));//推挽输出，10MHz
		//端口输出寄存器
		*(unsigned int *)0X40010C0C &=~(1<<5);//输出低电平
		delay_ms(100);
		*(unsigned int *)0X40010C00 = 0X44444444;//复位
		
		//PB0端口配置寄存器：推挽输出，10MHz
		*(unsigned int *)0X40010C00 &=~(0X0F<<(4*0));//清零
		*(unsigned int *)0X40010C00 |= (1<<(4*0));//推挽输出，10MHz
		//端口输出寄存器
		*(unsigned int *)0X40010C0C &=~(1<<0);//输出低电平
		delay_ms(100);
		*(unsigned int *)0X40010C00 = 0X44444444;//复位
		
		//PB1端口配置寄存器：推挽输出，10MHz
		*(unsigned int *)0X40010C00 &=~(0X0F<<(4*1));//清零
		*(unsigned int *)0X40010C00 |= (1<<(4*1));//推挽输出，10MHz
		//端口输出寄存器
		*(unsigned int *)0X40010C0C &=~(1<<1);//输出低电平	
		delay_ms(100);
		*(unsigned int *)0X40010C00 = 0X44444444;//复位		
	}
}
void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //自己定义
      while(i--);    
   }
}
void SystemInit(void)
{
	//space
}
