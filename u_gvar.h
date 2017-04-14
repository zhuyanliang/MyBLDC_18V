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
	unsigned lowVolt	:1; 	/* voltage low */ 
	unsigned ovCur		:1;		/* overcurrent */
	unsigned comm 		:1;
	unsigned mos_ovTemp :1;
	unsigned ovload		:1;		/* overload*/
	unsigned curshort	:1;
	unsigned hallerr	:1;
	unsigned 			:1;
	
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
	MOTOR_NULL = 0,
	MOTOR_STOP 		= 1,
	MOTOR_STARTUP 	= 2,
	MOTOR_RUNNING	= 3,
	MOTOR_BRAKE		= 4,
	MOTOR_BLOCK		= 5,
}E_MOTOR_STATUS;

typedef struct
{
	uint8_t interval;  		/* flash interval uint:10Ms */
	uint8_t flash_times;  
	uint16_t const_On_Time; 	/* led on duration time  uint:10Ms*/
}S_LED_SET;


extern uint32_t 		g_sysTick;
extern bool 			g_elapse2Ms;
extern uint8_t			g_elapse20MsCnt;

extern S_SYS_PROTECT	g_sysProtect;
extern S_LED_SET		g_ledSet;
extern E_MOTOR_STATUS	g_motorState;
extern uint8_t			g_hallState;
extern bool 			g_btnPress;
extern uint16_t 		g_motorCurrent;
extern bool 			g_motorDirection;
extern bool 			g_motorStopFlag;

extern uint16_t 		g_voltLow;
extern uint16_t			g_curShort;
extern uint16_t			g_curOvLoad;
extern uint16_t			g_ovTemp;

extern volatile int16_t		g_speedPWM;
extern volatile uint16_t	g_realSpeed;
extern uint16_t				g_setSpeed;

extern volatile uint32_t	g_dltSpeedTick;
extern uint32_t				g_justForTest;

void Global_Var_Init(void);

#endif