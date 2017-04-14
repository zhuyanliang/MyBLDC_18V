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
* File Name    : r_cg_adc_user.c
* Version      : CodeGenerator for RL78/G14 V2.04.05.01 [11 Nov 2016]
* Device(s)    : R5F104BA
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for ADC module.
* Creation Date: 2017/4/14
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_adc.h"
/* Start user code for include. Do not edit comment generated here */
#include "u_include.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/* Start user code for adding. Do not edit comment generated here */

/*
 * return ADC original value
 */
uint16_t ADC_Convert_Original(uint8_t channel)
{
	uint16_t ret = 0;
	
	ADS = channel;
	R_ADC_Set_OperationOn();
	Delay_1Us();
	R_ADC_Start();
	while(!ADIF);	// 26us
	ADIF = 0;
	ret = (uint16_t)(ADCR >> 6U);
	R_ADC_Stop();
	R_ADC_Set_OperationOff();

	return ret;
}

/* 
 * return voltage value
 *
 */
float ADC_Convert_Volt(uint8_t channel)
{
	uint16_t orival = ADC_Convert_Original(channel);
	
	float ret = (float)orival/1024U*5.0F;

	return ret;
}

/*
 * return num value average
 * Tips:num < 64
 */
uint16_t ADC_Average_Original(uint8_t num,uint8_t channel)
{
	uint8_t i;
	uint16_t sum = 0;
	for(i=0;i<num;i++)
	{
		sum += ADC_Convert_Original(channel);
		NOP();NOP();NOP();
	}

	return (uint16_t)sum/num;
}


/* End user code. Do not edit comment generated here */
