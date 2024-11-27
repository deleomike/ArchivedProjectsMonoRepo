//
//  main.cpp
//  BubbleSort
//
//  Created by Michael DeLeo on 9/8/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//  Description: This code sorts an array of n size of integer values. Sorting method is bubble sort
//  Input: n (size)
//         1 2 ... n (array)

#include <iostream>
#include <vector>

using namespace std;

vector<string> split_string(string);

// Complete the countSwaps function below.
void countSwaps(vector<int> a) {
    int swaps = 0;
    
    for (int i = 0; i < a.size(); i++){
        for (int j = 0; j < (a.size() -1); j++){
            if (a[j] > a[j+1]){
                int temp = a[j+1];
                a[j+1] = a[j];
                a[j]=temp;
                swaps++;
            }  //compares this element to the next, if j is greater than j + 1 switch
            
        }
    }
    std::cout << "Array is sorted in " << swaps<< " swaps." << std::endl;
    std::cout << "First Element: " << a[0] << std::endl;
    std::cout << "Last Element: " << a[a.size()-1] << std::endl;
    
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    string a_temp_temp;
    getline(cin, a_temp_temp);
    
    vector<string> a_temp = split_string(a_temp_temp);
    
    vector<int> a(n);
    
    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);
        
        a[i] = a_item;
    }
    
    countSwaps(a);
    
    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });
    
    input_string.erase(new_end, input_string.end());
    
    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }
    
    vector<string> splits;
    char delimiter = ' ';
    
    size_t i = 0;
    size_t pos = input_string.find(delimiter);
    
    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));
        
        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }
    
    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));
    
    return splits;
}

