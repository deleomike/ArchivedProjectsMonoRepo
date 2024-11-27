//
//  main.cpp
//  QuickSort
//
//  Created by Michael DeLeo on 9/9/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<string> split_string(string);
void quicksort(vector<int> & a, const int left, const int right, const int sz);
int partition(vector<int> & a, const int left, const int right);


// Complete the maximumToys function below.
int maximumToys(vector<int> prices, int k) {
    
    quicksort(prices,   0,  prices.size()-1,    prices.size());
    int money = k;
    int num_toys = 0;
    for(int i = 0; i < prices.size(); i++){
        if (prices[i] > money){
            
        }
        else{
            money = money - prices[i];
            num_toys++;
        }
    }
    return num_toys;
}

int partition(vector<int> & a, const int left, const int right) {
    const int mid = left + (right - left) / 2;  //midpoint value
    const int pivot = a[mid];           //pivot is the value at the midpoint index
    // move the mid point value to the front.
    std::swap(a[mid],a[left]);          //swap the midpoint and the value at left index
    int i = left + 1;
    int j = right;
    while (i <= j) {
        while(i <= j && a[i] <= pivot) {
            i++;
        }
        
        while(i <= j && a[j] > pivot) {
            j--;
        }
        
        if (i < j) {
            std::swap(a[i], a[j]);
        }
    }
    std::swap(a[i - 1],a[left]);
    return i - 1;
}

void quicksort(vector<int> & a, const int left, const int right, const int sz){
    
    if (left >= right) {    //if left index is greater than right index then recursion is over
        return;
    }
    
    
    int part = partition(a, left, right);   //find the partition
    std::cout << "QSC:" << left << "," << right << " part=" << part << "\n";
    
    //DIVIDE AND CONQUER
    quicksort(a, left, part - 1, sz);   //do the quicksort on values less than the midpoint
    quicksort(a, part + 1, right, sz);  //do the quicksort on values greater than the midpoint
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));
    
    string nk_temp;
    getline(cin, nk_temp);
    
    vector<string> nk = split_string(nk_temp);
    
    int n = stoi(nk[0]);
    
    int k = stoi(nk[1]);
    
    string prices_temp_temp;
    getline(cin, prices_temp_temp);
    
    vector<string> prices_temp = split_string(prices_temp_temp);
    
    vector<int> prices(n);
    
    for (int i = 0; i < n; i++) {
        int prices_item = stoi(prices_temp[i]);
        
        prices[i] = prices_item;
    }
    
    int result = maximumToys(prices, k);
    
    fout << result << "\n";
    
    fout.close();
    
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

