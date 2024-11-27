#include "string.h"

//----------------------------------------------------------------------------
//Precondition: string, index of string, and value to place
//Postcondition: new string
//Function: sets value at index of string
//----------------------------------------------------------------------------
string_b8 set_at(string_b8 dest, uint8_t index, unsigned char val){
    if (index == 8){
        dest.s7 = val;
    }
    if (index == 7){
        dest.s6 = val;
    }
    if (index == 6){
        dest.s5 = val;
    }
    if (index == 5){
        dest.s4 = val;
    }
    if (index == 4){
        dest.s3 = val;
    }
    if (index == 3){
        dest.s2 = val;
    }
    if (index == 2){
        dest.s1 = val;
    }
    if (index == 1){
        dest.s0 = val;
    }
    else{}
    return dest;
}

//----------------------------------------------------------------------------
//Precondition: string, start index, stop index, and value to place
//Postcondition: new string
//Function: sets value at index of string, to end of index
//----------------------------------------------------------------------------
string_b8 set_at_range(string_b8 dest, uint8_t start, uint8_t stop, unsigned char val){

    while (start <=stop){
        dest = set_at(dest,start,val);
        start++;
    }

    return dest;
}

//----------------------------------------------------------------------------
//Precondition: char array, size of array
//Postcondition: returns 8 bit string with char array assigned inside
//----------------------------------------------------------------------------
string_b8 new_string(unsigned char str[], uint8_t size)
{
    string_b8 temp;
    uint8_t i = 0;
    while (i < 8)
    {
        if (i < size){
            temp = set_at(temp, i+1,str[i]);
        }
        else{
            temp = set_at(temp, i+1, 0);
        }
        i++;
    }

    return temp;
}

//----------------------------------------------------------------------------
//Precondition: string source, index
//Postcondition: char found at index
//Function: finds the char at the index and returns it
//----------------------------------------------------------------------------
unsigned char find (string_b8 source1, uint8_t index){
    string_b8 source = source1; //copy
    unsigned char val = 0;  // temp
    if (index == 8){
        val = source.s7;
    }
    if (index == 7){
        val = source.s6;
    }
    if (index == 6){
        val = source.s5;
    }
    if (index == 5){
        val = source.s4;
    }
    if (index == 4){
        val = source.s3;
    }
    if (index == 3){
       val = source.s2;
    }
    if (index == 2){
        val = source.s1;
    }
    if (index == 1){
       val = source.s0;
    }
    return val;
}

//----------------------------------------------------------------------------
//Precondition: destination to copy to, source to copy from
//Postcondition: new string
//Function: copies every char from source to destination with respective index
//----------------------------------------------------------------------------
string_b8 copy(string_b8 dest, string_b8 source){
    string_b8 copy;
    uint8_t i = 1;
    while (i <= 8){
        set_at(copy, i, find(source,i));//sets the copy at i to the source at i
        i++;
    }
    return copy;
}

//----------------------------------------------------------------------------
//Precondition: number to convert, size of number (digits)
//Postcondition: returns an 8 bit string of the number
//----------------------------------------------------------------------------
string_b8 num2str(uint8_t num, uint8_t size){
    //!!!!!!!!!!!!!!!There is a More efficient way than this
    string_b8 x;
    uint8_t temp = num % 10;    //tens place
    x = set_at(x,size,temp+48);    //give first number in the string
    uint8_t i = 1;
    while (i < size){
        num = num - temp;   //subtract moded number from number given
        num = num / 10;     //bring number given back by one place
        temp = num % 10;    //mod a number
        x = set_at(x,size-i,temp+48);   //adds a character the next highest spot
        i++;
    }

    return x;
}
