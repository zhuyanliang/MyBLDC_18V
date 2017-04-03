
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


/*  button was pressed
 * false  -- button not pressed
 * true   -- button was pressed
 */
bool 			g_btnPress = false;	

/*motor's current*/
uint16_t 		g_motorCurrent;

/* motor rotation direction
 * false -- reverse
 * true  -- forward
 */
bool 			g_motorDirection = true;

/*just for test system tick*/
uint32_t	g_justForTest; 

