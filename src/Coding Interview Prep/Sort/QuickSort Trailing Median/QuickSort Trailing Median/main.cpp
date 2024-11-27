//
//  main.cpp
//  QuickSort Trailing Median
//
//  Created by Michael DeLeo on 9/10/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>


using namespace std;
void quicksort(vector<int> & a, const int left, const int right, const int sz);
int partition(vector<int> & a, const int left, const int right);
void Swap_One(vector<int> & a, int num1, int num2);

vector<string> split_string(string);

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {
    int notices = 0;
    vector<int> trailing_days;
    for (int i = 0; i < expenditure.size(); i++){
        if (i >= d){    //at this point, the iteration has the reached the step after d days. i is thus the current day
            
            //only gets an unsorted array for the first time, then keeps the sorted array and replaces the new element
            if (notices == 0){
                for(int j = 1; j <= d; j++){ //get d days before this day
                    trailing_days.push_back(expenditure[i-j]);
                }
                //now the list of trailing days is ready, now find the median
                //sort
            }
            else{
                Swap_One(trailing_days, expenditure[i-d-1],expenditure[i-1]);
            }
            
            quicksort(trailing_days,0,d-1, d);
            double median = 0;
            //finds median for even number
            if (trailing_days.size() % 2 == 0){
                int m1 = d/2;
                int m2 = m1 -1;
                median = (trailing_days[m1] + trailing_days[m2]);
            }
            else{
                median = trailing_days[(d -1)/2] * 2;
            }
            //std::cout << median << " "<< expenditure[i] << std::endl;
            if ((median) <= expenditure[i]){
                notices++;
                //std::cout << notices<< std::endl;
            }
        }
    }
    return notices;
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
    //std::cout << "QSC:" << left << "," << right << " part=" << part << "\n";
    
    //DIVIDE AND CONQUER
    quicksort(a, left, part - 1, sz);   //do the quicksort on values less than the midpoint
    quicksort(a, part + 1, right, sz);  //do the quicksort on values greater than the midpoint
}

void Swap_One(vector<int> & a, int num1, int num2){
    int sz = a.size();
    if (a[sz/2] > num1){
        vector<int>::iterator it = find(a.begin() + sz/2, a.end(),num1);
        *it = num2;
    }
    else{
        vector<int>::iterator it = find(a.begin(), a.begin() + sz/2, num1);
        *it = num2;
    }
    
    return;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));
    
    string nd_temp;
    getline(cin, nd_temp);
    
    vector<string> nd = split_string(nd_temp);
    
    int n = stoi(nd[0]);
    
    int d = stoi(nd[1]);
    
    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);
    
    vector<string> expenditure_temp = split_string(expenditure_temp_temp);
    
    vector<int> expenditure(n);
    
    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);
        
        expenditure[i] = expenditure_item;
    }
    
    int result = activityNotifications(expenditure, d);
    
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

