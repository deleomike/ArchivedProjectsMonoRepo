//
//  main.cpp
//  Binary Numbers
//
//  Created by Michael DeLeo on 1/12/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <iterator>

using namespace std;

void DecToBin( const int num1 );


deque<int> bits;

int main() {
    int n;
    cin >> n;
    DecToBin(n);
    int best = 0;
    int temp =0;
    for (int i = 0; i < bits.size(); i++)
    {
        bits.at(i) ==1 ? (temp++) : (temp = 0); //add one to the temp if it is 1, reset temp if it is 0
        if (temp >=best)
        {best = temp;}//replace the best if the pattern is greater
        
    }
    cout << best;
    return 0;
}


//Recursive
void DecToBin( const int num1 )
{
    if( num1 == 0 )
    {
        return;
    }
    
    DecToBin( num1/2 );
    bits.push_back(num1 %2);
}


