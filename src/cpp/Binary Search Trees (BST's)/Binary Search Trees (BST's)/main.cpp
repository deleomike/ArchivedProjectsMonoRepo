//
//  main.cpp
//  Binary Search Trees (BST's)
//
//  Created by Michael DeLeo on 4/7/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>

#include <iostream>
#include <cstddef>

using namespace std;

class Node{
public:
    int data;
    Node *left;
    Node *right;
    Node(int d){
        data = d;
        left = NULL;
        right = NULL;
    }
};
class Solution{
public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            }
            else {
                Node* cur;
                if(data <= root->data){
                    cur = insert(root->left, data);
                    root->left = cur;
                }
                else{
                    cur = insert(root->right, data);
                    root->right = cur;
                }
                
                return root;
            }
        }
    //////////////////////////////////////////////
    int getHeight(Node* root){
        //Write your code here
        //exit case: both branches have no connection, therefore they are -1, and height of that node is
        //1+max(-1,-1), => 1+ (-1) => 0
        //or the root is not on a connection
        if (root == NULL){
            return 0;
        }
        if (root->left == NULL && root->right == NULL){
            return 0;
        }//node is a leaf, and has a height of 0
        int left = getHeight(root->left);
        int right = getHeight(root->right);
        int temp = 1+ max(left,right);

        return temp;
    }
    
    



}; //End of Solution

int main() {
    Solution myTree;
    Node* root = NULL;
    int t;
    int data;
    
    cin >> t;
    
    while(t-- > 0){
        cin >> data;
        root = myTree.insert(root, data);
    }
    int height = myTree.getHeight(root);
    cout << height;
    
    return 0;
}

