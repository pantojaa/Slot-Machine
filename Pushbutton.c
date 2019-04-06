/*
 * Pushbutton.c
 *
 *  Created on: Mar 20, 2019
 *      Author: Austin James Johnson
 */
#include "msp.h"
#include "SysTick.h"
#include <stdbool.h>

#define    PB_PORT P5
#define     INC_PB BIT5
#define     DEC_PB BIT1
#define    PLAY_PB BIT0
#define CASHOUT_PB BIT6


/* 'Extern' Keyword tells compiler variable exists and the program is going to use it
 *  - But the Variable is declared somewhere else */
extern uint8_t IncPressed;
extern uint8_t DecPressed;
/* ----- Functions ----- */

/* ----------------------------------------------------------
 * Function: Sets up ports and pins to allow interface with
 *           the buttons
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void GPIO_Init_PB(void)
{
    /*configured as GPIO */
    PB_PORT-> SEL0 &= ~(INC_PB|DEC_PB|PLAY_PB);
    PB_PORT-> SEL1 &= ~(INC_PB|DEC_PB|PLAY_PB);

    PB_PORT->DIR &= ~(INC_PB|DEC_PB|PLAY_PB);
    PB_PORT->DIR &= ~(INC_PB|DEC_PB|PLAY_PB);

    /* Button want to use pull up resistors*/

    PB_PORT->REN |= (INC_PB|DEC_PB|PLAY_PB);
    PB_PORT->OUT |= (INC_PB|DEC_PB|PLAY_PB);

    PB_PORT->IES &=  ~(PLAY_PB | DEC_PB); // Sets Interrupt Edge Select Register to low-to-high
    PB_PORT->IE   = 0;
    PB_PORT->IFG  = 0;

}
/* ----------------------------------------------------------
 * Function: Checks to see if the Increment button is pressed
 *           the buttons
 *    Input: N/A
 *   Output: true - if pressed | else, false
 * ---------------------------------------------------------- */
uint8_t Inc_Pressed(void)
{
    bool checkpressed = false;

    if(!(PB_PORT->IN & INC_PB))

    {
        delay_ms(10);
        if(!(PB_PORT->IN & INC_PB))
        {
            checkpressed = true;
        }
    }
    return checkpressed;
}
/* ----------------------------------------------------------
 * Function: Checks to see if the Decrement button is pressed
 *           the buttons
 *    Input: N/A
 *   Output: true - if pressed | else, false
 * ---------------------------------------------------------- */
uint8_t Dec_Pressed(void)
{
    bool checkpressed = false;

    if(!(PB_PORT->IN & DEC_PB))

    {
        delay_ms(10);
        if(!(PB_PORT->IN & DEC_PB))
        {
            checkpressed = true;
        }
    }
    return checkpressed;
}
/* ----------------------------------------------------------
 * Function: Enables the use of interrupts
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void setInter(void)
{
   PB_PORT->IE  |=  (PLAY_PB | DEC_PB | INC_PB); // Enables Interrupt
   PB_PORT->IFG  &= 0; // Clears Interrupt Flag for all bits
}

/* ----------------------------------------------------------
 * Function: Handles any interrupt caused by the buttons
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void PORT5_IRQHandler(void)
{
    if(PB_PORT->IFG & INC_PB)
    {
        IncPressed = 1;
    }
    if(PB_PORT->IFG & DEC_PB)
    {
        DecPressed = 1;
    }


    PB_PORT->IFG = 0;
}
