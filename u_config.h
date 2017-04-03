
#ifndef CONFIG_H
#define CONFIG_H

#define SPEED_MAX	4799U
#define SPEED_MIN	800U

#define VDD			5U
#define AVREF		VDD
#define ADC10BITS	1024U

/* protect parameter set*/
/*VBUS*/
#define	Rtop					200U
#define	Rbottom					47U
#define Voltage_Normal			18U
#define Voltage_Low_Value		14U
#define Voltage_Low_Value_AD	(uint16_t)(Voltage_Low_Value*1.0F*Rbottom/(Rtop+Rbottom)/VDD*ADC10BITS)

/*current check parameters*/
#define R_curchk				0.001F
#define Current_Short_Value		100U	/* uint: A*/
#define Current_Overload_Value	45U		/* uint: A*/
#define Current_Short_AD		(uint16_t)(Current_Short_Value*R_curchk/VDD*ADC10BITS)
#define Current_Overload_AD		(uint16_t)(Current_Overload_Value*R_curchk/VDD*ADC10BITS)

/*mosfet temperature parameters*/
#define R_div				10U
//#define Temp_Over_AD		100U  /*!!!!!!!!!!rember to modify*/
#define	Temp_Over_AD         23U   //1.2676/11.2676/5*1024

#define Adc_Channel_Current	1U
#define Adc_Channel_Voltage	2U
#define Adc_Channel_MOSTemp	3U


#define Enable		true
#define NeedBrake	Enable

#endif