/*
 * File:   string.h
 * Author: MAD6068
 *
 * Created on February 7, 2018, 8:25 PM
 */


#include <stdint.h>
#ifndef STRING_H
#define	STRING_H

//string 8 bits long
//read from left to right
//s0 -> s7
typedef union{  //string
    struct{
        unsigned char s0    :8;
        unsigned char s1    :8;
        unsigned char s2    :8;
        unsigned char s3    :8;
        unsigned char s4    :8;
        unsigned char s5    :8;
        unsigned char s6    :8;
        unsigned char s7    :8;
    };
}string_b8;

//
//Precondition: string, index of string, and value to place
//Postcondition: new string
//Function: sets value at index of string
string_b8 set_at(string_b8 dest, uint8_t index, unsigned char val);

//Precondition: string, start index, stop index, and value to place
//Postcondition: new string
//Function: sets value at index of string, to end of index
string_b8 set_at_range(string_b8 dest, uint8_t start, uint8_t stop, unsigned char val);

//Precondition: destination to copy to, source to copy from
//Postcondition: new string
//Function: copies every char from source to destination with respective index
string_b8 copy(string_b8 dest, string_b8 source);

//Precondition: string source, index
//Postcondition: char found at index
//Function: finds the char at the index and returns it
unsigned char find(string_b8 source, uint8_t index);

//Precondition: number to convert, size of number (digits)
//Postcondition: returns an 8 bit string of the number
string_b8 num2str(uint8_t num, uint8_t size);

//Precondition: char array, size of array
//Postcondition: returns 8 bit string with char array assigned inside
string_b8 new_string(unsigned char str[], uint8_t size);

#endif	/* STRING_H */

