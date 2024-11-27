//
//  main.cpp
//  Queues and Stacks
//
//  Created by Michael DeLeo on 4/7/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Solution {
    //Write your code here
private:
    stack<char> st;
    queue<char> qu;
public:
    void pushCharacter(char x);
    void enqueueCharacter(char x);
    char popCharacter();
    char dequeueCharacter();
};

//NOTES:
//stacks are LIFO - Last in first out
//this means that if a char x is pushed in, and then a char is popped, it will be x

//top is end of container, bottom is beginning

/////////////////////////////////////////////////////////////////
//Precondition: char variable
//Postcondition: nothing
//function: pushes a char x onto the stack
/////////////////////////////////////////////////////////////////
void Solution::pushCharacter(char x){
    st.push(x);
    return;
}

/////////////////////////////////////////////////////////////////
//Precondition: nothing
//Postcondition: char
//function: pops a char x from the top of the stack, and returns it
/////////////////////////////////////////////////////////////////
char Solution::popCharacter(){
    char temp = st.top();
    st.pop();
    return temp;
}

//NOTES:
//queues are FIFO - first in first out
//addition: enqueue, adds an element to bottom of queue
//subtractions: dequeue, subtracts an element from top of queue

//back is the spot where push adds an element, front is where the elements are popped

/////////////////////////////////////////////////////////////////
//Precondition: char x
//Postcondition: nothing
//function: pushes a char to the beginning of the queue
/////////////////////////////////////////////////////////////////
void Solution::enqueueCharacter(char x){
    qu.push(x);//puts it in the back
    return;
}

/////////////////////////////////////////////////////////////////
//Precondition: nothing
//Postcondition: char
//function: pops a char from the front of the queue and returns it
/////////////////////////////////////////////////////////////////
char Solution::dequeueCharacter(){
    char temp = qu.front();
    qu.pop();
    return temp;
}

int main() {
    // read the string s.
    string s;
    getline(cin, s);
    
    // create the Solution class object p.
    Solution obj;
    
    // push/enqueue all the characters of string s to stack.
    for (int i = 0; i < s.length(); i++) {
        obj.pushCharacter(s[i]);
        obj.enqueueCharacter(s[i]);
    }
    
    bool isPalindrome = true;
    
    // pop the top character from stack.
    // dequeue the first character from queue.
    // compare both the characters.
    for (int i = 0; i < s.length() / 2; i++) {
        if (obj.popCharacter() != obj.dequeueCharacter()) {
            isPalindrome = false;
            
            break;
        }
    }
    
    // finally print whether string s is palindrome or not.
    if (isPalindrome) {
        cout << "The word, " << s << ", is a palindrome.";
    } else {
        cout << "The word, " << s << ", is not a palindrome.";
    }
    
    return 0;
}
