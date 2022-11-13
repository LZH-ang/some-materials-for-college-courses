#ifndef __bsp_dma_H
#define __bsp_dma_H

#include "stm32f10x.h"

// ��ʹ�ô洢�����洢��ģʽʱ��ͨ���������ѡ��û��Ӳ�ԵĹ涨
#define DMA_CHANNEL     DMA1_Channel2	//DMAy_Channelx
#define DMA_CLOCK       RCC_AHBPeriph_DMA1

// ������ɱ�־
#define DMA_FLAG_TC     DMA1_FLAG_TC2

// Ҫ���͵����ݴ�С
#define BUFFER_SIZE     32

/* ����aSRC_Const_Buffer������ΪDMA��������Դ
 * const�ؼ��ֽ�aSRC_Const_Buffer�����������Ϊ��������
 * ��ʾ���ݴ洢���ڲ���FLASH��
 */
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
/* ����DMA����Ŀ��洢��
 * �洢���ڲ���SRAM��																		
 */
extern uint32_t aDST_Buffer[BUFFER_SIZE];

void DMA_Config(void);
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);

#endif /*__bsp_dma_H*/
