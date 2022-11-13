#include "bsp_exti.h"

volatile uint8_t EXTI_flag = 0;

static void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(EXTI_CLK, ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);						//优先级分组设置
	/***************内核中断配置******************/
	NVIC_InitStructure.NVIC_IRQChannel = KEY1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void KEY_EXTI_Init(void)
{
	GPIO_InitTypeDef GPIO_EXTI;
	EXTI_InitTypeDef EXTI_KEY;
	
	NVIC_Config();
	
	RCC_APB2PeriphClockCmd(KEY1_CLK, ENABLE);
	GPIO_EXTI.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_EXTI.GPIO_Pin = KEY1_PIN;
	GPIO_Init(KEY1_PORT, &GPIO_EXTI);
	
	GPIO_EXTILineConfig(KEY1_PortSource, KEY1_PinSource);			//中断线配置
	/***************中断模式配置******************/
	EXTI_KEY.EXTI_Line = KEY1_LINE;
	EXTI_KEY.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_KEY.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_KEY.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_KEY);
}

//用指针？
uint8_t Readflag(void)
{
	return EXTI_flag;
}

void Setflag(uint8_t flag)
{
	EXTI_flag = flag;
}
