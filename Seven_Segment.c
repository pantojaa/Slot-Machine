#include "msp.h"
#include <stdio.h>
#include <stdint.h>

#define SEG_PORT_0 P3
#define SEG_A BIT6
#define SEG_B BIT7
#define SEG_C BIT0
#define SEG_D BIT5
#define SEG_E BIT2
#define SEG_G BIT3

#define SEG_PORT_1 P1
#define SEG_F BIT7

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
float digital_to_voltage(int digital)
{
    return (digital * 0.0002);
}
void displayNumber(int result)
{
    if(result > 1508 && result <= 3016)
    {
        segment(9);
    }
    else if(result > 3016 && result <= 4524)
    {
        segment(8);
    }
    else if(result > 4524 && result <= 6032)
    {
        segment(7);
    }
    else if(result > 6032 && result <= 7540)
    {
        segment(6);
    }
    else if(result > 7540 && result <= 9048)
    {
        segment(5);
    }
    else if(result > 9048 && result <= 10556)
    {
        segment(4);
    }
    else if(result > 10556 && result <= 12064)
    {
        segment(3);
    }
    else if(result > 12064 && result <= 13572)
    {
        segment(2);
    }
    else if(result > 13572 && result <= 15080)
    {
        segment(1);
    }
    else if(result > 15080)
    {
        segment(0);
    }
}
void segment(int number)
{
    SEG_PORT_0->OUT = 0b00000000;
    SEG_PORT_1->OUT &= ~SEG_F;

    switch(number)
    {
    case 0:
        SEG_PORT_0->OUT |= (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E);
        SEG_PORT_1->OUT |= SEG_F;
        break;
    case 1:
        SEG_PORT_0->OUT |= (SEG_B | SEG_C);
        SEG_PORT_1->OUT &= ~SEG_F;
        break;
    case 2:
        SEG_PORT_0->OUT |= (SEG_A | SEG_B | SEG_G | SEG_E | SEG_D);
        SEG_PORT_1->OUT &= ~SEG_F;
        break;
    case 3:
        SEG_PORT_0->OUT |= (SEG_A | SEG_B | SEG_G | SEG_C | SEG_D);
        SEG_PORT_1->OUT &= ~SEG_F;
        break;
    case 4:
        SEG_PORT_0->OUT |= (SEG_B | SEG_G | SEG_C);
        SEG_PORT_1->OUT |= SEG_F;
        break;
    case 5:
        SEG_PORT_0->OUT |= (SEG_A | SEG_G | SEG_C | SEG_D);
        SEG_PORT_1->OUT |= SEG_F;
        break;
    case 6:
        SEG_PORT_0->OUT |= (SEG_A | SEG_G | SEG_C | SEG_D | SEG_E);
        SEG_PORT_1->OUT |= SEG_F;
        break;
    case 7:
        SEG_PORT_0->OUT |= (SEG_A | SEG_B | SEG_C);
        SEG_PORT_1->OUT |= SEG_F;
        break;
    case 8:
        SEG_PORT_0->OUT |= (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_G);
        SEG_PORT_1->OUT |= SEG_F;
        break;
    case 9:
        SEG_PORT_0->OUT |= (SEG_A | SEG_B | SEG_C | SEG_D | SEG_G);
        SEG_PORT_1->OUT |= SEG_F;
        break;
    }
}


