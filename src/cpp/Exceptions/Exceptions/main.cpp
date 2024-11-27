//
//  main.cpp
//  Exceptions
//
//  Created by Michael DeLeo on 4/7/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//
#include <cmath>
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

struct negative : exception{
    const char* what() const noexcept {return "n and p should be non-negative";}
};

class Calculator{
public:
    //Calculator();
    int power(int n, int p){
        if (n <0 || p<0){
            throw negative();
            return 0;
        }
        else{
            return pow(n,p);
        }
    }
};

int main()
{
    Calculator myCalculator=Calculator();
    int T,n,p;
    cin>>T;
    while(T-->0){
        if(scanf("%d %d",&n,&p)==2){
            try{
                int ans=myCalculator.power(n,p);
                cout<<ans<<endl;
            }
            catch(exception& e){
                cout<<e.what()<<endl;
            }
        }
    }
    
}
