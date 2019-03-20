/*
 * Keypad.c
 *  Created on: Mar 20, 2019
 *      Author: Adan
 */

/* ----- Libraries ----- */
#include "SysTick.h"
#include "msp.h"

/* ----- Definitions ----- */
#define KEYPAD_PORT P4
#define R0 BIT0
#define R1 BIT1
#define R2 BIT2
#define R3 BIT3
#define C0 BIT4
#define C1 BIT5
#define C2 BIT6
// --------------------------
#define ONE_KEY_VALUE 1
#define TWO_KEY_VALUE 2
#define THREE_KEY_VALUE 3
#define FOUR_KEY_VALUE 4
#define FIVE_KEY_VALUE 5
#define SIX_KEY_VALUE 6
#define SEVEN_KEY_VALUE 7
#define EIGHT_KEY_VALUE 8
#define NINE_KEY_VALUE 9
#define ASTERISK_KEY_VALUE 10
#define ZERO_KEY_VALUE 11
#define POUND_KEY_VALUE 12


/* ----------------------------------------------------------
 * Function: Sets up port and pins to interface with keypad
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void Keypad_init(void)
{
    KEYPAD_PORT->SEL0 &= ~0x00; // Sets all pins in KEYPAD_PORT to GPIO
    KEYPAD_PORT->SEL1 &= ~0x00; // Sets all pins in KEYPAD_PORT to GPIO
    KEYPAD_PORT->DIR &= ~0x00; // Sets rows of the keypad as inputs
    KEYPAD_PORT->REN |= (R0 | R1 | R2 | R3); // Enables pull resistors for the rows
    KEYPAD_PORT->OUT |= (R0 | R1 | R2 | R3); // Sets the resistor as a pull-up resistor
}
/* ----------------------------------------------------------
 * Function: Will check to see if a button was pressed along with
 *           retrieving what number was pressed
 *    Input: Variable where the number pressed will be stored
 *   Output: if button is pressed return 1, else 0
 * ---------------------------------------------------------- */
uint8_t Read_Keypad(uint8_t* value)
{
    int col, row;
    for(col = 0; col < 3; col++)
    {
        KEYPAD_PORT->DIR &= 0x00; // Sets all pins as inputs
        KEYPAD_PORT->DIR |= BIT(4 + col); // Toggles on column N to check if a row is pressed in that column
        KEYPAD_PORT->OUT &= ~BIT(4 + col); // Toggles off column N in order to test the next one

        delay_ms(10); // Delays the program for 10 ms
        row = KEYPAD_PORT->IN & 0x0F; // Reads all input pins from the keypad and maps it with 0x0F to see what row was pressed

        // While the button is held down, the program won't take another reading
        while(!(KEYPAD_PORT->IN & R0) | !(KEYPAD_PORT->IN & R1) | !(KEYPAD_PORT->IN & R2) | !(KEYPAD_PORT->IN & R3));

        // If the program reads a button pressed it will get out of the for loop
        if(row != 0x0F)
        {
            break;
        }
    }
    // if column is equal to three it means that while it was cycling through each column, it read no button pressed
    if(col == 3)
    {
        return 0; // No button was pressed
    }
    // If the first row (row0)is pressed
    if(row == 0x0E)
    {
        *value = col + 1; // Obtains the value pressed using the column it read the press in
        // (i.e. if column 1 in row 0 was detected, then the value is equal to (value = 1 + 1 = 2)
    }
    // If the second row (row1)is pressed
    if(row == 0x0D)
    {
        *value = 3 + col + 1;
    }
    // If the third row (row2)is pressed
    if(row == 0x0B)
    {
        *value = 6 + col + 1;
    }
    // If the fourth row (row3)is pressed
    if(row == 0x07)
    {
        *value = 9 + col + 1;
    }

    return 1; // A button was pressed
}
