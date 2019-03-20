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
    send_string("Adan");

    setBlinkerLine2(4);
    send_string("Austin");

    setBlinkerLine4(2);
    send_string("Slot ");
    send_string("Machine "); 
}
/* ----------------------------------------------------------
 * Function: Displays: "1- Sound  2- Enter Credits  3- Play" on LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void mainMenu(void)
{
    setBlinkerLine1(0);
    send_string("1 - Sounds "); 
    
    setBlinkerLine2(0);
    send_string("Enter Credits");

    setBlinkerLine3(0);
    send_string("Play");
}
/* ----------------------------------------------------------
 * Function: Displays: "1- Chirp  2- Siren  3- Beep" on LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void soundOption(void)
{
    setBlinkerLine1(0);
    send_string("1 - Chirp")
    
    setBlinkerLine2(0);
    send_string("2- Beep"); 

    setBlinkerLine3(0);
    send_string("3 - Siren"); 
}
/* ----------------------------------------------------------
 * Function: Displays: "Enter Credits" on LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void enterCreditOption(void)
{
    setBlinkerLine1(0);
    send_string("Enter Credits");
    setBlinkerLine2(0);
    send_string("* = Cancel");

    setBlinkerLine3(0);
    send_string("# = Accept");
}
/* ----------------------------------------------------------
 * Function: Displays the message for cashout
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void cashOut(void)
{
    setBlinkerLine1(0);
    send_string("Cash Out:")

    setBlinkerLine3(0);
    send_string("Thanks 4 Playing");
    setBlinkerLine4(2);
    send_string("Slot Machine");
/* ----------------------------------------------------------
 * Function: Displays the message for when user has won
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void game_screen(void)
{
    setBlinkerLine1(11);
    send_string("WIN!")

    setBlinkerLine3(0);
    send_string("CR");

    setBlinkerLine3(7);
    send_string("Menu");
    setBlinkerLine3(13);
    send_string("Bet");
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
