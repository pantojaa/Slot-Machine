/*
 * TimerA_init.c
 *
 *  Created on: Mar 21, 2019
 *      Author: Adan
 */

/* ----- Libraries ----- */
#include "msp.h"

/* ----- Definitions ----- */
#define TIMERA_PORT P5
#define TIMERA_PIN BIT6
#define TIMER_A_CCTLN_OUTPUT_7 BIT3
#define TIMER_A_CTL_SSEL_SMCLK BIT9
#define TIMER_A_CTL_MC_UP BIT4
#define TIMER_A_CTL_CLR BIT2

/* ----------------------------------------------------------
 * Function: Turns off the PWM signal for Timer A2
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void turnSoundOFF(void)
{
    TIMER_A2->CTL = (TIMER_A_CTL_SSEL_SMCLK | ~TIMER_A_CTL_MC_UP | TIMER_A_CTL_CLR);
}
/* ----------------------------------------------------------
 * Function: Sends a PWM to the Piezzo Sounder to create a
 *           distinctive noise
 *    Input: Frequency of the sound converted to its period
 *   Output: N/A
 * ---------------------------------------------------------- */
void TimerA2_init(int period)
{
    TIMERA_PORT->SEL0 |= TIMERA_PIN;
    TIMERA_PORT->SEL1 &= ~TIMERA_PIN;
    TIMERA_PORT->DIR |= TIMERA_PIN;

    TIMER_A2->CCR[0] = period - 1;
    TIMER_A2->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A2->CCR[1] = (period / 2);

    TIMER_A2->CTL = (TIMER_A_CTL_SSEL_SMCLK | TIMER_A_CTL_MC_UP | TIMER_A_CTL_CLR);
}



