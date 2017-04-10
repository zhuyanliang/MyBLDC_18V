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

	if(ADC_Average_Original(3U,Adc_Channel_Voltage) < g_voltLow)
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

	for(i=0;i<4U;i++)
	{
		g_motorCurrent = ADC_Convert_Original(Adc_Channel_Current);
		if(g_motorCurrent > g_curShort)
		{
			g_sysProtect.curshort = 0b1;
		}
		
		sum += g_motorCurrent;
	}
	g_motorCurrent = sum/4U;
	
	if(g_motorCurrent > g_curOvLoad)
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
	static uint8_t cnt = 0;
	
	if(ADC_Average_Original(3U,Adc_Channel_MOSTemp) < g_ovTemp)
	{
		if(cnt++>3)
			g_sysProtect.mos_ovTemp = 0b1;
	}
	else
	{
		cnt = 0;
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

void Task_Motor_SpeedControl(void)
{
	if(!g_btnPress)
	{
		g_speedPWM = SPEED_MIN;
		return;
	}
	if(g_speedPWM < SPEED_Expected)
	{
		g_speedPWM += SPEED_Up_Rate;
	}
	if(g_speedPWM >= SPEED_MAX)
	{
		g_speedPWM = SPEED_MAX - 1;
	}
	
	PWM_Set_Duty(g_speedPWM);
}

/*
 * execution cycle is 10Ms
 *
 */


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

/*
 * execution cycle is 10Ms
 *
 */
void Task_Calc_Speed(void)
{
	static uint8_t cnt = 0;

	if(MOTOR_STOP == g_motorState)
		return;
	
	if(cnt++ > 20)
	{
		cnt = 0;
		g_speed = 60000U/g_dltSpeedTick*10;
	}

	if(g_speed > 5000U)
	{
		Led_Set(25,3,100);
	}
}


