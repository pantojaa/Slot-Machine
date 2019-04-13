/* ----- Libraries ----- */
#include "msp.h"
#include "LCD_Display.h"
#include "LCD_Library.h"
#include "LCD_CustomImages.h"
#include "Seven_Segment.h"
#include "SysTick.h"
#include "ADC_init.h"
#include "Keypad.h"
#include "TimerA_init.h"
#include "Timer32_init.h"
#include "Button_Init.h"
#include "LED.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define     MAINMENU 0
#define        SOUND 1
#define ENTERCREDITS 2
#define         PLAY 3
#define      CASHOUT 4
// ---------------------------
#define        ALARM 1
#define         BEEP 2
#define       RAMPUP 3
// ---------------------------
#define      CLEARED 999
#define      NOTHING 999
#define         ZERO 11
// --------------------------
#define         BELL 1
#define     STICKFIG 2
#define        SMILE 3
#define         STAR 4
#define        HOUSE 5
// -------------------------
#define FIVE_SECONDS 34

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
void convertToString(void);
int getCredits(int num_of_digits, char userCredits[]);
void displayBet(void);


/* ----- Global Variables ----- */
uint8_t current;
uint8_t Bet;
int credits;
uint8_t Spinning = false;
uint8_t Total_Wins = 0;
int Pot_Value;
int top_reel[] = {1, 2, 3, 4};
int bottom_reel[] = {1, 2, 3, 4};
volatile uint8_t IncPressed;
volatile uint8_t DecPressed;
volatile uint8_t CO_Pressed;
volatile uint8_t PLAY_Pressed;
uint8_t bell_Icon;
uint8_t stickfig_Icon;
uint8_t smile_Icon;
uint8_t star_Icon;
uint8_t house_Icon;
volatile int Test;
volatile int wait;
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
void convertToString(void)
{
    int temp = credits;
    int N = 0;
    int i = 0;
    char user[10] = {'0','0','0','0','0'};
    if(credits == 0)
    {
        if(current == PLAY)
        {
            setBlinkerLine4(0);
        }
        else
        {
            setBlinkerLine1(10);
        }
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
        // Location where to display the credits
        if(current == PLAY)
        {
            setBlinkerLine4(0);
            send_string("    ");
            setBlinkerLine4(0);
        }
        else
        {
            setBlinkerLine1(10);
            send_string("    ");
            setBlinkerLine1(10);
        }

        for(i = 0; i < N; i++)
        {
            dataWrite(user[i]);
        }

/*        if(credits < 1000 && current == PLAY)
        {
            setBlinkerLine4(3);
            dataWrite(' ');
        }*/
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

void Top_reel(int a, int b, int c, int d)
{
    switch(a)
    {
        case 1:
            lcdSetChar(bell_Icon, 5, 0);
            top_reel[0] = BELL;
            break;
        case 2:
            lcdSetChar(star_Icon, 5, 0);
            top_reel[0] = STAR;
            break;
        case 3:
            lcdSetChar(stickfig_Icon, 5, 0);
            top_reel[0] = STICKFIG;
            break;
        case 4:
            lcdSetChar(smile_Icon, 5, 0);
            top_reel[0] = SMILE;
            break;
        case 5:
            lcdSetChar(house_Icon, 5, 0);
            top_reel[0] = HOUSE;
            break;
    }
    switch(b)
    {
        case 1:
            lcdSetChar(bell_Icon, 6, 0);
            top_reel[1] = BELL;
            break;
        case 2:
            lcdSetChar(star_Icon, 6, 0);
            top_reel[1] = STAR;
            break;
        case 3:
            lcdSetChar(stickfig_Icon, 6, 0);
            top_reel[1] = STICKFIG;
            break;
        case 4:
            lcdSetChar(smile_Icon, 6, 0);
            top_reel[1] = SMILE;
            break;
        case 5:
            lcdSetChar(house_Icon, 6, 0);
            top_reel[1] = HOUSE;
            break;
    }

    switch(c)
    {
        case 1:
            lcdSetChar(bell_Icon, 7, 0);
            top_reel[2] = BELL;
            break;
        case 2:
            lcdSetChar(star_Icon, 7, 0);
            top_reel[2] = STAR;
            break;
        case 3:
            lcdSetChar(stickfig_Icon, 7, 0);
            top_reel[2] = STICKFIG;
            break;
        case 4:
            lcdSetChar(smile_Icon, 7, 0);
            top_reel[2] = SMILE;
            break;
        case 5:
            lcdSetChar(house_Icon, 7, 0);
            top_reel[2] = HOUSE;
            break;
    }

    switch(d)
    {
        case 1:
            lcdSetChar(bell_Icon, 8, 0);
            top_reel[3] = BELL;
            break;
        case 2:
            lcdSetChar(star_Icon, 8, 0);
            top_reel[3] = STAR;
            break;
        case 3:
            lcdSetChar(stickfig_Icon, 8, 0);
            top_reel[3] = STICKFIG;
            break;
        case 4:
            lcdSetChar(smile_Icon, 8, 0);
            top_reel[3] = SMILE;
            break;
        case 5:
            lcdSetChar(house_Icon, 8, 0);
            top_reel[3] = HOUSE;
            break;
    }
}
void Bottom_reel(int a, int b, int c, int d)
{
    switch(a)
    {
        case 1:
            lcdSetChar(house_Icon, 5, 1);
            bottom_reel[0] = HOUSE;
            break;
        case 2:
            lcdSetChar(smile_Icon, 5, 1);
            bottom_reel[0] = SMILE;
            break;
        case 3:
            lcdSetChar(bell_Icon, 5, 1);
            bottom_reel[0] = BELL;
            break;
        case 4:
            lcdSetChar(star_Icon, 5, 1);
            bottom_reel[0] = STAR;
            break;
        case 5:
            lcdSetChar(stickfig_Icon, 5, 1);
            bottom_reel[0] = STICKFIG;
            break;
    }
    switch(b)
    {
        case 1:
            lcdSetChar(house_Icon, 6, 1);
            bottom_reel[1] = HOUSE;
            break;
        case 2:
            lcdSetChar(smile_Icon, 6, 1);
            bottom_reel[1] = SMILE;
            break;
        case 3:
            lcdSetChar(bell_Icon, 6, 1);
            bottom_reel[1] = BELL;
            break;
        case 4:
            lcdSetChar(star_Icon, 6, 1);
            bottom_reel[1] = STAR;
            break;
        case 5:
            lcdSetChar(stickfig_Icon, 6, 1);
            bottom_reel[1] = STICKFIG;
            break;
    }

    switch(c)
    {
        case 1:
            lcdSetChar(house_Icon, 7, 1);
            bottom_reel[2] = HOUSE;
            break;
        case 2:
            lcdSetChar(smile_Icon, 7, 1);
            bottom_reel[2] = SMILE;
            break;
        case 3:
            lcdSetChar(bell_Icon, 7, 1);
            bottom_reel[2] = BELL;
            break;
        case 4:
            lcdSetChar(star_Icon, 7, 1);
            bottom_reel[2] = STAR;
            break;
        case 5:
            lcdSetChar(stickfig_Icon, 7, 1);
            bottom_reel[2] = STICKFIG;
            break;
    }

    switch(d)
    {
        case 1:
            lcdSetChar(house_Icon, 8, 1);
            bottom_reel[3] = HOUSE;
            break;
        case 2:
            lcdSetChar(smile_Icon, 8, 1);
            bottom_reel[3] = SMILE;
            break;
        case 3:
            lcdSetChar(bell_Icon, 8, 1);
            bottom_reel[3] = BELL;
            break;
        case 4:
            lcdSetChar(star_Icon, 8, 1);
            bottom_reel[3] = STAR;
            break;
        case 5:
            lcdSetChar(stickfig_Icon, 8, 1);
            bottom_reel[3] = STICKFIG;
            break;
    }
}

int checkTopWin(void)
{
    int same = 0, // Holds the number of reels that are the same
           j = 0; // Control variable for 'for' loop

    // Checks characters to see if all match
    for (j = 0; j < 3; j++)
    {
        if (top_reel[j] == top_reel[j + 1])
        {
            same++;
        }
    }

    // If all characters match
    if(same == 3)
    {
        return true;
    }
    else
        return false;
}
int checkBottomWin(void)
{
    int same = 0, // Holds the number of reels that are the same
           j = 0; // Control variable for 'for' loop

    // Checks characters to see if all match
    for (j = 0; j < 3; j++)
    {
        if (bottom_reel[j] == bottom_reel[j + 1])
        {
            same++;
        }
    }

    // If all characters match
    if(same == 3)
    {
        return true;
    }
    else
        return false;
}

void start_reel(void)
{
    lcdSetChar(stickfig_Icon, 5, 0);
    lcdSetChar(bell_Icon, 6, 0);
    lcdSetChar(star_Icon, 7, 0);
    lcdSetChar(house_Icon, 8, 0);
    lcdSetChar(stickfig_Icon, 5, 1);
    lcdSetChar(bell_Icon, 6, 1);
    lcdSetChar(star_Icon, 7, 1);
    lcdSetChar(house_Icon, 8, 1);
}

void display_Top_Win()
{
    setBlinkerLine1(11);
    send_string("WIN!");
}
void display_Bottom_Win()
{
    setBlinkerLine2(11);
    send_string("WIN!");
}

void noCredits(void)
{
    clear_display();
    setBlinkerLine1(0);
    send_string("You do not have");
    setBlinkerLine2(0);
    send_string("enough credits");
    delay_ms(3000);
}
void clearWin(void)
{
    setBlinkerLine1(11);
    send_string("    ");
    setBlinkerLine2(11);
    send_string("    ");
}
void playSound(int sound)
{
    switch(sound)
    {
    case ALARM:
        soundAlarm();
        break;
    case BEEP:
        soundBeep();
        break;
    case RAMPUP:
        soundRampUp();
        break;
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
    Timer32_init();
    gpioInitial_LED();
    Segment_init();

    NVIC_EnableIRQ(T32_INT2_IRQn);
    NVIC_EnableIRQ(PORT5_IRQn);
    __enable_interrupt();
    // ----- Local Variables -----
    int     UI_MainMenu = CLEARED, // Holds the option the user chooses from the main menu (U.I -> User Input)
              UI_Sound  = CLEARED, // Holds the option the user chooses from the sound menu (U.I -> User Input)
               UI_Play  = CLEARED,
           Accept_Sound = CLEARED, // Holds the option the user chooses for the sound (U.I -> User Input)
        Sound_Selected  = ALARM; // Stores the sound the user chose
    int enterCredits = CLEARED; // Holds the value for credits the user picks
    char userCredits[] = {'0', '0', '0'}; // Array that stores the value chosen for credits so it can be displayed onto the LCD // Stores the number of credits the user has
    int num_of_digits = 0; // Used as a dummy variable
    int pressed = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    int g = 0;
    int h = 0;
    // Obtaining special characters
    bell_Icon = lcdCreateCustomChar(&bell_layout);
    stickfig_Icon = lcdCreateCustomChar(&stickfig_layout);
    smile_Icon = lcdCreateCustomChar(&smile_layout);
    star_Icon = lcdCreateCustomChar(&star_layout);
    house_Icon = lcdCreateCustomChar(&house_layout);
    // Stores the current state of the program
    current = MAINMENU;

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
                    Pot_Value = convertAnalog();
                    displayNumber(Pot_Value);

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
                    else if(UI_MainMenu == 3 && credits == 0)
                    {
                        noCredits();
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
                            previewSound(BEEP);
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
                        if(enterCredits == ASTERISK)
                        {
                            int a = 0;

                            for(a = 0; a < 4; a++)
                            {
                                userCredits[a] = '0';
                            }
                        }
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
                for(a = 0; a < 4; a++)
                {
                    userCredits[a] = '0';
                }
                break;
            case PLAY:
                Bet = 0; // Resets the current bet
                setInter();
                clear_display();
                game_screen();
                setBlinkerLine4(0);
                convertToString();
                displayBet();
                start_reel();
                pressed = Read_Keypad();
                TIMER32_2->CONTROL = 0b11000011;
                Test = 999;
                while(pressed == false)
                {

                    displayBet();
                    if(IncPressed == true && Inc_Pressed() == true && Bet < 5 && Spinning == false)
                    {
                        if(Bet < credits)
                        {
                            Bet++;
                        }
                        IncPressed = false;
                    }
                    if(DecPressed == true && Dec_Pressed() == true && Bet > 0 && Spinning == false)
                    {
                        Bet--;
                        DecPressed = false;
                    }
                    if(CO_Pressed == true && CashOut_Pressed() == true && Spinning == false)
                    {
                        current = CASHOUT;
                        break;
                    }

                    if(Test == 1)
                    {
                        a = rand() % (5 + 1 - 1) + 1;
                        b = rand() % (5 + 1 - 1) + 1;
                        c = rand() % (5 + 1 - 1) + 1;
                        d = rand() % (5 + 1 - 1) + 1;
                        e = rand() % (5 + 1 - 1) + 1;
                        f = rand() % (5 + 1 - 1) + 1;
                        g = rand() % (5 + 1 - 1) + 1;
                        h = rand() % (5 + 1 - 1) + 1;

                        Test = 0;
                    }
                    Top_reel(a, b, c, d);
                    Bottom_reel(e, f, g, h);

                    // Spins the reel for 5 seconds
                    if(wait == FIVE_SECONDS && Test != CLEARED)
                    {
                        TIMER32_2->CONTROL = 0b11000011; // Stops the reel
                        Test = 999;
                        wait = 0;
                        Spinning = false;
                        if(credits == 999)
                        {
                            // Forces the reel to display winning characters
                            a = 1; b = 1; c = 1; d = 1;
                            e = 3; f = 3; g = 3; h = 3;
                            Top_reel(a, b, c, d);
                            Bottom_reel(e, f, g, h);
                        }

                        if(checkTopWin())
                        {
                            display_Top_Win();
                            turnGreenLEDon();
                            Total_Wins = Total_Wins + 1;
                            playSound(Sound_Selected);
                        }

                       if(checkBottomWin())
                       {
                           display_Bottom_Win();
                           turnGreenLEDon();
                           playSound(Sound_Selected);
                           Total_Wins = Total_Wins + 1;
                       }
                       else
                       {
                           credits -= Bet;
                           turnRedLEDon();
                           Bet = 0;
                       }

                       if(Total_Wins == 1)
                       {
                           credits = credits + Bet;
                           Bet = 0; // Clears the Bet
                           Total_Wins = 0; // Clears total wins
                       }
                       else if(Total_Wins == 2)
                       {
                           credits = credits + (2 * Bet);
                           Bet = 0; // Clears the Bet
                           Total_Wins = 0; // Clears total wins
                       }

                       convertToString();
                       displayBet();

                       wait = 0;
                   }
                   // If the 'Play' button is pressed before the 5 seconds are over
                   else if(PLAY_Pressed == true && Play_Pressed() == true && Test != 999)
                   {
                       TIMER32_2->CONTROL = 0b11000011; // Stops the reel
                       Test = 999;
                       PLAY_Pressed = 0;
                       wait = 0;
                       Spinning = false;
                       if(credits == 999)
                       {
                           // Forces the reel to display winning characters
                           Top_reel(1,1,1,1);
                           Bottom_reel(2, 2, 2, 2);
                       }

                       if(checkTopWin())
                       {
                           display_Top_Win();
                           turnGreenLEDon();
                           Total_Wins = Total_Wins + 1;
                           playSound(Sound_Selected);
                       }

                       if(checkBottomWin())
                       {
                           display_Bottom_Win();
                           turnGreenLEDon();
                           playSound(Sound_Selected);
                           Total_Wins = Total_Wins + 1;
                       }
                       else
                       {
                           credits -= Bet;
                           turnRedLEDon();
                           Bet = 0;
                       }

                       if(Total_Wins == 1)
                       {
                           credits = credits + Bet;
                           Bet = 0; // Clears the Bet
                           Total_Wins = 0; // Clears total wins
                       }
                       else if(Total_Wins == 2)
                       {
                           credits = credits + (2 * Bet);
                           Bet = 0; // Clears the Bet
                           Total_Wins = 0; // Clears total wins
                       }

                       convertToString();
                       displayBet();

                       wait = 0;


                   }

                   // -- Allows the reel to begin to spin --
                   if(PLAY_Pressed == true && Play_Pressed() == true && Test == 999 && Bet > 0)
                   {
                       TIMER32_2->CONTROL = 0b11100011; // Starts the reel
                       Test = 0;
                       PLAY_Pressed = 0;
                       clearWin();
                       turnRedLEDoff();
                       turnGreenLEDoff();
                       Spinning = true;
                   }

                   pressed = Read_Keypad();
                   UI_Play = getKeyPressed();

                }
                if(UI_Play == ASTERISK)
                {
                    enterCredits = CLEARED;
                    current = MAINMENU;
                }


                break;
            case CASHOUT:
                clear_display();
                cashOut();
                turnRedLEDoff();
                turnGreenLEDoff();
                setBlinkerLine1(10);
                convertToString();
                delay_ms(5000);
                credits = 0;
                Bet = 0;
                current = MAINMENU;
                break;

        }
    }
}
