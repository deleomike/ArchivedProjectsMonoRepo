/*
 * File:   LCD.h
 * Author: MAD6068
 *
 * Created on February 7, 2018, 7:31 PM
 */



#ifndef LCD_H
#define LCD_H

#include "string.h"
#include <xc.h>
#include <stdint.h>

#define CLEAR_DISPLAY 0b00000001
#define DISPLAY_ON   0b00001100   //12    //Blink char at curs off, cursor off, display on
#define FUNCTION_SET  0b00111000  //56   //uses 5x7 char, 2 lines, and 8 bit data width
#define RS_PIN PORTDbits.RD6 //1 is read/set, 0 is do not
#define RW_PIN PORTDbits.RD11 //1 is read, 0 is write
#define EN_PIN PORTDbits.RD5 //Enable pin, 0 is off, 1 is on
#define LCD_OUT PORTE    //8 pins for LCD


//Precondition: nothing
//Postcondition: intializes LCD
void LCD_initialize(void);

//Precondition: 8 bit command, int or bits
//Postcondition: sends command to LCd
void LCD_SendCommand(uint8_t cmd);

//Precondition: 8 bit string, and size of string
//Postcondition: sends string, character by character to LCD using send character
void LCD_SendString(string_b8 x, uint8_t size);

//Precondition: nothing
//Postcondition: sends a command to clear the display
void LCD_ClearDisplay(void);

//Precondition: int version of character
//Postcondition: sends character to LCD
void LCD_SendCharacter(uint8_t ch);

//Precondition: easier way to use 8 bit string. send a char array and size
//Postcondition: sends string through send character
void LCD_SendPhrase(char str[], uint8_t size);

//Precondition: nothing
//Postcondition: sends 8 bits of blank characters
void LCD_SendHalfBlank(void);

//Precondition: nothing
//Postcondition: calls send half blank twice
void LCD_SendFullBlank(void);



#endif /*LCD_H*/
