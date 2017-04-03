#include "u_include.h"

/*
 * execution cycle is 10Ms
 *
 * Check Battery Voltage
 *
 */
void Task_Voltage_Check(void)
{
	static uint8_t cnt = 0;

	if(ADC_Average_Original(3U,Adc_Channel_Voltage) < Voltage_Low_Value_AD)
	{
		if(cnt++ > 3)
			g_sysProtect.lowVolt = 0b1;
	}
	else
	{
		cnt = 0;
		g_sysProtect.lowVolt = 0b0;
	}
}

void Task_Current_Check(void)
{
	uint8_t i;
	uint16_t sum = 0;

	for(i=0;i<8;i++)
	{
		g_motorCurrent = ADC_Convert_Original(Adc_Channel_Current);
		if(g_motorCurrent > Current_Short_AD)
		{
			g_sysProtect.curshort = 0b1;
		}
		
		sum += g_motorCurrent;
	}
	g_motorCurrent = sum/8U;
	
	if(g_motorCurrent > Current_Overload_AD)
	{
		g_sysProtect.ovload = 0b1;
	}
	else
	{
		g_sysProtect.ovload = 0b0;
	}
}

void Task_Temperature_Check(void)
{
	if(ADC_Average_Original(3U,Adc_Channel_MOSTemp) < Temp_Over_AD)
	{
		g_sysProtect.mos_ovTemp = 0b1;
	}
	else
	{
		g_sysProtect.mos_ovTemp = 0b0;
	}
}

void Task_Motor_Control(void)
{
	/* 1. manage motor speed*/
	/* 2. control the motor commutate*/
	Manage_Motor_State();
	Manage_Motor_Phase();
}

void Task_LED(void)
{
	Manege_Led();
}

/*
 * execution cycle is 10Ms
 *
 */
void Task_Btn_Scan(void)
{
	static uint8_t cnt = 0;
	if(BUTTON)
	{	
		if(cnt++ > 2)
		{
			cnt = 2;
			g_btnPress = true;
		}
	}
	else
	{
		cnt = 0;
		g_btnPress = false;
	}
}

void Task_Delay(void)
{
	
}

void Task_Manage_ProtectInfo(void)
{
	uint8_t protectInfo =  *(uint8_t*)&g_sysProtect;
	if((0 == protectInfo) && g_btnPress)
	{
		return;
	}
	else
	{
		if(g_sysProtect.hallerr)
		{
			Led_Set(30,7,200);
		}
		if(g_sysProtect.ovCur)
		{
			Led_Set(30,6,200);
		}
		if(g_sysProtect.ovload)
		{
			Led_Set(30,5,200);
		}
		if(g_sysProtect.lowVolt)
		{
			Led_Set(30,4,200);
		}
		Motor_Stop();
	}
}

