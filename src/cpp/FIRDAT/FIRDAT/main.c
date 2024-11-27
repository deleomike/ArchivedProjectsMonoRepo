//
//  main.c
//  FIRDAT
//
//  Created by Michael DeLeo on 3/22/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>

uint32_t tags[64];
int main()
{

}

void init(){
    //Set all tags to 1
}
void insert(uint32_t x){
    shiftLeft();
    tags[0] = x;
}

//shifts the numbers over
void shiftLeft (){
    for (uint8_t i = 63; i >= 0; i--){
        if (i == 0){
            tags[0] = 1;
        }
        else{
        tags[i] = tags[i-1];
        }
    }
    //shifts the tags upwards in significance, and replaces first spot by 1
    return;
}

void Timer(){
    
}
