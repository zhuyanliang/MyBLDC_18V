
#ifndef LED_H
#define LED_H

#define LED	P0.0

#define Led_On()		(LED = 0b0)
#define Led_Off()		(LED = 0b1)
#define Led_Trig()		(LED = ~LED)

void Set_Led(uint8_t interval,uint8_t flashtimes,uint8_t constontimes);
void Manege_Led(void);

#endif