/*
 * LCD_Display_code.c
 *
 *  Created on: March 17, 2019
 *      Author: Adan
 */
#include "SysTick.h"
#include "msp.h"

/* ----- Definitions ----- */
#define LCD_PORT P4
#define DB7 BIT7
#define DB6 BIT6
#define DB5 BIT5
#define DB4 BIT4
#define RW  BIT2
#define RS  BIT1
#define E   BIT0


/* ----- Functions ----- */

/* ----------------------------------------------------------
 * Function: Sets up ports and pins to allow interface with LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void GPIO_init(void)
{
    LCD_PORT->SEL0 &= ~(0xFF); // Set all pins to general purpose i/o
    LCD_PORT->SEL1 &= ~(0xFF); // Set all pins to general purpose i/o
    LCD_PORT->DIR  |=   0xFF;  // Set all pins as outputs
    LCD_PORT->OUT  &= ~(0xFF); // Set all pins to LOW
}
/* ----------------------------------------------------------
 * Function: Sets up LCD by writing a sequence of commands
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void LCD_init(void)
{
    GPIO_init(); // Sets up pins to allow them to interface with LCD

    commandWrite(3);
    delay_ms(100);
    commandWrite(3);
    delay_us(100);
    commandWrite(3);
    delay_ms(100);

    commandWrite(2);
    delay_us(100);
    commandWrite(2);
    delay_us(100);

    commandWrite(8);
    delay_us(100);
    commandWrite(0x0F);
    delay_us(100);
    commandWrite(1);
    delay_us(100);
    commandWrite(6);
    delay_ms(10);
}
/* ----------------------------------------------------------
 * Function: Pulses the enable pin to allow communication
 *           between the MSP and the LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void PulseEnablePin(void)
{
    LCD_PORT->OUT &= ~(E);
    delay_us(10);
    LCD_PORT->OUT |=   E;
    delay_us(10);
    LCD_PORT->OUT &= ~(E);
    delay_us(10);
}
/* ----------------------------------------------------------
 * Function: Pushes a nibble of data into the D4-D7 bits of
 *           the LCD
 *    Input: Nibble of data that you want written to the LCD
 *   Output: N/A
 * ---------------------------------------------------------- */
void pushNibble(uint8_t nibble)
{
    LCD_PORT->OUT &= ~(0xF0); // Clears all P4.7 - P4.4
    LCD_PORT->OUT |= (nibble & 0x0F) << 4;
    PulseEnablePin();
}
/* ----------------------------------------------------------
 * Function: Takes a byte of data a sends it to the MSP a nibble
 *           at a time
 *    Input: Byte of data that will be sent to LCD
 *   Output: N/A
 * ---------------------------------------------------------- */
void pushByte(uint8_t byte)
{
    uint8_t nibble;

    nibble = (byte & 0xF0) >> 4;
    pushNibble(nibble);
    nibble = (byte & 0x0F);
    pushNibble(nibble);
}
/* ----------------------------------------------------------
 * Function: Accepts a command that will be sent to the LCD
 *    Input: Hex representation of that command
 *   Output: N/A
 * ---------------------------------------------------------- */
void commandWrite(uint8_t command)
{
    LCD_PORT->OUT &= ~RS;
    pushByte(command);
    delay_us(100);
}
/* ----------------------------------------------------------
 * Function: Accepts piece of data that will be displayed on
 *           the LCD
 *    Input: Byte sized data that will be sent to the LCD
 *   Output: N/A
 * ---------------------------------------------------------- */
void dataWrite(uint8_t data)
{
    LCD_PORT->OUT |= RS;
    pushByte(data);
    delay_us(100);
}
/* ----------------------------------------------------------
 * Function: Sends string values to string_decoder function 
 *    Input: Individual values of any string 
 *   Output: N/A
 * ---------------------------------------------------------- */
void send_string(uint8_t *s)
{
    string_decoder(s);
}
/* ----------------------------------------------------------
 * Function: Sends string values to dataWrite function to print
 *           values on LCD
 *    Input: Individual values of any string 
 *   Output: N/A
 * ---------------------------------------------------------- */
void string_decoder(uint8_t* s)
{
    //string is passed
    uint8_t* c;

    c = s;
    //until EOF, send string elements to LCD_data
    while (*c != 0)
    {
        data_Write(*c);
        c++;
    }
}

/* ----------------------------------------------------------
 * Function: Will clear the display of the LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void clear_display(void)
{
    commandWrite(0x01);
    delay_ms(10);
}
/* ----------------------------------------------------------
 * Function: Will send the cursor to the home position on the
 *           LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void send_cursor_HOME(void)
{
    commandWrite(0x02);
    delay_ms(10);
}
/* ----------------------------------------------------------
 * Function: Will disable the cursor from blinking
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void setBlinkerOFF(void)
{
    commandWrite(0x0C);
}
/* ----------------------------------------------------------
 * Function: Will enable the cursor to start blinking
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void setBlinkerON(void)
{
    commandWrite(0x0F);
}
/* ----------------------------------------------------------
 * Function: Will send the cursor to a specified position on
 *           the first row
 *    Input: space the blinker should go to [0 < space < 15]
 *   Output: N/A
 * ---------------------------------------------------------- */
void setBlinkerLine1(int space)
{
    commandWrite(0x80 + space);
}
/* ----------------------------------------------------------
 * Function: Will send the cursor to a specified position on
 *           the second row
 *    Input: space the blinker should go to [0 < space < 15]
 *   Output: N/A
 * ---------------------------------------------------------- */
void setBlinkerLine2(int space)
{
    commandWrite(0xC0 + space);
}
/* ----------------------------------------------------------
 * Function: Will send the cursor to a specified position on
 *           the third row
 *    Input: space the blinker should go to [0 < space < 15]
 *   Output: N/A
 * ---------------------------------------------------------- */
void setBlinkerLine3(int space)
{
    commandWrite(0x90 + space);
}
/* ----------------------------------------------------------
 * Function: Will send the cursor to a specified position on
 *           the fourth row
 *    Input: space the blinker should go to [0 < space < 15]
 *   Output: N/A
 * ---------------------------------------------------------- */
void setBlinkerLine4(int space)
{
    commandWrite(0xD0 + space);
}
