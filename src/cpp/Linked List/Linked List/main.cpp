//
//  main.cpp
//  Linked List
//
//  Created by Michael DeLeo on 1/19/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <cstddef>
using namespace std;

/*
 Node:
 
 Head -> NULL
 Head -> [data, Next] -> NULL
 Head -> [1, NULL] -> NULL
 Head -> [1, Node2] -> [2, NULL] -> NULL
 Head -> [1, Node2] -> [2, Node3] -> [3,NULL] -> NULL
 
 
 */
class Node
{
public:
    int data;
    Node *next;
    Node(int d){        //constructor
        data=d;
        next=NULL;
    }
};
class Solution{
    public:
        Node* insert(Node *head,int data)
        {
            if (head == NULL){
                //empty list
                Node * temp =  new Node(data);    //new node
                head = temp;
                return head;
            }
            //list is not empty
            Node* iterator = head;
            for (iterator; iterator->next != NULL; iterator = iterator->next){ //goes until it finds a node that is not connected
            }
            Node * temp = new Node(data);
            iterator->next = temp;
            return head;
            
        }


    void display(Node *head)
    {
        Node *start=head;
        while(start)
        {
            cout<<start->data<<" ";
            start=start->next;
        }
    }
};
int main()
{
    Node* head=NULL;
    Solution mylist;
    int T,data;
    cin>>T;
    while(T-- >0){
        cin>>data;
        head=mylist.insert(head,data);
    }
    mylist.display(head);
    
}
