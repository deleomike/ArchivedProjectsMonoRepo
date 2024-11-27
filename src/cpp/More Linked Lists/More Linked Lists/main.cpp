//
//  main.cpp
//  More Linked Lists
//
//  Created by Michael DeLeo on 4/7/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <cstddef>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Node
{
public:
    int data;
    Node *next;
    Node(int d){
        data=d;
        next=NULL;
    }
};
class Solution{
public:
    
    Node* removeDuplicates(Node *head)
    {
        vector<int> data;
        //Write your code here
        vector<int> unique;
        Node* iterator = head;
        for (iterator = head; iterator -> next != NULL; iterator = iterator = iterator -> next){
            data.push_back(iterator->data);
        }
        data.push_back(iterator->data);
        for (int i = 0; i < data.size(); i++){
            //check if it is unique
            if (!unique.empty()){
                if (find(unique.begin(),unique.end(),data[i]) == unique.end() && unique[unique.size()-1] != data[i]){
                    //not a copy, save as unique
                    unique.push_back(data[i]);
                }
                else{
                    //delete copy
                    data.erase(data.begin()+i);
                    i--;
                    //keep iterating till its gone, offset the iterator because an element is gone
                }

            }//empty, pushback
            else{
                unique.push_back(data[i]);
            }
        }
        head = NULL;
        for (int i = 0; i < data.size(); i++){
            head = insert(head, data[i]);
        }
        
        return head;
    }
    
//    Node* deleteNode(Node* head, int index){
//        Node* iterator = head;
//        for (int i = 0; i < index -1; i++){
//            iterator = iterator->next;
//        }
//        Node* secondNode = iterator->next -> next;
//        iterator -> next = secondNode;
//        return head;
//    }

Node* insert(Node *head,int data)
{
    Node* p=new Node(data);
    if(head==NULL){
        head=p;
        
    }
    else if(head->next==NULL){
        head->next=p;
        
    }
    else{
        Node *start=head;
        while(start->next!=NULL){
            start=start->next;
        }
        start->next=p;
        
    }
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
    while(T-->0){
        cin>>data;
        head=mylist.insert(head,data);
    }
    head=mylist.removeDuplicates(head);
    
    mylist.display(head);
    
}
