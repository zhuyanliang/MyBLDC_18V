
/*
 * Global variables in this file
 *
 */

#include "u_include.h"

/* system tick*/
uint32_t 		g_sysTick;	

/* systrm 2ms flag*/
bool 	 		g_elapse2Ms;

/* protect case*/
S_SYS_PROTECT	g_sysProtect;

/*led's parameters*/
S_LED_SET		g_ledSet;


E_MOTOR_STATUS	g_motorState;
uint8_t			g_hallState;


uint16_t 		g_voltLow;
uint16_t		g_curShort;
uint16_t		g_curOvLoad;
uint16_t		g_ovTemp;


/*  button was pressed
 * false  -- button not pressed
 * true   -- button was pressed
 */
bool 			g_btnPress;	

/*motor's current*/
uint16_t 		g_motorCurrent;

/* motor rotation direction
 * false -- reverse
 * true  -- forward
 */
bool 			g_motorDirection;
uint16_t		g_speedPWM;
bool 			g_motorStopFlag;
volatile uint16_t		g_dltSpeedTick;
uint16_t		g_speed;


/*just for test system tick*/
uint32_t	g_justForTest; 


void Global_Var_Init(void)
{
	g_voltLow 	= Voltage_Low_Value_AD;
	g_curShort 	= Current_Short_AD;
	g_curOvLoad = Current_Overload_AD;
	g_ovTemp	= Temp_Over_AD;

	g_speedPWM = SPEED_MIN;
	g_motorStopFlag = true;

	g_btnPress = false;
	g_motorDirection = true;
	g_elapse2Ms = true;

	g_dltSpeedTick = g_sysTick;
}

