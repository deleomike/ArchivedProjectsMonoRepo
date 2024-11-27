//
//  main.cpp
//  StringManip
//
//  Created by Michael DeLeo on 3/17/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main() {
    string s(10,'0');
    cout << s << endl;
    string s2 = "1001";
    s.replace(s.size()-s2.size(),s2.size(),s2);
    cout << s << endl;
    
    return 0;
}
