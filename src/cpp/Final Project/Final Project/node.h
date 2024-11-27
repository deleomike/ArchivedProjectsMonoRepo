//
//  node.h
//  Final Project
//
//  Created by Michael DeLeo on 6/18/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#ifndef node_h
#define node_h

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <vector>

using namespace std;

struct node{
    int ID;
    node* parent;
};

vector<int> getCoord(int & node, vector<vector<int>> grid);
int heuristic(int start, int end, vector<vector<int>> grid);
vector<int> findAdjacent(int node, vector<vector<int>> grid);
void closeNode(int node, vector<int> & open, vector<int> & closed);
void closeNode(int node, vector<int> & closed);
vector<int> removeCopies(vector<int> open, vector<int> closed, vector<int> & victim);

vector<node*> connectParent(vector<node*> nodeList, vector<int> nodes, node* & par);
vector<node*>::iterator find(vector<node*>::iterator begin, vector<node*>::iterator const & end, int ID);
int findMinNode(vector<int> const & open, int const & Goal, vector<vector<int>> const & distances);
void reverse(vector<int> & subject);
vector<string> finalPath(int n, vector <string> grid);

#endif /* node_h */
