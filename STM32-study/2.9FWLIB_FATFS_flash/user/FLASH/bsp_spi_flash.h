#ifndef __BSP_SPI_FLASH_H
#define __BSP_SPI_FLASH_H

#include "stm32f10x.h"
#include <stdio.h>

//#define  sFLASH_ID				0xEF3015	//W25X16
//#define  sFLASH_ID              0xEF4015	//W25Q16
//#define  sFLASH_ID              0XEF4018	//W25Q128
#define  sFLASH_ID              0XEF4017    //W25Q64

#define SPI_FLASH_PageSize				256
#define SPI_FLASH_PerWritePageSize		256

/***********************CMD_W25Q64JV*********************/
#define W25Q64_WriteEnable				0x06
#define W25Q64_WriteDisable				0x04
#define W25Q64_Powerdown				0xB9
#define W25Q64_ReleasePowerdownorID		0xAB	/*Dummy Dummy Dummy (ID7-ID0)*/
#define W25Q64_ManufacturerandDeviceID	0x90	/*Dummy Dummy 00h (MF7-MF0) (ID7-ID0)*/
#define W25Q64_JEDECID					0x9F	/*(MF7-MF0) (ID15-ID8) (ID7-ID0)*/
#define W25Q64_ReadData					0x03	/*(A23-A16) (A15-A8) (A7-A0) (D7-D0)*/
#define W25Q64_PageProgram				0x02	/*(A23-A16) (A15-A8) (A7-A0) (D7-D0)...*/
#define W25Q64_SectorErase4KB			0x20	/*(A23-A16) (A15-A8) (A7-A0)*/
#define W25Q64_BlockErase32KB			0x52	/*(A23-A16) (A15-A8) (A7-A0)*/
#define W25Q64_BlockErase64KB			0xD8	/*(A23-A16) (A15-A8) (A7-A0)*/
#define W25Q64_ChipErase				0xC7
#define W25Q64_ReadStatusRegister1		0x05	/*(S7-S0)*/
#define W25Q64_WriteStatusRegister1		0x01	/*(S7-S0)*/
#define W25Q64_GlobalBlockLock			0x7E
#define W25Q64_GlobalBlockUnlock		0x98
#define W25Q64_EnableReset				0x66
#define W25Q64_ResetDevice				0x99

/* WIP(busy)标志，FLASH内部正在写入 */
#define WIP_Flag			0x01
#define Dummy_Byte			0xFF
/*******************************SPI_IO*****************************/
#define	FLASH_SPIx						SPI1
#define	FLASH_SPI_APBxClock_FUN			RCC_APB2PeriphClockCmd
#define	FLASH_SPI_CLK					RCC_APB2Periph_SPI1
//CS(NSS)引脚 片选选普通GPIO即可
#define	FLASH_SPI_CS_APBxClock_FUN		RCC_APB2PeriphClockCmd
#define	FLASH_SPI_CS_CLK				RCC_APB2Periph_GPIOC
#define	FLASH_SPI_CS_PORT				GPIOC
#define	FLASH_SPI_CS_PIN				GPIO_Pin_0
//SCK引脚
#define	FLASH_SPI_SCK_APBxClock_FUN		RCC_APB2PeriphClockCmd
#define	FLASH_SPI_SCK_CLK				RCC_APB2Periph_GPIOA
#define	FLASH_SPI_SCK_PORT				GPIOA
#define	FLASH_SPI_SCK_PIN				GPIO_Pin_5
//MISO引脚
#define	FLASH_SPI_MISO_APBxClock_FUN	RCC_APB2PeriphClockCmd
#define	FLASH_SPI_MISO_CLK				RCC_APB2Periph_GPIOA
#define	FLASH_SPI_MISO_PORT				GPIOA
#define	FLASH_SPI_MISO_PIN				GPIO_Pin_6
//MOSI引脚
#define	FLASH_SPI_MOSI_APBxClock_FUN	RCC_APB2PeriphClockCmd
#define	FLASH_SPI_MOSI_CLK				RCC_APB2Periph_GPIOA
#define	FLASH_SPI_MOSI_PORT				GPIOA
#define	FLASH_SPI_MOSI_PIN				GPIO_Pin_7

#define	SPI_FLASH_CS_LOW()				GPIO_ResetBits( FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN )
#define	SPI_FLASH_CS_HIGH()				GPIO_SetBits( FLASH_SPI_CS_PORT, FLASH_SPI_CS_PIN )
/********************************END******************************/

/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT		((uint32_t)0x10000)
/*信息输出*/
#define FLASH_DEBUG_ON			0

#define FLASH_INFO(fmt,arg...)		printf("<<-FLASH-INFO->> "fmt"\n",##arg)
#define FLASH_ERROR(fmt,arg...)		printf("<<-FLASH-ERROR->> "fmt"\n",##arg)
#define FLASH_DEBUG(fmt,arg...)		do{\
									if(FLASH_DEBUG_ON)\
									printf("<<-FLASH-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
									}while(0)

void SPI_FLASH_Init(void);
uint8_t SPI_FLASH_SendByte(uint8_t byte);
uint8_t SPI_FLASH_ReadByte(void);
uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WriteDisable(void);
void SPI_FLASH_WaitForWriteEnd(void);
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr);
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void SPI_FLASH_Sector_BlockErase(uint8_t Erasemode, uint32_t EraseAddr);
void SPI_FLASH_ChipErase(void);
void SPI_Flash_PowerDown(void);
void SPI_Flash_WAKEUP(void);
uint32_t SPI_FLASH_ReadID(void);
uint8_t SPI_FLASH_ReleaseReadID(void);
void SPI_FLASH_Reset(void);

#endif /*__BSP_SPI_FLASH_H*/
