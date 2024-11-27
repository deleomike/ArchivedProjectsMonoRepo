//
//  main.cpp
//  Pointers
//
//  Created by Michael DeLeo on 4/5/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#include <iostream>


int main()
{
    int x = 1;
    int y = 2;
    int* i = &x;
    
    //& before a variable, gives the address
    
    std::cout << *i << std::endl;
    //This should print out 1
    //* says to pick the value
    
    std::cout << &y << std::endl;
    
    std::cout << &i << std::endl;
    //This should print out the address
    //& says to pick the address
    
    *i = 4;
    
    std::cout << *i << std::endl;
    //This should print out 4
    //* says to pick the value
    
    std::cout << &i << std::endl;
    //This should print out the address
    //& says to pick the address
    
    
    int* j;
    j = i;
    
    std::cout << *j << std::endl;
    //This should print out 4
    //* says to pick the value
    
    std::cout << &j << std::endl;
    //This should print out the address of 'y'
    //& says to pick the address
}
