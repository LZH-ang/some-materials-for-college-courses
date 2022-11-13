#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_spi_flash.h"

static void Show_Message(void);

typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;
TestStatus Buffercmp(uint8_t* pBuffer1,uint8_t* pBuffer2, uint16_t BufferLength);
/* ��ȡ�������ĳ��� */
#define  countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress
/* ���ͻ�������ʼ�� */
uint8_t Tx_Buffer[] = "���,����Kelee,Ұ��stm32ָ���ߡ�";
uint8_t Rx_Buffer[BufferSize];
__IO uint8_t DeviceID = 0;
__IO uint32_t JEDECID = 0;
__IO TestStatus TransferStatus1 = FAILED;
/*-------------------------------------------------------*/

int main(void)
{
    char ch;
	uint8_t k;
	/*�洢С�������������飬��7��*/
	long double double_buffer[7] = {0};
	int int_bufffer[7] = {0};

    LED_Init();
	LED_BLUE;
    USART_Config();
	SPI_FLASH_Init();
    Usart_SendString( DEBUG_USARTx, "\n Hello STM32!\n");
    printf("\n stm32��ү��\n");	//ʹ��printf���ļ�Ҫ��ANSI���뷽ʽ
	JEDECID = SPI_FLASH_ReadID();
    delay_ms(10);
	DeviceID = SPI_FLASH_ReleaseReadID();
    printf("\r\n JEDECID is 0x%X,Manufacturer Device ID is 0x%X\r\n", JEDECID, DeviceID);

	if (JEDECID == sFLASH_ID)
    {
        printf("\r\n ��⵽����flash W25Q64 !\r\n");
        /* ������Ҫд��� SPI FLASH ������FLASHд��ǰҪ�Ȳ��� */
        // �������4K����һ����������������С��λ������
        SPI_FLASH_Sector_BlockErase(W25Q64_SectorErase4KB,FLASH_SectorToErase);
        /* �����ͻ�����������д��flash�� */
        // ����дһҳ��һҳ�Ĵ�СΪ256���ֽ�
        SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
        printf("\r\n д�������Ϊ��%s \r\n", Tx_Buffer);
        /* ���ո�д������ݶ������ŵ����ջ������� */
        SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
        printf("\r\n ����������Ϊ��%s \r\n", Rx_Buffer);
        /* ���д�������������������Ƿ���� */
        TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
        if(PASSED == TransferStatus1)
        {
            LED_GREEN;
            printf("\r\n 8M����flash(W25Q64)���Գɹ�!\n\r");
        }
        else
        {
            LED_RED;
            printf("\r\n 8M����flash(W25Q64)����ʧ��!\n\r");
        }
		printf("---����С��д��ʵ��---\r\n");
		/*����Ҫд�������*/
		for( k=0; k<7; k++ )
		{
			double_buffer[k] = k+0.1;
			int_bufffer[k] = k*500+1;
		}
		/*д��С�����ݵ���һҳ*/
		SPI_FLASH_BufferWrite((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
		/*д���������ݵ��ڶ�ҳ*/
		SPI_FLASH_BufferWrite((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));
		printf("\r\n��оƬд�����ݣ�\r\n");
		/*��ӡ������*/
		for( k=0; k<7; k++ )
		{
			printf("С��tx = %LF\r\n",double_buffer[k]);
			printf("����tx = %d\r\n",int_bufffer[k]);
		}	
		for( k=0; k<7; k++ )
		{
			double_buffer[k] = 0;
			int_bufffer[k] = 0;
		}
		/*��ȡС������*/
		SPI_FLASH_BufferRead((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
		/*��ȡ��������*/
		SPI_FLASH_BufferRead((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));	
		printf("\r\n��оƬ�������ݣ�\r\n");			
		for( k=0; k<7; k++ )
		{
			printf("С�� rx = %LF \r\n",double_buffer[k]);
			printf("���� rx = %d \r\n",int_bufffer[k]);				
		}		
    }
    else
    {
        LED_RED;
        printf("\r\n ��ȡ���� W25Q64 ID!\n\r");
    }
	
    while(1)
    {
        ch=getchar();
        printf("Receive��%c\n",ch);
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
 * ��������Buffercmp
 * ����  ���Ƚ������������е������Ƿ����
 * ����  ��-pBuffer1     src������ָ��
 *         -pBuffer2     dst������ָ��
 *         -BufferLength ����������
 * ���  ����
 * ����  ��-PASSED pBuffer1 ����   pBuffer2
 *         -FAILED pBuffer1 ��ͬ�� pBuffer2
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
