
#include "msp.h"

#ifndef SYSTICK_H_
#define SYSTICK_H_

/* ----- Public Functions */
void SysTick_init_NoInt(void);
void SysTick_init_Int(void);
void delay_us(uint8_t time);
void delay_ms(uint32_t time);

#endif /* SYSTICK_H_ */

