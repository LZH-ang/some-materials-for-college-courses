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

/* 基本混色，后面高级用法使用PWM可混出全彩颜色,且效果更好 */

//红
#define LED_RED  \
					LED_R_ON;\
					LED_G_OFF;\
					LED_B_OFF
//绿
#define LED_GREEN		\
					LED_R_OFF;\
					LED_G_ON;\
					LED_B_OFF
//蓝
#define LED_BLUE	\
					LED_R_OFF;\
					LED_G_OFF;\
					LED_B_ON			
//黄(红+绿)					
#define LED_YELLOW	\
					LED_R_ON;\
					LED_G_ON;\
					LED_B_OFF
//紫(红+蓝)
#define LED_PURPLE	\
					LED_R_ON;\
					LED_G_OFF;\
					LED_B_ON
//青(绿+蓝)
#define LED_CYAN \
					LED_R_OFF;\
					LED_G_ON;\
					LED_B_ON				
//白(红+绿+蓝)
#define LED_WHITE	\
					LED_R_ON;\
					LED_G_ON;\
					LED_B_ON				
//黑(全部关闭)
#define LED_RGBOFF	\
					LED_R_OFF;\
					LED_G_OFF;\
					LED_B_OFF

#endif /*__bsp_led_H*/
