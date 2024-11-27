//
//  main.cpp
//  Abstract Class
//
//  Created by Michael DeLeo on 1/19/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class Book{
protected:
    string title;
    string author;
public:
    Book(string t,string a){
        title=t;
        author=a;
    }
    virtual void display()=0;
    
};

//ABSTRACT CLASS - A class with at least one abstract method (declared without implementation)
//                - May have abstract and non abstract methods
//                - Cannot be initialized

// Write your MyBook class here
class MyBook : public Book{
public:
//   Class Constructor
//
//   Parameters:
//   title - The book's title.
//   author - The book's author.
//   price - The book's price.
//
// Write your constructor here
    MyBook(string title, string author, int price);

//   Function Name: display
//   Print the title, author, and price in the specified format.
//
// Write your method here
    void display(void);
    
    int price;
};
// End class

int main() {
    string title,author;
    int price;
    getline(cin,title);
    getline(cin,author);
    cin>>price;
    MyBook novel(title,author,price);
    novel.display();
    return 0;
}


MyBook::MyBook(string title, string author, int price)
        : Book(title, author){
    this -> price = price;
}

void MyBook::display(void){
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Price: " << price << endl;
    return;
}
