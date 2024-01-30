/*
 * Basic_Oscilloscope.c
 *
 * Created: 1/17/2024 9:47:11 PM
 * Author : Eng Mohamed
 */ 
#define F_CPU 16000000UL
 
 #include <util/delay.h>
 
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_Interface.h"
#include "T6963_interface.h"

#define PERIOD   ((T6963_WIDTH-2)/8)
#define ON       T6963_HIGHT-80
#define OFF      T6963_HIGHT-20

void updateSreen(uint32 freq, uint16 duty);
uint32 count=0;
uint8  stat=0;
uint8  pstate=0;
uint32 flips=0;
uint32 ups=0;
uint32 downs=0;
int main(void)
{
	DIO_setPinDirection(DIO_PORTA,DIO_PIN0,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN1,DIO_PIN_OUTPUT);
	T6963_init();
	T6963_drawLine(0,0,T6963_WIDTH-1,0); //draw upper border
	T6963_drawLine(T6963_WIDTH-1,0,T6963_WIDTH-1,T6963_HIGHT-1); //draw right border
	T6963_drawLine(T6963_WIDTH-1,T6963_HIGHT-1,0,T6963_HIGHT-1); //draw lower border
	T6963_drawLine(0,T6963_HIGHT-1,0,0); //draw lift border
	T6963_goToLine(1,1);
	T6963_writeString("Frequency=        ");
	T6963_writeString("Hz ");
	T6963_writeString("Duty Cycle=    %");
	T6963_drawLine(1+PERIOD,ON-3,PERIOD+1,ON-23);
	T6963_drawLine(1+PERIOD,ON-7,PERIOD*2+1,ON-7);
	T6963_drawLine(1+PERIOD*2,ON-3,PERIOD*2+1,ON-23);
	T6963_goToLine(5,4);
	T6963_writeString("  ms");
	updateSreen(0,0);
    /* Replace with your application code */
	uint8 i;
    while (1) 
    {
		count+=320;
		DIO_getPinValue(DIO_PORTA,DIO_PIN0,&stat);
		ups+=stat;
		downs+=(stat^1);
		flips+=stat^pstate;
		pstate=stat;
		for (i=0;i<46;i++)
		{
			asm("NOP");
		}
		asm("NOP");
		asm("NOP");
		asm("NOP");
		if(count>=F_CPU)
		{
			DIO_togglePinValue(DIO_PORTA,DIO_PIN1);
			updateSreen(flips/2,(ups*1000)/(ups+downs));
			flips=0;
			count=0;
			ups=0;
			downs=0;
			DIO_togglePinValue(DIO_PORTA,DIO_PIN1);
		}
    }
}
void updateSreen(uint32 freq, uint16 duty)
{
	static uint16 pduty=0;
	uint8 i;
	for(i=0;i<8;i++)
	{
		T6963_dellLine(1+i*PERIOD,ON,1+i*PERIOD+(pduty*PERIOD)/1000,ON);
		T6963_dellLine(1+i*PERIOD+(pduty*PERIOD)/1000,ON,1+i*PERIOD+(pduty*PERIOD)/1000,OFF);
		T6963_dellLine(1+i*PERIOD+(pduty*PERIOD)/1000,OFF,1+(i+1)*PERIOD,OFF);
		T6963_dellLine(1+(i+1)*PERIOD,OFF,1+(i+1)*PERIOD,ON);
	}
	T6963_goToLine(11,1);
	for(i=0;i<8;i++)T6963_sendChar(' ');
	T6963_goToLine(34,1);
	for(i=0;i<4;i++)T6963_sendChar(' ');
	T6963_goToLine(5,3);
	for(i=0;i<4;i++)T6963_sendChar(' ');
	for(i=0;i<8;i++)
	{
		T6963_drawLine(1+i*PERIOD,ON,1+i*PERIOD+(duty*PERIOD)/1000,ON);
		T6963_drawLine(1+i*PERIOD+(duty*PERIOD)/1000,ON,1+i*PERIOD+(duty*PERIOD)/1000,OFF);
		T6963_drawLine(1+i*PERIOD+(duty*PERIOD)/1000,OFF,1+i*PERIOD+PERIOD,OFF);
		T6963_drawLine(1+i*PERIOD+PERIOD,OFF,1+i*PERIOD+PERIOD,ON);
	}
	T6963_goToLine(11,1);
	T6963_writeNum(freq);
	T6963_goToLine(34,1);
	T6963_writeNum(duty/10);
	T6963_sendChar('.');
	T6963_writeNum(duty-(duty/10)*10);
	T6963_goToLine(5,3);
	T6963_writeNum(1000/freq);
	pduty=duty;
}

