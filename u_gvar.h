#ifndef GVAR_H
#define GVAR_H

#include "r_cg_macrodriver.h"

typedef enum
{
	false = 0,
	true = 1,
}bool;

typedef struct
{
	unsigned vlow	:1; 	/* voltage low */ 
	unsigned cov	:1;		/* overcurrent */
	unsigned com 	:1;
	unsigned mos_ot :1;
	unsigned		:4;
}S_SYS_PROTECT;

typedef enum
{
	PROTECT_NULL = 0,
	PROTECT_COV,		/* current over normal value*/
	PROTECT_VLOW,		/* voltage low*/
	PROTECT_COM,		/* communication error*/
	PROTECT_MOS_OT,		/* MOSFET temperature over normal value*/
}E_PROTECT_CASE;

typedef enum
{
	MOTOR_STOP 		= 1,
	MOTOR_STARTUP 	= 2,
	MOTOR_FWDRUN	= 3,
	MOTOR_REVRUN	= 4,
	MOTOR_BRAKE		= 5,
	MOTOR_BLOCK		= 6,
}E_MOTOR_STATUS;

typedef struct
{
	uint8_t interval;  		/* flash interval uint:10Ms */
	uint8_t flash_times;  
	uint8_t const_On_Time; 	/* led on duration time  uint:10Ms*/
}S_LED_SET;

extern uint32_t 		g_sysTick;
extern bool 			g_elapse2Ms;
extern S_SYS_PROTECT	g_sysProtect;
extern S_LED_SET		g_ledSet;
extern E_MOTOR_STATUS	g_MotorState;

extern uint32_t		g_justForTest;

#endif