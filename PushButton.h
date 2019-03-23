/*
 * PushButton.h
 *
 *  Created on: Mar 20, 2019
 *      Author: Austin James Johnson
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

uint8_t IncreaseButtonIsPressed(void);
uint8_t DecreasedButtonIsPressed(void);
uint8_t SpinButtonIsPressed(void);
uint8_t CashOutButtonIsPressed(void);
void gpioInitial_PB();


#endif /* PUSHBUTTON_H_ */
