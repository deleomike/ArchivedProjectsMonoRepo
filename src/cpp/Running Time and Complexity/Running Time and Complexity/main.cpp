//
//  main.cpp
//  Running Time and Complexity
//
//  Created by Michael DeLeo on 4/7/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>



bool isPrime(int n)
{
    // Corner cases
    if (n <= 1)  return false;
    if (n <= 3)  return true;
    
    // This is checked so that we can skip
    // middle five numbers in below loop
    if (n%2 == 0 || n%3 == 0) return false;
    
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
            return false;
    
    return true;
}
//this is an O(sqrtn) algorithm

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int T,data;
    std::cin>>T;
    while(T-->0){
        std::cin>>data;
        isPrime(data) ? std::cout<<"Prime\n" : std::cout<<"Not prime\n";
    }
    return 0;
}
