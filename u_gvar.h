#ifndef GVAR_H
#define GVAR_H

#include "r_cg_macrodriver.h"

typedef enum
{
	false = 0,
	true = 1,
}bool;

extern uint32_t 	g_sysTick;
extern bool 		g_elapse2Ms;

#endif