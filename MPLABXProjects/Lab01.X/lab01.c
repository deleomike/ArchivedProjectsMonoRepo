//------------------------------------------------------------------------------
// File:          main.c
// Written By:    E.G. Walters
// Date Created:  16 Jan 18
// Description:   Program to simulate rolling a die
// Compiler:	  XC8 v1.33
// Target:        PIC16F1709
// Schematic(s):  Drawing L01-11
//
// Revision History (date, initials, description)
//  16 Jan 18, egw100, Initial version
//------------------------------------------------------------------------------

// Includes
#include <xc.h>
#include <stdint.h>
#include "lab01.h"

//------------------------------------------------------------------------------
// Function: main()
//------------------------------------------------------------------------------
void main(void) {

    uint8_t dieValue = 1;  // value of die, always 1..6

    initialize();   //set all the variables for LED, ANSEL, 

    while(1) {

        // Check On/Off Switch
        if (ONOFF_SW == 1) {

            if (ROLL_PB == 1){  //button is pressed
                dieValue++; //increment dievalue
                reset();   //turns off lights
                if (dieValue == 7)  //die value is 7
                {dieValue = 1;}     //reset die value
            }
            else{
                set(dieValue);//sets the LED lights to the die roll
            }

        } else {

            reset();//reset all LEDS
        
        }  // end if (ONOFF_SW == 1)


    } // end while(1)

} // end main()



//------------------------------------------------------------------------------
// Function:   initialize()
// Parameters: void
// Returns:    void
// Initialization code for the application
//------------------------------------------------------------------------------
void initialize(void) {

    // Configure oscillator for 32 MHz
    OSCCONbits.IRCF = 14;  // Internal frequency 8 MHz x4 (PLL)
    OSCCONbits.SPLLEN = 1; // Enable 4x PLL
    OSCCONbits.SCS = 0;    // Fosc comes from PLLMUX

    
    // Configure I/O pins
    // RA4, input,  Roll Pushbutton
    // RA5, input,  On/Off Switch
    // RC0, output, LED1 (Upper Left)
    // RC1, output, LED2 (Upper Right))
    // RC2, output, LED3 (Middle Left)
    // RC3, output, LED4 (Center)
    // RC4, output, LED5 (Middle Right)
    // RC5, output, LED6 (Lower Left)
    // RC6, output, LED7 (Lower Right)
    ANSELA  = 0b00000000;  // Port A analog select (0=digital, 1=analog)
    ANSELB  = 0b00000000;  // Port B analog select (0=digital, 1=analog)
    ANSELC  = 0b00000000;  // Port C analog select (0=digital, 1=analog)
    SLRCONA = 0b00000000;  // Port A slew rate control (1=slew rate limited)
    SLRCONB = 0b00000000;  // Port B slew rate control (1=slew rate limited)
    SLRCONC = 0b00000000;  // Port C slew rate control (1=slew rate limited)
    TRISA   = 0b11111111;  // Port A tri-state (0=output, 1=input)
    TRISB   = 0b11111111;  // Port B tri-state (0=output, 1=input)
    TRISC   = 0b10000000;  // Port C tri-state (0=output, 1=input)

    // Initialize outputs
    reset();

} // end initialize()

//------------------------------------------------------------------------------
//Name: reset()
//Precondition: Nothing
//Postcondition: Nothing
//Function: sets all LEDS to 0
//------------------------------------------------------------------------------
void reset(void){
    // LED outputs are off
    LED1 = 0;
    LED2 = 0;
    LED3 = 0;
    LED4 = 0;
    LED5 = 0;
    LED6 = 0;
    LED7 = 0;
    return;
}

//Constant matrix of die values
uint8_t const static dies [6][7] = {{0,0,0,1,0,0,0},//1
        {1,0,0,0,0,0,1},//2
        {0,0,1,1,1,0,0},//3
        {1,0,1,0,1,0,1},//4
        {1,0,1,1,1,0,1},//5
        {1,1,1,0,1,1,1}};//6  
        //this a matrix of 6 x 7, where there are six die combinations, and each combination is 7 long

//------------------------------------------------------------------------------
//Name: reset()
//Precondition: Current dievalue (int 8)
//Postcondition: Nothing
//Function: Sets all of the LEDS to the pattern for the current die value
//------------------------------------------------------------------------------
void set(const uint8_t dieValue)
{
        
            LED1 = dies[dieValue-1][0];//assigns first LED
            LED2 = dies[dieValue-1][1];//assigns second LED
            LED3 = dies[dieValue-1][2];//assigns third LED
            LED4 = dies[dieValue-1][3];//assigns fourth LED
            LED5 = dies[dieValue-1][4];//assigns fifth LED
            LED6 = dies[dieValue-1][5];//assigns sixth LED
            LED7 = dies[dieValue-1][6];//assigns seventh LED
    return;
}
