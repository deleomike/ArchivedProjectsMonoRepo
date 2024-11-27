//
//  main.cpp
//  Heighway Dragon
//
//  Created by Michael DeLeo on 11/6/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
using namespace std;



string str_rewrite_recurse(string D, int n){
    
    std::regex a ("\\a");
    std::regex b ("\\b");
    //take one iteration of replacing
    
    //std::regex_replace (std::back_inserter(result), s.begin(), s.end(), e, "$2");
    
    
    return "s";
}

string str_rewrite_once(string & D){
    vector<string> subsets;
    string temp;
    subsets.push_back(temp);
    int cursor = 0;
    for (int i = 0; i < D.size(); i++){
        if (D.at(i) == 'a' || D.at(i) == 'b'){
            subsets[cursor] += D.at(i);
            cursor++;
        }
        else{
            subsets[cursor] += D.at(i);
        }
    }
    //the string has been seperated into parts
    
    std::regex a ("(a)(.*)");
    std::cmatch m;
    //std::regex_match(D,m,a);
    //td::regex_match(D, m, a);
    
    if(std::regex_match(D,a)){
        std::cout << "match";
    }
    std::string result;
    result = std::regex_replace(D,a,"D");
    
    return D;
}

int main() {
    std::string D = "Fa";
    //cout << "h";
    cout << str_rewrite_once(D);
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    string a = "FeeksForGeeks";
    
    // Here b is an object of regex (regular expression)
    regex b("(F)(.)"); // Geeks followed by any character
    
    // regex_match function matches string a against regex b
    if ( regex_match(a, b) )
    cout << "String 'a' matches regular expression 'b' \n";
    
    // regex_match function for matching a range in string
    // against regex b
    if ( regex_match(a.begin(), a.end(), b) )
    cout << "String 'a' matches with regular expression "
    "'b' in the range from 0 to string end\n";
    return 0;
}

