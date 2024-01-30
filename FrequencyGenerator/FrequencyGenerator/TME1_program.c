/*
 * TME1_program.c
 *
 * Created: 10/28/2023 5:39:29 PM
 *  Author: EngMo
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TME1_interface.h"
#include "TMR1_config.h"
#include "TMR1_private.h"

void TMR1_init (void)
{
	RESET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	RESET_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	
	ICR1_u16= 4999;
}
void TMR1_start(void)
{
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	RESET_BIT(TCCR1B,CS12);
}
void TMR1_stop (void)
{
	RESET_BIT(TCCR1B,CS10);
	RESET_BIT(TCCR1B,CS11);
	RESET_BIT(TCCR1B,CS12);
}
void TMR1_setComValueA(uint8 val)
{
	OCR1A_u16=val;
}
void TMR1_setDutyCycle(uint8 val)
{
	if(val<=100)OCR1A_u16=(((uint32)val*(ICR1_u16+1))/100)-1;
}
void TMR1_setFrequency(uint32 val)
{
	ICR1_u16= (1000000UL-val*4)/(val*4); // val in hertz
}