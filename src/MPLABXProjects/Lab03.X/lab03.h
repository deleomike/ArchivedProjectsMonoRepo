
//------------------------------------------------------------------------------
// File:          lab02.h
// Written By:    Mike DeLeo
// Modified By:   Morayo Ogunsina
// Date Created:  23 Jan 18
// Date Modified: 24 Jan 18
// Description:   Program to simulate rolling a die
// Compiler:	  XC8 v1.33
// Target:        PIC16F1709
// Schematic(s):  Drawing L01-11
//
// Revision History : none
//------------------------------------------------------------------------------

#include <xc.h>
#include <stdint.h>
#ifndef LAB03_H
#define LAB03_H

    // MCU Configuration Bits
    #pragma config FOSC = INTOSC    // Oscillator Selection Bits (INTOSC oscillator: I/O function on CLKIN pin)
    #pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
    #pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
    #pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
    #pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
    #pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
    #pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
    #pragma config IESO = OFF       // Internal/External Switchover Mode (Internal/External Switchover Mode is disabled)
    #pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)
    #pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
    #pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit cannot be cleared once it is set by software)
    #pragma config ZCDDIS = ON      // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR)
    #pragma config PLLEN = OFF      // Phase Lock Loop enable (4x PLL is enabled by SPLLEN)
    #pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
    #pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
    #pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
    #pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)
//#pragma config T0CKI = 1;

    // Defines
    #define START PORTAbits.RA2     // Start Button
    #define STOP  PORTAbits.RA4  // Stop button
    #define RESET_ PORTAbits.RA5  // Reset button
    #define LED1 PORTCbits.RC0  // LED1 (Upper Left)
    #define LED2 PORTCbits.RC1  // LED2 (Upper Right)
    #define LED3 PORTCbits.RC2  // LED3 (Middle Left)
    #define LED4 PORTCbits.RC3  // LED4 (Center)
    #define LED5 PORTCbits.RC4  // LED5 (Middle Right)
    #define LED6 PORTCbits.RC5  // LED6 (Lower Left)
    #define LED7 PORTCbits.RC6  // LED7 (Lower Right)
    #define LEDBLINK  PORTCbits.RC7  //LED Turns on when RC7 is 0
    #define TIMER0_FLAG TMR0IF   //Interrupt flag for timer 0


    #define DIGIT1  PORTBbits.RB4   //Digit 4
    #define DIGIT2  PORTBbits.RB5   //Digit 3
    #define DIGIT3  PORTBbits.RB6   //Digit 2
    #define DIGIT4  PORTBbits.RB7   //Digit 1

    // Function Prototypes

    //------------------------------------------------------------------------------
    //Name: intialize(void)
    //Precondition: Nothing
    //Postcondition: Nothing
    //Function: calls reset(), sets ANSELS, Slew Rate and tri states
    //------------------------------------------------------------------------------
    void MCU_initialize(void);

    //------------------------------------------------------------------------------
    //Name: reset()
    //Precondition: Nothing
    //Postcondition: Nothing
    //Function: sets all LEDS to 0
    //------------------------------------------------------------------------------
    void reset(void);

    //------------------------------------------------------------------------------
    //Name: reset()
    //Precondition: Current dievalue (int 8)
    //Postcondition: Nothing
    //Function: Sets all of the LEDS to the pattern for the current die value
    //------------------------------------------------------------------------------
    void set(const uint8_t dieValue);

    void Display(uint8_t num[4], uint8_t digit);

    void Timer0Handler(void);

    void interrupt ISR(void);


#endif /*LAB03_H*/
