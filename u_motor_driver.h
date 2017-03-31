#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#define	HALL_U 		P5.0
#define	HALL_V   	P3.0
#define	HALL_W    	P5.1

uint8_t Get_Hall_State(void);
uint8_t Next_Hall_State_Expected(bool isFwd,uint8_t state);
void 	Commutate_Phase(bool isFwd,uint8_t state);
void 	Set_PWM_Duty(uint16_t val);
void 	Motor_Stop(void);
void 	Motor_Brake(void);

#endif