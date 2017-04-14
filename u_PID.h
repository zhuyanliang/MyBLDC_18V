#ifndef PID_H
#define PID_H

typedef struct _PID
{
    int16_t 	setSpeed;           
    int16_t 	realSpeed;        
    int16_t 	errPre;               
    int16_t 	errLast;           
    float 	Kp,Ki,Kd;                     
    float 	integral;            
}S_PID;

void PID_Init(void);

int16_t PID_Control(void);

#endif