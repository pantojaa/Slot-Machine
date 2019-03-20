/*
 * LCD_Display.h
 *
 *  Created on: Mar 17, 2019
 *      Author: Adan
 */
#include "msp.h"

#ifndef LCD_DISPLAY_H_
#define LCD_DISPLAY_H_

/* ----- Public Functions ----- */
void LCD_init(void);
void commandWrite(uint8_t command);
void dataWrite(uint8_t data);
void string_decoder(uint8_t* s);
void send_string(uint8_t *s);
void clear_display(void);
void send_cursor_HOME(void);
void setBlinkerOFF(void);
void setBlinkerON(void);
void setBlinkerLine1(int space);
void setBlinkerLine2(int space);
void setBlinkerLine3(int space);
void setBlinkerLine4(int space);

#endif /* LCD_DISPLAY_H_ */

