//
//  main.cpp
//  Venn Diagram
//
//
//
//  Created by Michael DeLeo on 1/24/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> A;
    vector<int> B;
    vector<int> C;
    vector<int> venn;
    
    
    for (int i = 0; i <= 1; i++)
    {
        //A.push_back(i);
        for (int j = 0; j <= 1; j++)
        {
            //A.push_back(i);
            //B.push_back(j);
            for (int k = 0; k <= 1; k++)
            {
                A.push_back(i);
                B.push_back(j);
                C.push_back(k);
                if (i*(!j)*(!k))
                {
                    venn.push_back(1);
                }
                
                else{
                    venn.push_back(0);
                }
            }
        }
    }
    
    cout << "A  B  C   (A-B)^(A-C)" << endl;
    
    for (int i = 0; i < A.size(); i++)
    {
        cout<< A.at(i) << "  "<< B.at(i) << "  " << C.at(i) << "        " << venn.at(i) << endl;
    }
    return 0;
}
