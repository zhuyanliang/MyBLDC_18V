
#ifndef CONFIG_H
#define CONFIG_H

#define SPEED_MAX	4799U
#define SPEED_MIN	1000U

#define VDD			5U
#define AVREF		VDD
#define ADC10BITS	1024U

/* protect parameter set*/
/*VBUS*/
#define	Rtop					200U
#define	Rbottom					47U
#define Voltage_Normal			18U
#define Voltage_Low_Value		14U
#define Voltage_Low_Value_AD	(uint16_t)(Voltage_Low_Value*1.0*Rbottom/(Rtop+Rbottom)/VDD*ADC10BITS)


#define Current_Adc_Channel	1U
#define Voltage_Adc_Channel	2U
#define MOSTemp_Adc_Channel	3U

#endif