/* ----- Libraries ----- */
#include "msp.h"
#include "LCD_Display.h"
#include "LCD_Library.h"
#include "LCD_CustomImages.h"
#include "SysTick.h"
#include "ADC_init.h"
#include "Keypad.h"
#include "TimerA_init.h"
#include "Button_Init.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


#define     MAINMENU 0
#define        SOUND 1
#define ENTERCREDITS 2
#define         PLAY 3
// ---------------------------
#define        ALARM 1
#define         BEEP 2
#define       RAMPUP 3
// ---------------------------
#define      CLEARED 999
#define      NOTHING 999
#define         ZERO 11

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
void convertToString(int credits);
int getCredits(int num_of_digits, char userCredits[]);
void displayBet(void);


/* ----- Global Variables ----- */
uint8_t Bet = 0;
uint8_t IncPressed;
uint8_t DecPressed;
uint8_t Bell_Icon;
uint8_t stickfig_Icon;
uint8_t smile_Icon;
uint8_t star_Icon;
uint8_t house_Icon;

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
    send_string("Machine");
}
/* ----------------------------------------------------------
 * Function: Displays: "1- Sound  2- Enter Credits  3- Play" on LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void mainMenu(void)
{
    setBlinkerLine1(0);
    send_string("1- Sounds ");

    setBlinkerLine2(0);
    send_string("2- Enter Credits");

    setBlinkerLine3(0);
    send_string("3- Play");
}
/* ----------------------------------------------------------
 * Function: Displays: "1- Chirp  2- Siren  3- Beep" on LCD
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void soundOption(void)
{
    setBlinkerLine1(0);
    send_string("1- Alarm");

    setBlinkerLine2(0);
    send_string("2- Beep");

    setBlinkerLine3(0);
    send_string("3- Ramp Up");

    setBlinkerLine4(4);
    send_string("#- Main Menu");


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
    send_string("Cash Out:");

    setBlinkerLine3(0);
    send_string("Thanks 4 Playing");
    setBlinkerLine4(2);
    send_string("Slot Machine");
}
/* ----------------------------------------------------------
 * Function: Displays the message for when user has won
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void game_screen(void)
{
    setBlinkerLine3(0);
    send_string("CR");

    setBlinkerLine3(7);
    send_string("Menu");
    setBlinkerLine3(13);
    send_string("Bet");

    setBlinkerLine4(8);
    send_string("*");
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
/* ----------------------------------------------------------
 * Function: Converts the total credits into an array of characters so it can be displayed onto
 *           the LCD
 *    Input: credits: total credits the user has
 *   Output: N/A
 * ---------------------------------------------------------- */
void convertToString(int credits)
{
    int temp = credits;
    int N = 0;
    int i = 0;
    char user[10] = {'0','0','0','0','0'};
    if(credits == 0)
    {
        setBlinkerLine4(0);
        dataWrite('0');
    }
    else
    {
        while(temp != 0)
        {
            temp = temp / 10;
            N++;
        }

        temp = credits;

        for(i = N - 1; i >= 0; i--)
        {
            user[i] = (temp % 10) + '0';
            temp = temp / 10;
        }

        setBlinkerLine4(0);

        for(i = 0; i < N; i++)
        {
            dataWrite(user[i]);
        }
    }
}
/* ----------------------------------------------------------
 * Function: Takes the character array of values the user entered for credits and
 *           converts it into an integer value
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
int getCredits(int num_of_digits, char userCredits[])
{
    static int credits = 0;

    switch(num_of_digits)
    {
        case 0:
            credits = credits;
            break;
        case 1:
            credits = ( (int)userCredits[0] - 48 ) + credits;
            break;
        case 2:
            credits = ( ( (int)userCredits[0] - 48 ) * 10 ) + ( (int)userCredits[1] - 48 ) + credits;
            break;
        case 3:
            credits = ( ( (int)userCredits[0] - 48 ) * 100 )  + ( ( (int)userCredits[1] - 48 ) * 10 ) + ( (int)userCredits[2] - 48 ) + credits;
            break;
    }

    return credits;
}
/* ----------------------------------------------------------
 * Function: Will display the Bet value onto the LCD screen
 *    Input: N/A
 *   Output: N/A
 * ---------------------------------------------------------- */
void displayBet(void)
{
    int temp = Bet;
    int N = 0;
    int i = 0;
    char user[10] = {'0','0','0','0','0'};

    if(Bet == 0)
    {
        setBlinkerLine4(15);
        dataWrite('0');
    }
    else
    {
        while(temp != 0)
        {
            temp = temp / 10;
            N++;
        }

        temp = Bet;

        for(i = N - 1; i >= 0; i--)
        {
            user[i] = (temp % 10) + '0';
            temp = temp / 10;
        }

        if(N == 1)
        {
            setBlinkerLine4(14);
            dataWrite(' ');
            for(i = 0; i < N; i++)
            {
                dataWrite(user[i]);
            }
        }
        else
        setBlinkerLine4(14);

        for(i = 0; i < N; i++)
        {
            dataWrite(user[i]);
        }
    }
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
    GPIO_Init_PB();
    lcdInit();

    NVIC_EnableIRQ(PORT5_IRQn);
    __enable_interrupt();

    /* ----- Local Variables ----- */
    int     UI_MainMenu = CLEARED, // Holds the option the user chooses from the main menu (U.I -> User Input)
              UI_Sound  = CLEARED, // Holds the option the user chooses from the sound menu (U.I -> User Input)
           Accept_Sound = CLEARED, // Holds the option the user chooses for the sound (U.I -> User Input)
        Sound_Selected  = NOTHING; // Stores the sound the user chose
    int enterCredits = CLEARED; // Holds the value for credits the user picks
    char userCredits[] = {'0', '0', '0'}; // Array that stores the value chosen for credits so it can be displayed onto the LCD
    int credits = 0; // Stores the number of credits the user has
    int num_of_digits = 0; // Used as a dummy variable
    int current = MAINMENU; // Stores the current state of the program
    int pressed = 0;

    /* Obtaining special characters */
    Bell_Icon = lcdCreateCustomChar(&bell_layout);
    stickfig_Icon = lcdCreateCustomChar(&stickfig_layout);
    smile_Icon = lcdCreateCustomChar(&smile_layout);
    star_Icon = lcdCreateCustomChar(&star_layout);
    house_Icon = lcdCreateCustomChar(&house_layout);

    setBlinkerOFF();
     introMessage();
     delay_ms(3000);
    clear_display();

    while(1)
    {
        switch(current)
        {
            case MAINMENU:
                clear_display();
                mainMenu();
                // Checks to see if keypad was pressed
                pressed = Read_Keypad();
                // Waits for the user to press something
                while(pressed == false)
                {
                    pressed = Read_Keypad();
                    UI_MainMenu = getKeyPressed();
                }
                // Displayed if attempting to select something that is not 1, 2, or 3
                if(UI_MainMenu != 3 && UI_MainMenu != 2 && UI_MainMenu != 1)
                {
                     invalidEntry();
                     UI_MainMenu = CLEARED;
                }
                else
                {
                    if(UI_MainMenu == 1)
                    {
                        current = SOUND;
                    }
                    else if(UI_MainMenu == 2)
                    {
                        current = ENTERCREDITS;
                    }
                    else
                    {
                        current = PLAY;
                    }

                    UI_MainMenu = CLEARED;
                }

                break;
            case SOUND:
                clear_display();
                soundOption();

                UI_Sound  = CLEARED,
                Accept_Sound  = CLEARED,
                Sound_Selected  = CLEARED;

                // Checks to see if keypad was pressed
                pressed = Read_Keypad();
                // Waits for the user to press something
                while(pressed == false)
                {
                    pressed = Read_Keypad();
                    UI_Sound = getKeyPressed();
                }

                if(UI_Sound != ALARM && UI_Sound != BEEP && UI_Sound != RAMPUP && UI_Sound != POUND)
                {
                     invalidEntry();
                     UI_Sound = CLEARED;
                }
                else
                {
                    switch (UI_Sound)
                    {
                        case ALARM:
                            clear_display();
                            previewSound(ALARM);
                            // Checks to see if keypad was pressed
                            pressed = Read_Keypad();
                            // Waits for the user to press something
                            while(pressed == false)
                            {
                                pressed = Read_Keypad();
                                Accept_Sound = getKeyPressed();
                            }

                            if(Accept_Sound != POUND && Accept_Sound != ASTERISK)
                            {
                                 invalidEntry();
                                 Accept_Sound = CLEARED;
                            }
                            else if(Accept_Sound == POUND)
                            {
                                       current = SOUND;
                                      UI_Sound = CLEARED;
                                Sound_Selected = NOTHING;
                                  Accept_Sound = CLEARED;
                            }
                            else if(Accept_Sound == ASTERISK)
                            {
                                       current = MAINMENU;
                                Sound_Selected = ALARM;
                            }
                            break;

                        case BEEP:
                            clear_display();
                            previewSound(ALARM);
                            // Checks to see if keypad was pressed
                            pressed = Read_Keypad();
                            // Waits for the user to press something
                            while(pressed == false)
                            {
                                pressed = Read_Keypad();
                                Accept_Sound = getKeyPressed();
                            }

                            if(Accept_Sound != POUND && Accept_Sound != ASTERISK)
                            {
                                 invalidEntry();
                                 Accept_Sound = CLEARED;
                            }
                            else if(Accept_Sound == POUND)
                            {
                                current = SOUND;
                                UI_Sound = CLEARED;
                                Sound_Selected = CLEARED;
                                Accept_Sound = CLEARED;
                            }
                            else if(Accept_Sound == ASTERISK)
                            {
                                current = MAINMENU;
                                Sound_Selected = BEEP;
                            }
                            break;

                        case RAMPUP:
                            clear_display();
                            previewSound(RAMPUP);
                            // Checks to see if keypad was pressed
                            pressed = Read_Keypad();
                            // Waits for the user to press something
                            while(pressed == false)
                            {
                                pressed = Read_Keypad();
                                Accept_Sound = getKeyPressed();
                            }

                            if(Accept_Sound != POUND && Accept_Sound != ASTERISK)
                            {
                                 invalidEntry();
                                 Accept_Sound = CLEARED;
                            }
                            else if(Accept_Sound == POUND)
                            {
                                       current = SOUND;
                                      UI_Sound = CLEARED;
                                Sound_Selected = NOTHING;
                                  Accept_Sound = CLEARED;
                            }
                            else if(Accept_Sound == ASTERISK)
                            {
                                current = MAINMENU;
                                Sound_Selected = RAMPUP;
                            }
                            break;

                        case POUND:
                            clear_display();
                            current = MAINMENU;
                            UI_Sound = CLEARED;
                            Sound_Selected = CLEARED;
                            Accept_Sound = CLEARED;
                            break;
                    }
                }
                break;

            case ENTERCREDITS:
                clear_display();
                enterCreditOption();
                setBlinkerLine4(0);
                setBlinkerON();
                int i = 0;
                while(enterCredits == CLEARED)
                {
                    for(i = 0; i < 3; i++)
                    {
                        // Checks to see if keypad was pressed
                        pressed = Read_Keypad();
                        // Waits for the user to press something
                        while(pressed == false)
                        {
                            pressed = Read_Keypad();
                            enterCredits = getKeyPressed();
                        }

                        if(enterCredits == ASTERISK || enterCredits == POUND)
                        {
                            break;
                        }
                        else if(num_of_digits < 3)
                        {
                            if(enterCredits ==  ZERO)
                            {
                                userCredits[i] = '0';
                                dataWrite(userCredits[i]);
                                num_of_digits++;
                            }
                            else
                            {
                                userCredits[i] = enterCredits + '0';
                                dataWrite(userCredits[i]);
                                num_of_digits++;
                            }
                        }
                        enterCredits = CLEARED;
                    }

                    if(enterCredits == ASTERISK || enterCredits == POUND)
                    {
                        enterCredits = CLEARED;
                        current = MAINMENU;
                        setBlinkerOFF();
                        break;
                    }
                }

                // Converts the array of characters into an actual value for credits
                credits = getCredits(num_of_digits, userCredits);

                // Resets the number of digits entered
                num_of_digits = 0;
                break;
            case PLAY:
                Bet = 0; // Resets the current bet
                setInter();
                clear_display();
                game_screen();
                setBlinkerLine4(0);
                convertToString(credits);
                displayBet();
                pressed = Read_Keypad();
                uint8_t Bell_Icon = lcdCreateCustomChar(&bell_layout);
                uint8_t stickfig_Icon = lcdCreateCustomChar(&stickfig_layout);
                uint8_t smile_Icon = lcdCreateCustomChar(&smile_layout);
                uint8_t star_Icon = lcdCreateCustomChar(&star_layout);
                uint8_t house_Icon = lcdCreateCustomChar(&house_layout);
                lcdSetChar(Bell_Icon, 5, 0);
                lcdSetChar(stickfig_Icon, 6, 0);
                lcdSetChar(smile_Icon, 7, 0);
                lcdSetChar(star_Icon, 8, 0);
                lcdSetChar(house_Icon, 5, 1);
                lcdSetChar(house_Icon, 6, 1);
                lcdSetChar(house_Icon, 7, 1);
                lcdSetChar(house_Icon, 8, 1);
                while(pressed == false)
                {
                    displayBet();
                    if(IncPressed == true && Inc_Pressed() == true && Bet < 5)
                    {
                        if(Bet < credits)
                            Bet++;
                        IncPressed = false;
                    }
                    if(DecPressed == true && Dec_Pressed() == true && Bet > 0)
                    {
                        Bet--;
                        DecPressed = false;
                    }
                    pressed = Read_Keypad();
                    UI_MainMenu = getKeyPressed();
                }

                if(UI_MainMenu == ASTERISK)
                {
                    enterCredits = CLEARED;
                    current = MAINMENU;
                }
                break;

        }
    }
}
