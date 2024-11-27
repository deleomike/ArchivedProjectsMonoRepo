//
//  main.cpp
//  30 Days Code - King and Four Sons
//
//  Created by Michael DeLeo on 12/18/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

//pre: number for factorial
//Post: x!
inline int Factorial(int x);
//Pre: int n and int r
//Post: combinations
uint64_t Combinations(int const & n, int const & r);
//pre: int n
//Post sum of combinations 0, 4, 8, 16...
int SumCombinations(int n);

int resize( int x);

vector<vector<int>> comb(int N, int K);

int main() {
    //There are four sons, and when evaluated the number of soldiers must be divisible by the number of sons (4)
    //For the input, the first number is the number of battalions N
    //The second number is the number of countries to conquer K
    int Battalions = 0;
    int Countries = 0;
    
    string input;
    bool redo = true;
    
    while (redo){
        getline(cin,input);
        string string_batt; //string version of battalions
        string string_count;//string version of countries
    
    
        bool tripwire = false;
        for (int i = 0; i < input.size(); i++)
        {
            if (input.at(i) == '.')
            {
                abort();
            }
            
            if (!tripwire)  //looking for battalions
            {
                if (input.at(i) != ' ')
                {
                    int size = string_batt.size();
                    string_batt.resize( size +1, input.at(i));
                }
                else
                    tripwire = true;    //now it is countries
            }
            else
            {
                int size = string_count.size();
                string_count.resize( size + 1, input.at(i));
            }
        }
        Battalions = stoi(string_batt);
        Countries = stoi(string_count);
        
        //Constraints
        if (Battalions >= 1 && Battalions <= 10000)
        {
            
            redo = false;
        }
        else{
            abort();
            redo = true;
        }
        if (Countries >= 1 && Countries <= min(100, Battalions))
        {
            redo = false;
        }
        
        else{
            abort();
            redo = true;
        }
    }
    //works for any input that is a number
    
    
    //may need to do the above a simpler way
    
    //Make an army of N size, and get number of soldiers for each battalion (iteration
    int * Army = new int [Battalions];
    
    /*
    for (int i = 0; i < Battalions; i++)
    {
        cin >> Army[i];
        cout << " ";
    }*/
    //Without getline
    
    int check_size = 0;
    
    string * string_army;
    string_army = new string [Battalions];//array of size number of battalions
    redo = true;
    while (redo){
        getline(cin, input);
        
        int choose_which = 0;//added to string army index to get next string
        for (int i = 0; i < input.size(); i++)
        {
            if (input.at(i) == '.')
            {
                abort();
            }
            
            if (input.at(i) != ' ')
            {
                int size = string_army[choose_which].size();
                string_army[choose_which].resize(size + 1, input.at(i));
                check_size++;
            }
            else{
                choose_which++;
                //increment to next battalion string
            }
        }
        
        redo = false;
        for (int i = 0; i < Battalions; i++)
        {
            Army[i] = stoi(string_army[i]);   //convert each string into the army int
            if (Army[i] < 1 || Army[i] > 1000)
            {
                abort();
                redo = true;
            }
        }
    }
    if (check_size< 1 || check_size >1000000000)
    {
        abort();
    }
    
    int comb_armies = Combinations(Battalions, Countries); //number of combinations
    vector<pair<int,int>> taken;
    for (int i = 0; i <= comb_armies; i++)
    {
        pair<int,int> temp (-1,-1);
        taken.push_back(temp);
    }
    
    bool skip = false;
    int possibilities = 0;
    int taken_counter = 0;
    //Needs to be subset size countries, {...} size Countries
    //This subset will contain Detachments {A0,A1,...A(countries)}
    vector<vector<int>> Detachments = comb(Battalions, Countries);
    //set of all combinations
    for (int i = 0; i < Detachments.size(); i++)
    {
        int64_t temp_detachment_poss = 1;
        for (int j = 0; j < Countries; j++)
        {
            //No need to check for combinations, they're all here
            temp_detachment_poss = temp_detachment_poss * SumCombinations(Army[Detachments.at(i).at(j)]);
        }
        possibilities = possibilities + temp_detachment_poss;
    }
    /*
    for (int i = 0; i < Battalions; i++)
    {
        for (int j = 0; j < Battalions; j++)
        {
            
            //TODO
            //if taken, skip
            for (int k = 0; k <= comb_armies;k++)
            {
                if ((taken.at(k).first == i && taken.at(k).second == j) || (taken.at(k).first == j && taken.at(k).second == i))
                {
                    //skip, they are already taken
                    skip = true;
                    
                }
                else{
                }
            }
            
            if (i == j && Battalions != 1)
            {
                //skip, they are the same army
            }
            
            else if (skip)
            {
                skip = false; //reset and skip
            }
            
            //else
            else{
                // not taken
                detachments.clear();
                for (int k = 0; k < Countries; k++)
                {
                    detachments.push_back();
                }
                int temp1 = SumCombinations(Army[i]);
                int temp2 = SumCombinations(Army[j]);
                if (Battalions == 1)
                {
                    temp1 = 1;
                }
                possibilities = possibilities + temp1 * temp2;
                //# of soldiers -- Combinations -- 4. so if there is none, then combinations is 0 + 1 for the empty detachment
                taken.at(taken_counter).first = i;
                taken.at(taken_counter).second = j;    //saves the taken value of the two battalions
                taken_counter++;
            }
        }
    }*/
    //Number of possibilities for the four sons for all detachments of the battalions
    cout << (possibilities % (1000000000 + 7));
    
    delete [] string_army;
    delete [] Army;
    
    return 0;
}

inline int Factorial(int x) {
    return (x == 1 ? x : x * Factorial(x - 1));
    /*
     ? x : x*Factorial(x-1)
     means
     
     if (x==1)
     {
     return x;
     }
     else{
     return x*Factorial(x-1)
     }
     
     */
}
//Precondition: K is Battalion size, N is Countries to divide up to
//Postcondition: returns the lists of combinations
vector<vector<int>> comb(int N, int K)
{
    vector<vector<int>> temp;
    vector<int> temp1;
    temp.push_back(temp1);
    std::string bitmask(K, 1); // K leading 1's
    bitmask.resize(N, 0); // N-K trailing 0's
    
    int set_counter = 0;
    // print integers and permute bitmask
    do {
        for (int i = 0; i < N; ++i) // [0..N-1] integers
        {
            if (bitmask[i]){
                temp.at(set_counter).push_back(i);
                //std::cout << " " << i;
        }
        }
       // std::cout << std::endl;
        temp.push_back(temp1);
        set_counter++;
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    temp.pop_back();
    return temp;
}
int SumCombinations(int n)
{
    uint sum = 0;
    for (int i = 0; i <= n; i = i+4)
    {
        sum = Combinations(n, i) + sum;
    }
    return sum;
}
uint64_t Combinations(int const & n, int const & r){
    if (n < r){
        return 0;   // if the first is smaller than the second
    }
    if (n == 0 || r == 0)
    {
        return 1;
    }
    if ((n - r) == 0)
    {
        return 1; //x C x, they are the same
    }
    uint x = Factorial (n);  //n!
    uint y = Factorial (r);  //r!
    uint temp = n - r;
    uint xy = Factorial (temp); //(n-r)!
    std::cout << x << " " << y << " " << temp << " " << xy;
    
    x = resize(x);
    y = resize(y);
    xy = resize(xy);
    int temp3 = y * xy;
    temp3 = resize(temp3);
    if (temp3 == 0)
    {
        return 1;
    }
    int new_temp = (x / temp3);
    
    return new_temp;
}

int resize( int x){
    int y = x % (10^9 + 7);
    return y;
}
