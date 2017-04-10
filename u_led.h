
#ifndef LED_H
#define LED_H

#define LED	P0.0

#define Led_On()		(LED = 0b0)
#define Led_Off()		(LED = 0b1)
#define Led_Trig()		(LED = ~LED)

#define Switch			P14.7
#define SwitchOn()		Switch = 0b1
#define SwitchOff()		Switch = 0b0

#define SwitchTrig()	Switch = ~Switch

void Led_Set(uint8_t interval,uint8_t flashtimes,uint16_t constontimes);
void Task_Manage_Led(void);

#endif