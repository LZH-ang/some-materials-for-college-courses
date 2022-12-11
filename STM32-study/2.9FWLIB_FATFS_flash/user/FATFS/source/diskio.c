/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "bsp_spi_flash.h"	/* Low level disk I/O */
	/* other */
#include "bsp_usart.h"
#include "bsp_led.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */
#define DEV_FLASH	3	/* Map FLASH(W28Q64) to physical drive 3 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
//	int result;

	switch (pdrv) {
	case DEV_RAM :
//		result = RAM_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
//		result = MMC_disk_status();

		// translate the reslut code here

		return stat;

	case DEV_USB :
//		result = USB_disk_status();

		// translate the reslut code here

		return stat;
	case DEV_FLASH :	
		if(sFLASH_ID == SPI_FLASH_ReadID())	/* SPI Flash状态检测：读取SPI Flash 设备ID */
		{	
#if DEBUG
			printf("\r\n JEDECID is 0x%X,Manufacturer Device ID is 0x%X\r\n", sFLASH_ID, SPI_FLASH_ReleaseReadID());
#endif
			stat &= ~STA_NOINIT;	/* 设备ID读取结果正确 */
		}
		else
		{
#if DEBUG
			printf("\r\n READ DEVICE ID FAIL\r\n");
#endif
			stat |= STA_NOINIT;		/* 设备ID读取结果错误 */
		}
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
//	int result;

	switch (pdrv) {
	case DEV_RAM :
//		result = RAM_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_MMC :
//		result = MMC_disk_initialize();

		// translate the reslut code here

		return stat;

	case DEV_USB :
//		result = USB_disk_initialize();

		// translate the reslut code here

		return stat;
	case DEV_FLASH :
        SPI_FLASH_Init();
		delay_ms(10);
        SPI_Flash_WAKEUP();
        stat = disk_status(DEV_FLASH);
		return stat;	
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_OK;
//	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

//		result = RAM_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

//		result = MMC_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here

//		result = USB_disk_read(buff, sector, count);

		// translate the reslut code here

		return res;
	case DEV_FLASH :
        /* 扇区偏移2MB，外部Flash文件系统空间放在SPI Flash后面6MB空间 */
        sector+=512;
		SPI_FLASH_BufferRead(buff, sector<<12, count<<12);
		res = RES_OK;
		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res = RES_OK;
//	int result;

	switch (pdrv) {
	case DEV_RAM :
		// translate the arguments here

//		result = RAM_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_MMC :
		// translate the arguments here

//		result = MMC_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;

	case DEV_USB :
		// translate the arguments here

//		result = USB_disk_write(buff, sector, count);

		// translate the reslut code here

		return res;
	case DEV_FLASH :
        /* 扇区偏移2MB，外部Flash文件系统空间放在SPI Flash后面6MB空间 */
        sector+=512;
		SPI_FLASH_Sector_BlockErase(W25Q64_SectorErase4KB, sector<<12);
		SPI_FLASH_BufferWrite((uint8_t*)buff, sector<<12, count<<12);
		res = RES_OK;
		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_OK;
//	int result;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	case DEV_FLASH :
        switch (cmd) {
        /* 扇区数量：1536*4096/1024/1024=6(MB) */
        case GET_SECTOR_COUNT:
            *(DWORD*)buff = 1536;
            break;
        case GET_SECTOR_SIZE :
            *(WORD*)buff = 4096;
            break;
        case GET_BLOCK_SIZE :
            *(DWORD*)buff = 1;
            break;
        }
        res = RES_OK;
		return res;
	}

	return RES_PARERR;
}

/* This function is not needed when FF_FS_READONLY == 1 or FF_FS_NORTC == 1
DWORD get_fattime (void)
{
    time_t t;
    struct tm *stm;


    t = time(0);
    stm = localtime(&t);

    return (DWORD)(stm->tm_year - 80) << 25 |
           (DWORD)(stm->tm_mon + 1) << 21 |
           (DWORD)stm->tm_mday << 16 |
           (DWORD)stm->tm_hour << 11 |
           (DWORD)stm->tm_min << 5 |
           (DWORD)stm->tm_sec >> 1;
}
*/
