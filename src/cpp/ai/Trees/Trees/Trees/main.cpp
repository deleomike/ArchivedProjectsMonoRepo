//
//  main.cpp
//  Trees
//
//  Created by Michael DeLeo on 4/8/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

struct node{
    int key;
    node* left = NULL;
    node* right = NULL;
};

/////////
//AVL
void insert_AVL(node * root, int key);
////////


int main() {
    
    vector<int> input = {6,5,4,3,2,1};
    
    node *root = new node();
    root->key = input[0];
    
    insert_AVL(root, 5);
    insert_AVL(root, 3)
    
    
    return 0;
}

void insert_AVL(node * root, int key){
    if (root == NULL){
        node * n = new node();
        n->key = key;
        root = n;
    }
    if (root -> key > key){
        insert_AVL(root->left,key);
    }
}
