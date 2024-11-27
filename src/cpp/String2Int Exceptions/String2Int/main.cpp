#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


int main(){
    string S;
    cin >> S;
    int value = 0;
    try{
        value = stoi(S);
        cout << value;
    }
    catch (const invalid_argument){
        cout << "Bad String";
    }
    
    
    /*
     format is 
     
     try{
     //try this it may not work
     }
     catch (exception we are expecting){
     //it is not right!
     }
     finally{
     //do this no matter what
     }
     
     this is used to catch things that are actually wrong in the program without crashing,
     and can be used to find illogical things in the program that dont crash it but is not supposed to happen
     
     ex:
     in a game you should not have negative points. so an exception is thrown if there is negative score
     
     ---
     normal exceptions arise from logical errors
     and from syntax or bad access
     */
    return 0;
}
