//
//  main.cpp
//  BITWISE AND
//
//  Created by Michael DeLeo on 6/10/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> split_string(string);



int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<int> results;
    for (int t_itr = 0; t_itr < t; t_itr++) {
        string nk_temp;
        getline(cin, nk_temp);
        
        vector<string> nk = split_string(nk_temp);
        
        int n = stoi(nk[0]);
        
        int k = stoi(nk[1]);
        
        //dataset is N size, and the maximum allowed value is less than k
        int max = 0;
        for (int a = 1; a <= n; a++){
            for (int b = 1; b <= n; b++){
                if (a >= b){}
                else if (((a&b) < k) && ((a&b)> max)){
                    max = a&b;
                }
            }
        }
        results.push_back(max);
    }
    for (int i = 0; i < results.size(); i++){
        cout << results.at(i) << endl;
    }
    
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

