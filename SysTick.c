#include "msp.h"

/* ----------------------------------------------------------
 * Function: Initializes the SysTick timer with no interrupt
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void SysTick_init_NoInt(void)
{
    SysTick->CTRL = 0; // Disables clock
    SysTick->LOAD = 0x00FFFFFF; // Sets the load value to MAX
    SysTick->VAL  = 0; // Resets count
    SysTick->CTRL = 0x00000005; // Enables clock, sets bus
}
/* ----------------------------------------------------------
 * Function: Initializes the SysTick timer with interrupt
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void SysTick_init_Int(void)
{
    SysTick->CTRL = 0; // Disables clock
    SysTick->LOAD = 0x00FFFFFF; // Sets the load value to MAX
    SysTick->VAL  = 0; // Resets count
    SysTick->CTRL = 0x00000007; // Enables clock, sets bus
}
/* ----------------------------------------------------------
 * Function: Delays the program for a set time in microseconds
 *    Input: time - number of microseconds to pause the program
 *   Output: N/A
 * ---------------------------------------------------------- */
void delay_us(uint8_t time)
{
    SysTick->LOAD = (time * 3) - 1;
    SysTick->VAL  = 0;
    while( (SysTick->CTRL & 0x00010000) == 0);
}
/* ----------------------------------------------------------
 * Function: Delays the program for a set time in milliseconds
 *    Input: time - number of milliseconds to pause the program
 *   Output: N/A
 * ---------------------------------------------------------- */
void delay_ms(uint32_t time)
{
    SysTick->LOAD = (time * 3000) - 1;
    SysTick->VAL  = 0;
    while( (SysTick->CTRL & 0x00010000) == 0);
}



