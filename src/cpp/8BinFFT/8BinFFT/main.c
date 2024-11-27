//
//  main.c
//  64BinFFT
//
//  Created by Michael DeLeo on 5/6/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//


//This will actually be a 64 bin fft

#include <stdio.h>
#include <math.h>
#include <stdint.h>

void initialize();

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
int16_t coefficients[size][size];   //implied decimal of 2^15
int16_t input[size];  //implied decimal of 2^15


int main(){
    initialize();
    uint8_t n = 0;
    uint8_t k = 0;
    //output iterator k
    while (k < size){
//        struct imag16 output;
//        output.real = 0;
//        output.imaginary = 0;
        //input iterator n
        int32_t output = 0;
        while (n < size){
            //output = imag16_add(output, imag16_multiply_int(coefficients[n][k], input[n]));
            //temporary output, may overflow
            output += input[n]*coefficients[n][k];  //input at n * mag(exp(-1(2Pi/#bins)*n*k))
            n++;
        }
        n =0;
        k++;
    }
    return 0;
}

void initialize(){
    uint8_t k = 0;
    while (k < size){
        input[k] = 0;
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
            real = cos(-1*(2*3.14)*i*k); //real part of Exponent
            imag = sin(-1*(2*3.14)*i*k);   //iimaginary part
            real = sqrt(pow(real, real)+ pow(imag,imag));   //magnitude
            //since this relationship is linear for multiplication, the input may be multiplied by
            //this coefficient (magnitude), and it would be the same as if the mag operation were done
            //after the summation
            coefficients[k][i] = (int)real * 32768; //implied decimal of 2^15
            i++;
        }
        i = 0;
        k++;

    }
    
}
