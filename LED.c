/*
 * LED.c
 *
 *  Created on: Mar 20, 2019
 *      Author: Austin James Johnson
 */

#include "msp.h"
#include <stdint.h>
#include <stdio.h>

/*********************
 Definitions
 *********************/

#define LED_PORT P6
#define RED_LED BIT0
#define GREEN_LED BIT1


void turnRedLEDon()
{
    LED_PORT->OUT |= RED_LED;
}
void turnRedLEDoff()
{
    LED_PORT-> OUT &= ~RED_LED;
}
void turnGreenLEDon()
{
    LED_PORT-> OUT |= GREEN_LED;
}

void turnGreenLEDoff()
{
    LED_PORT-> OUT &= ~GREEN_LED;
}


void gpioInitial_LED()
{
    /*configured as GPIO */
    LED_PORT->SEL0 &= ~(RED_LED | GREEN_LED);
    LED_PORT->SEL1 &= ~(RED_LED | GREEN_LED);

    /*LEDs are outputs, set to 1 and inputs are buttons, set to 0 */

    LED_PORT->DIR |= (RED_LED | GREEN_LED);
    //Sets port pins of outputs
    LED_PORT->OUT &= ~(RED_LED | GREEN_LED);
}



