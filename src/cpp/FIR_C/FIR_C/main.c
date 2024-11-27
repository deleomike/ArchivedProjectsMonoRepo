//
//  main.c
//  FIR_Configure
//
//  Created by Michael DeLeo on 4/17/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
//#include <vector.h>
#include <math.h>
#include <stdint.h>


int ADC_Read(int channel);
void configure();
void timer0_dummy(int time);    //is just the shift

//note that in a different setup, the number of tags can be chosen variabley
//CHECK THE IMPLIED DECIMAL, i was tweaking things a lot and im not sure where it stands on the values decimal place

const uint8_t size = 64;
//would not be constant in the variable FIR
int16_t coefficients[size];   //implied decimal of 2^15
int16_t input[size];  //implied decimal of 2^15

const float freq_cutoff = 0.628;
//in a variable FIR this would not be constant, it would be set automatically


//three parts
//main is where the calculations are done continuously for the FIR
//timer0 samples new input
//timer1 puts out FIR response values

uint32_t output;
int main() {
    configure();
    while (1){
        timer0_dummy(0);
    }
}

void configure(){
    //configure for a variable FIR
    //sample
    uint8_t i = 0;
    //input and output array initialization
    while(i < 64){
        input[i] = 0;
        i++;
    }
    //initialize COEFFICIENTS
    i = 0;
    while(i < 63){
        //casts input to sin as a double, because input is a double
        if (i == 32){
            coefficients[i] = coefficients[i-1];
            //for some reason the math.h file gives NaN (Not a Number)
        }
        else{
            float temp = sin(freq_cutoff*(i-32))/(3.14*(i-32))*0.1;
            coefficients[i] = temp * 32768;  //becomes an implied decimal of 2^15
        }
        //use floating point for accuracy
        //multiply 2^15, not 2^16 because of the sign
        i++;
    }

    //finished initializing local variables
    
    
    //    std::vector<uint16_t> samples;
    //    msDelay(250);
    //    uint i = 0;
    //    uint max = 0;
    //    while(i < samples.size()){
    //        if (samples[i] > max){max = samples[i];}
    //        i++;
    //    }
    return;
}
int ADC_Read(int channel){
    return 0;
    //dummy function for reading the ADC channel input of the PIC32
}

//sampling timer
void timer0_dummy(int time){
    //reset timer
    //todo
    
    ///////////////////////////////
    //    //part of variable FIR, do not use in static
    //    sample.push_back(ADC_Read(2));
    //    ///////////////////////////////
    
    for (uint8_t i = 0; i < size-1; i++){
        input[i] = input[i+1];
    }
    //shift input list down
    //new sample is at top
    //needs to be converted
    input[size-1]=ADC_Read(time);  // use 100 implied decimal
    //samples come in at the top (n) of the sample input, and shift down
    
    //do single convolution
    int64_t temp = 0;
    uint8_t k = 0;
    while (k < size){
        temp += coefficients[k]*input[k];
        //temp = h[k]*x[M-1-k];
        k++;
    }
    //assign sum of h[k]*x[n-k] to the output
    output = temp; //implied decimal of 2^15
    //resets position
    return;
}

uint16_t ADC2volt(uint8_t channel){
    //convert
    return 0;
}

//output timer,
void timer1_dummy(){
    
}

