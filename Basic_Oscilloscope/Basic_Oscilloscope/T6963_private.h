/*
 * T6963_private.h
 *
 * Created: 12/18/2023 11:51:51 AM
 *  Author: EngMo
 */ 


#ifndef T6963_PRIVATE_H_
#define T6963_PRIVATE_H_


#define T6963_SET_ADDRESS_POINTER        0b00100100
#define T6963_SET_OFFSET_REGISTER        0b00100010
#define T6963_SET_CURSOR_POINTER         0b00100001


#define T6963_SET_TEXT_HOME_ADDRESS      0b01000000
#define T6963_SET_TEXT_AREA              0b01000001
#define T6963_SET_GRAPHIC_HOME_ADDRESS   0b01000010
#define T6963_SET_GRAPHIC_AREA           0b01000011


#define T6963_MODE_SET                   0b10000000
#define T6963_CG_ROM_MODE                0b00000000
#define T6963_CG_RAM_MODE                0b00001000
#define T6963_OR_MODE                    0b00000000
#define T6963_EXOR_MODE                  0b00000001
#define T6963_AND_MODE                   0b00000011
#define T6963_TEXT_ONLY_MODE             0b00000100

#define T6963_DISPLAY_MODE               0b10010000
#define T6963_GRAPHICS_ON                0b00001000
#define T6963_TEXT_ON                    0b00000100
#define T6963_CURSOR_ON                  0b00000010
#define T6963_CURSOR_BLINK_ON            0b00000001


#define T6963_CURSOR_PATTERN             0b10100000
#define T6963_CURSOR_BOTTOM_LINE         0b00000000
#define T6963_CURSOR_TWO_LINE            0b00000001
#define T6963_CURSOR_EIGHT_LINE          0b00000111

#define T6963_DATA_READ                  0b11000001
#define T6963_DATA_WRITE                 0b11000000
#define T6963_ADDRESS_POINTER_UP         0b00000000
#define T6963_ADDRESS_POINTER_DOWN       0b00000010
#define T6963_ADDRESS_POINTER_UNCHANGED  0b00000100

#define T6963_BIT_SET                    0b11111000
#define T6963_BIT_CLR                    0b11110000



#endif /* T6963_PRIVATE_H_ */