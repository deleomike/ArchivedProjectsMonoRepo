//
//  main.cpp
//  Recursions
//
//  Created by Michael DeLeo on 4/1/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;

vector<int> mergeSort(vector<int> A);
vector<int> merge(vector<int> B, vector<int> C);

vector<int> inversions;

int main() {
    //GET INPUT
    ifstream file;
    int N = 5;
    //TODO
    
    vector<int> *input = new vector<int>[N];
    input[0] = {2,4,1,3,5};
    input[1] = {1,2,4,8,9,3,5,6};
    input[2] = {1,20,6,4,5};
    input[3] = {1,2,3,4};
    input[4] = {4,3,2,1};
    //INPUT IS GOTTEN
    
    
    
    std::vector<int> temp;
    for (int i = 0; i < N; i++){
        inversions.push_back(0);
        temp = mergeSort(input[i]);
    }
    
    for (int i = 0; i < inversions.size(); i++){
        cout << "The sequence has " << inversions.at(i) << " inversions." << endl;
    }
    
    delete [] input;
    return 0;
}

vector<int> mergeSort(vector<int> A){
    //base case
    if (A.size() == 1){
        return A;
    }
    else{
        int middle = floor(A.size()/2);
        
        //setup B, and get the first half of the array
        vector<int> B;
        vector<int>::iterator it = A.begin();
        advance(it,middle);
        B.assign(A.begin(),it);
        //now, send B to mergeSort
        B = mergeSort(B);
        
        //setup C, and get the second half of the array
        vector<int> C;
        //advance(it,1);
        C.assign(it,A.end());
        //now send to mergeSort
        C = mergeSort(C);
        
        //Now Merge the two lists
        
        return merge(B,C);
    }
    
}


vector<int> merge(vector<int> B, vector<int> C){
    vector<int> A;
    
    int inversions_temp = inversions.back();
    
    int i, j, m, n;
    i = 0;
    j = 0;
    
    m = B.size();
    n = C.size();
    while (i < m && j < n) {
        if (B[i] <= C[j]) {
            A.push_back(B[i]);
            i++;
        } else {
            inversions_temp += m-i;
            A.push_back(C[j]);
            j++;
        }
    }
    //B is not done yet
    if (i < m) {
        for (int p = i; p < m; p++) {
            A.push_back(B[p]);
        }
    } else {
        //C is not done yet
        for (int p = j; p < n; p++) {
            A.push_back(C[p]);
        }
    }
    
    inversions.at(inversions.size()-1) = inversions_temp;
    return A;
}
