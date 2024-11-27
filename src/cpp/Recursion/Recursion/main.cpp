//
//  main.cpp
//  Recursion
//
//  Created by Michael DeLeo on 1/12/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <bits/stdc++.h>

using namespace std;

int factorial(int n) {
    /*
    if (n == 0)
    {
        return n;
    }
    else{
        return n * factorial(n - 1);
    }*/
    //^^^^^^^^one way to do it
    int x;
    n==1 ? (x= n) : (x = n * factorial(n-1));
    //go down  |  add
    return x;
    
    /*
     3!
     3 + 2 + 1
     */
    // Complete this function
}

int main() {
    int n;
    cin >> n;
    int result = factorial(n);
    cout << result << endl;
    return 0;
}

