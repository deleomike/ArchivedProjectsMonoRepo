//
//  main.cpp
//  2D Arrays
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
using namespace std;

//Precondition: an hourglass. 3x3 vector vector
//Postcondition: prints hourglass
//void print(vector<vector<int>> x);

//Precondition: an hourglass. 3x3 vector vector
//Postcondition: returns sum of vector vector matrix
int sum(vector<vector<int>> x);

int main(){
    vector< vector<int> > arr(6,vector<int>(6));
    for(int arr_i = 0;arr_i < 6;arr_i++){
        for(int arr_j = 0;arr_j < 6;arr_j++){
            cin >> arr[arr_i][arr_j];
        }
    }
    //Makes array
    
    vector<vector<int>> list[16];   //list of hourglass combinations
    
    //i is the row, j is the column
    int counter = 0;
    vector<vector<int>> temp(3, vector<int>(3));    //temporary hourglass
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            temp.at(0) = {arr[i][j],    arr[i][j+1],    arr[i][j+2]};   //first row
            temp.at(1) = {0,    arr[i+1][j+1],    0};                   //second row
            temp.at(2) = {arr[i+2][j],    arr[i+2][j+1],    arr[i+2][j+2]};//third row
            //assigns the row i, with three elements from that row selected by j
            list[counter] = temp;//save hourglass
            counter++;
        }
    }//may not work
    
    
    
    int index = 0; //index to print (max hourglass)
    int best = sum(list[0]);//set best sum to the first hourglass
    for (int i = 0; i < 16; i++)
    {
        if (sum(list[i]) > best)//if the sum is better, replace the best
        {best = sum(list[i]);}
    }
    cout << best;
    
    return 0;
}

int sum(vector<vector<int>> x){
    int sum =0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            sum = x[i][j] + sum;
        }
    }
    return sum;
}
