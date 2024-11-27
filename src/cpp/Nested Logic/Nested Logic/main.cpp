//
//  main.cpp
//  Nested Logic
//
//  Created by Michael DeLeo on 4/7/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    int dayExp = 0;
    int dayReturned = 0;
    int monthExp = 0;
    int monthReturned = 0;
    int yearExp = 0;
    int yearReturned = 0;
    
    string in1, in2;
    getline(cin,in1);
    getline(cin,in2);
    
    int list[3];
    string temp;
    int c = 0;
    for(int i =0; i < in1.size(); i++){
        if (in1[i] != ' '){
            temp += in1[i];
        }
        else{
            list[c] = stoi(temp);
            c++;
            temp.erase();
        }
    }
    list[c] = stoi(temp);
    c++;
    temp.erase();
    dayReturned =  list[0];
    monthReturned = list[1];
    yearReturned = list[2];
    c = 0;
    temp.erase();
    for(int i =0; i < in2.size(); i++){
        if (in2[i] != ' '){
            temp += in2[i];
        }
        else{
            list[c] = stoi(temp);
            c++;
            temp.erase();
        }
    }
    list[c] = stoi(temp);
    c++;
    temp.erase();
    dayExp = list[0];
    monthExp =list[1];
    yearExp = list[2];
    
    if (yearReturned > yearExp){
        cout << "10000";
    }
    else if (yearReturned < yearExp){
        cout << 0;
    }
    else if (monthReturned > monthExp){
        cout << (monthReturned-monthExp) * 500;
    }
    else if (monthReturned < monthExp){
        cout << 0;
    }
    else if (dayReturned > dayExp){
        cout << (dayReturned - dayExp) * 15;
    }
    else{
        cout << "0";
    }
    return 0;
}
