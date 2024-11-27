//
//  main.cpp
//  64binFFT_FileOutput
//
//  Created by Michael DeLeo on 5/6/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
//#include <vector.h>
#include <math.h>
#include <cstdint>
#include <fstream>
#include <vector>
#include <iostream>

void initialize();
int ADC_Read(int channel);
void timer0_dummy(int time);

struct imag32{
    int32_t real;
    int32_t imag;
};
//struct imag16{
//    int16_t real;
//    int16_t imaginary;
//};
//inline struct imag16 imag16_multiply(struct imag16 x, struct imag16 y);
//inline struct imag16 imag16_multiply_int(struct imag16 x, int16_t y);
//inline struct imag16 imag16_add(struct imag16 x, struct imag16 y);
//
//
//inline struct imag16 imag16_multiply(struct imag16 x, struct imag16 y){
//    struct imag16 value;
//    value.real = x.real * y.real - ( x.imaginary * y.imaginary);
//    value.imaginary = x.real* y.imaginary + x.imaginary*y.real;
//    return value;
//}
//
//inline struct imag16 imag16_multiply_int(struct imag16 x, int16_t y){
//    struct imag16 value;
//    value.real *= y;
//    value.imaginary *= y;
//    return value;
//}
//
//inline struct imag16 imag16_add(struct imag16 x, struct imag16 y){
//    struct imag16 value;
//    value.real = x.real + y.real;
//    value.imaginary = x.imaginary + y.imaginary;
//    return value;
//}
const int size = 64;
imag32 coefficients[size][size];   //implied decimal of 2^15
int16_t input[1024];  //implied decimal of 2^15
int32_t output[64];
std::vector<int16_t> sin_buffer;    //implied decimal of 2^15


int main(){
    initialize();
    while(1){
        uint8_t n = 0;
        uint16_t k = 0;
        timer0_dummy(0);
        std::ofstream file;
        file.open("/Users/michaeldeleo/Documents/MATLAB/datFFT.csv");
        //output iterator k
        while (k < 64){
            //        struct imag16 output;
            //        output.real = 0;
            //        output.imaginary = 0;
            //input iterator n
            int32_t output_temp = 0;
            while (n < size){
                //output = imag16_add(output, imag16_multiply_int(coefficients[n][k], input[n]));
                //temporary output, may overflow
                output_temp += input[n]*coefficients[n][k];  //input at n * mag(exp(-1(2Pi/#bins)*n*k))
                n++;
            }
            n =0;
            k++;
            timer0_dummy(0);
            output[k] = output_temp;
        }
        for (int i = 0; i < 1024; i++){
            timer0_dummy(2);
        }
        for (int i = 0; i < 63; i++){
            file << output[i] << ",";
        }
        file << output[63];
        file.close();
    }
    return 0;
}

void initialize(){
    uint16_t k = 0;
    while (k < 1024){
        input[k] = 0;
        k++;
    }
    k = 0;
    while (k < 64){
        output[k] = 0;
        k++;
    }
    
    uint8_t i = 0;
    k = 0;
    float real = 0;
    float imag = 0;
    
    while (k < size){
        //k is iterator
        //Exp(-j(2Pi/#bins)*iterator*outputiterator
        //i is output iterator
        
        while (i < size){
            real = cos(-1*((3.14)/32)*i*k); //real part of Exponent
            imag = sin(-1*((3.14)/32)*i*k);   //iimaginary part
            real = sqrt(pow(real, 2)- pow(imag,2));   //magnitude
            //since this relationship is linear for multiplication, the input may be multiplied by
            //this coefficient (magnitude), and it would be the same as if the mag operation were done
            //after the summation'
            int64_t temp = (real * 16384);
            coefficients[k][i] = temp; //implied decimal of 2^14
            i++;
        }
        i = 0;
        k++;
        
    }
    
    float ii = 0;
    while(ii < 3.14*100){
        if (i == 32){
            sin_buffer.push_back(sin_buffer[30]);
        }
        else{
            float temp = sin(ii);
            sin_buffer.push_back(temp*32768);
        }
        ii+= 0.098125*2;
    }
    return;
}


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

//sampling timer
void timer0_dummy(int time){
    //reset timer
    ///////////////////////////////
    //    //part of variable FIR, do not use in static
    //    sample.push_back(ADC_Read(2));
    //    ///////////////////////////////
    
    for (uint16_t i = 0; i < 1023; i++){
        input[i] = input[i+1];
    }
    //shift input list down
    //new sample is at top
    //needs to be converted
    input[1023]=ADC_Read(time);  // use 100 implied decimal
    
}

