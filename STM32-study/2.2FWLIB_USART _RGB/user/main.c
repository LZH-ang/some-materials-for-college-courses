#include "stm32f10x.h"   // �൱��51��Ƭ���е�  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"

static void Show_Message(void);

int main(void)
{
	char ch;

	LED_Init();
	USART_Config();
	Usart_SendString( DEBUG_USARTx, "\nHello STM32!\n");
	printf("\nstm32��ү��\n");//ʹ��printf���ļ�Ҫ��ANSI���뷽ʽ
	
	while(1)
	{
		ch=getchar();
    printf("Receive��%c\n",ch);
		switch(ch)
		{
			case '1': LED_RED; break;
			case '2': LED_GREEN; break;
			case '3': LED_BLUE; break;
			case '4': LED_YELLOW; break;
			case '5': LED_PURPLE; break;
			case '6': LED_CYAN; break;
			case '7': LED_WHITE; break;
			case '8': LED_RGBOFF; break;
			default :	Show_Message(); break;
		}
	}
}

static void Show_Message(void)
{
  printf("  USART��%d 8-N-1 \n",DEBUG_USART_BAUDRATE);
  printf("   CMD   ------    RGB   \n");
  printf("    1    ------    RED   \n");
  printf("    2    ------   GREEN  \n");
  printf("    3    ------    BLUE  \n");
  printf("    4    ------   YELLOW \n");
  printf("    5    ------   PURPLE \n");
  printf("    6    ------    CYAN  \n");
  printf("    7    ------   WHITE  \n");
  printf("    8    ------   RGBOFF \n");  
}
