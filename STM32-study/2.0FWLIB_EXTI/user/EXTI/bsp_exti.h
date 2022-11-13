#ifndef __bsp_exti_H
#define __bsp_exti_H

#include "stm32f10x.h"


#define KEY1_PORT         GPIOA
#define KEY1_CLK          RCC_APB2Periph_GPIOA
#define KEY1_PIN          GPIO_Pin_0
#define KEY1_LINE					EXTI_Line0						//�ж�������
#define KEY1_IRQChannel		EXTI0_IRQn;						//�ж�ͨ������
#define EXTI_CLK					RCC_APB2Periph_AFIO
#define KEY1_PortSource		GPIO_PortSourceGPIOA
#define KEY1_PinSource		GPIO_PinSource0
#define KEY1_IRQHandler		EXTI0_IRQHandler			//�жϺ���

void KEY_EXTI_Init(void);
uint8_t Readflag(void);
void Setflag(uint8_t flag);

#endif /*__bsp_exti_H*/
