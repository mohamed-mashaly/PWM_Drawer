/*
 * ADC_interface.h
 *
 * Created: 10/13/2023 2:55:55 PM
 *  Author: EngMo
 */ 
#include "STD_TYPES.h"

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


#define ADC_AVCC         1
#define ADC_AREF         2
#define ADC_INTERNAL     3

#define ADC_CHANNEL0     0
#define ADC_CHANNEL1     1
#define ADC_CHANNEL2     2
#define ADC_CHANNEL3     3
#define ADC_CHANNEL4     4
#define ADC_CHANNEL5     5
#define ADC_CHANNEL6     6
#define ADC_CHANNEL7     7
#define ADC_FREE_RUN     1
#define ADC_SINGLE       0

 
void ADC_init(uint8 referenceVoltage,uint8 conMode);
void ADC_getDigitalValue(uint8 channelNum, uint16 *digitalValue);
void ADC_selectChannel(uint8 channelNum);
void ADC_readFree(uint16 *Val,uint8 *stat);
void ADC_readSingle(uint16 *Val,uint8 *stat);




#endif /* ADC_INTERFACE_H_ */