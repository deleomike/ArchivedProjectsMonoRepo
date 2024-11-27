//
//  main.cpp
//  30DOC Testing
//
//  Created by Michael DeLeo on 4/17/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

std::vector<int> string2int (std::string num);
bool isCancel(std::vector<int> first, std::vector<int> students);

int main() {
    std::vector<std::vector<int>> raw_data;
    std::string temp;
    getline(std::cin, temp);
    int line_num = std::stoi(temp)*2;
    for (int i = 0; i < line_num; i++){
        getline(std::cin,temp);
        std::vector<int> raw_values = string2int(temp);
        raw_data.push_back(raw_values);
    }
    for (int i = 0; i < line_num; i+=2){
        if (isCancel(raw_data[i],raw_data[i+1])){
            std::cout<<"NO" <<std::endl;
        }
        else{
            std::cout <<"YES"<< std::endl;
        }
    }
    return 0;
}

bool isCancel(std::vector<int> first, std::vector<int> students){
    int size = first[0];
    int late_thresh = first[1];
    
    int num_late = 0;
    for (int i = 0; i < size; i++){
        if (students[i] > 0){
            num_late++;
            //counts late student
        }
    }
    if (num_late >= late_thresh){
        return true;
    }
    else{
        return false;
    }
}

std::vector<int> string2int (std::string num){
    std::stringstream stream(num);
    std::vector<int> temp;
    while(stream){
        int n;
        stream>>n;
        temp.push_back(n);
    }
    temp.pop_back();
    return temp;
}
