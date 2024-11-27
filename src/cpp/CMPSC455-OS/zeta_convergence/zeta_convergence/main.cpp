//
//  main.cpp
//  zeta_convergence
//
//  Created by Michael DeLeo on 12/13/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

void compute_norm_term();
void compute_term(int seq_num, int index);
void update_all();

vector<vector<float>> seq;

int main() {
    
    vector<float> first;
    seq.push_back(first);
    seq[0].push_back(1);
    seq[0].push_back(1 + 1/pow(2,1.01));
    //first sequence
    
    while(true){
        //check if the highest sequence is size 3
        
        update_all();
        int seq_highest = seq.size() - 1;
        int last_index = seq[seq_highest].size() - 1;
        if (floor(seq[seq_highest-1][last_index]*pow(10,8)) == floor(seq[seq_highest-1][last_index-1]*pow(10,8))){
            float seq_n = seq[seq_highest][last_index];
            float last_n1 = seq[seq_highest][last_index - 1];
            printf("The last value is %10f\nThe second last value is %10f",seq_n,last_n1);
            break;
        }
    }
    //for the first three values, one of the next is created. After, the index is shifted down one for each corresponding index
    
    
    
    return 0;
}

void compute_norm_term(){
    seq[0].push_back(seq[0][seq[0].size()-1] + 1 / pow(seq[0].size()+1,1.01));
    return;
}

void update_all(){
    compute_norm_term();
    if (seq[seq.size()-1].size() >= 3){
        //create new sequence
        vector<float> x;
        seq.push_back(x);
    }
    
    for (int i = 1; i < seq.size(); i++){
        compute_term(i,seq[i].size());
        //computes next term for each sequence
    }
    return;
}

void compute_term(int seq_num, int index){

    long double upper = pow((seq[seq_num-1][index+1]-seq[seq_num-1][index]),2);
    long double lower = (seq[seq_num-1][index+2] - 2*seq[seq_num-1][index+1] + seq[seq_num-1][index]);
    
    //float upper = pow((index + 2),-2.02);
    //float lower = pow(index+3, -1.01) - 2* pow(index+2,-1.01) + pow(index+1,-1.01);
    
    seq[seq_num].push_back(seq[seq_num-1][index] - upper/lower);
    //seq[seq_num].push_back(seq[seq_num-1][index] - upper/lower);

    return;
}
