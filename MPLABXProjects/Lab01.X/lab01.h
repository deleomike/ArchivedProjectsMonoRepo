/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   lab01.h
 * Author: Michael DeLeo
 * Comments: Contains the prototypes for 
 * 
 * 
 * 
 * Revision history: 
 */

#ifndef LAB01_H
#define LAB01_H

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


    // Defines
    #define ROLL_PB  PORTAbits.RA4  // Roll Pushbutton
    #define ONOFF_SW PORTAbits.RA5  // On/Off Switch
    #define LED1 PORTCbits.RC0  // LED1 (Upper Left)
    #define LED2 PORTCbits.RC1  // LED2 (Upper Right)
    #define LED3 PORTCbits.RC2  // LED3 (Middle Left)
    #define LED4 PORTCbits.RC3  // LED4 (Center)
    #define LED5 PORTCbits.RC4  // LED5 (Middle Right)
    #define LED6 PORTCbits.RC5  // LED6 (Lower Left)
    #define LED7 PORTCbits.RC6  // LED7 (Lower Right)

    // Function Prototypes

    //------------------------------------------------------------------------------
    //Name: intialize(void)
    //Precondition: Nothing
    //Postcondition: Nothing
    //Function: calls reset(), sets ANSELS, Slew Rate and tri states
    //------------------------------------------------------------------------------
    void initialize(void);
    
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

#endif /*LAB01_H*/
