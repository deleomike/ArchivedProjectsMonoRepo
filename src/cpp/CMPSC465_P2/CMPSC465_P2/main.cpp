//
//  main.cpp
//  CMPSC465_P2
//
//  Created by Michael DeLeo on 2/20/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>


std::vector<std::string> combinations(int n);
bool find(std::vector<std::string> v, std::string s);
bool balanced(std::string v);

int main() {
    int value = 0;
    
    std::cin >> value;
    //std::cout << value << std::endl;
    
    std::vector<std::string> strings;
    
    strings = combinations(value);
    
    //std::cout << "===============" << std::endl;
    
    for (int i = 0; i < strings.size(); i++){
        std::cout << strings.at(i) << std::endl;
    }
    
    return 0;
}

std::vector<std::string> combinations(int n){
    std::vector<std::string> s;
    std::string term = "";
    for (int i = 0; i < n; i++){
        term += "(";
    }
    for (int i = 0; i < n; i++){
        term += ")";
    }
    
    s.push_back(term);
    
    for (int i = 0; i < 2*n; i++){
        for (int j = 0; j < 2*n; j++){
            if (i != j){
                std::string temp = term;
                temp[i] = term[j];
                temp[j] = term[i];
                //std::cout << temp << std::endl;
                if (!find(s,temp)){
                    if (balanced(temp)){
                        s.push_back(temp);
                    }

                }
            }
        }
    }
    return s;
}

bool find(std::vector<std::string> v, std::string s){
    for (int i = 0; i < v.size(); i++){
        if (v.at(i) == s){
            return true;
        }
    }
    return false;
}

bool balanced(std::string v){
    int sum = 0;
    for (int i = 0; i < v.size(); i++){
        if (v.at(i) == '('){
            sum++;
        }
        else{
            sum--;
        }
        
        if (sum < 0){
            return false;
        }
    }
    return true;
}
