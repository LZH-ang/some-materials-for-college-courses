#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_spi_flash.h"
#include "ff.h"
#include "diskio.h"	

#define CHIPERASE	0
static BYTE flashwork[FF_MAX_SS] = {0};
static FRESULT res_flash;
static FATFS fs_flash;
static FIL fil_flash;
static UINT fw_num;
static BYTE writetest0[] = "lseek\r\n MCU:STM32F1;\r\n FATFS:R0.13b;\r\n DEVICE:SPIFLASH(W25Q64)\r\n";
static BYTE readbuffer[FF_MAX_SS] = {0};
/*-------------------------------------------------------*/

int main(void)
{
    LED_Init();
    LED_BLUE;
    USART_Config();
	printf("\r\n======================================================================");
	printf("\r\n=                           Hello STM32!                             =");
	printf("\r\n=                                                                    =");
	printf("\r\n=                     STM32F1_Fatfs Program Demo                     =");
	printf("\r\n=                                                                    =");
	printf("\r\n=                                           By Kelee                 =");
	printf("\r\n======================================================================");
#if CHIPERASE
	printf("\n>ERASE FATFS...\n");
	SPI_FLASH_Init();
	SPI_FLASH_ChipErase();
#endif
    res_flash = f_mount(&fs_flash, "3:", 1);
#if DEBUG
    printf("\n f_mount %d\n", res_flash);
#endif
    if(res_flash == FR_NO_FILESYSTEM)
    {
        printf("\n>FLASH_NO_FILESYSTEM START TO MKFS\n>WAIT...\n");
        res_flash = f_mkfs("3:", FM_FAT, 0, flashwork, sizeof flashwork);
#if DEBUG
        printf("\n f_mkfs %d\n", res_flash);
#endif
        if(res_flash == FR_OK)
        {
            printf("\n>MKFS OVER\n");
            res_flash = f_unmount("3:");
            res_flash = f_mount(&fs_flash, "3:", 1);
        }
        else
        {
            printf("\n>MKFS FAIL\n");
        }
    }
    else if(res_flash != FR_OK)
    {
        printf("\n>MOUNT FAIL\n");
    }
    else
    {
        printf("\n>MOUNT OVER\n");
    }
	printf("\r\n======================================================================");
	printf("\r\n=                           WRITE TEST                               =");
	printf("\r\n======================================================================");
	res_flash = f_open(&fil_flash, "3:info.txt", FA_WRITE|FA_CREATE_ALWAYS);
#if DEBUG
    printf("\n f_open %d\n", res_flash);
#endif
    if(res_flash == FR_OK)
    {
		printf("\n>OPEN OVER START TO WRITE\n>FILE NUMBER OF BYTES TO WRITE %d\n", sizeof writetest0);
		res_flash = f_write(&fil_flash, writetest0, sizeof writetest0, &fw_num);
#if DEBUG
		printf("\n f_write %d\n", res_flash);
#endif
		if(res_flash==FR_OK)
		{
			printf("\n>WRITE OVER\n>NUMBER OF BYTES WRITTEN: %d\n", fw_num);
		}
		else
		{
			printf("\n>WRITE FAIL\n");
		}
    }
    else
    {
		printf("\n>FOPEN FAIL\n");
    }
	res_flash = f_close(&fil_flash);
#if DEBUG
    printf("\n f_close %d\n", res_flash);
#endif
	if(res_flash==FR_OK)
	{
		printf("\n>FCLOSE OVER\n");
	}
	else
	{
		printf("\n>FCLOSE FAIL\n");
	}
	printf("\r\n======================================================================");
	printf("\r\n=                            READ TEST                               =");
	printf("\r\n======================================================================");
	res_flash = f_open(&fil_flash, "3:info.txt", FA_READ|FA_OPEN_EXISTING);
#if DEBUG
    printf("\n f_open %d\n", res_flash);
#endif
    if(res_flash == FR_OK)
    {
		printf("\n>OPEN OVER START TO READ\n");
		res_flash = f_lseek(&fil_flash, 5);
#if DEBUG
		printf("\n f_lseek %d\n", res_flash);
#endif
		res_flash = f_read(&fil_flash, readbuffer, sizeof readbuffer, &fw_num);
#if DEBUG
		printf("\n f_read %d\n", res_flash);
#endif
		if(res_flash==FR_OK)
		{
			printf("\n>READ OVER\n>NUMBER OF BYTES READ: %d\n", fw_num);
			printf("\n>THE DATA READ: %s\n", readbuffer);
		}
		else
		{
			printf("\n>READ FAIL\n");
		}
    }
    else
    {
		printf("\n>FOPEN FAIL\n");
    }
	res_flash = f_close(&fil_flash);
#if DEBUG
    printf("\n f_close %d\n", res_flash);
#endif
	if(res_flash==FR_OK)
	{
		printf("\n>FCLOSE OVER\n");
	}
	else
	{
		printf("\n>FCLOSE FAIL\n");
	}
	
    while(1)
    {

    }
}

