#include "u_include.h"

/*
P1.0(D1) ---->AH   PWM OUT 
P1.1(C1) ---->BH   PWM OUT	
P1.2(B1) ---->CH   PWM OUT	
P1.4	 ---->AL   I/O-O
P1.5	 ---->BL   I/O-O
P1.6	 ---->CL   I/O-O

HALL   PHASE_REV    PHASE_FWD
  1 	A-->B		 B-->A
  5 	A-->C		 C-->A		
  4 	B-->C		 C-->B
  6 	B-->A		 A-->B
  2 	C-->A		 A-->C
  3 	C-->B		 B-->C
*/

const uint8_t PWM_OUT_EN_FWD[8]   		= {0xff,0xbf,0x7f,0xbf,0xdf,0xdf,0x7f,0xff};
const uint8_t BRIDGE_LOW_FWD[8]   		= {0x00,0x10,0x40,0x40,0x20,0x10,0x20,0x00};
const uint8_t BRIDGE_LOW_KEEP_FWD[8]  	= {0x88,0x98,0xc8,0xc8,0xa8,0x98,0xa8,0x88};

const uint8_t PWM_OUT_EN_REV[8]   		= {0xff,0x7f,0xdf,0xdf,0xbf,0x7f,0xbf,0xff};
const uint8_t BRIDGE_LOW_REV[8]   		= {0x00,0x20,0x10,0x20,0x40,0x40,0x10,0x00};
const uint8_t BRIDGE_LOW_KEEP_REV[8]  	= {0x88,0xa8,0x98,0xa8,0xc8,0xc8,0x98,0x88};

/*
 * Èý¸ö»ô¶ûÐÅºÅ: U V W 
 * U - 0x04 	V - 0x02	W - 0x01 
 */
uint8_t Get_Hall_State(void)
{
	uint8_t state = 0;
	if(HALL_U) state |= 0x04;
	if(HALL_V) state |= 0x02;
	if(HALL_W) state |= 0x01;

	return state;	
}

/*
 * isFWD - true  :Foreward direction expected 
 * isFWD - false :Reversal direction expected
*/
uint8_t Next_Hall_State_Expected(bool isFwd,uint8_t state)
{
	if(isFwd)
	{
		if(1U == state)
			return 5U;
		else if(2U == state)
			return 3U;
		else if(3U == state)
			return 1U;
		else if(4U == state)
			return 6U;
		else if(5U == state)
			return 4U;
		else if(6U == state)
			return 2U;
		else
			return 0;
	}
	else
	{
		if(1U == state)
			return 3U;
		else if(2U == state)
			return 6U;
		else if(3U == state)
			return 2U;
		else if(4U == state)
			return 5U;
		else if(5U == state)
			return 1U;
		else if(6U == state)
			return 4U;
		else
			return 0;
	}
}


void Set_PWM_Duty(uint16_t val)
{
	if(val > SPEED_MAX)
	{
		val = SPEED_MAX;
	}
	else if(val < SPEED_MIN)
	{
		val = SPEED_MIN;
	}
	
	TRDGRB1 = val;
    TRDGRC1 = val;
    TRDGRD1 = val;
}

void Commutate_Phase(bool isFwd,uint8_t state)
{
	if(isFwd)
	{
		P1 		&= BRIDGE_LOW_KEEP_FWD[state];
		TRDOER1	= PWM_OUT_EN_FWD[state];   /*enable relative high bridge PWM pin*/	
		P1 		|= BRIDGE_LOW_FWD[state];  /*set high to enabled low bridge pin, */ 
	}
	else
	{
		P1 		&= BRIDGE_LOW_KEEP_REV[state];
		TRDOER1 = BRIDGE_LOW_REV[state];   /*enable relative high bridge PWM pin*/	
		P1 		|= PWM_OUT_EN_REV[state];  /*set high to enabled low bridge pin, */ 
	}
	
}

void Motor_Stop(void)
{	
	TRDOER1 |= 0xff;       /*disable all high bridge PWM pin,*/
	P1 &= 0x88;          /*set low to all high bridge PWM  pin and all low bridge disabled pin,*/
}

void Motor_Brake(void)
{
	TRDOER1 |= 0xff;   //disable all high bridge PWM pin,
	P1 &= 0xF8;                 //set low to all high bridge pin,
	Delay_Ms(1);
	P1 |= 0x70;                 //set all low bridge pin high to brake,  
}




