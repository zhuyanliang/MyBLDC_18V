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

/**/
void Scan_Hall_State(void)
{
	g_hallState = Get_Hall_State();
}

/*
 * isFWD - true  :Foreward direction expected 
 * isFWD - false :Reversal direction expected
*/
uint8_t Next_Hall_State_Expected(bool isFwd,uint8_t state)
{
	if(!isFwd)
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
	else
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
}


void PWM_Set_Duty(uint16_t val)
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
		TRDOER1 = PWM_OUT_EN_REV[state];   /*enable relative high bridge PWM pin*/	
		P1 		|= BRIDGE_LOW_REV[state];  /*set high to enabled low bridge pin, */ 
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

void Get_Hall_Commutate_Phase(void)
{
	g_hallState = Get_Hall_State();

	Commutate_Phase(g_motorDirection,g_hallState);
}

void Manage_Motor_Phase(void)
{	
	static uint16_t cnt = SPEED_MIN;
	static bool 	firstStart = true;
	
	if(MOTOR_STARTUP == g_motorState)
	{
		if(firstStart)
		{
			firstStart = false;
			PWM_On();
			Get_Hall_Commutate_Phase();
			Hall_Int_On();
		}
		else
		{
			Get_Hall_Commutate_Phase();
		}
		return;
	}
	else if(MOTOR_RUNNING == g_motorState)
	{
		Get_Hall_Commutate_Phase();
		firstStart = true;
	}
	else if(MOTOR_BRAKE == g_motorState)
	{
		static uint8_t cnt;
		firstStart = true;
		if(cnt++ < 10)
		{
			Motor_Stop();
		}
		else if(cnt++ < 20)
		{
			Motor_Brake();
		}
		else
		{
			cnt = 0;
		}
	}
	else if(MOTOR_STOP == g_motorState)
	{
		firstStart = true;
		Motor_Stop();
	}
}

void Hall_Interupt_Process(void)
{
	static uint8_t lastHallState;
	static uint8_t expectHallState;
	static uint8_t hallErrorCnt;
	
	if(!g_btnPress)
		return;
		
	g_hallState = Get_Hall_State();
	if(g_hallState != lastHallState)
	{
		Manage_Motor_Phase();

		if( MOTOR_RUNNING == g_motorState)
		{
			if(expectHallState != g_hallState)
			{
				if(hallErrorCnt++ > 200)
				{
					g_sysProtect.hallerr = 0b1;
				}
			}
			else
			{
				hallErrorCnt = 0;
			}
			expectHallState = Next_Hall_State_Expected(g_motorDirection,g_hallState);
			lastHallState = g_hallState;
		}
	}
}

void Manage_Motor_State(void)
{	
	if(g_btnPress)
	{
		if(0 == *((uint8_t*)&g_sysProtect))
		{	
			if(g_speedPWM < (g_setSpeed - 200U))
			{
				g_motorState = MOTOR_STARTUP;
			}
			else
			{
				g_motorState = MOTOR_RUNNING;
			}
			
		}
		else
		{
			/* motor exception information process */
			g_motorState = MOTOR_STOP;
		}
	}
	else
	{
		g_motorState = MOTOR_STOP;
	}
}

/*
 *  check if the motor stop completely
 *  if motor stop return true,else return false
 *
 */
bool Check_Motor_Stop(void)
{
	bool ret = false;
	static uint32_t lastTick = 0;
	
	if(g_motorStopFlag)
	{
		if((g_sysTick - lastTick) > 80)
			ret = true;
	}
	else
	{
		g_motorStopFlag = true;
		lastTick = g_sysTick;
	}

	return ret;
}


