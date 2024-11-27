//
//  main.cpp
//  Biconditional
//
//  Created by Michael DeLeo on 1/25/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    //  -(P<->Q) <-> ( (P<->Q) ^ -(PVQ))
    //  -(p->q ^ q->p) <-> ( (p->q ^ q->p) ^ (-p^-q))
    //  -(-pVq ^ -qVp) <-> ( (-pVq ^ -qVp) ^ (-p^-q))
    //  (p^-q)V(q^-p) <-> ((-p^-q V q^-p) ^ ( -p^-q)
    //  (p^-q)V(q^-p) <-> (-p^-q)
    //  ( [ -(p^-q)V(q^-p) V (-p^-q) ] ^ [ -(-p^-q) V (p^-q)V(q^-p) ] )
    //( [ ( [ (-pVq)V(q^-p) V (-p^-q) ] ^ [ (pVq) V (p^-q)V(q^-p) ] ) ] )
    
    vector<int> P;
    vector<int> Q;
    vector<int> set;
    
    for (int i = 0; i <= 1; i++)
    {
        for (int j = 0; j <= 1; j++)
        {
            P.push_back(i);
            Q.push_back(j);
            bool temp = i;
            
            if (!temp*(j))
            {
                set.push_back(1);
            }
            else
            {
                set.push_back(0);
            }
        
        }
    }
    
    cout << "P  Q   Q^-P    " << endl;
    
    for (int i = 0; i < P.size(); i++)
    {
        cout<< P.at(i) << "  "<< Q.at(i) <<  "        " << set.at(i) << endl;
    }
                
                return 0;

    
}
