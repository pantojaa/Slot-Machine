/**************************************************************************************
***************************************************************************************
*                                LCD_Library.c
*                                Trevor Ekin (Adapted from Dr. Nabeeh Kandalaft)
*                         EGR226      Date: February-21-2019
*
*  This is a library for the 4x16 LCD.
*
*  All functions are briefly described in their comment blocks.  The /// notation makes
*  it so the function description block is visible when you hovering over a function call
*  in any file (this feature is called Intellisense).
*
*  All pins are set with default values (see below) but they can be easily changed.  See
*  description below in "Pins" comment block
* **************************************************************************************/

#ifndef LCD_LIBRARY_H_
#define LCD_LIBRARY_H_

//#include "driverlib.h"  // for use with driverlib
#include "msp.h"
#include <stdint.h>

/************  Pins   *******************************
*          MSP432 PINS (Default)
* P4.0 -> LCD D4
* P4.1 -> LCD D5
* P4.2 -> LCD D6
* P4.3 -> LCD D7
* P4.4 -> LCD E
* P4.5 -> LCD RS
* NOTICE:
*   This section is configurable and dynamic.  If you
*   would like to use different pins, make the swaps
*   here.  For example, if you would like D5 to be on
*   P2.4 instead of P4.1 make following changes:
*       D5_DIR P2DIR
*       D5_OUT P2OUT
*       D5 BIT4
* *****************************************************/

// direction registers (modify as needed)
#define EN_DIR  P4DIR
#define RS_DIR  P4DIR
#define D4_DIR  P4DIR
#define D5_DIR  P4DIR
#define D6_DIR  P4DIR
#define D7_DIR  P4DIR

// Port registers (modify as needed)
#define EN_OUT  P4OUT
#define RS_OUT  P4OUT
#define D4_OUT  P4OUT
#define D5_OUT  P4OUT
#define D6_OUT  P4OUT
#define D7_OUT  P4OUT

// Pin BITs (modify as needed)
#define EN  BIT0
#define RS  BIT1
#define D4  BIT4
#define D5  BIT5
#define D6  BIT6
#define D7  BIT7

// Bit Toggling (DO NOT CHANGE)
#define EN_LOW (EN_OUT &= ~EN)
#define EN_HIGH (EN_OUT |= EN)
#define RS_LOW (RS_OUT &= ~RS)
#define RS_HIGH (RS_OUT |= RS)
#define D4_LOW (D4_OUT &= ~D4)
#define D4_HIGH (D4_OUT |= D4)
#define D5_LOW (D5_OUT &= ~D5)
#define D5_HIGH (D5_OUT |= D5)
#define D6_LOW (D6_OUT &= ~D6)
#define D6_HIGH (D6_OUT |= D6)
#define D7_LOW (D7_OUT &= ~D7)
#define D7_HIGH (D7_OUT |= D7)

/// represent provided nibble on data lines use ternary statements and multi-line macro
/// *  note: ternary statements are like an "if / else" statement.
/// *      if/else example:
/// *
/// *      if(x & 0x01) {
/// *          D4_HIGH;
/// *      } else {
/// *          D4_LOW;
/// *      }
/// *
/// *      Ternary version with exact same result:
/// *      (x & 0x01) ? D4_HIGH : D4_LOW;
/// */
#define SetNibble(x) \
    ((x & 0x01) ? D4_HIGH : D4_LOW); \
    ((x & 0x02) ? D5_HIGH : D5_LOW); \
    ((x & 0x04) ? D6_HIGH : D6_LOW); \
    ((x & 0x08) ? D7_HIGH : D7_LOW);


/************************** Commands ***********************************
************************************************************************/
#define CLEAR       0x01
#define HOME        0x02

// ENTRY MODE COMMAND: 0b0000 01[I][S] -- I = Increment, S = Shift
#define ENTRYMODE_00    0x04    // no auto increment, no display shift  (DEFAULT)
#define ENTRYMODE_01    0x05    // no auto increment, display shift
#define ENTRYMODE_10    0x06    // auto increment, no display shift
#define ENTRYMODE_11    0x07    // auto increment, display shift

// DISPLAY CONTORL COMMAND: 0b0000 1[D][C][B] -- D = Display, C = Cursor, B = Blinking
#define DISPLAY_000     0x08    // display off, cursor off, blinking off    (DEFAULT)
#define DISPLAY_001     0x09    // display off, cursor off, blinking on     (not useful)
#define DISPLAY_010     0x0A    // display off, cursor on, blinking off     (not useful)
#define DISPLAY_011     0x0B    // display off, cursor on, blinking on      (not useful)
#define DISPLAY_100     0x0C    // display on, cursor off, blinking off
#define DISPLAY_101     0x0D    // display on, cursor off, blinking on
#define DISPLAY_110     0x0E    // display on, cursor on, blinking off
#define DISPLAY_111     0x0F    // display on, cursor on, blinking on

// CURSOR/DISPLAY SHIFT COMMAND: 0b0001 [DC][RL] * * -- DC = Display or Cursor, RL = Right or Left, * = don't care
#define SHIFT_00        0x10;   // cursor shift to the left
#define SHIFT_01        0x14;   // cursor shift to the right
#define SHIFT_10        0x18;   // display shift to the left
#define SHIFT_11        0x1C;   // display shift to the right

// FUNCTION SET COMMAND: 0b001[DL] [N][F] * * -- DL = Data length, N = display lines, F = character font
#define FSET_000        0x20    // 4-bit data, 1 line, 5x8 dot font
#define FSET_001        0x24    // 4-bit data, 1 line, 5x10 dot font
#define FSET_010        0x28    // 4-bit data, 2 lines, 5x8 dot font
#define FSET_011        0x2C    // 4-bit data, 2 lines, 5x10 dot font
#define FSET_100        0x30    // 8-bit data, 1 line, 5x8 dot font     (standard)
#define FSET_101        0x34    // 8-bit data, 1 line, 5x10 dot font
#define FSET_110        0x38    // 8-bit data, 2 lines, 5x8 dot font
#define FSET_111        0x3C    // 8-bit data, 2 lines, 5x10 dot font

// CGRAM ADDRESS
#define CGRAM           0x40    // start address for CGRAM data, custom graphics

/************************** Commands ***********************************
************************************************************************/

/********************* Structure Definitions ***************************
************************************************************************/
/// custom_char_t is a struct containing 8 bytes of data, representing the
///      8 rows of dots that create an LCD character. Each bit is either
///      on (1) or off (0) to display the image you desire.
/// You can make a custom character at (https://omerk.github.io/lcdchargen/)
typedef struct custom_char{
    uint8_t line0;
    uint8_t line1;
    uint8_t line2;
    uint8_t line3;
    uint8_t line4;
    uint8_t line5;
    uint8_t line6;
    uint8_t line7;
}custom_char_t;
/********************* Structure Definitions ***************************
************************************************************************/

/********************** Global Definitions *****************************
************************************************************************/
uint8_t _offset;                // offset in CGRAM for new custom characters
/********************** Global Definitions *****************************
************************************************************************/

/********************* Function Prototypes *****************************
************************************************************************/
void lcdInit ();
void lcdClear();
void lcdTriggerEN();
void lcdWriteData(unsigned char data);
void lcdWriteCmd (unsigned char  cmd);
void lcdSetText(char * text, int x, int y);
void lcdSetChar(char c, int x, int y);
void lcdSetInt (int val,     int x, int y);
uint8_t lcdCreateCustomChar(custom_char_t* cc);
/********************* Function Prototypes *****************************
************************************************************************/



#endif /* LIQUID_CRYSTAL_H_ */

