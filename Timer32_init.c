/*
 * Timer32_init.c
 *
 *  Created on: Apr 11, 2019
 *      Author: Adan
 */
#include "msp.h"
extern int Test;
extern int wait;
void Timer32_init(void)
{
    TIMER32_2->CONTROL = 0b11000011;
    TIMER32_2->LOAD = 450000;
}

void T32_INT2_IRQHandler(void)
{
    Test = 1;
    wait++;
    TIMER32_2->INTCLR = 1;
    TIMER32_2->LOAD = 450000;
}

