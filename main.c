/* ----- Libraries ----- */
#include "msp.h"
#include "LCD_Display.h"
#include "SysTick.h"
#include "ADC_init.h"
#include <stdint.h>
#include <stdio.h>

/* ----- Function Prototypes ----- */
void introMessage(void);
void mainMenu(void);
void soundOption(void);
void enterCreditOption(void);
void cashOut(void);
void game_screen(void);
/* ------ Public Functions ----- */
/* ----------------------------------------------------------
 * Function: Displays: "Adan P. Austin J. Slot Machine" on LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void introMessage(void)
{
    setBlinkerLine1(4);
    dataWrite('A');dataWrite('d');dataWrite('a');dataWrite('n');dataWrite(' ');dataWrite('P');dataWrite('.');

    setBlinkerLine2(4);
    dataWrite('A');dataWrite('u');dataWrite('s');dataWrite('t');dataWrite('i');dataWrite('n');dataWrite(' ');dataWrite('J');dataWrite('.');

    setBlinkerLine4(2);
    dataWrite('S');dataWrite('l');dataWrite('o');dataWrite('t');dataWrite(' ');
    dataWrite('M');dataWrite('a');dataWrite('c');dataWrite('h');dataWrite('i');dataWrite('n');dataWrite('e');
}
/* ----------------------------------------------------------
 * Function: Displays: "1- Sound  2- Enter Credits  3- Play" on LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void mainMenu(void)
{
    setBlinkerLine1(0);
    dataWrite('1'); dataWrite('-'); dataWrite(' ');
    dataWrite('S');dataWrite('o');dataWrite('u');dataWrite('n');dataWrite('d');dataWrite('s');

    setBlinkerLine2(0);
    dataWrite('2');dataWrite('-');dataWrite(' ');
    dataWrite('E');dataWrite('n');dataWrite('t');dataWrite('e');dataWrite('r');dataWrite(' ');
    dataWrite('C');dataWrite('r');dataWrite('e');dataWrite('d');dataWrite('i');dataWrite('t');dataWrite('s');

    setBlinkerLine3(0);
    dataWrite('3');dataWrite('-');dataWrite(' ');
    dataWrite('P');dataWrite('l');dataWrite('a');dataWrite('y');
}
/* ----------------------------------------------------------
 * Function: Displays: "1- Chirp  2- Siren  3- Beep" on LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void soundOption(void)
{
    setBlinkerLine1(0);
    dataWrite('1'); dataWrite('-'); dataWrite(' ');
    dataWrite('C');dataWrite('h');dataWrite('i');dataWrite('r');dataWrite('p');

    setBlinkerLine2(0);
    dataWrite('2');dataWrite('-');dataWrite(' ');
    dataWrite('S');dataWrite('i');dataWrite('r');dataWrite('e');dataWrite('n');

    setBlinkerLine3(0);
    dataWrite('3');dataWrite('-');dataWrite(' ');
    dataWrite('B');dataWrite('e');dataWrite('e');dataWrite('p');
}
/* ----------------------------------------------------------
 * Function: Displays: "Enter Credits" on LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void enterCreditOption(void)
{
    setBlinkerLine1(0);
    dataWrite('E');dataWrite('n');dataWrite('t');dataWrite('e');dataWrite('r');dataWrite(' ');
    dataWrite('C');dataWrite('r');dataWrite('e');dataWrite('d');dataWrite('i');dataWrite('t');dataWrite('s');dataWrite(':');

    setBlinkerLine2(0);
    dataWrite('*');dataWrite(' ');dataWrite('=');dataWrite(' ');dataWrite('C');dataWrite('a');dataWrite('n');dataWrite('c');dataWrite('e');dataWrite('l');

    setBlinkerLine3(0);
    dataWrite('#');dataWrite(' ');dataWrite('=');dataWrite(' ');dataWrite('A');dataWrite('c');dataWrite('c');dataWrite('e');dataWrite('p');dataWrite('t');
}
/* ----------------------------------------------------------
 * Function: Displays the message for cashout
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void cashOut(void)
{
    setBlinkerLine1(0);
    dataWrite('C');dataWrite('a');dataWrite('s');dataWrite('h');dataWrite(' ');
    dataWrite('O');dataWrite('u');dataWrite('t');dataWrite(':');

    setBlinkerLine3(0);
    dataWrite('T');dataWrite('h');dataWrite('a');dataWrite('n');dataWrite('k');dataWrite('s'); dataWrite(' ');
    dataWrite('4');dataWrite(' ');
    dataWrite('P');dataWrite('l');dataWrite('a');dataWrite('y');dataWrite('i');dataWrite('n');dataWrite('g');

    setBlinkerLine4(2);
    dataWrite('S');dataWrite('l');dataWrite('o');dataWrite('t');dataWrite(' ');
    dataWrite('M');dataWrite('a');dataWrite('c');dataWrite('h');dataWrite('i');dataWrite('n');dataWrite('e');
}
/* ----------------------------------------------------------
 * Function: Displays the message for when user has won
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void game_screen(void)
{
    setBlinkerLine1(11);
    dataWrite('W');dataWrite('I');dataWrite('N');dataWrite('!');

    setBlinkerLine3(0);
    dataWrite('C');dataWrite('R');

    setBlinkerLine3(7);
    dataWrite('M');dataWrite('e');dataWrite('n');dataWrite('u');

    setBlinkerLine3(13);
    dataWrite('B');dataWrite('e');dataWrite('t');
}
void main(void)
{
    uint8_t current = 1;
    // ----- Stop Watchdog Timer -----
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // ----- Initializing Peripherals -----
    SysTick_init_NoInt();
    LCD_init();
    ADC_init();
    /* ----- Local Variables ----- */
    uint8_t userChoiceMM = 9; // Stores what option the user picks in the main menu

    setBlinkerOFF();
    introMessage();
    delay_ms(3000);
    while(1)
    {

        switch(current)
        {
            case 1:
                clear_display();
                mainMenu();
                while (userChoiceMM == 999)
                {

                }
                break;
            case 2:
                clear_display();
                soundOption();
                break;
            case 3:
                clear_display();
                enterCreditOption();
                break;
            case 4:
                clear_display();
                cashOut();
                break;
            case 5:
                clear_display();
                game_screen();
                break;
            default:
                current = 1;
                break;
        }
    }
}
