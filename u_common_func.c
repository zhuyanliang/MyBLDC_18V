#include "u_common_func.h"

//������ʱ
void Delay_Ms(uint32_t val)
{
	uint32_t waitTime = g_sysTick + val;
	while(g_sysTick < waitTime);
}

