/*
 * TME1_interface.h
 *
 * Created: 10/28/2023 5:37:46 PM
 *  Author: EngMo
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#ifndef TME1_INTERFACE_H_
#define TME1_INTERFACE_H_

void TMR1_init (void);
void TMR1_start(void);
void TMR1_stop (void);
void TMR1_setComValueA(uint8 val);
void TMR1_setDutyCycle(uint8 val);
void TMR1_setFrequency(uint32 val);




#endif /* TME1_INTERFACE_H_ */