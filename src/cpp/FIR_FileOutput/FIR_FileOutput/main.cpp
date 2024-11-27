//
//  main.cpp
//  FIR_Configure
//
//  Created by Michael DeLeo on 4/17/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

////////////////////////////////////
////Author: Mike DeLeo
////File name: FIR_C
////Summary: This file simulates an FIR filter on an embedded device.
//// The input is a sin wave, and the output is the attenuated signal.
//// To change the input and output, adjust the variables shown just below the dependencies
////REQUIREMENTS FOR RUNNING: C++ compiler
////////////////////////////////////

#include <stdio.h>
//#include <vector.h>
#include <math.h>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

////////////
//GLOBAL VARIABLES TO ADJUST INPUT AND OUTPUT
std::string INPUT_FILE = "/Users/michaeldeleo/Documents/MATLAB/wave.csv";
std::string COEFFICIENT_FILE = "/Users/michaeldeleo/Documents/MATLAB/coeff.csv";
std::string OUTPUT_FILE = "/Users/michaeldeleo/Documents/MATLAB/dat.csv";

const float FREQ_CUTOFF = 0.628; //Used for generating coefficients
////////////

int ADC_Read(int channel);
void configure();
void timer0_dummy(int time);    //is just the shift

//note that in a different setup, the number of tags can be chosen variabley
//CHECK THE IMPLIED DECIMAL, i was tweaking things a lot and im not sure where it stands on the values decimal place


//would not be constant in the variable FIR
int16_t coefficients[64];   //implied decimal of 2^15
int32_t output[1024];
int16_t input[1024];  //implied decimal of 2^15
std::vector<int16_t> sin_buffer;    //implied decimal of 2^15


const uint8_t size = 64;
//in a variable FIR this would not be constant, it would be set automatically


//three parts
//main is where the calculations are done continuously for the FIR
//timer0 samples new input
//timer1 puts out FIR response values

int main() {
    configure();
    
    std::ofstream file;
    file.open(INPUT_FILE);
    for (int i = 0; i < size-1; i++){
        file << sin_buffer[i] << ",";
    }
    file << sin_buffer[size-1];
    file.close();
    file.open(COEFFICIENT_FILE);
    for (int i = 0; i < size-1; i++){
        file << coefficients[i] << ",";
    }
    file << coefficients[size-1];
    file.close();
    while (1){
//        //samples come in at the top (n) of the sample input, and shift down
//        for (int i = 0; i < size-1; i++){
//            file << (int)sin_buffer[i] << ",";
//        }
//        file << (int)sin_buffer[size-1];
//        file.close();
            file.open(OUTPUT_FILE);
        timer0_dummy(0);
        uint16_t n = 1023;
        while (n > 0){
            int64_t temp = 0;
            uint8_t k = 0;
            while (k < size){
                temp += coefficients[k]*input[k];
                //temp = h[k]*x[M-1-k];
                k++;
            }
            output[n] = temp; //implied decimal of 2^15
            //assign sum of h[k]*x[n-k] to the output
            n--;
            timer0_dummy(n);
        }
        output[0] = coefficients[0];
        for (int i = 0; i < 1023; i++){
            file << output[i] << ",";
        }
        file << output[1023];
        file.close();
    }
}

////////////////////////////////////
//Precondition: Nothing
//Postcondition: Nothing
//Summary: Computes the coefficients for the FIR,
//And also computes the sinusoid function that is an input
////////////////////////////////////
void configure(){
    //configure for a variable FIR
    //sample
    uint16_t i = 0;
    //input and output array initialization
    while(i < 1024){
        input[i] = 0;
        output[i] = 0;
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
            float temp = sin(FREQ_CUTOFF*(i-32))/(3.14*(i-32))*0.1;
            coefficients[i] = temp * 32768;  //becomes an implied decimal of 2^15
        }
        //use floating point for accuracy
        //multiply 2^15, not 2^16 because of the sign
        i++;
    }
    
    //sin generation
    float ii = 0;
    while(ii < 3.14*100){
        if (i == 32){
            sin_buffer.push_back(sin_buffer[30]);
        }
        else{
            float temp = sin(ii);
            sin_buffer.push_back(temp*32768);
        }
        ii+= 0.098125*6.5;
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

////////////////////////////////////
//Precondition: Channel number
//Postcondition: Digital value (implied decimal) of the analog at the port
//Summary: Simulates what the sinusoid value would be at the pin
//And converts it into an implied decimal integer
////////////////////////////////////
int ADC_Read(int channel){
    int temp;
    if (!(sin_buffer.empty())){
        temp = sin_buffer[sin_buffer.size()-1];
        sin_buffer.pop_back();
    }
    else{
        temp = 0;
    }
    return temp;
    //dummy function for reading the ADC channel input of the PIC32
}

////////////////////////////////////
//Precondition: integer current time
//Postcondition: Nothing
//Summary: Acts as the timer module, and shifts over the input buffer
//And adds the next value of the input
////////////////////////////////////
void timer0_dummy(int time){
    //reset timer
    ///////////////////////////////
    //    //part of variable FIR, do not use in static
    //    sample.push_back(ADC_Read(2));
    //    ///////////////////////////////
    
    for (uint8_t i = 0; i < 63; i++){
        input[i] = input[i+1];
    }
    //shift input list down
    //new sample is at top
    //needs to be converted
    input[63]=ADC_Read(time);  // use 100 implied decimal
    
}
