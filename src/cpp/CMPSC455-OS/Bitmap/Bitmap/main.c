//
//  main.c
//  Bitmap
//
//  Created by Michael DeLeo on 11/27/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>

unsigned int set_bit(unsigned int x,int bitnum);
unsigned int clear_bit(unsigned int x, int bitnum);
unsigned int search(int n, int *bit_pos);
int binary_conversion(int num);
unsigned int clear_space(unsigned int x, int start, int sz);



int main(){
    /*
    while(1){
        printf("TESTING set_bit(uint x,int bitnum\n");
        printf("Enter an integer, and a bit to turn to 1\n");
        unsigned int num = 0;
        int bitnum = 1;
        scanf("%d",&num);
        scanf("%d",&bitnum);
        printf("Number: %d\nBinary: %d\nBinary Set: %d\n",num,binary_conversion(num),binary_conversion(set_bit(num,bitnum)));
    }*/
    while(1){
        
    }
}

unsigned int set_bit(unsigned int x, int bitnum){
    unsigned int replace = 1;
    replace = replace << (bitnum-1);
    unsigned int res = x | replace;
    return res;
}

unsigned int clear_bit(unsigned int x, int bitnum){
    unsigned int replace = 1;
    replace = replace << (bitnum - 1);
    replace = ~replace;
    unsigned int res = x & replace;
    return res;
}

unsigned int search(int n, int *bit_pos){
    unsigned int bitmap;
    unsigned int open_space = bitmap;
    open_space = clear_space(bitmap,0,n);
    //clears out an open space (0) of size n in the copy of the bitmap
    int i = 0;
    int size = 0;
    while(i < (size - n)){
        open_space = clear_space(bitmap,i,n);
        if ((open_space & bitmap) == bitmap){
            //space is available
            *bit_pos = i;
            //save bit offset
            break;
        }
        //else, space is not available
        //if the space in question exists,then when ANDED the space will be equal to the space from before
        i++;
    }
    
    return &bit_pos;
}

unsigned int clear_space(unsigned int x, int start, int sz){
    unsigned int copy = x;
    int i = start;
    while(i < sz){
        copy = clear_bit(copy,i);
        i++;
    }
    
    return copy;
    
}

int binary_conversion(int num){
    
    if (num == 0){
        return 0;
    }
    else{
        return (num % 2) + 10 * binary_conversion(num/2);
    }
}
