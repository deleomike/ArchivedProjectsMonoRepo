//
//  main.cpp
//  Company Matrix
//
//  Created by Michael DeLeo on 1/30/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>


using namespace std;
int sum (vector<int> temp);
int compare (int first, int second, int third, int fourth);

int main()
{
    
    //Q V O V   |   N W
    //True: 1, False: 0
    vector<int> mary = {1,1,1,0,1,1};
    vector<int> david = {0,1,1,1,0,1};
    vector<int> karen = {1,1,1,1,1,1};
    vector<int> paul = {1,0,1,1,1,1};
    
    
    
    cout << "Mary: " << sum(mary) << endl;
    cout << "David: " << sum(david) << endl;
    cout << "Karen: " << sum(karen) << endl;
    cout << "Paul: " << sum(paul) << endl;
    
    int best_choice = compare(sum(mary),sum(david),sum(karen),sum(paul));
    
    if (best_choice==sum(mary))
    {
        cout << "Mary is the best choice." << endl;
    }
    
    else if (best_choice==sum(david))
    {
        cout << "David is the best choice." << endl;
    }
    
    else if (best_choice==sum(karen))
    {
        cout << "Karen is the best choice." << endl;
    }
    
    else{
        cout << "Paul is the best choice" << endl;
    }
    
    
    return 0;
}

int sum (vector<int> temp)
{
    int value = 0;
    for (int i = 0; i < temp.size(); i++)
    {
        value = temp.at(i) + value;
    }
    
    return value;
}

int compare(int first, int second, int third, int fourth)
{
    int temp_ = first;
    int temp[4] = {first, second, third, fourth};
    
    for (int i = 0; i <4; i++)
    {
        if (temp_ > temp[i])
        {
        }
        
        else if (temp_ == temp[i])
        {
        }
        
        else {
            temp_ = temp[i];
            
        }
    }
    return temp_;
}
