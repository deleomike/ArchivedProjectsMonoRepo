#include <iostream>
#include <string>
#include <vector>
using namespace std;

class whole_lotta_stacks
{
public:
    void pop();
    //pre: nothing
    //post: deletes top(last) integer of stack
    void push(int x);
    //pre: integer to push back
    //post: stack is pushed back with int at the front
    void print(int iterat);
    //pre: iterator to print
    //post: prints iterator
    int get_size();
    //pre: nothign
    //post: get size of stack
    
    vector<int> stack;
};

int main() {
    string line;
    while (getline(cin, line)) {
        whole_lotta_stacks mystack;
        for (int i = 0; i < line.size(); i++)
        {
            if (line.at(i) == ' ')
            {//do nothing
            }
            else{
                mystack.push(line.at(i)-48);
            }
        }
        
        /*
         int size = mystack.get_size();
         for (int i = 0; i < size; i++)
         {
         mystack.print(i);
         //order may be messed up on popping, pushing
         mystack.pop();
         }*/
        while (mystack.get_size() > 0)
        {
            //mystack.print(0);
            mystack.pop();
        }
        
        
    }
}

void whole_lotta_stacks::pop()
{
    vector<int> temp;
    
    for (int i = stack.size(); i > 1; i--)
    {
        temp.push_back(stack.at(i));
    }//does not save last one
    temp.pop_back();
    vector<int> new_temp;
    for (int i = temp.size(); i >0; i--)
    {
        new_temp.push_back(temp.at(i));
    }
    
    stack = new_temp;
    return;
}

void whole_lotta_stacks::push(int x)
{
    stack.push_back(x);
    return;
}

void whole_lotta_stacks::print(int iterat)
{
    cout << stack.at(iterat);
    return;
}

int whole_lotta_stacks::get_size()
{
    return stack.size();
}
