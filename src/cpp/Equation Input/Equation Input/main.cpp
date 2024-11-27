//
//  main.cpp
//  Equation Input
//
//  Created by Michael DeLeo on 2/11/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <vector>

//Precondition: vector int, and value to find
//Postcondition: true if the value is present, false if not
bool find(std::vector<int> x, int val);

int main() {
    // insert code here...
    std::string input;
    std::getline(std::cin, input);
    //Gets line
    
    std::vector<int> numbers;
    std::vector<int> operations;    //1 is multiply, 2 is add, 3 is subtract
    std::vector<char> var;
    
    bool multiply_check = false;    //flips to true if a variable is recorded. next time around, checks if there is an operator. If not, then it is multiplication
    for (int i = 0; i < input.size(); i++)
    {
        if (multiply_check){    //checks for multiply
            if ((input.at(i) >= 97) && (input.at(i) <= 122)){   //no operator there, so it must be *
                operations.push_back(1);    //multiply
                multiply_check = false;//reset
            }
            else{
                multiply_check = false; //there is an operator
            }
        }
        if ((input.at(i) >= 48) && (input.at(i) <= 57)){
            numbers.push_back(input.at(i)-48); //this is a number
        }
        else if ((input.at(i) >= 97) && (input.at(i) <= 122)){
            var.push_back(input.at(i)); //pushback variable
            multiply_check = true;  //tells program to look for an operator for next cycle
        }
        else if (input.at(i) == 32){}//space, dont do anything
        else{
            if (input.at(i) == 43){
                operations.push_back(2);//+
            }
            else if (input.at(i) == 45){
                operations.push_back(3);//-
            }
        }
    }
    
    
    //this could be simplified into a for loop, with an increment of the while loop calling a function with a type def for the mult, add, sub
    //equation is sorted into the three sets
    while (find(operations,1)){ //as long as there is multiplication
        for (int i = 0; i < operations.size(); i++)    //multiplication
        {
            if (operations.size() == 0){
                i = 10; //exits "for loop"
            }
            if (operations.at(i) == 1){ //multiply
                numbers.at(i) = numbers.at(i) * numbers.at(i+1);    //multiply left by right, and assign
                numbers.erase(numbers.begin() + 1 + i);             //pop number to right
                operations.erase(operations.begin() + i);           //pop operation
            }
        }
    }
    while(find(operations,2))
    for (int i = 0; i < operations.size(); i++)    //Addition
    {
        if (operations.size() == 0){
            i = 10; //exits "for loop"
        }
        if (operations.at(i) == 2){ //Add
            numbers.at(i) = numbers.at(i) + numbers.at(i+1);    //add left by right, and assign
            numbers.erase(numbers.begin() + 1 + i);             //pop number to right
            operations.erase(operations.begin() + i);           //pop operation
        }
    }
    //SUBTRACTION IS NOT WORKING
    //1 - 2 - 3 - 4
    //Program answer = 0
    //Answer = -8
    //Problem, overassigning the - operator
    //Possible solution, get rid of subtraction loop. Turn number that would subtract into negative numbers, and just use the add loop
    while(find(operations,3)){
        for (int i = 0; i < operations.size(); i++)    //Subtraction
        {
            if (operations.size() == 0){
                i = 10; //exits "for loop"
            }
            if (operations.at(i) == 3){ //sub
                numbers.at(i) = numbers.at(i) - numbers.at(i+1);    //sub left by right, and assign
                numbers.erase(numbers.begin() + 1 + i);             //pop number to right
                operations.erase(operations.begin() + i);           //pop operation
                i = 0;
            }
        }
    }
    std::cout << numbers.at(0) << std::endl;
}

bool find(std::vector<int> x, int val){
   for (int i = 0; i < x.size(); i++)
   {
       if (x.at(i) == val){
           return true;
       }
   }
   return false;
}
