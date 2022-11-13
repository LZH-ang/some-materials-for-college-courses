#ifndef __bsp_dma_H
#define __bsp_dma_H

#include "stm32f10x.h"

// ��ʹ�ô洢�����洢��ģʽʱ��ͨ���������ѡ��û��Ӳ�ԵĹ涨
#define DMA_MtoM_CHANNEL    DMA1_Channel2	//DMAy_Channelx
#define DMA_CLOCK       		RCC_AHBPeriph_DMA1
// ���ڶ�Ӧ��DMA����ͨ��
#define DMA_TX_CHANNEL      DMA1_Channel4

// ������ɱ�־
#define DMA_FLAG_TC     		DMA1_FLAG_TC2
#define DMAtoUSART_FLAG_TC	DMA1_FLAG_TC4

// ����Ĵ�����ַ
#define USART_DR_ADDRESS   (USART1_BASE+0x04)

// Ҫ���͵����ݴ�С
#define BUFFER_SIZE     		32
// һ�η��͵�������
#define SENDBUFF_SIZE      5000

/* ����aSRC_Const_Buffer������ΪDMA��������Դ
 * const�ؼ��ֽ�aSRC_Const_Buffer�����������Ϊ��������
 * ��ʾ���ݴ洢���ڲ���FLASH��
 */
extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
/* ����DMA����Ŀ��洢��
 * �洢���ڲ���SRAM��																		
 */
extern uint32_t aDST_Buffer[BUFFER_SIZE];
extern uint8_t SendBuff[SENDBUFF_SIZE];

void DMA_Config(void);
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);

#endif /*__bsp_dma_H*/
