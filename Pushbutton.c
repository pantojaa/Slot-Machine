/*
 * Pushbutton.c
 *
 *  Created on: Mar 20, 2019
 *      Author: Austin James Johnson
 */
#include "msp.h"
#include <stdint.h>
#include <stdio.h>
#include "SysTick.h"

#define IncPB BIT0
#define DecPB BIT1
#define SpinPB BIT2
#define CashOutPB BIT3
#define PB_PORT P6

uint8_t IncreaseButtonIsPressed(void)
{
    int checkpressed = 0;
    if(!(PB_PORT->IN & IncPB))

    {
        delay_ms(10);
        if(!(PB_PORT->IN & IncPB))
        {
            checkpressed = 1;
        }
    }
    return(checkpressed);
}

uint8_t DecreasedButtonIsPressed(void)
{

    int checkpressed = 0;
    if(!(PB_PORT->IN & DecPB))
    {
        delay_ms(10);
        if(!(PB_PORT->IN & DecPB))
        {

            checkpressed = 1;
        }
    }
    return(checkpressed);
}

uint8_t SpinButtonIsPressed(void)
{
    int checkpressed = 0;
    if(!(PB_PORT->IN & SpinPB))
    {
        delay_ms(10);
        if(!(PB_PORT->IN & SpinPB))
        {

            checkpressed = 1;
        }
    }
    return(checkpressed);
}

uint8_t CashOutButtonIsPressed(void)
{

    int checkpressed = 0;
    if(!(PB_PORT->IN & CashOutPB))
    {
        delay_ms(10);
        if(!(PB_PORT->IN & CashOutPB))
        {

            checkpressed = 1;
        }
    }
    return(checkpressed);
}


void gpioInitial_PB()
{
    /*configured as GPIO */
    PB_PORT-> SEL0 &= ~(IncPB|DecPB|SpinPB|CashOutPB);
    PB_PORT-> SEL1 &= ~(IncPB|DecPB|SpinPB|CashOutPB);

    PB_PORT->DIR &= ~(IncPB|DecPB|SpinPB|CashOutPB);
    PB_PORT->DIR &= ~(IncPB|DecPB|SpinPB|CashOutPB);

    /* Button want to use pull up resistors*/

    PB_PORT->REN |= (IncPB|DecPB|SpinPB|CashOutPB);
    PB_PORT->OUT |= (IncPB|DecPB|SpinPB|CashOutPB);

}
