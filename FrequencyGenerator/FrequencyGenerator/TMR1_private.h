/*
 * TMR1_private.h
 *
 * Created: 10/28/2023 5:39:14 PM
 *  Author: EngMo
 */ 


#ifndef TMR1_PRIVATE_H_
#define TMR1_PRIVATE_H_
#define TCCR1A      (*(volatile uint8*)0x4F)
#define COM1A1      7
#define COM1A0      6
#define COM1B1      5
#define COM1B0      4
#define FOC1A       3
#define FOC1B       2
#define WGM11       1
#define WGM10       0

#define TCCR1B     (*(volatile uint8*)0x4E)
#define ICNC1       7
#define ICES1       6

#define WGM13       4
#define WGM12       3
#define CS12        2
#define CS11        1
#define CS10        0

#define TCNT1_u16          (*(volatile uint16*)0x4C)
#define OCR1A_u16          (*(volatile uint16*)0x4A)
#define OCR1B_u16          (*(volatile uint16*)0x48)
#define ICR1_u16           (*(volatile uint16*)0x46)

#define TIMSK              (*(volatile uint8*)0x59)

#define TOIE1              2
#define OCIE1B             3
#define OCIE1A             4
#define TICIE1             5

#define TIFR              (*(volatile uint8*)0x58)






#endif /* TMR1_PRIVATE_H_ */