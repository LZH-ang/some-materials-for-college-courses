#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_iic_eeprom.h"

#define DOUBLE_ADDR 		0x08
#define LONGINT_ADDR    0x40
#define DIGITAL_ADDR    0x60
#define LETTERLOW_ADDR  0x70
#define LETTERUP_ADDR   0x90
#define CHINESE_ADDR		0xb0

int main(void)
{
	uint8_t cal_flag = 0x00;
	uint8_t k;
	char digital_char[] = "0123456789";
	char letter_Lchar[] = "abcdefghijklmnopqrstuvwxyz";
	char letter_Uchar[] = "ABCDEFGHIGKLMNOPQRSTUVWXYZ";
	char Chinese_char[] = "STM32好贵啊";
	long double double_buffer[7] = {0};	//64bit
	int int_bufffer[7] = {0};						//32bit

	LED_Init();
	USART_Config();
	I2C_Config();
	Usart_SendString( DEBUG_USARTx, "	Hello STM32!\n");
	printf("	stm32给爷爬!\n\r");//使用printf的文件要用ANSI编码方式
	
	/*存取字符*/
	printf("\r\ndigital_char=%d '%s'\r\n",sizeof(digital_char),digital_char);
	I2C_EEPROM_BufferW(DIGITAL_ADDR, (void*)digital_char, sizeof(digital_char));
	I2C_EEPROM_BufferR(DIGITAL_ADDR, (void*)digital_char, sizeof(digital_char));
	printf("READ_EEPROM:%s\r\n",digital_char);
	printf("letter_Lchar=%d '%s'\r\n",sizeof(letter_Lchar),letter_Lchar);
	I2C_EEPROM_BufferW(LETTERLOW_ADDR, (void*)letter_Lchar, sizeof(letter_Lchar));
	I2C_EEPROM_BufferR(LETTERLOW_ADDR, (void*)letter_Lchar, sizeof(letter_Lchar));
	printf("READ_EEPROM:%s\r\n",letter_Lchar);
	printf("letter_Uchar=%d '%s'\r\n",sizeof(letter_Uchar),letter_Uchar);
	I2C_EEPROM_BufferW(LETTERUP_ADDR, (void*)letter_Uchar, sizeof(letter_Uchar));
	I2C_EEPROM_BufferR(LETTERUP_ADDR, (void*)letter_Uchar, sizeof(letter_Uchar));
	printf("READ_EEPROM:%s\r\n",letter_Uchar);
	printf("Chinese_char=%d '%s'\r\n",sizeof(Chinese_char),Chinese_char);
	I2C_EEPROM_BufferW(CHINESE_ADDR, (void*)Chinese_char, sizeof(Chinese_char));
	I2C_EEPROM_BufferR(CHINESE_ADDR, (void*)Chinese_char, sizeof(Chinese_char));
	printf("READ_EEPROM:%s\r\n",Chinese_char);
	
	/*读取数据标志位*/
	cal_flag = I2C_EEPROM_ByteR(cal_flag);
	if( cal_flag != 0xCD )	/*若标志等于0xcd，表示之前已有写入数据*/
	{      
			printf("\r\n没有检测到数据标志，FLASH没有存储数据，即将进行小数写入实验\r\n");
			cal_flag =0xCD;		
			/*写入标志到0地址*/
			I2C_EEPROM_ByteW(0x00, &cal_flag);
			/*生成要写入的数据*/
			for( k=0; k<7; k++ )
			{
				 double_buffer[k] = k +0.1;
				 int_bufffer[k]=k*500+1 ;
			}
			/*写入小数数据到地址10*/
			I2C_EEPROM_BufferW(DOUBLE_ADDR, (void*)double_buffer, sizeof(double_buffer));
			/*写入整数数据到地址60*/
			I2C_EEPROM_BufferW(LONGINT_ADDR, (void*)int_bufffer, sizeof(int_bufffer));
						
			printf("向芯片写入数据：");
			/*打印到串口*/
			for( k=0; k<7; k++ )
			{
				printf("小数tx = %LF\r\n",double_buffer[k]);
				printf("整数tx = %d\r\n",int_bufffer[k]);
			}		
			printf("\r\n请复位开发板，以读取数据进行检验\r\n");      
	}    
	else
	{      
		printf("\r\n检测到数据标志\r\n");
		/*读取小数数据*/
		I2C_EEPROM_BufferR(DOUBLE_ADDR, (void*)double_buffer, sizeof(double_buffer));
		/*读取整数数据*/
		I2C_EEPROM_BufferR(LONGINT_ADDR, (void*)int_bufffer, sizeof(int_bufffer));
		printf("\r\n从芯片读到数据：\r\n");			
		for( k=0; k<7; k++ )
		{
			printf("小数 rx = %LF \r\n",double_buffer[k]);
			printf("整数 rx = %d \r\n",int_bufffer[k]);				
		}	
	}
	
	while(1)
	{
		
	}
}
