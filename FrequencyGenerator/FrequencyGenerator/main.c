/*
 * FrequencyGenerator.c
 *
 * Created: 1/30/2024 9:31:40 PM
 * Author : EngMo
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "TME1_interface.h"
#include "ADC_interface.h"



int main(void)
{
	DIO_setPinDirection(DIO_PORTD,DIO_PIN5,DIO_PIN_OUTPUT);
	TMR1_init();
	TMR1_setFrequency(10);
	TMR1_setDutyCycle(50);
	TMR1_start();
	ADC_init(ADC_AVCC,ADC_SINGLE);
	uint16 duty;
	uint16 pduty=0;
	uint16 freq=1;
	uint16 pfreq=10;
	/* Replace with your application code */
	while (1)
	{
		ADC_getDigitalValue(ADC_CHANNEL0, &duty);
		ADC_getDigitalValue(ADC_CHANNEL1, &freq);
		if (pfreq!=freq)
		{
			TMR1_setFrequency(((uint32)freq*1000)/1023);
			TMR1_setDutyCycle(((uint32)duty*100)/1023);
			pfreq=freq;
		}
		if (pduty!=duty)
		{
			TMR1_setDutyCycle(((uint32)duty*100)/1023);
			pduty=duty;
		}
	}
}

