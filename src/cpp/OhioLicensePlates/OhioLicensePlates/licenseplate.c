//
//  main.c
//  OhioLicensePlates
//
//  Created by Michael DeLeo on 10/1/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//  Created between 5pm and 7pm on Monday

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char * add_plate(char * licensePlate, int addition);
long lic2num(char * licensePlate);
char * num2lic(long num);
long licDiff(char * lic1, char * lic2);

main() {
    printf("Hi, please select comparison or raw addition");
    printf("Comparison: c");
    printf("Raw Addition: a");
    
    char * input;
    scanf("%c", input); //gets a single character
    
    if (input[0] == 'c' || input[0] == 'C'){
        input[0] = 'c';
    }
    else if (input[0] == 'a' || input[0] == 'A'){
        input[0] = 'a';
    }
    else{   //incorrect input
        while (1){
            printf("Do it right this time.\n");
            printf("Comparison: c\n");
            printf("Raw Addition: a");
            scanf("%c", input); //gets a single character
            if (input[0] == 'c' || input[0] == 'C'){
                input[0] = 'c';
                break;
            }
            else if (input[0] == 'a' || input[0] == 'A'){
                input[0] = 'a';
                break;
            }
        }
    }
    
    //now we have the choice
    
    //addition
    if (input[0] == 'a'){
        printf("Please no spaces after your input");
        printf("License Plate:");
        char * lic = malloc(7);
        scanf("%s",lic);
        printf("Addition:");
        char adder[30];
        scanf("%s",adder);
        //now i have the license plate and the addition
        int num = atoi(adder);
        lic = add_plate(lic,num);
        printf(lic);
        //free the memory
    }
    
    else{
        printf("Print licenses between two license plates");
        printf("First: ");
        char * lic1 = malloc(7);
        scanf("%s",lic1);
        printf("Second: ");
        char * lic2 = malloc(7);
        scanf("%s",lic2);
        
        //now i have the two license plates
        
        long diff = licDiff(lic1,lic2);
        
        printf("There are %d licenses between %s and %s",diff,lic1,lic2);
    }
    
    return 0;
    
}

//summary: adds the plate by the number, and if it needs to be rolled over, do it
//pre: license plate char length of 7, addition
//Post: license plate number that has been added with addition number
char * add_plate(char * licensePlate, int addition){
    
    long licNum = lic2num(licensePlate) + addition;
    licensePlate = num2lic(licNum);
    
    return licensePlate;
}

//pre: license plate length 7
//Post: the numerical value of the license plate long
long lic2num(char * licensePlate){
    char num[4];
    int i = 0;
    while (i < 4){
        num[i] = licensePlate[3+i];
        i = i + 1;
    }//select the numbers from the license plate
    
    long licNum = atoi(num); //convert to int
    
    int let[3] = {licensePlate[0] - 65, licensePlate[1] -65, licensePlate[2] - 65};
    licNum = licNum + let[2] * 10000 + let[1] * 260000 + let[0] * 6760000;
    
    return licNum;
}

//pre: any number (preferably numerical rep of license plate)
//post: license plate char string length 7
char * num2lic(long num_t){
    long num = num_t;
    while (0 > num){//roll back over
        num = num + 175760000;
    }
    int lic[7];
    
    long val[3] = {6760000,260000,10000};
    //first digit
    int i = 0;
    while (i < 3){
        //if the value does not exist in this number
        if ((num / val[i]) < 1){
            lic[i] = 0;
        }
        //the value exists, extract how mnay there are of it
        else{
            lic[i] = floor(num / val[i]);
        }
        num = num - (val[i] * lic[i]);  //removes the number from the decimal license
        i = i + 1;
    }
    
    i = 0;
    int valu[4] = {1000,100,10,1};
    while (i < 4){
        lic[3+i] = floor(num / valu[i]);     //finds the digit and puts it into the array
        num = num - (lic[3+i] * valu[i]);    //gets rid of that digit
        i = i + 1;
    }
    
    //now all numbers are in the license, now convert the first three to letters, and the entire thing to a string
    
    char * license = malloc(7);
    i = 0;
    while(i < 3){
        license[i] = lic[i] + 65;
        i = i + 1;
    }
    if (license[0] > 90){
        license[0] = 65;
    }
    //the first three are now letters
    
    //i is 3
    while (i < 7){
        license[i] = lic[i] + 48;
        i = i + 1;
    }
    //license is now done
    
    return license;
    
}

//pre: two license plates
//post: the difference between the two license plates
long licDiff(char * lic1, char * lic2){
    long len1 = lic2num(lic1);
    long len2 = lic2num(lic2);
    
    long diff = len1 - len2;
    diff = fabsl(diff);
    
    return diff;
}
