/*
 * PushButton.h
 *
 *  Created on: Mar 20, 2019
 *      Author: Austin James Johnson
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

 void GPIO_Init_PB(void);
 int PlayButtonIsPressed(void);
 uint8_t Dec_Pressed(void);
 uint8_t Inc_Pressed(void);
 void setInter(void);


#endif /* PUSHBUTTON_H_ */
