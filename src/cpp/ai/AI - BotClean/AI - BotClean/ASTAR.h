//
//  Header.h
//  AI - BotClean
//
//  Created by Michael DeLeo on 6/14/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string>

using namespace std;

struct node{
    int ID;
    node* parent;
};

vector<int> getCoord(int & node, vector<vector<int>> grid);
int heuristic(int start, int end, vector<vector<int>> grid);
vector<int> findAdjacent(int node, vector<vector<int>> grid);
void closeNode(int node, vector<int> & open, vector<int> & closed);
vector<int> removeCopies(vector<int> open, vector<int> closed, vector<int> & victim);
vector<node*> connectParent(vector<node*> nodeList, vector<int> nodes, node* & par);
vector<node*>::iterator find(vector<node*>::iterator begin, vector<node*>::iterator const & end, int ID);
int findMinNode(vector<int> const & open, int const & Goal, vector<vector<int>> const & distances);
void reverse(vector<int> & subject);

#endif /* Header_h */
