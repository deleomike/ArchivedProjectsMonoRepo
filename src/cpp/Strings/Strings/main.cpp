#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string eostring(string input);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int strings;
    vector<string> s;
    cin >> strings;
    cin.ignore();
    for (int i = 0; i < strings; i++)
    {
        string temp;
        getline(cin, temp);
        temp = eostring(temp);
        s.push_back(temp);
    }
    
    for (int i = 0; i < s.size(); i++)
    {
        string temp = s.at(i);
        for (int j = 0; j < (s.at(i)).size(); j++)
        {
            
            cout << temp.at(j);
        }
        cout << endl;
    }
    
    
    return 0;
}


string eostring(string input)
{
    int length = input.size();
    string even = "";
    string odd = "";
    for (int i = 0; i < length; i++)
    {
        if (i == 0 || ((i % 2) == 0))
        {
            even += input.at(i);
        }
        else
        {
            odd += input.at(i);
        }
    }
    
    even += " ";
    even += odd;
    return even;
}
