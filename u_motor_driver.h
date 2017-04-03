#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#define	HALL_U 		P5.0
#define	HALL_V   	P3.0
#define	HALL_W    	P5.1

#define PWM_On()			R_TMR_RD1_Start()
#define PWM_Off()			R_TMR_RD1_Stop()
#define	Hall_Int_On()     	R_INTC1_Start();R_INTC2_Start();R_INTC3_Start()
#define	Hall_Int_Off()  	R_INTC1_Stop();R_INTC2_Stop();R_INTC3_Stop()

uint8_t Get_Hall_State(void);
void 	Scan_Hall_State(void);
uint8_t Next_Hall_State_Expected(bool isFwd,uint8_t state);
void 	Commutate_Phase(bool isFwd,uint8_t state);
void 	PWM_Set_Duty(uint16_t val);
void 	Motor_Stop(void);
void 	Motor_Brake(void);
void 	Manage_Motor_Phase(void);
void 	Hall_Interupt_Process(void);
void 	Manage_Motor_State(void);

#endif