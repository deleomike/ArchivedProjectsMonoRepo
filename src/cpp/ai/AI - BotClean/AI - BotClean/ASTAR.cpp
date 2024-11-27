//
//  ASTAR.cpp
//  AI - BotClean
//
//  Created by Michael DeLeo on 6/14/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>
#include "ASTAR.h"

vector<node*>::iterator find(vector<node*>::iterator begin, vector<node*>::iterator const & end, int ID){
    for (vector<node*>::iterator it = begin; it != end; it++){
        if ((*it)->ID == ID){
            return it;
        }
    }
    return end;
}

int findMinNode(vector<int> const & open, int const & Goal, vector<vector<int>> const & distances){
    int min = 10000;
    int min_node = -1;
    for (int i = 0; i < open.size(); i++){
        int F = 1;
        F += heuristic(open[i], Goal, distances);
        if (min > F){
            min = F;
            min_node = open[i];
        }
    }
    return min_node;
}

void reverse(vector<int> & subject){
    vector<int> reversed;
    for (int i = subject.size()-1; i >= 0; i--){
        reversed.push_back(subject[i]);
    }
    subject = reversed;
    return;
}



//////////////////////////////////////////////////////////
//Precondition: node ID, open list, closed list
//Postcondition: removes node from open list and adds it to closed list
//////////////////////////////////////////////////////////
void closeNode(int node, vector<int> & open, vector<int> & closed){
    vector<int>::iterator it = find(open.begin(),open.end(),node);
    open.erase(it);
    closed.push_back(node);
    return;
}

//////////////////////////////////////////////////////////
//Precondition: node list to be added to, list of node IDs to use, parent node to be connected
//Postcondition: returns coordinates. [0] is x axis, [1] is y axis. 0->N-1
//////////////////////////////////////////////////////////
vector<node*> connectParent(vector<node*> nodeList, vector<int> nodes, node* & par){
    node** n = new node*[nodes.size()];
    for (int i = 0; i < nodes.size(); i++){
        n[i] = new node; //new child node
        n[i]->ID = nodes[i];   //list of ID's to use
        n[i]->parent = &(*par);
        nodeList.push_back(n[i]);
        //make a node, assign ID, and assign start as the parent. Then push back into node list
    }
    return nodeList;
}

//////////////////////////////////////////////////////////
//Precondition: open list, closed list, and victim list that will have copies removed
//Postcondition: returns copies removed
//////////////////////////////////////////////////////////
vector<int> removeCopies(vector<int> open, vector<int> closed, vector<int> & victim){
    vector<int> copies;
    int last_node_open = open.at(open.size()-1);
    int last_node_closed = closed.at(closed.size()-1);
    //gets the last nodes to check with the find function
    for (int i = 0; i < victim.size(); i++){
        if (find(open.begin(),open.end(),victim[i]) == open.end() && last_node_open != victim[i]){}
        else{
            //there is a copy in the open list
            copies.push_back(victim[i]);
        }
        if (find(closed.begin(),closed.end(),victim[i]) == closed.end() && last_node_closed != victim[i]){}
        else{
            //there is a copy in the closed list
            copies.push_back(victim[i]);
        }
    }
    for (int i = 0; i < copies.size(); i++){
        victim.erase(find(victim.begin(),victim.end(),copies[i]));
    }
    //erases copies from victim list
    return copies;
}

//////////////////////////////////////////////////////////
//Precondition: node ID, and distance grid
//Postcondition: returns vector of adjacent node ID's
//////////////////////////////////////////////////////////
//only finds horizontal and vertical movements. assuming no obstacles. if there are obstacles, filter them out here with distance grid
vector<int> findAdjacent(int node, vector<vector<int>> grid){
    int nodex, nodey;
    vector<int> adjacent;
    vector<int> coord = getCoord(node, grid);
    nodex = coord[0];
    nodey = coord[1];
    if (nodex != grid[0].size()-1){
        //not an end
        adjacent.push_back(node+1);
    }
    if (nodex != 0){
        //not a beginning
        adjacent.push_back(node-1);
    }
    if (nodey != 0){
        //not the first row
        adjacent.push_back(node - grid[0].size());  //subtract by the row length
    }
    if (nodey != grid[0].size()-1){
        adjacent.push_back(node + grid[0].size());  //add by the row length
    }
    
    return adjacent;
}

//////////////////////////////////////////////////////////
//Precondition: node ID start and goal, and distance grid
//Postcondition: returns distance to goal
//////////////////////////////////////////////////////////
int heuristic(int start, int end, vector<vector<int>> grid){
    /*
     x2 = coordinate of the goal location
     x1 = coordinate of the current location
     y2 = coordinate of the goal location
     y1 = coordinate of current location
     dx = | x2 - x1 |
     dy = | y2 - y1 |*/
    
    vector<int> startCoord = getCoord(start, grid);
    vector<int> endCoord = getCoord(end, grid);
    
    return sqrt(pow((endCoord[0] - startCoord[0]),2) + pow((endCoord[1] - startCoord[1]),2));
}

//////////////////////////////////////////////////////////
//Precondition: node ID, and distance grid
//Postcondition: returns coordinates. [0] is x axis, [1] is y axis. 0->N-1
//////////////////////////////////////////////////////////
vector<int> getCoord(int & node, vector<vector<int>> grid){
    int counter = 1;
    int col, row;
    for (int i = 0; i < grid[0].size(); i++){
        for (int j = 0; j < grid[0].size(); j++){
            if (counter == node){
                col = j;
                row = i;
            }
            counter++;
        }
    }
    vector<int> val = {col,row};
    return val;
}
