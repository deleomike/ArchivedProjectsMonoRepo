//
//  main.cpp
//  Image Segmentation - Blocks
//
//  Created by Michael DeLeo on 6/26/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int findAdjacent(int nodex, int nodey, int*** const grid);


//incomplete
/*image segmentation by 4 pixel connectivity
 return number of blocks. answer is 7
 */

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int board[4][12] = {{0,0,0,1,1,0,0,0,1,0,1,0},
        {1,1,1,0,1,1,1,1,0,0,0,1},
        {1,1,1,0,1,0,0,1,0,0,1,0},
        {1,0,0,0,0,0,0,0,0,1,0,0}};
    
    int blocks = 0;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 12; j++){
            if (board[i][j] == 1){
                int count = 0;
                int nodey = i;
                int nodex = j;
                if (nodex != 11){
                    //not an end
                    if (board[nodex+1][nodey] == 1){
                        count++;
                    }
                }
                if (nodex != 0){
                    //not a beginning
                    if (board[nodex-1][nodey] == 1){
                        count++;
                    }
                }
                if (nodey != 0){
                    //not the first row
                    if (board[nodex][nodey-1] == 1){
                        count++;
                    }
                }
                if (nodey != 3){
                    if (board[nodex][nodey+1] == 1){
                        count++;
                    }
                }
                if (count >= 4){
                    blocks++;
                }
            }
        }
    }
    cout << blocks;
    return 0;
}
