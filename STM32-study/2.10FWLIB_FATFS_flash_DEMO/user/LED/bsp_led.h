#ifndef __bsp_led_H
#define __bsp_led_H

#include "stm32f10x.h"

#define LED_R GPIO_Pin_5
#define LED_G GPIO_Pin_0
#define LED_B GPIO_Pin_1

#define LED_R_ON  GPIO_WriteBit(GPIOB,LED_R,Bit_RESET)
#define LED_R_OFF GPIO_WriteBit(GPIOB,LED_R,Bit_SET)
#define LED_G_ON  GPIO_WriteBit(GPIOB,LED_G,Bit_RESET)
#define LED_G_OFF GPIO_WriteBit(GPIOB,LED_G,Bit_SET)
#define LED_B_ON  GPIO_WriteBit(GPIOB,LED_B,Bit_RESET)
#define LED_B_OFF GPIO_WriteBit(GPIOB,LED_B,Bit_SET)

void LED_Init(void);
void delay_ms(uint16_t time);

/* ������ɫ������߼��÷�ʹ��PWM�ɻ��ȫ����ɫ,��Ч������ */

//��
#define LED_RED  \
					LED_R_ON;\
					LED_G_OFF;\
					LED_B_OFF
//��
#define LED_GREEN		\
					LED_R_OFF;\
					LED_G_ON;\
					LED_B_OFF
//��
#define LED_BLUE	\
					LED_R_OFF;\
					LED_G_OFF;\
					LED_B_ON			
//��(��+��)					
#define LED_YELLOW	\
					LED_R_ON;\
					LED_G_ON;\
					LED_B_OFF
//��(��+��)
#define LED_PURPLE	\
					LED_R_ON;\
					LED_G_OFF;\
					LED_B_ON
//��(��+��)
#define LED_CYAN \
					LED_R_OFF;\
					LED_G_ON;\
					LED_B_ON				
//��(��+��+��)
#define LED_WHITE	\
					LED_R_ON;\
					LED_G_ON;\
					LED_B_ON				
//��(ȫ���ر�)
#define LED_RGBOFF	\
					LED_R_OFF;\
					LED_G_OFF;\
					LED_B_OFF

#endif /*__bsp_led_H*/
