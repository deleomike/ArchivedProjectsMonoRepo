//
//  main.cpp
//  Midterm
//
//  Created by Michael DeLeo on 3/15/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

int func(int x, int y);

#include <iostream>

using namespace std;

int main()
{
    for (int i = 0; i <= 1; i++)
    {
        //X
        for (int j = 0; j <=1; j++)
        {
            //Y
            cout << func(i,j) << " ";
        }
        cout << endl;
    }
    //      Y   notY
    //X     0   1
    //notX  1   1
    
    //For the function f(x,y) = (xy + xy') + (xy + x'y)
}


int func(int x, int y)
{
    int notY;
    if (y == 0)
    {
        notY = 1;
    }
    else
    {
        notY = 0;
    }
    
    int notX;
    if (x == 0)
    {
        notX = 1;
    }
    else{
        notX = 0;
    }
    if (x*y + x*y + x*notY + notX*y == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
    
   
    
}
