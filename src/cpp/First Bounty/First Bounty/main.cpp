//
//  main.cpp
//  First Bounty
//
//  Created by Michael DeLeo on 4/3/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

int matrix[3][4];

#include <iostream>
#include <utility>

int cellValue(int i, int j);

int main()
{
    
    
    for (int i = 0; i <3; i++)
    {
        for (int j = 0; j<4; j++)
        {
            matrix[i][j]=0;
        }
    }
    for (int i = 0; i < 4; i++)
    {
    matrix[0][i] = 1500;
    }
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (j == 0 && i == 0)
            {
                i = 1;
            }
           
            matrix[i][j]= cellValue(i,j);
            
            
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            
            std::cout<<matrix[i][j] << " ";

        }
        std::cout<<std::endl;
    }
    
    return 0;
}

int cellValue(int i, int j)
{
    int max_1 = matrix[i-1][j];
    
    int max_2 = matrix[i-1][j-0];
    
    int stereo = 3;
    int laptop = 2;
    if (i == 1)
    {
        
        if (j == stereo)
        {
             max_2 = 3000;
        }
    }
    else if (i == 2)
    {
        if (j >= laptop)
        {
            if (j-laptop == 1)
            {
                max_2 = 1500+2000;
            }
            else{
                max_2 = 2000;
            }
        }
    }
    
    
    
    if (max_1 >= max_2)
    {
        return max_1;
    }
    else
    {
        return max_2;
    }
}
