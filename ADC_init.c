/*
 * ADC_init.c
 *
 *  Created on: Mar 19, 2019
 *      Author: Adan
 */

/* ----- Libraries ----- */
#include "msp.h"

/* ----- Definitions ----- */
#define ADC14_PORT P5
#define ADC14_PIN BIT5

/* ----------------------------------------------------------
 * Function: Initializes the port and pin to allow the use of
 *           the built in ADC
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void ADC_Port_init(void)
{
    ADC14_PORT->SEL0 |= ADC14_PIN;
    ADC14_PORT->SEL1 |= ADC14_PIN;
}
/* ----------------------------------------------------------
 * Function: Sets up the registers of the ADC to allow for it
 *           to be used to convert an analog signal to a digital
 *           one
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void ADC_init(void)
{
    ADC14->CTL0 = 0x00000010;  // Power on and disabled during configuration
    ADC14->CTL0 |= 0x04D80300; // S/H pulse mode, MCLK, 32 sample clocks, sw trigger, /4 clock divide

    ADC14->CTL1 = 0x00000030;  // 14-bit resolution
    ADC14->MCTL[5] = 0;        // A0 input, single ended, Vref = avcc

    ADC_Port_init();

    ADC14->CTL1 |= 0x00050000; // Save to memory register 5
    ADC14->CTL0 |= 2;          // enable ADC after configuration
}
/* ----------------------------------------------------------
 * Function: Converts the analog reading into digital
 *    Input: N/A
 *   Output: Digitally converted analog value - in decimal
 * ---------------------------------------------------------- */
uint16_t convertAnalog(void)
{
    uint16_t result = 0;

    ADC14->CTL0 |= 1;
    while(!ADC14->IFGR0); // Waits for interrupt of ADC
    result = ADC14->MEM[5]; // Saves the decimal value of the voltage reading

    return result;
}
