/*
 * ADC_program.c
 *
 * Created: 10/13/2023 2:56:17 PM
 *  Author: EngMo
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"


void ADC_init(uint8 referenceVoltage, uint8 conMode)
{
	switch(referenceVoltage)
	{
		case ADC_AVCC:
		SET_BIT(ADMUX,REFS0);
		RESET_BIT(ADMUX,REFS1);
		break;
		
		case ADC_AREF:
		RESET_BIT(ADMUX,REFS0);
		RESET_BIT(ADMUX,REFS1);
		break;
		
		default:
		case ADC_INTERNAL:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	switch(conMode)
	{
		case ADC_FREE_RUN:
		SET_BIT(ADCSRA,ADATE);
		RESET_BIT(SFIOR,ADTS2);
		RESET_BIT(SFIOR,ADTS1);
		RESET_BIT(SFIOR,ADTS0);
		break;
		default:
		case ADC_SINGLE:
		RESET_BIT(ADCSRA,ADATE);
		break;
		
	}
	RESET_BIT(ADMUX,ADLAR);
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	RESET_BIT(ADCSRA,ADIE);
	
	
	SET_BIT(ADCSRA,ADEN);
}
void ADC_getDigitalValue(uint8 channelNum, uint16 *digitalValue)
{	
	if(channelNum<32&&(digitalValue!=NULL))
	{
		//SELECT CHANNEL
		ADMUX&=0xE0;
		ADMUX|=channelNum;
		//START CONVERSION
		SET_BIT(ADCSRA,ADSC);
		while((GET_BIT(ADCSRA,ADIF))==0);
		SET_BIT(ADCSRA,ADIF);
		*digitalValue=ADC_u16;
	}
	else
	{
		
	}
}
void ADC_selectChannel(uint8 channelNum)
{
	ADMUX&=0xE0;
	ADMUX|=channelNum;
	SET_BIT(ADCSRA,ADSC);
}
void ADC_readFree(uint16 *Val,uint8 *stat)
{
	if(GET_BIT(ADCSRA,ADIF))
	{
		SET_BIT(ADCSRA,ADIF);
		*Val=ADC_u16;
		*stat=1;
	}
	else
	{
		*stat=0;
	}
}

void ADC_readSingle(uint16 *Val,uint8 *stat)
{
	if(GET_BIT(ADCSRA,ADIF))
	{
		SET_BIT(ADCSRA,ADIF);
		*Val=ADC_u16;
		SET_BIT(ADCSRA,ADSC);
		*stat=1;
	}
	else
	{
		*stat=0;
	}
}