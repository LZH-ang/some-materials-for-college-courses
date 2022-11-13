#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_spi_flash.h"

static void Show_Message(void);

typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
TestStatus Buffercmp(uint8_t* pBuffer1,uint8_t* pBuffer2, uint16_t BufferLength);
/* 获取缓冲区的长度 */
#define  countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress
/* 发送缓冲区初始化 */
uint8_t Tx_Buffer[] = "你好,我是Kelee,野火stm32指南者。";
uint8_t Rx_Buffer[BufferSize];
__IO uint8_t DeviceID = 0;
__IO uint32_t JEDECID = 0;
__IO TestStatus TransferStatus1 = FAILED;
/*-------------------------------------------------------*/

int main(void)
{
    char ch;
	uint8_t k;
	/*存储小数和整数的数组，各7个*/
	long double double_buffer[7] = {0};
	int int_bufffer[7] = {0};

    LED_Init();
	LED_BLUE;
    USART_Config();
	SPI_FLASH_Init();
    Usart_SendString( DEBUG_USARTx, "\n Hello STM32!\n");
    printf("\n stm32给爷爬\n");	//使用printf的文件要用ANSI编码方式
	JEDECID = SPI_FLASH_ReadID();
    delay_ms(10);
	DeviceID = SPI_FLASH_ReleaseReadID();
    printf("\r\n JEDECID is 0x%X,Manufacturer Device ID is 0x%X\r\n", JEDECID, DeviceID);

	if (JEDECID == sFLASH_ID)
    {
        printf("\r\n 检测到串行flash W25Q64 !\r\n");
        /* 擦除将要写入的 SPI FLASH 扇区，FLASH写入前要先擦除 */
        // 这里擦除4K，即一个扇区，擦除的最小单位是扇区
        SPI_FLASH_Sector_BlockErase(W25Q64_SectorErase4KB,FLASH_SectorToErase);
        /* 将发送缓冲区的数据写到flash中 */
        // 这里写一页，一页的大小为256个字节
        SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
        printf("\r\n 写入的数据为：%s \r\n", Tx_Buffer);
        /* 将刚刚写入的数据读出来放到接收缓冲区中 */
        SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
        printf("\r\n 读出的数据为：%s \r\n", Rx_Buffer);
        /* 检查写入的数据与读出的数据是否相等 */
        TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
        if(PASSED == TransferStatus1)
        {
            LED_GREEN;
            printf("\r\n 8M串行flash(W25Q64)测试成功!\n\r");
        }
        else
        {
            LED_RED;
            printf("\r\n 8M串行flash(W25Q64)测试失败!\n\r");
        }
		printf("---进行小数写入实验---\r\n");
		/*生成要写入的数据*/
		for( k=0; k<7; k++ )
		{
			double_buffer[k] = k+0.1;
			int_bufffer[k] = k*500+1;
		}
		/*写入小数数据到第一页*/
		SPI_FLASH_BufferWrite((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
		/*写入整数数据到第二页*/
		SPI_FLASH_BufferWrite((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));
		printf("\r\n向芯片写入数据：\r\n");
		/*打印到串口*/
		for( k=0; k<7; k++ )
		{
			printf("小数tx = %LF\r\n",double_buffer[k]);
			printf("整数tx = %d\r\n",int_bufffer[k]);
		}	
		for( k=0; k<7; k++ )
		{
			double_buffer[k] = 0;
			int_bufffer[k] = 0;
		}
		/*读取小数数据*/
		SPI_FLASH_BufferRead((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
		/*读取整数数据*/
		SPI_FLASH_BufferRead((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));	
		printf("\r\n从芯片读到数据：\r\n");			
		for( k=0; k<7; k++ )
		{
			printf("小数 rx = %LF \r\n",double_buffer[k]);
			printf("整数 rx = %d \r\n",int_bufffer[k]);				
		}		
    }
    else
    {
        LED_RED;
        printf("\r\n 获取不到 W25Q64 ID!\n\r");
    }
	
    while(1)
    {
        ch=getchar();
        printf("Receive：%c\n",ch);
        switch(ch)
        {
        case '1':
            LED_RED;
            break;
        case '2':
            LED_GREEN;
            break;
        case '3':
            LED_BLUE;
            break;
        case '4':
            LED_YELLOW;
            break;
        case '5':
            LED_PURPLE;
            break;
        case '6':
            LED_CYAN;
            break;
        case '7':
            LED_WHITE;
            break;
        case '8':
            LED_RGBOFF;
            break;
        default :
            Show_Message();
            break;
        }
    }
}

/*
 * 函数名：Buffercmp
 * 描述  ：比较两个缓冲区中的数据是否相等
 * 输入  ：-pBuffer1     src缓冲区指针
 *         -pBuffer2     dst缓冲区指针
 *         -BufferLength 缓冲区长度
 * 输出  ：无
 * 返回  ：-PASSED pBuffer1 等于   pBuffer2
 *         -FAILED pBuffer1 不同于 pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while(BufferLength--)
    {
        if(*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }
        pBuffer1++;
        pBuffer2++;
    }
    return PASSED;
}

static void Show_Message(void)
{
    printf("  USART：%d 8-N-1 \n",DEBUG_USART_BAUDRATE);
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
