//
//  main.cpp
//  Sorting
//
//  Created by Michael DeLeo on 4/7/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>

//#include <bits/stdc++.h>
#include <vector>

using namespace std;

int BubbleSort(vector<int> & a){
    int numSwaps = 0;
    for (int i = 0; i < a.size(); i++) {
        // Track number of elements swapped during a single array traversal
        int numberOfSwaps = 0;
        
        for (int j = 0; j < a.size() - 1; j++) {
            // Swap adjacent elements if they are in decreasing order
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                numberOfSwaps++;
            }
        }
        
        // If no elements were swapped during a traversal, array is sorted
        if (numberOfSwaps == 0) {
            break;
        }
        numSwaps += numberOfSwaps;
    }
    return numSwaps;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int a_i = 0; a_i < n; a_i++){
        cin >> a[a_i];
    }
    // Write Your Code Here
    int numSwaps =  BubbleSort(a);
    cout << "Array is sorted in " << numSwaps <<" swaps." << endl;
    cout << "First Element: " << a.front() << endl;
    cout << "Last Element: " << a.back();
    return 0;
}
