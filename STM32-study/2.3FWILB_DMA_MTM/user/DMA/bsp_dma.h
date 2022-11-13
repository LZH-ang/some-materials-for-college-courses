#ifndef __bsp_dma_H
#define __bsp_dma_H

#include "stm32f10x.h"

// 当使用存储器到存储器模式时候，通道可以随便选，没有硬性的规定
#define DMA_CHANNEL     DMA1_Channel2	//DMAy_Channelx
#define DMA_CLOCK       RCC_AHBPeriph_DMA1

// 传输完成标志
#define DMA_FLAG_TC     DMA1_FLAG_TC2

// 要发送的数据大小
#define BUFFER_SIZE     32

/* 定义aSRC_Const_Buffer数组作为DMA传输数据源
 * const关键字将aSRC_Const_Buffer数组变量定义为常量类型
 * 表示数据存储在内部的FLASH中
 */
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
/* 定义DMA传输目标存储器
 * 存储在内部的SRAM中																		
 */
extern uint32_t aDST_Buffer[BUFFER_SIZE];

void DMA_Config(void);
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);

#endif /*__bsp_dma_H*/
