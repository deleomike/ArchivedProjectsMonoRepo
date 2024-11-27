/* 
 * File:   lab08.h
 * Author: MAD6068
 *
 * Created on March 21, 2018, 7:21 PM
 */

#ifndef LAB08_H
#define	LAB08_H



#include <stdio.h>
#include <stdlib.h>
#define _SUPPRESS_PLIB_WARNING
#include <plib.h>
#include "spi.h"
#include "tft.h"
#include "touch.h"
#include "i2c.h"
#include <math.h>
//#include "Adafruit_LIS3DH.h"

    // PIC32MX340F512H Configuration Bit Settings
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider (2x Divider)
    #pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier)
    #pragma config FPLLODIV = DIV_1         // System PLL Output Clock Divider(PLL Divide by 1)
    #pragma config FNOSC = PRIPLL           // Oscillator Selection Bits(Primary Osc w/PLL (XT+,HS+,EC+PLL))
    #pragma config FSOSCEN = OFF            // Secondary Oscillator Enable(Disabled)
    #pragma config IESO = OFF               // Internal/External Switch Over(Disabled)
    #pragma config POSCMOD = HS             // Primary OscillatorConfiguration (HS osc mode)
    #pragma config OSCIOFNC = OFF           // CLKO Output Signal Active othe OSCO Pin (Disabled)
    #pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor(Pb_Clk is Sys_Clk/8)
    #pragma config FCKSM = CSDCMD           // Clock Switching and MonitorSelection (Clock Switch Disable, FSCM Disabled)
    #pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler(1:1048576)
    #pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDTDisabled (SWDTEN Bit Controls))
    #pragma config DEBUG = OFF              // Background Debugger Enable(Debugger is disabled)
    #pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select(ICE EMUC2/EMUD2 pins shared with PGC2/PGD2)
    #pragma config PWP = OFF                // Program Flash Write Protect(Disable)
    #pragma config BWP = OFF                // Boot Flash Write Protect bit(Protection Disabled)
    #pragma config CP = OFF                 // Code Protect (ProtectionDisabled)

    // Includes
    #include <xc.h>
    #include <stdint.h>

    #define TRIS_OUTPUT 0  // Used to set tristate to output
    #define TRIS_INPUT 1   // Used to set tristate to input
    #define LED_OUT PORTFbits.RF0      // LED pin value
    #define LD5_TRIS TRISFbits.TRISF0  // LED pin tristate

    //NEEDS PORTS
    #define ROT_A PORTDbits.RD2
    #define ROT_B PORTDbits.RD0
    #define SW PORTFbits.RF1


    #define MCP_ADDR 0b00100000
    #define ACC_ADDR 0b00011000
    // Function prototypes
    void MCU_initialize(void);

    //Params:   c; character to send to stdout
    //Returns:  void
    // Redfine _mon_putc so stdout goes to UART
    void _mon_putc (char c);

    //Precondition: milliseconds up to 1000ms
    //Postcondition: nothing
    //Function: delays for number of milliseconds
    void msDelay(uint16_t delay);

    //Precondition: nothing
    //Postcondition:
    //function: delays one millisecond
    void delay_one_ms();

    //Precondition: nothing
    //Postcondition:
    //function: displays a main page with course name,
    //and name of each member
    void DrawMenu();

    //Precondition: nothing
    //Postcondition:
    //function: displays a screen with coordinates as touch feedback
    //and pixel at the touch coordinates
    void GoTo23008();

    //Precondition: nothing
    //Postcondition:
    //function: displays a page with buttons to turn an LED drawing
    //on or off and number of times turned
    void GoToLed();

    //Precondition: nothing
    //Postcondition:
    //function:  draws an led turned on
    void TurnOnLED();

    //Precondition: nothing
    //Postcondition:
    //function:  draws an led turned off
    void TurnOffLED();

    //Precondition: nothing
    //Postcondition:
    //function:  displays A and B values of Rotary Encoder,
    // position count and direction.
    void GoToLIS3DH();

//    void GoToMain();
//
//    void MCP23008_INIT();
//
//    uint8_t MCP23008_GetValues();
//
//    void MCP23008_WriteValues(uint8_t data);

#endif	/* LAB08_H */

