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
#define     INC_PB BIT4
#define     DEC_PB BIT0
#define    PLAY_PB BIT1
#define CASHOUT_PB BIT7


/* 'Extern' Keyword tells compiler variable exists and the program is going to use it
 *  - But the Variable is declared somewhere else */
extern uint8_t IncPressed;
extern uint8_t DecPressed;
extern uint8_t CO_Pressed;
extern uint8_t PLAY_Pressed;
/* ----- Functions ----- */

/* ----------------------------------------------------------
 * Function: Sets up ports and pins to allow interface with
 *           the buttons
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void GPIO_Init_PB(void)
{
    /* configured as GPIO */
    PB_PORT-> SEL0 &= ~(INC_PB | DEC_PB | PLAY_PB | CASHOUT_PB);
    PB_PORT-> SEL1 &= ~(INC_PB | DEC_PB | PLAY_PB | CASHOUT_PB);
    /* Set Direction as input */
    PB_PORT->DIR &= ~(INC_PB | DEC_PB | PLAY_PB | CASHOUT_PB);
    // PB_PORT->DIR &= ~(INC_PB | DEC_PB | PLAY_PB | CASHOUT_PB);

    /* Button want to use pull up resistors*/
    PB_PORT->REN |= (INC_PB | DEC_PB | PLAY_PB | CASHOUT_PB);
    PB_PORT->OUT |= (INC_PB | DEC_PB | PLAY_PB | CASHOUT_PB);

    PB_PORT->IES &=  ~(INC_PB | DEC_PB | PLAY_PB | CASHOUT_PB); // Sets Interrupt Edge Select Register to low-to-high
    PB_PORT->IE   = 0;
    PB_PORT->IFG  = 0;

}
/* ----------------------------------------------------------
 * Function: Checks to see if the Increment button is pressed
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
 * Function: Checks to see if the Play button is pressed
 *    Input: N/A
 *   Output: true - if pressed | else, false
 * ---------------------------------------------------------- */
uint8_t Play_Pressed(void)
{
    bool checkpressed = false;

    if(!(PB_PORT->IN & PLAY_PB))

    {
        delay_ms(10);
        if(!(PB_PORT->IN & PLAY_PB))
        {
            checkpressed = true;
        }
    }
    return checkpressed;
}
/* ----------------------------------------------------------
 * Function: Checks to see if the Cashout button is pressed
 *    Input: N/A
 *   Output: true - if pressed | else, false
 * ---------------------------------------------------------- */
uint8_t CashOut_Pressed(void)
{
    bool checkpressed = false;

    if(!(PB_PORT->IN & CASHOUT_PB))

    {
        delay_ms(10);
        if(!(PB_PORT->IN & CASHOUT_PB))
        {
            checkpressed = true;
        }
    }
    return checkpressed;
}
void setInter(void)
{
   PB_PORT->IE  |=  (INC_PB | DEC_PB | PLAY_PB | CASHOUT_PB); // Enables Interrupt
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
    if(PB_PORT->IFG & CASHOUT_PB)
    {
        CO_Pressed = 1;
    }
    if(PB_PORT->IFG & PLAY_PB)
    {
        PLAY_Pressed = 1;
    }

    PB_PORT->IFG = 0;
}
