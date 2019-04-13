/*
 * Seven_Segment.c
 *
 *  Created on: Apr 12, 2019
 *      Author: Adan
 */
#include "msp.h"
#include <stdio.h>
#include <stdint.h>

#define SEG_PORT_0 P3
#define SEG_PORT_1 P1
void Segment_init(void)
{
    SEG_PORT_0->SEL0 = 0;
    SEG_PORT_0->SEL1 = 0;
    SEG_PORT_1->SEL0 = 0;
    SEG_PORT_1->SEL1 = 0;

    SEG_PORT_0->DIR = 0b11111111;
    SEG_PORT_1->DIR |= (BIT6 | BIT7);

    SEG_PORT_0->OUT = 0;
    SEG_PORT_1->OUT = 0;
}
void displayNumber(int result)
{

    if(result <= 1638)
    {
        segment(0);
    }
    else if(result > 1638 && result <= 3276)
    {
        segment(1);
    }
    else if(result > 3276 && result <= 4914)
    {
        segment(2);
    }
    else if(result > 4917 && result <= 6552)
    {
        segment(3);
    }
    else if(result > 6552 && result <= 8190)
    {
        segment(4);
    }
    else if(result > 8190 && result <= 9828)
    {
        segment(5);
    }
    else if(result > 9828 && result <= 11466)
    {
        segment(6);
    }
    else if(result > 11466 && result <= 13104)
    {
        segment(7);
    }
    else if(result > 13104 && result <= 14742)
    {
        segment(8);
    }
    else
    {
        segment(9);
    }
}
void segment(int number)
{
    switch(number)
    {
    case 0:
        SEG_PORT_0->OUT = 0b11101001;
        SEG_PORT_1->OUT |= BIT7;
        break;
    case 1:
        SEG_PORT_0->OUT = 0b10000000;
        SEG_PORT_1->OUT |= BIT7;
        break;
    case 2:
        SEG_PORT_0->OUT = 0b11101100;
        SEG_PORT_1->OUT &= ~BIT7;
        break;
    case 3:
        SEG_PORT_0->OUT = 0b11100100;
        SEG_PORT_1->OUT |= BIT7;
        break;
    case 4:
        SEG_PORT_0->OUT = 0b10000101;
        SEG_PORT_1->OUT |= BIT7;
        break;
    case 5:
        SEG_PORT_0->OUT = 0b01100101;
        SEG_PORT_1->OUT |= BIT7;
        break;
    case 6:
        SEG_PORT_0->OUT = 0b01101101;
        SEG_PORT_1->OUT |= BIT7;
        break;
    case 7:
        SEG_PORT_0->OUT = 0b11000000;
        SEG_PORT_1->OUT |= BIT7;
        break;
    case 8:
        SEG_PORT_0->OUT = 0b11101101;
        SEG_PORT_1->OUT |= BIT7;
        break;
    case 9:
        SEG_PORT_0->OUT = 0b11000101;
        SEG_PORT_1->OUT |= BIT7;
        break;
    }
}


