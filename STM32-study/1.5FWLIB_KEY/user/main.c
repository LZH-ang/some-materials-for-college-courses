#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#include "bsp_key.h"

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
	KEY_Init();
	while(1)
	{
		if(KEY_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
			LEDG_TOGGLE;
		if(KEY_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON)
			LEDB_TOGGLE;
		
	}
}
