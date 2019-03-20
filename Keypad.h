/*
 * Keypad.h
 *
 *  Created on: Mar 20, 2019
 *      Author: Adan
 */
#include "msp.h"

#ifndef KEYPAD_H_
#define KEYPAD_H_

/* ----- Public Functions ----- */
void Keypad_init(void);
uint8_t Read_Keypad(uint8_t* value);


#endif /* KEYPAD_H_ */
