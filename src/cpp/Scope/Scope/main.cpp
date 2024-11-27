//
//  main.cpp
//  Scope
//
//  Created by Michael DeLeo on 1/19/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Difference {
private:
    vector<int> elements;
    
public:
    int maximumDifference;
    
    Difference(vector<int> num)
    {this -> elements = num;}

    //Precondition: nothing
    //Postcondition: stores the absolute difference of two numbers in elements, into max difference
    void computeDifference(){
        int max = elements.at(0);
        int min = elements.at(0);

        for (int i = 0; i < elements.size(); i++)
        {
            if (elements.at(i) > max)
            {max = elements.at(i);}     //if the number is greater than the max, then this is the new max
            if (elements.at(i) < min)
            {min = elements.at(i);}     //if the number is less than the min, then this is the new min
        }
        maximumDifference = max - min;
        return;
}
}; //end of class

int main() {
    int N;
    cin >> N;
    
    vector<int> a;
    
    for (int i = 0; i < N; i++) {
        int e;
        cin >> e;
        
        a.push_back(e);
    }
    
    Difference d(a);
    
    d.computeDifference();
    
    cout << d.maximumDifference;
    
    return 0;
}
