#include "u_include.h"

void Task_Voltage_Check(void)
{
	static uint8_t cnt = 0;

	if(ADC_Average_Original(3U,Voltage_Adc_Channel) < Voltage_Low_Value_AD)
	{
		if(cnt++ > 3)
			g_sysProtect.cov = 0b1;
	}
	else
	{
		cnt = 0;
		g_sysProtect.cov = 0b0;
	}
}

void Task_Current_Check(void)
{
	
}

void Task_Temperature_Check(void)
{

}

void Task_Motor(void)
{
}

void Task_LED(void)
{
	Manege_Led();
}

void Task_Button(void)
{
	static uint8_t cnt = 0;
	if(BUTTON)
	{	
		if(cnt++ > 1)
		{
			g_MotorState = MOTOR_STARTUP;
		}
	}
	else
	{
		cnt = 0;
		g_MotorState = MOTOR_STOP;
	}
}

void Task_Delay(void)
{}
void Task_Process_ProtectInfo(void)
{}



