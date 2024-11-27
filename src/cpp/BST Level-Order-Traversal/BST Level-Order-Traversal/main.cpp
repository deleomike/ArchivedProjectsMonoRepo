//
//  main.cpp
//  BST Level-Order-Traversal
//
//  Created by Michael DeLeo on 4/7/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <cstddef>
#include <queue>
#include <string>
#include <cstdlib>

using namespace std;
class Node{
public:
    int data;
    Node *left,*right;
    Node(int d){
        data=d;
        left=right=NULL;
    }
};
class Solution{
public:
  		Node* insert(Node* root, int data){
            if(root==NULL){
                return new Node(data);
            }
            else{
                Node* cur;
                if(data<=root->data){
                    cur=insert(root->left,data);
                    root->left=cur;
                }
                else{
                    cur=insert(root->right,data);
                    root->right=cur;
                }
                return root;
            }
        }

    void levelOrder(Node * root){
        //Write your code here
        
        queue<Node*> q;
        
        if (root) {
            q.push(root);
        }
        while (!q.empty())
        {
            const Node * const temp_node = q.front();
            q.pop();
            cout<<temp_node->data << " ";
            
            if (temp_node->left) {
                q.push(temp_node->left);
            }
            if (temp_node->right) {
                q.push(temp_node->right);
            }
        }
        /*
        //if node is not a leaf, enqueue
        if (root != NULL){
            qu.push(root);
        }
        
        while (!(qu.empty())){
            Node * new_root = dequeueCharacter();
            
            levelOrder(new_root);
            
            if (root -> left != NULL){
                qu.push(root->left);
            }
            if (root -> right != NULL){
                qu.push(root->right);
            }
        }
        */
        
    }
};//End of Solution
int main(){
    Solution myTree;
    Node* root=NULL;
    int T,data;
    cin>>T;
    while(T-->0){
        cin>>data;
        root= myTree.insert(root,data);
    }
    myTree.levelOrder(root);
    return 0;
}
