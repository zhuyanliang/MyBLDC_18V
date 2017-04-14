#include "u_include.h"

/*
 *  interval  - on and off interval time uint:100Ms
 *  flashtimes    
 *  constontimes  uint:10Ms  
 */
void Led_Set(uint8_t interval,uint8_t flashtimes,uint16_t constontimes)
{
	g_ledSet.interval 		= interval;
	g_ledSet.flash_times 	= flashtimes;
	g_ledSet.const_On_Time 	= constontimes;
}

/* execution cycle - 10Ms*/
void Task_Manage_Led(void)
{
	static bool flashFlag = false; 
	static uint8_t elapse10Ms = 0;
	
	static uint8_t interval;
	static uint8_t flash_times;
	static uint16_t const_On_Time;

	if((g_ledSet.interval == 0) 
	&& (g_ledSet.flash_times == 0) 
	&& (g_ledSet.const_On_Time == 0U))
	{
		Led_Off();
		return;
	}

	if((g_ledSet.interval == 0xFF) 
	&& (g_ledSet.flash_times == 0xFF) 
	&& (g_ledSet.const_On_Time == 0xFFFF))
	{
		Led_On();
		return;
	}
	
	if(!flashFlag)
	{
		const_On_Time++;
		Led_On();
		if(const_On_Time == g_ledSet.const_On_Time)
		{
			const_On_Time = 0;
			flashFlag = true;
			interval = 0;
		}
	}
	else
	{
		interval++;
		if(interval > (g_ledSet.interval<<1))
		{
			interval = 0;
			flash_times++;
		}
		else if(interval > g_ledSet.interval)
		{
			Led_On();
		}
		else
		{
			Led_Off();
		}

		if(flash_times == g_ledSet.flash_times)
		{
			flashFlag = false;
			flash_times = 0;
			const_On_Time = 0;
		}
	}
}



