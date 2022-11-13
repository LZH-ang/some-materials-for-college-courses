#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"

/*stdint.h*/
//    /* exact-width signed integer types */
//typedef   signed          char int8_t;
//typedef   signed short     int int16_t;
//typedef   signed           int int32_t;
//typedef   signed       __INT64 int64_t;

//    /* exact-width unsigned integer types */
//typedef unsigned          char uint8_t;
//typedef unsigned short     int uint16_t;
//typedef unsigned           int uint32_t;
//typedef unsigned       __INT64 uint64_t;

int main(void)
{
	// 来到这里的时候，系统的时钟已经被配置成72M。
	LED_Init();
	LED_R_OFF;
//	LED_R_ON;
	LED_G_OFF;
//	LED_G_ON;
	LED_B_OFF;
//	LED_B_ON;
	while(1)
	{
		LED_RED;delay_ms(500);
		LED_YELLOW;delay_ms(500);
		LED_BLUE;delay_ms(500);
		LED_GREEN;delay_ms(500);
		LED_CYAN;delay_ms(500);
		LED_PURPLE;delay_ms(500);
	}
}
