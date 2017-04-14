
#ifndef CONFIG_H
#define CONFIG_H

#define SPEED_MAX		(int16_t)4799
#define SPEED_MIN		(int16_t)0
#define SPEED_EXPECT	3000U

#define MAGNEDTIC_POLE_NUM 		4U
#define SPEEDAVGNUM				4U


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
#define Current_Short_Value		50U	/* uint: A*/
#define Current_Overload_Value	30U		/* uint: A*/
#define Amplifier				10U
#define Current_Short_AD		(uint16_t)(Current_Short_Value*R_curchk/VDD*ADC10BITS*Amplifier)
#define Current_Overload_AD		(uint16_t)(Current_Overload_Value*R_curchk/VDD*ADC10BITS*Amplifier)


/*mosfet temperature parameters*/
#define R_div				10U
#define Temp_Over_R_Val		0.98F 
#define	Temp_Over_AD        (uint16_t)(Temp_Over_R_Val/(R_div+Temp_Over_R_Val)*ADC10BITS)

#define Adc_Channel_Current		1U
#define Adc_Channel_Voltage		2U
#define Adc_Channel_MOSTemp		3U


#define Enable		true
#define NeedBrake	Enable

#endif