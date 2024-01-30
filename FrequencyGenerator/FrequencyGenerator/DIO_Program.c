/*
 * DIO_Program.c
 *
 * Created: 9/22/2023 4:11:20 PM
 *  Author: EngMo
 */ 
#include "DIO_Interface.h"
void DIO_setPinDirection(uint8 PortId, uint8 PinId, uint8 PinDirection)
{
	if((PortId<=3) && (PinId<=7)&&((PinDirection==DIO_PORT_INPUT)||(PinDirection==DIO_PORT_OUTPUT)))
	{
		switch (PortId)
		{
			case DIO_PORTA:
			switch(PinDirection)
			{
				case DIO_PIN_INPUT:
				RESET_BIT(DDRA,PinId);
				break;
				case DIO_PIN_OUTPUT:
				SET_BIT(DDRA,PinId);
				break;
			}
			break;

			case DIO_PORTB:
			switch(PinDirection)
			{
				case DIO_PIN_INPUT:
				RESET_BIT(DDRB,PinId);
				break;
				case DIO_PIN_OUTPUT:
				SET_BIT(DDRB,PinId);
				break;
			}
			break;
			
			case DIO_PORTC:
			switch(PinDirection)
			{
				case DIO_PIN_INPUT:
				RESET_BIT(DDRC,PinId);
				break;
				case DIO_PIN_OUTPUT:
				SET_BIT(DDRC,PinId);
				break;
			}
			break;
			
			case DIO_PORTD:
			switch(PinDirection)
			{
				case DIO_PIN_INPUT:
				RESET_BIT(DDRD,PinId);
				break;
				case DIO_PIN_OUTPUT:
				SET_BIT(DDRD,PinId);
				break;
			}
			break;
		}
	}
	else
	{
		//Do Nothing
	}
}

void DIO_setPinValue(uint8 PortId, uint8 PinId, uint8 PinValue)
{
	if((PortId<=3) && (PinId<=7)&&((PinValue==DIO_PIN_LOW)||(PinValue==DIO_PIN_OUTPUT)))
	{
		switch (PortId)
		{
			case DIO_PORTA:
			switch (PinValue)
			{
				case DIO_PIN_LOW:
				RESET_BIT(PORTA,PinId);
				break;
				case DIO_PIN_HIGH:
				SET_BIT(PORTA,PinId);
				break;
			}
			break;
			case DIO_PORTB:
			switch (PinValue)
			{
				case DIO_PIN_LOW:
				RESET_BIT(PORTB,PinId);
				break;
				case DIO_PIN_HIGH:
				SET_BIT(PORTB,PinId);
				break;
			}
			break;
			case DIO_PORTC:
			switch (PinValue)
			{
				case DIO_PIN_LOW:
				RESET_BIT(PORTC,PinId);
				break;
				case DIO_PIN_HIGH:
				SET_BIT(PORTC,PinId);
				break;
			}
			break;
			case DIO_PORTD:
			switch (PinValue)
			{
				case DIO_PIN_LOW:
				RESET_BIT(PORTD,PinId);
				break;
				case DIO_PIN_HIGH:
				SET_BIT(PORTD,PinId);
				break;
			}
			break;
		}
	}
	else
	{
		//Do Nothing
	}
}

void  DIO_getPinValue(uint8 PortId, uint8 PinId, uint8 *PinValue)
{
	if((PortId<=3) && (PinId<=7)&&(PinValue!=NULL))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			*PinValue=GET_BIT(PINA,PinId);
			break;
			case DIO_PORTB:
			*PinValue=GET_BIT(PINB,PinId);
			break;
			case DIO_PORTC:
			*PinValue=GET_BIT(PINC,PinId);
			break;
			case DIO_PORTD:
			*PinValue=GET_BIT(PIND,PinId);
			break;
		}
	}
	else
	{
		//Do Nothing
	}
}

void  DIO_togglePinValue(uint8 PortId, uint8 PinId)
{
	if((PortId<=3) && (PinId<=7))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			TOGGLE(PORTA,PinId);
			break;
			
			case DIO_PORTB:
			TOGGLE(PORTB,PinId);
			break;
			
			case DIO_PORTC:
			TOGGLE(PORTC,PinId);
			break;
			
			case DIO_PORTD:
			TOGGLE(PORTD,PinId);
			break;
		}
	}
	else
	{
		//do nothing
	}	
		
}

void  DIO_setPinInPullUpResistance(uint8 PortId, uint8 PinId)
{
	if((PortId<=3) && (PinId<=7))
	{
		switch (PortId)
		{
			case DIO_PORTA:
			SET_BIT(PORTA,PinId);
			break;
			
			case DIO_PORTB:
			SET_BIT(PORTB,PinId);
			break;
			
			case DIO_PORTC:
			SET_BIT(PORTC,PinId);
			break;
			
			case DIO_PORTD:
			SET_BIT(PORTD,PinId);
			break;
		}
	}
	else
	{
		//do nothing
	}
}

void  DIO_setPortDirection(uint8 PortId, uint8 PortDirection)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
			case DIO_PORTA:
			switch(PortDirection)
			{
				case DIO_PORT_OUTPUT:
				DDRA=0b11111111;
				break;
				
				case DIO_PORT_INPUT:
				DDRA=0b00000000;
				break;
			}
			break;
	
			case DIO_PORTB:
			switch(PortDirection)
			{
				case DIO_PORT_OUTPUT:
				DDRB=0b11111111;
				break;
				
				case DIO_PORT_INPUT:
				DDRB=0b00000000;
				break;
			}
			break;
			
			case DIO_PORTC:
			switch(PortDirection)
			{
				case DIO_PORT_OUTPUT:
				DDRC=0b11111111;
				break;
				
				case DIO_PORT_INPUT:
				DDRC=0b00000000;
				break;
			}
			break;
			
			case DIO_PORTD:
			switch(PortDirection)
			{
				case DIO_PORT_OUTPUT:
				DDRD=0b11111111;
				break;
				
				case DIO_PORT_INPUT:
				DDRD=0b00000000;
				break;
			}
			break;
		}
	}
	else
	{
		//Do Nothing
	}
	
}

void  DIO_setPortValue(uint8 PortId, uint8 PortValue)
{
	if(PortId<=3)
	{
		switch (PortId)
		{
			case DIO_PORTA:
			PORTA=PortValue;
			break;
			
			case DIO_PORTB:
			PORTB=PortValue;
			break;
			
			case DIO_PORTC:
			PORTC=PortValue;
			break;
			
			case DIO_PORTD:
			PORTD=PortValue;
			break;
		}
	}
}

void  DIO_getPortValue(uint8 PortId, uint8 *PortValue)
{
	if(PortId<=3)
	{
		switch (PortId)
		{
			case DIO_PORTA:
			*PortValue = PINA;
			break;
			
			case DIO_PORTB:
			*PortValue = PINB;
			break;
			
			case DIO_PORTC:
			*PortValue = PINC;
			break;
			
			case DIO_PORTD:
			*PortValue = PIND;
			break;
		}
		
	}
	else
	{
		//do nothing
	}
}

void  DIO_togglePortValue(uint8 PortId)
{
	if(PortId<=3)
	{
		switch (PortId)
		{
			case DIO_PORTA:
			PORTA=~PORTA;
			break;
			
			case DIO_PORTB:
			PORTB=~PORTB;
			break;
			
			case DIO_PORTC:
			PORTC=~PORTC;
			break;
			
			case DIO_PORTD:
			PORTD=~PORTD;
			break;
		}
		
	}
	else
	{
		
	}
}