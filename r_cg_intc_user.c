/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_intc_user.c
* Version      : CodeGenerator for RL78/G14 V2.04.05.01 [11 Nov 2016]
* Device(s)    : R5F104BA
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for INTC module.
* Creation Date: 2017/5/22
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt INTP1 r_intc1_interrupt
#pragma interrupt INTP2 r_intc2_interrupt
#pragma interrupt INTP3 r_intc3_interrupt
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_intc.h"
/* Start user code for include. Do not edit comment generated here */
#include "u_include.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_intc1_interrupt
* Description  : This function is INTP1 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_intc1_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    /* for calculate motor speed r/min */
    /* timer intval is 1/3 uS */
 	
 	static uint8_t  index = 0x00;
#define _20Ms (_EA5F_TMRJ_TRJ0_VALUE+1)
	static uint16_t lastTick = 0;
	uint16_t current = 0;	
	
	current = TRJ0;
	if(current > lastTick)
	{
		g_dltSpeedTick = _20Ms + lastTick - current; 
		g_dltSpeedTick /= 3U;
		if(g_elapse20MsCnt > 1U)
		{
			g_dltSpeedTick += ((g_elapse20MsCnt-1)*20000U);
		}
	}
	else
	{
		g_dltSpeedTick = lastTick - current; 
		g_dltSpeedTick /= 3U;
		if(0 != g_elapse20MsCnt)
		{
			g_dltSpeedTick += g_elapse20MsCnt*20000U;
		}
	}
	
	g_elapse20MsCnt = 0;
	lastTick = TRJ0;
	
    g_motorStopFlag = false;
    Hall_Interupt_Process();
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_intc2_interrupt
* Description  : This function is INTP2 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_intc2_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    g_motorStopFlag = false;
    Hall_Interupt_Process();
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_intc3_interrupt
* Description  : This function is INTP3 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_intc3_interrupt(void)
{
    /* Start user code. Do not edit comment generated here */
    g_motorStopFlag = false;
    Hall_Interupt_Process();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
