#include "u_common_func.h"

void Delay_Ms(uint32_t val)
{
	uint32_t waitTime = g_sysTick + val;
	while(g_sysTick < waitTime);
}

void Delay_1Us(void)
{
	NOP();
}

