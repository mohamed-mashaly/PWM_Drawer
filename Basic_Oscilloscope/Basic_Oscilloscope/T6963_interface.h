/*
 * T6963_interface.h
 *
 * Created: 12/18/2023 10:19:55 AM
 *  Author: EngMo
 */ 

#include "STD_TYPES.h"
#include "T6963_config.h"

#ifndef T6963_INTERFACE_H_
#define T6963_INTERFACE_H_

void T6963_init(void);
void T6963_sendCmnd(uint8 Cmd);
void T6963_sendData(uint8 data);
void T6963_clear(void);
void delay(unsigned long int k);
void T6963_sendChar(uint8 c);
void T6963_setAddress(uint16 address);
void T6963_setCursor(uint8 column, uint8 row);
void T6963_setCursor(uint8 column, uint8 row);
void T6963_setOffSetReg(uint8 address);
void T6963_setTextHome(uint16 address);
void T6963_setGraphicHome(uint16 address);
void T6963_setTextArea(uint8 area);
void T6963_setGraphicArea(uint8 area);
void T6963_clrBit(uint8 num);
void T6963_setBit(uint8 num);
void T6963_setGraphicAddress(uint16 address);
void T6963_sendDis(uint8 c);
void T6963_drawLine(uint8 x1,uint8 y1,uint8 x2,uint8 y2);
void T6963_dellLine(uint8 x1,uint8 y1,uint8 x2,uint8 y2);
void T6963_writeString(uint8 *c);
void T6963_writeNum(uint16 num);
void T6963_goToLine(uint8 x,uint8 y);
void T6963_writeCol(uint8 x,uint8 y1,uint8 y2,uint8 v1,uint8 v2);



#endif /* T6963_INTERFACE_H_ */