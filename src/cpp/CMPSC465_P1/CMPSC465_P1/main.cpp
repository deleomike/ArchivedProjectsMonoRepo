//
//  main.cpp
//  CMPSC465_P1
//
//  Created by Michael DeLeo on 1/14/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

class stack{
private:
    std::vector<int> values;
    
public:
    
    stack(){}
    
    stack(std::vector<int> x){
        values = x;
    }
    
    std::vector<int> getValues(){
        return values;
    }
    
    int getTop(){
        if (values.size() == 0){
            return 0;
        }
        else{
            return values.at(values.size()-1);
        }

    }
    
    void push(int x){
        values.push_back(x);
    }
    
    void empty(){
        std::vector<int> x;
        values = x;
    }
    
    int pop(){
        if (values.size() == 0){
            std::cout << "error, stack is already empty" << std::endl;
            return 0;
        }
        else{
            int temp = values[values.size()-1];
            values.pop_back();
            return temp;
        }
    }
};

std::vector<int> makeTrain(int size);
std::vector<int> parseLine(std::string line);
std::string checkPermutations(std::vector<int> train, std::vector<std::vector<int>> perm);

int main(int argc, const char * argv[]) {
    
    std::ifstream file;
    file.open("/Users/michaeldeleo/Documents/workspace/CMPSC465_P1/CMPSC465_P1/lab1in.txt");
    if (!file.is_open()){
        std::cout << "File location is invalid" << std::endl;
    }
    std::string line;
    int lastNum = 1;
    int size = 0;
    
    std::vector<int> incomingTrain;
    std::vector<std::vector<int>> permutations;
    
    std::string printValue = "";
    
    while(std::getline(file,line)){
        //std::cout << line << std::endl;
        std::vector<int> test = parseLine(line);
        //first case, it is not an array
        if (test.size() == 1){
            
            int num = stoi(line);
            //It is a size of an array
            if (num > 0){
                //start of new block
                size = num;
                incomingTrain = makeTrain(size);    //get train
            }
            else{
                if (num == lastNum){
                    //this is the end of the file
                }
                else{
                    //this is the end of the block
                    //Do the calculations here for the block
                    printValue += checkPermutations(incomingTrain, permutations);
                    printValue += "\n";
                    std::vector<std::vector<int>> temp;
                    permutations = temp;
                    //reset permuations
                }
            }
            //store previous value
            lastNum = num;
        }
        //second case it is an array
        else{
            //parse the line for the vector
            permutations.push_back(test);
        }
        
    }
    /*
    for (int i = 0; i < length; i++){
        storage.push(trackA[i]);
        std::cout << "Track A at " << i << " is " << trackA[i] << std::endl;
        
        trackB.push_back(storage.pop());
    }
    
    if (trackA == trackB){
        std::cout << "Tracks are the same" << std::endl;
    }
    */
    
    file.close();
    
    for (int i = 0; i < 2; i++){
        printValue.pop_back();
    }
    std::ofstream out;
    out.open("/Users/michaeldeleo/Documents/workspace/CMPSC465_P1/CMPSC465_P1/lab1out.txt");
    if (!out.is_open()){
        std::cout<< "output is not open" << std::endl;
    }
    out << printValue;
    
    out.close();
    
    return 0;
}

///////////////////
//Precondition: size of the train
//Postcondition: returns a vector of the incoming train 1,2,3...,N
//summary:
///////////////////
std::vector<int> makeTrain(int size){
    std::vector<int> x;
    for (int i = 0; i < size; i++){
        x.push_back(i+1);
    }
    return x;
}

///////////////////
//Precondition: String of the line that is from the text file
//Postcondition: The contents of the line in a vector
//summary: splits the string into an int vector using " " as the deliminator
///////////////////
std::vector<int> parseLine(std::string line){
    std::vector<int> x;
    std::string substring = "";
    for (int i = 0; i < line.size(); i++){
        if(line.at(i) == ' '){
            x.push_back(stoi(substring));
            substring = " ";
        }
        else{
            substring += line.at(i);
        }
    }
    x.push_back(stoi(substring));
    return x;
}

///////////////////
//Precondition: Vector of the incoming train, 2D vector of the combinations to test
//Postcondition: nothing
//summary: Tests the incoming train against each combination given, and prints out "yes" if it can be done and "no" if it cannot.
//It implements a stack to help
///////////////////
std::string checkPermutations(std::vector<int> train, std::vector<std::vector<int>> perm){
    stack station;
    std::string reValue = "";
    //push train car onto stack, if it matches the train car in the expected sequence, pop it
    //then check to see if there are others be popped
    //else, push another train car on.
    //if after the whole train has been pushed and there is still some left...then it is not possible
    for (int j = 0; j < perm.size(); j++){
        for (int i = 0; i < train.size(); i++){
            //std::cout << "j: " << j << " i: " << i << std::endl;
            station.push(train.at(i));
            //push train car
            //train.erase(train.begin());
            //delete that train car from incoming track
            
            bool checkAgain = true;
            while(checkAgain){
                checkAgain = false;
                //check with the permutation to see if the top matches
                if (station.getTop() == perm[j][0]){
                    station.pop();
                    //the top matches, so pop the train car to the track b
                    perm[j].erase(perm[j].begin());
                    //cancel the train car
                    checkAgain = true;
                    //there might be another match, check again
                }
            }
        }
        std::vector<int> leftOver = station.getValues();
        if (leftOver.size() != 0){
            reValue += "No\n";
            std::cout << "No" << std::endl;
        }
        else{
            reValue += "Yes\n";
            std::cout << "Yes" << std::endl;
        }
        station.empty();
    }
    
    return reValue;
}
