//
//  main.cpp
//  MergeSort
//
//  Created by Michael DeLeo on 9/11/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

void mergeHalves(vector<int> & arr, int begin, int end);
void mergesort(vector<int> arr, int begin, int end);
void print(vector<int> a);


// Complete the countInversions function below.
int main(){
    vector<int> test  = {10,22,27,1,25,10,13,7,45};
    print(test);
    mergesort(test,0,test.size()-1);
    print(test);
    
    return 0;
}

void print(vector<int> a){
    for (int i = 0; i < a.size(); i++){
        cout << a[i] << " ";
    }
    cout << endl;
    return;
}

void mergesort(vector<int>  arr, int begin, int end){
    if (begin >= end){
        return;
        //mergesort is done
    }
    
    int middle = floor((begin + end)/2);
    mergesort(arr, begin, middle);
    mergesort(arr, middle + 1, end);
    mergeHalves(arr, begin, end);
    return;
}

void mergeHalves(vector<int>  & arr, int begin, int end){
    int leftEnd = (begin + end)/2;  //middle is the left end of the iteration
    int rightstart = leftEnd + 1;   //the right starting point is one index from the left end
    int size = end - begin +1;  //the size is basically half the size + 1
    
    int left = begin;   //left index at the beginning of the array
    int right = rightstart;//right index at the middle, 1 index past the left's end of iteration
    int index = begin;
    
    vector<int> temp;   //the new array to store the sorted values
    //the condition basically says that while the left iterator is less than the halfway point
    //and while the right iterator is less than the end of the array, keep going
    while (left <= leftEnd && right <= end){
        if (arr[left] <= arr[right]){
            //left index value is less than the right index value, store in sorted array
            temp.push_back(arr[left]);
            left++;
            index++;
        }
        else{
            //right index value is less than the lest index value, store in sorted array
            temp.push_back(arr[right]);
            right++;
            index++;
        }
    }
    
    //MERGES//
    //Merge the remaining elements of the array into temp
    
    
    //copy array starting at left iterator to temp array starting at index,
    //till length half of array
    copy(arr.begin() + left, arr.begin() +leftEnd - left + 1, temp.begin() + index);
    
    //copy array starting at right index to temp array starting at index
    //till the end - right index + 1
    copy(arr.begin() + right, arr.begin() + end - right + 1, temp.begin() + index);
    
    //merge the temp vector that is partially sorted back into the array
    copy(temp.begin() + begin, temp.end(), arr.begin() + begin);
    return;
}
