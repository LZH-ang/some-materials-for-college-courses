#ifndef __BSP_CLKCONFIG_H
#define __BSP_CLKCONFIG_H

#include "stm32f10x.h"

void HSE_SetSysClock(uint32_t pllmul);
void HSI_SetSysClock(uint32_t pllmul);
void MCO_Init(void);

#endif
