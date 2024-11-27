//
//  main.cpp
//  Hash Project
//
//  Created by Michael DeLeo on 2/3/17.
//  Copyright � 2017 Michael DeLeo. All rights reserved.
//

//Project 1

#include <iostream>
#include <string>
#include <random>

std::random_device rd;

std::string Encrypt(std::string const &input, int key);
//Pre: string value, Post: returns converted hash string

std::string Decrypt(std::string const &hash, int key);
//Pre: hash string value, Post: returns converted string

using namespace std;

int main()
{
    int random = rd() % 25;
    string input;
    cout << "Enter a Word or Phrase: " << endl;
    getline(cin,input);
    cout << endl;
    
    //Input string name
    
    
    string hash;
    hash = Encrypt(input,random);
    //convert string to hashed string
    
    
    cout << "Hash Value: " << hash << endl;
    //print out hash
    
    string original;
    original = Decrypt(hash,random);
    //convert hash string back to string
    
    
    cout << "Returned String: " << original << endl;
    //Print out string
    
    return 0;
}

std::string Decrypt(std::string const &hash, int key)
{
    string return_value = "";
    
    for (int i = 0; i < hash.size(); i++)
    {
        char temp_;
        
        if (hash.at(i) == ' ')
        {
            temp_= ' ';
        }
        else
        {
            int temp = 90 - (hash.at(i) - 1 + key);
            temp_ = temp + 64;
        }
        
        // cout << hash.at(i) << "    " << temp << "   " << temp_ << endl;
        return_value.push_back(temp_);
    }
    // 26 - ((char-96) - 1) = new char + 96
    return return_value;
}

std::string Encrypt(std::string const &input, int key)
{
    string return_value = "";
    
    for (int i = 0; i < input.size(); i++)
    {
        char temp_;
        
        if (input.at(i) == ' ')
        {
            temp_ = ' ';
        }
        else{
            
        int temp = 90 - (input.at(i) - 1 +key);
            temp_ = temp + 64;
        }
        return_value.push_back(temp_);
    }
    return return_value;
}
