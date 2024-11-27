//
//  main.cpp
//  Arduino Control 8 Lights
//
//  Created by Michael DeLeo on 1/10/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//
//  Description:    This code will cycle through 8 lights on the PIC16F1709 by using PortB
//  and shifting a high bit left by one until the binary value is at 128, and then the position
//  is reset back to the first light in the order.
//
//  Target Compiler:MPLAB X
//  Target Device: PIC16F1709
//
//

#include <iostream>

int main(){
    int PortB = 1;
    while(1)
    {
        for (int i = 0; i < 7; i++)
        {
            PortB << 1; //  The bit will be shifted left by one, 8 times in total
            /*
             PortB      PortB
             Before     After   Iteration i
             
             1          2       1
             2          4       2
             4          8       3
             8          16      4
             16         32      5
             32         64      6
             64         128     7
             
             PortB is represented as an integer, if we took a look at what
             the integer value is, it would show as a 1 digit followed by i number of zeroes.
             This represents the light # with the position of the 1.
             
             7 iterations are used because the light is reset after 7 iterations. So the light's
             starting position is on light #0, and with 7 iterations it goes to light #7
             */
        }
        
        PortB = 1;  //Reset
        //  0   0   0   0   0   0   0   1
        //  This is the reset position
        
    }
}
