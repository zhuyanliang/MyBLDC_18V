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

uint16_t Calc_AverageCalculate(uint16_t *TableEntry,uint8_t len)
{
	uint8_t i;
	uint32_t temp = 0;

	for (i=0; i<len; i++)
	{
		temp += *(TableEntry+i);
	}

	if(2 == len)
		return ((uint16_t)(temp>>1));
	else if(4 == len)
		return ((uint16_t)(temp>>2));
	else if(8 == len)
		return ((uint16_t)(temp>>3));
	else if(16 == len)
		return ((uint16_t)(temp>>4));
	else 
		return (uint16_t)(temp/len);
}

uint32_t Calc_AverageCalculate_32Bit(uint32_t *TableEntry,uint8_t len)
{
	uint8_t i;
	uint32_t temp = 0;

	for (i=0; i<len; i++)
	{
		temp += *(TableEntry+i);
	}

	if(2 == len)
		return ((uint16_t)(temp>>1));
	else if(4 == len)
		return ((uint16_t)(temp>>2));
	else if(8 == len)
		return ((uint16_t)(temp>>3));
	else if(16 == len)
		return ((uint16_t)(temp>>4));
	else 
		return (uint16_t)(temp/len);
}


