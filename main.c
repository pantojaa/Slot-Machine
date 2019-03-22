/* ----- Libraries ----- */
#include "msp.h"
#include "LCD_Display.h"
#include "SysTick.h"
#include "ADC_init.h"
#include "TimerA_init.h"
#include <stdint.h>
#include <stdio.h>

#define MAINMENU 0
#define SOUND 1
#define ENTERCREDITS 2
#define PLAY 3

#define ALARM 1
#define BEEP 2
#define RAMPUP 3
#define POUND 12
#define ASTERISK 10

/* ----- Function Prototypes ----- */
void introMessage(void);
void mainMenu(void);
void soundOption(void);
void enterCreditOption(void);
void cashOut(void);
void game_screen(void);
void invalidEntry(void);
void previewSound(int choice);
void soundBeep(void);
void soundAlarm(void);
void soundRampUp(void);

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
/* ----------------------------------------------------------
 * Function: Displays the an invalid entry message
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void invalidEntry(void)
{
    clear_display();
    setBlinkerLine1(1);
    send_string("Invalid Entry");
    setBlinkerLine2(3);
    send_string("Try Again");
    delay_ms(1500);
    clear_display();
}
/* ----------------------------------------------------------
 * Function: Displays the current sound playing
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void previewSound(int choice)
{
    setBlinkerLine1(0);
    send_string("Previewing Sound");
    setBlinkerLine2(4);

    switch(choice)
    {
    case 1:
        setBlinkerLine2(5);
        send_string("\"Alarm\"");
        setBlinkerLine4(0);
        send_string("*-Select  #-Exit");
        soundAlarm();
        break;
    case 2:
        setBlinkerLine2(5);
        send_string("\"Beep\"");
        setBlinkerLine4(0);
        send_string("*-Select  #-Exit");
        soundBeep();
        break;
    case 3:
        setBlinkerLine2(3);
        send_string("\"Ramp Up\"");
        setBlinkerLine4(0);
        send_string("*-Select  #-Exit");
        soundRampUp();
        break;
    }
}
/* ----------------------------------------------------------
 * Function: Creates a beeping noise for the Piezzo Sounder
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void soundBeep(void)
{
    TimerA2_init(12158);
    delay_ms(3000);
    turnSoundOFF();
}
/* ----------------------------------------------------------
 * Function: Creates a ramping up sound for the Piezzo Sounder
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void soundRampUp(void)
{
    TimerA2_init(30000);
    delay_ms(500);
    turnSoundOFF();
    TimerA2_init(25000);
    delay_ms(500);
    turnSoundOFF();
    TimerA2_init(20000);
    delay_ms(500);
    turnSoundOFF();
    TimerA2_init(15000);
    delay_ms(500);
    turnSoundOFF();
    TimerA2_init(10000);
    delay_ms(1000);
    turnSoundOFF();
}
/* ----------------------------------------------------------
 * Function: Creates an alarm sound for the Piezzo Sounder
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void soundAlarm(void)
{
    TimerA2_init(12158);
    delay_ms(500);
    turnSoundOFF();
    delay_ms(500);
    TimerA2_init(12158);
    delay_ms(500);
    turnSoundOFF();
    delay_ms(500);
    TimerA2_init(12158);
    delay_ms(500);
    turnSoundOFF();
    delay_ms(500);
    TimerA2_init(12158);
    delay_ms(500);
    turnSoundOFF();
    delay_ms(500);
}
void main(void)
{
    // ----- Stop Watchdog Timer -----
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // ----- Initializing Peripherals -----
    SysTick_init_NoInt();
    LCD_init();
    ADC_init();
    Keypad_init();
    /* ----- Local Variables ----- */
    int userChoiceMM = 999, // Value 999 is used as the defualt value used to reset any input
        userChoiceS  = 999, // * same as above *
        selectSound  = 999, // * same as above *
        soundPicked  = 999; // * same as above *
    int enterCredits = 999;
    int current = MAINMENU;

    setBlinkerOFF();
    introMessage();
    delay_ms(3000);
    clear_display();
    int pressed = 0;
    int value = 999;

    while(1)
    {
        switch(current)
        {
            case MAINMENU:
                clear_display();
                mainMenu();
                while(userChoiceMM == 999)
                {
                    pressed = Read_Keypad(&userChoiceMM);
                }
                if(userChoiceMM != 3 && userChoiceMM != 2 && userChoiceMM != 1)
                {
                     invalidEntry();
                     userChoiceMM = 999;
                }
                else
                {
                    current = userChoiceMM == 1 ? SOUND: userChoiceMM == 2 ? ENTERCREDITS: PLAY;
                    userChoiceMM = 999;
                }

                break;
            case SOUND:
                clear_display();
                soundOption();

                userChoiceS  = 999,
                selectSound  = 999,
                soundPicked  = 999;


                while(userChoiceS == 999)
                {
                    pressed = Read_Keypad(&userChoiceS);
                }

                if(userChoiceS != ALARM && userChoiceS != BEEP && userChoiceS != RAMPUP && userChoiceS != POUND)
                {
                     invalidEntry();
                     userChoiceS = 999;
                }
                else
                {
                    switch (userChoiceS)
                    {
                        case ALARM:
                            clear_display();
                            previewSound(1);
                            while(selectSound == 999)
                            {
                                pressed = Read_Keypad(&selectSound);
                            }

                            if(selectSound != POUND && selectSound != ASTERISK)
                            {
                                 invalidEntry();
                                 selectSound = 999;
                            }
                            else if(selectSound == POUND)
                            {
                                current = SOUND;
                                userChoiceS = 999;
                                soundPicked = 999;
                                selectSound = 999;
                            }
                            else if(selectSound == ASTERISK)
                            {
                                current = MAINMENU;
                                soundPicked = ALARM;
                            }
                            break;
                        case BEEP:
                            clear_display();
                            previewSound(2);
                            while(selectSound == 999)
                            {
                                pressed = Read_Keypad(&selectSound);
                            }

                            if(selectSound != POUND && selectSound != ASTERISK)
                            {
                                 invalidEntry();
                                 selectSound = 999;
                            }
                            else if(selectSound == POUND)
                            {
                                current = SOUND;
                                userChoiceS = 999;
                                soundPicked = 999;
                                selectSound = 999;
                            }
                            else if(selectSound == ASTERISK)
                            {
                                current = MAINMENU;
                                soundPicked = BEEP;
                            }
                            break;
                        case RAMPUP:
                            clear_display();
                            previewSound(3);
                            while(selectSound == 999)
                            {
                                pressed = Read_Keypad(&selectSound);
                            }

                            if(selectSound != POUND && selectSound != ASTERISK)
                            {
                                 invalidEntry();
                                 selectSound = 999;
                            }
                            else if(selectSound == POUND)
                            {
                                current = SOUND;
                                userChoiceS = 999;
                                soundPicked = 999;
                                selectSound = 999;
                            }
                            else if(selectSound == ASTERISK)
                            {
                                current = MAINMENU;
                                soundPicked = RAMPUP;
                            }
                            break;
                        case POUND:
                            clear_display();
                            current = MAINMENU;
                            userChoiceS = 999;
                            soundPicked = 999;
                            selectSound = 999;
                            break;
                    }
                }
                break;
            case ENTERCREDITS:
                clear_display();
                enterCreditOption();
                break;
            case PLAY:
                break;
        }
    }
}
