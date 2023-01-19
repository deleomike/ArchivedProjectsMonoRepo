#include "LCD.h"

//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition: intializes LCD
//----------------------------------------------------------------------------
void LCD_initialize(void){
    //LCD is off
    EN_PIN = 0;
    msDelay(100);    //wait 100ms
    //THERE IS SOMETHING THAT NEEDS TO BE INIT FOR DELAY

    //LCD is on

    //Powerup routine

    //LATC = FUNCTION_SET
    LCD_SendCommand(FUNCTION_SET); //00111000
    //Third bit, 0 is use 5x7 char
    //fourth bit, 1 is use two lines
    //fifth bit, 1 is 8 bit data width
    //6-8th bits, 001 is command function set


    msDelay(4); //wait 4ms

    LCD_SendCommand(DISPLAY_ON); //00001100
    //First bit, 0 is position blink char at the cursor is off
    //Second bit, 0 is Cursor OFF
    //Third bit, 1 is Display ON
    //4-8th bits, 00001 is Command: Display on/off control





    msDelay(5);  //wait 1 ms
    LCD_ClearDisplay();
    return;

}

//----------------------------------------------------------------------------
//Precondition: 8 bit command, int or bits
//Postcondition: sends command to LCd
//----------------------------------------------------------------------------
void LCD_SendCommand(uint8_t cmd){
    RS_PIN = 0; //READ SET on
    RW_PIN = 0; //WRITE
    //Read 1 / Write 0

    //PUT DATA on DB7 to DB0
    PORTE = cmd;

    EN_PIN = 1; //ENABLE
    msDelay(1); //Wait 1 ms
    EN_PIN = 0;
    //Address increments automatically
    return;

}

//----------------------------------------------------------------------------
//Precondition: int version of character
//Postcondition: sends character to LCD
//----------------------------------------------------------------------------
uint8_t position = 0x0;
void LCD_SendCharacter(uint8_t ch){
    //LCD_SendCommand(position);
    RS_PIN = 1;
    RW_PIN = 0;

    LCD_OUT = ch;
    EN_PIN = 1;
    msDelay(1);
    EN_PIN = 0;
    position++;
    if (position == 0x0F+1){
        position = 0x40;    //move to next line
        LCD_SendCommand(128+position);
    }
    if (position == (0x4F+1)){
        position = 0x0;     //reset to first line
        LCD_SendCommand(128+position);
    }

}

//----------------------------------------------------------------------------
//Precondition: 8 bit string, and size of string
//Postcondition: sends string, character by character to LCD using send character
//----------------------------------------------------------------------------
void LCD_SendString(string_b8 x,uint8_t size){
    uint8_t i = 1;
    while (i <= size){
        unsigned char temp = find(x,i); //saves the char here so it doesnt keep running to find it
        if ((temp >= 97) &&(temp <= 122)){
            LCD_SendCharacter(temp-32);   //lowercase, but we're sending uppercase
        }
        else{
            LCD_SendCharacter(temp);
        }
        i++;
    }
    return;
}

//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition: sends a command to clear the display
//----------------------------------------------------------------------------
void LCD_ClearDisplay(void){
    LCD_SendCommand(CLEAR_DISPLAY);
    return;
}


//----------------------------------------------------------------------------
//Precondition: easier way to use 8 bit string. send a char array and size
//Postcondition: sends string through send character
//----------------------------------------------------------------------------
void LCD_SendPhrase(char str[], uint8_t size){
    string_b8 temp = new_string(str,size);  //creates 8 bit string
    LCD_SendString(temp,size);  //Sends string
}

//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition: sends 8 bits of blank characters
//----------------------------------------------------------------------------
void LCD_SendHalfBlank(void){
    string_b8 temp = set_at_range(temp, 1,8,32);   //fill string with " "
    LCD_SendString(temp,8); //Send
}

//----------------------------------------------------------------------------
//Precondition: nothing
//Postcondition: calls send half blank twice
//----------------------------------------------------------------------------
void LCD_SendFullBlank(void){
    LCD_SendHalfBlank();
    LCD_SendHalfBlank();
}


