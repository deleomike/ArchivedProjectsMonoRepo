//
//  main.cpp
//  CMPSC465_P3
//
//  Created by Michael DeLeo on 3/17/19.
//  Copyright � 2019 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct coordinate{
    int x;
    int y;
};

std::vector<std::vector<char>> getInput();
std::vector<coordinate> adjacentO(coordinate c);
void dfs(coordinate c);


std::vector<std::vector<char>> input;
std::vector<std::vector<bool>> checked;

int main() {
    input = getInput();
    
    //setup the checked matrix
    for (int i = 0; i < input.size(); i++){
        std::vector<bool> v;
        checked.push_back(v);
        for (int j = 0; j < input.size(); j++){
            checked[i].push_back(false);
        }
    }
    
    //////////////////////////////
    //check obvious ones. such as if the 0 has four direct neighbors of x
    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.size(); j++){
            //if the node is a wall node
            if ((i == 0 || i == input.size()-1) || (j==0 || j == input.size()-1)){
                //if it hasnt been checked
                if (!checked[i][j]){
                    //if the node is an x
                    if (input[i][j] == 'X'){
                        checked[i][j] = true;
                    }
                    //if the node is an O
                    else{
                        //check if there is a branch
                        coordinate c;
                        c.x = i;
                        c.y = j;
                        dfs(c);
                    }
                }
            }
            
        }
    }
    
    for(int i = 1; i < input.size()-1; i++){
        for (int j = 1; j < input.size() -1; j++){
            if (!checked[i][j]){
                input[i][j] = 'X';
                checked[i][j] = true;
            }
        }
    }
    
    for (int i = 0; i < input.size(); i++){
        for (int j = 0; j < input.size(); j++){
            std::cout << input[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}

std::vector<std::vector<char>> getInput(){
    std::vector<std::vector<char>> res;
    std::fstream file;
    file.open("input.txt",std::ios::in);
    
    if (!file.is_open()){
        std::cout << "File could not be opened, you have it in the wrong place!" << std::endl;
        exit(1);
    }
    
    std::string line;
    getline(file,line);
    int n = stoi(line);
    
    for (int i = 0; i < n; i++){
        getline(file,line);//get the next line
        //parse the line
        std::vector<char> temp;
        res.push_back(temp);
        for (int j = 0; j < line.size(); j++){
            if (line.at(j) != ' '){
                res.at(i).push_back(line.at(j));
            }
        }
    }
    
    file.close();
    return res;
}


void dfs(coordinate c){
    checked[c.x][c.y] = true;//set the node as checked
    
    std::vector<coordinate> adjacent = adjacentO(c);
    //check all neighbors
    for (int i = 0; i < adjacent.size(); i++){
        coordinate temp = adjacent[i];
        //if it is not checked, check it
        if (!checked[temp.x][temp.y]){
            dfs(temp);
        }
    }
}


//find the coordinate of an adjacent O
std::vector<coordinate> adjacentO(coordinate c){
    std::vector<coordinate> res;
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            try{
                //try to get the neighbor at [current.x+i][current.y+i]
                //if it is 'O' it is a neighbor
                if (input.at(c.x+i).at(c.y+j) == 'O' && i!=j && (j+i)!=0){
                    coordinate x;
                    x.x = c.x+i;
                    x.y = c.y+j;
                    res.push_back(x);
                }
            }//catch out of range
            catch(std::out_of_range){}
        }
    }
    return res;
}

