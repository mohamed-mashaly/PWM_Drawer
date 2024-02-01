/*
 * T6963.c
 *
 * Created: 12/18/2023 10:21:52 AM
 *  Author: EngMo
 */
#define F_CPU 16000000UL 
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include <util/delay.h>

#include "DIO_Interface.h"

#include "T6963_interface.h"
#include "T6963_config.h"
#include "T6963_private.h"



void T6963_Busy(void)
{
	uint8 chk=0;
	DIO_setPortDirection(T6963_DATA_PORT,DIO_PORT_INPUT);
	
	DIO_setPinValue(T6963_RS_PORT,T6963_RS_PIN,DIO_PIN_HIGH);
	DIO_setPinValue(T6963_RW_PORT,T6963_RW_PIN,DIO_PIN_HIGH);
	DIO_setPinValue(T6963_RD_PORT,T6963_RD_PIN,DIO_PIN_LOW);
	DIO_setPinValue(T6963_E_PORT,T6963_E_PIN,DIO_PIN_LOW);
	while(GET_BIT(chk,0)!=1 && GET_BIT(chk,1)!=1)
	{
		DIO_getPortValue(T6963_BUSY_PORT,&chk);
	}
	DIO_setPinValue(T6963_RD_PORT,T6963_RD_PIN,DIO_PIN_HIGH);
	DIO_setPinValue(T6963_E_PORT,T6963_E_PIN,DIO_PIN_HIGH);
	DIO_setPortDirection(T6963_DATA_PORT,DIO_PORT_OUTPUT);
}

void T6963_init(void)
{
	//Setting Pins Directions
	DIO_setPortDirection(T6963_DATA_PORT,DIO_PORT_OUTPUT);
	DIO_setPinDirection(T6963_RS_PORT,T6963_RS_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(T6963_RW_PORT,T6963_RW_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(T6963_RW_PORT,T6963_RD_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(T6963_E_PORT,T6963_E_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(T6963_RST_PORT,T6963_RST_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(T6963_FS_PORT,T6963_FS_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(T6963_MD_PORT,T6963_MD_PIN,DIO_PIN_OUTPUT);
	// Reseting The LCD
	DIO_setPinValue(T6963_RST_PORT,T6963_RST_PIN,DIO_PIN_LOW);
	_delay_ms(20);
	DIO_setPinValue(T6963_RST_PORT,T6963_RST_PIN,DIO_PIN_HIGH);
	
	#if T6963_FONT == 6
        DIO_setPinValue(T6963_FS_PORT,T6963_FS_PIN,DIO_PIN_HIGH);
	#else
	    DIO_setPinValue(T6963_FS_PORT,T6963_FS_PIN,DIO_PIN_LOW);
    #endif
	#if T6963_TEXT_AREA ==40
	    DIO_setPinValue(T6963_MD_PORT,T6963_MD_PIN,DIO_PIN_LOW);
	#else
	    DIO_setPinValue(T6963_MD_PORT,T6963_MD_PIN,DIO_PIN_HIGH);
    #endif
	  
	T6963_setAddress(0);
	T6963_setCursor(0,0);
	T6963_setOffSetReg(T6963_OFFSET_REGISTER);
	
	T6963_setTextHome(T6963_TEXT_HOME);
	T6963_setTextArea(T6963_TEXT_AREA);
	
	T6963_setGraphicHome(T6963_GRAPHIC_HOME);
	T6963_setGraphicArea(T6963_GRAPHIC_AREA);
	
	T6963_sendCmnd(T6963_MODE_SET | T6963_CG_ROM_MODE | T6963_OR_MODE);
	T6963_sendCmnd(T6963_DISPLAY_MODE | T6963_GRAPHICS_ON | T6963_TEXT_ON); //Text and Graphics mode
	
	//T6963_sendCmnd(T6963_CURSOR_PATTERN | T6963_CURSOR_TWO_LINE);
	
}


void T6963_sendCmnd(uint8 Cmd)
{
	T6963_Busy();
	DIO_setPortValue(T6963_DATA_PORT,Cmd);
	DIO_setPinValue(T6963_RS_PORT,T6963_RS_PIN,DIO_PIN_HIGH);
	DIO_setPinValue(T6963_RW_PORT,T6963_RW_PIN,DIO_PIN_LOW);
	DIO_setPinValue(T6963_E_PORT,T6963_E_PIN,DIO_PIN_LOW);
	_delay_us(2);
	DIO_setPinValue(T6963_RW_PORT,T6963_RW_PIN,DIO_PIN_HIGH);
	DIO_setPinValue(T6963_E_PORT,T6963_E_PIN,DIO_PIN_HIGH);
}

void T6963_sendData(uint8 data)
{
	T6963_Busy();
	DIO_setPortValue(T6963_DATA_PORT,data);
	DIO_setPinValue(T6963_RS_PORT,T6963_RS_PIN,DIO_PIN_LOW);
	DIO_setPinValue(T6963_RW_PORT,T6963_RW_PIN,DIO_PIN_LOW);
	DIO_setPinValue(T6963_E_PORT,T6963_E_PIN,DIO_PIN_LOW);
	_delay_us(1);
	DIO_setPinValue(T6963_E_PORT,T6963_E_PIN,DIO_PIN_HIGH);
	DIO_setPinValue(T6963_RW_PORT,T6963_RW_PIN,DIO_PIN_HIGH);
}

void T6963_setBit(uint8 num)
{
	if (num<8) T6963_sendCmnd(T6963_BIT_SET | num);
}

void T6963_clrBit(uint8 num)
{
	if (num<8) T6963_sendCmnd(T6963_BIT_CLR | num);
}

void T6963_sendChar(uint8 c)
{
	T6963_sendData(c-32);
	T6963_sendCmnd(T6963_DATA_WRITE | T6963_ADDRESS_POINTER_UP);
}
void T6963_sendDis(uint8 c)
{
	T6963_sendData(c);
	T6963_sendCmnd(T6963_DATA_WRITE | T6963_ADDRESS_POINTER_UP);
}

void T6963_setAddress(uint16 address)
{
	T6963_sendData((uint8)address);
	T6963_sendData((uint8)(address>>8));
	T6963_sendCmnd(T6963_SET_ADDRESS_POINTER);
}

void T6963_setCursor(uint8 column, uint8 row)
{
	T6963_sendData(column);
	T6963_sendData(row);
	T6963_sendCmnd(T6963_SET_CURSOR_POINTER);
}

void T6963_setOffSetReg(uint8 data)
{
	T6963_sendData(data);
	T6963_sendData(0b0000000);
	T6963_sendCmnd(T6963_SET_OFFSET_REGISTER);
}

void T6963_setTextHome(uint16 address)
{
	T6963_sendData((uint8)address);
	T6963_sendData((uint8)(address>>8));
	T6963_sendCmnd(T6963_SET_TEXT_HOME_ADDRESS);
}

void T6963_setGraphicHome(uint16 address)
{
	T6963_sendData((uint8)address);
	T6963_sendData((uint8)(address>>8));
	T6963_sendCmnd(T6963_SET_GRAPHIC_HOME_ADDRESS);
}

void T6963_setTextArea(uint8 area)
{
	T6963_sendData(area);
	T6963_sendData(0x0);
	T6963_sendCmnd(T6963_SET_TEXT_AREA);
}

void T6963_setGraphicArea(uint8 area)
{
	T6963_sendData(area);
	T6963_sendData(0x0);
	T6963_sendCmnd(T6963_SET_GRAPHIC_AREA);
}

void T6963_setGraphicAddress(uint16 address)
{
	address+=T6963_GRAPHIC_HOME;
	T6963_sendData((uint8)address);
	T6963_sendData((uint8)(address>>8));
	T6963_sendCmnd(T6963_SET_ADDRESS_POINTER);
}

void T6963_drawLine(uint8 x1,uint8 y1,uint8 x2,uint8 y2)
{
	//if((x1<(T6963_GRAPHIC_AREA*T6963_FONT))&&(x2<(T6963_GRAPHIC_AREA*T6963_FONT))&&(y1<T6963_HIGHT)&&(y2<T6963_HIGHT))return;
	uint8 dx=(x2>x1)?(x2-x1):(x1-x2);
	uint8 dy=(y2>y1)?(y2-y1):(y1-y2);
	uint8 x=x1;
	uint8 y=y1;
	dx++;
	dy++;
	if (dx>dy)
	{
	    uint8 i;
		for(i=0;i<dx;i++)
			{
				T6963_setAddress(T6963_GRAPHIC_HOME+T6963_GRAPHIC_AREA*y+(x/T6963_FONT));
				T6963_setBit(7);
				T6963_setBit(5-x%T6963_FONT);
				x=(x2>x1)?x+1:x-1;
				if(x2>x1)
				{y=(y2>y1)?y1+(dy*(x-x1))/dx:y1-(dy*(x-x1))/dx;}
				else 
				{y=(y2>y1)?y1+(dy*(x1-x))/dx:y1-(dy*(x1-x))/dx;}
			}
	}
	else
	{
		uint8 i;
		for(i=0;i<dy;i++)
		{
			T6963_setAddress(T6963_GRAPHIC_HOME+T6963_GRAPHIC_AREA*y+(x/T6963_FONT));
			T6963_setBit(7);
			T6963_setBit(5-(x%T6963_FONT));
			y=(y2>y1)?y+1:y-1;
			if(y2>y1)
			{x=(x2>x1)?x1+(dx*(y-y1))/dy:x1-(dx*(y-y1))/dy;}
			else 
			{x=(x2>x1)?x1+(dx*(y1-y))/dy:x1-(dx*(y1-y))/dy;}
		}
	}
	
}

void T6963_dellLine(uint8 x1,uint8 y1,uint8 x2,uint8 y2)
{
	//if((x1<(T6963_GRAPHIC_AREA*T6963_FONT))&&(x2<(T6963_GRAPHIC_AREA*T6963_FONT))&&(y1<T6963_HIGHT)&&(y2<T6963_HIGHT))return;
	uint8 dx=(x2>x1)?(x2-x1):(x1-x2);
	uint8 dy=(y2>y1)?(y2-y1):(y1-y2);
	uint8 x=x1;
	uint8 y=y1;
	dx++;
	dy++;
	if (dx>dy)
	{
		uint8 i;
		for(i=0;i<dx;i++)
		{
			T6963_setAddress(T6963_GRAPHIC_HOME+T6963_GRAPHIC_AREA*y+(x/T6963_FONT));
			T6963_setBit(7);
			T6963_clrBit(5-x%T6963_FONT);
			x=(x2>x1)?x+1:x-1;
			if(x2>x1)
			{y=(y2>y1)?y1+(dy*(x-x1))/dx:y1-(dy*(x-x1))/dx;}
			else
			{y=(y2>y1)?y1+(dy*(x1-x))/dx:y1-(dy*(x1-x))/dx;}
		}
	}
	else
	{
		uint8 i;
		for(i=0;i<dy;i++)
		{
			T6963_setAddress(T6963_GRAPHIC_HOME+T6963_GRAPHIC_AREA*y+(x/T6963_FONT));
			T6963_setBit(7);
			T6963_clrBit(5-(x%T6963_FONT));
			y=(y2>y1)?y+1:y-1;
			if(y2>y1)
			{x=(x2>x1)?x1+(dx*(y-y1))/dy:x1-(dx*(y-y1))/dy;}
			else
			{x=(x2>x1)?x1+(dx*(y1-y))/dy:x1-(dx*(y1-y))/dy;}
		}
	}
	
}

void T6963_writeString(uint8 *c)
{
	if(c==NULL)return;
	for(;*c!='\0';c++)T6963_sendChar(*c);
}

void T6963_writeNum(uint16 num)
{
	if(num==0)
	{
		T6963_sendChar('0');
		return;
	}
	uint16 n=1;
	for(;num>0;)
	{
		n=n*10+num%10;
		num/=10;
	}
	for(;n>0;)
	{
		if(n/10==0)break;
		T6963_sendChar('0'+(n%10));
		n/=10;
	}
}

void T6963_goToLine(uint8 x,uint8 y)
{
	T6963_setAddress(T6963_TEXT_HOME+T6963_TEXT_AREA*y+x);
	
}

void T6963_writeCol(uint8 x,uint8 y1,uint8 y2,uint8 v1,uint8 v2)
{
	if(v1>v2)
	{
		v1=v1+v2;
		v2=v1-v2;
		v1=v1-v2;
	}
	uint8 i;
	for(i=y1;i<v1;i++)
	{
		T6963_setAddress(T6963_GRAPHIC_HOME+T6963_GRAPHIC_AREA*i+(x/T6963_FONT));
		T6963_clrBit(5-x%T6963_FONT);
	}
	for(i=v1;i<=v2;i++)
	{
		T6963_setAddress(T6963_GRAPHIC_HOME+T6963_GRAPHIC_AREA*i+(x/T6963_FONT));
		T6963_setBit(7);
		T6963_setBit(5-x%T6963_FONT);
	}
	for(i=v2+1;i<=y2;i++)
	{
		T6963_setAddress(T6963_GRAPHIC_HOME+T6963_GRAPHIC_AREA*i+(x/T6963_FONT));
		T6963_clrBit(5-x%T6963_FONT);
	}
}