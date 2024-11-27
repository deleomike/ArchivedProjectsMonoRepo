//
//  main.cpp
//  AI - BotClean
//
//  Created by Michael DeLeo on 6/14/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

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
vector<string> finalPath(int n, vector <string> grid);



//Precondition: posr is y coordinate, posc is x coordinate
void next_move(int posr, int posc, vector <string> board) {
    int linearPosition = posr * board.size() + posc+1;
    if (board[posr].at(posc) =='d'){
        cout << "CLEAN" << endl;
        return;
    }
    //takes care of the case where the bot cleans the dirt
    
    //if the program goes past here, the bot is not on dirt
    //First, determine the closest goal
    //make a distance matrix
    vector<vector<int>> distances;
    vector<int> t;
    distances.push_back(t);
    for(int i  = 0; i < board.size(); i++){
        for(int j = 0; j < board.at(0).size(); j++){
            if (board[i].at(j) == 'b'){
                distances.at(i).push_back(0);
            }//starting position
            else if(board[i].at(j) == 'd' || board[i].at(j) == '-'){
                distances.at(i).push_back(1);
            }//empty space or dirt
        }//end of line
        distances.push_back(t);
    }
    distances.pop_back();
    //now make a list of the goals
    vector<int> goals;
    int count = 0;
    for (int i = 0; i < board.size(); i++){
        for(int j = 0; j < board.size(); j++){
            if (board[i].at(j) == 'd'){
                goals.push_back(i*(board.size())+(j+1));
            }
        }

    }   //not sure if \n counts as one or two characters
    //i now have the list of goal ID's
    
    //find the goal with lowest F distance from the bot
    int minID = goals[0];
    int min = heuristic(linearPosition, goals[0], distances);
    for(int i = 0; i < goals.size();i++){
        if (heuristic(linearPosition, goals[i], distances) < min){
            minID = goals[i];
            min = heuristic(linearPosition, goals[i], distances);
        }
    }//finds closest goal, and saves the ID
    
    //that is the selected goal
    int goal = minID;
    
    vector<string> nboard;
    string n;
    nboard.push_back(n);
    count = 1;
    for(int i = 0; i < board.size(); i++){
        for (int j = 0; j < board.size(); j++){
            if (count == linearPosition || count == goal){
                nboard[i].push_back(board[i].at(j));
            }
            else{
                nboard[i].push_back('-');
            }
            count++;
        }
        nboard.push_back(n);
    }
    nboard.pop_back();
    //Go through the Astar algorithm, find shortest path and choose only the first step
    vector<string> path = finalPath(distances.size(),nboard);
    cout << path[0] << endl;
    return;
}

vector<string> finalPath(int n, vector <string> grid){
    int Goal = -1;
    int Start = -1;
    //now, make distance matrix
    vector<vector<int>> distances;
    //all 1
    vector<vector<int>> nodes;
    vector<int> temp;
    nodes.push_back(temp);
    distances.push_back(temp);
    int counter = 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            nodes[i].push_back(counter);
            counter++;
        }
        vector<int> temp;
        nodes.push_back(temp);
    }
    nodes.pop_back();
    //makes grid of nodes' ID values
    
    counter = 1;
    for (int i = 0; i < n; i++){    //goes up y axis
        for (int j = 0; j < n; j++){    //goes up x axis
            if (grid[i][j] == 'b'){
                Start = counter;
                distances[i].push_back(0);
            }
            else if (grid[i][j] == 'd'){
                Goal = counter;
                distances[i].push_back(1);
            }
            else{
                distances[i].push_back(1);
            }
            counter++;
        }
        distances.push_back(temp);
    }
    distances.pop_back();
    //find dest and source
    
    //now, the original node is created
    //1. make open and closed lists
    //start with the starting point in the open list
    vector<int> open;
    vector<int> closed;
    open.push_back(Start);  //add start to open list
    
    //add available adjacent squares to the starting point to the open list. assign start as the parent to these squares
    
    node* OG = new node;
    OG->ID = Start;
    OG->parent = NULL;
    
    vector<int> startAdjacent = findAdjacent(Start,distances);
    for (int i = 0; i < startAdjacent.size(); i++){
        open.push_back(startAdjacent[i]);
    }//copy adjacent squares into open list
    
    vector<node*> nodeList;
    nodeList = connectParent(nodeList,startAdjacent,OG);
    closeNode(Start,open,closed);    //close starting node
    
    ////////////////////////////////////////////////////////
    //path scoring
    
    
    //in this case, each step only takes 1. G = 1
    //F = H + G where H is heuristic distance
    //choose a node from the open list that has the lowest F
    //finds minimum F, and the respective node
    
    ////////////////////////////////////////////////////////
    //Continuing the Search
    int min_node;
    while (min_node != Goal){
        
        
        min_node = findMinNode(open,Goal,distances);
        //drop selected node from open list
        closeNode(min_node,open,closed);
        if (min_node == Goal){
            int temp = 0+1;
        }
        
        else{
            
            
            //Check all adjacent squares (ignoring inpassable or closed nodes)
            //if they are not on the open list, add them. and add the new ones so that the selected square is their parent
            startAdjacent = findAdjacent(min_node, distances);
            removeCopies(open,closed,startAdjacent);    //removes copies
            for (int i = 0; i < startAdjacent.size(); i++){
                open.push_back(startAdjacent[i]);
            }//copy adjacent squares into open list
            vector<node*>::iterator it = find(nodeList.begin(),nodeList.end(),min_node); //finds node object of min_node
            nodeList = connectParent(nodeList, startAdjacent, *it);    //connects new nodes to selected node
        }
        ///////////////////////////////////////////////////////
        //FOR A GRID THAT DOES NOT HAVE UNIVERSAL DISTANCES FOR MOVING
        //use the copies from removecopies(). Those are squares adjacent and already in open.
        //check if the G score is lower for that square, if it is then change the parent node
        
        //known as recalculating the path, dont worry about for this problem.
    }
    vector<node*>::iterator it = find(nodeList.begin(), nodeList.end(), Goal);
    //go back from goal to original node, save list
    vector<int> finalPath = {};
    node** nodeCursor = &(*it);
    while((*nodeCursor)->parent != NULL){
        finalPath.push_back((*nodeCursor)->ID);
        //cout << (*nodeCursor) -> ID << endl;
        nodeCursor = &(*nodeCursor) -> parent;
    }
    //TODO: reverse vector
    reverse(finalPath);
    int lastNode = Start;
    vector<string> s;
    for (int i = 0; i < finalPath.size(); i++){
        if (lastNode == (finalPath[i] - 1)){
            s.push_back( "RIGHT");
        }
        else if (lastNode == (finalPath[i] +1)){
            s.push_back("LEFT");
        }
        else if (lastNode == (finalPath[i] - grid[0].size())){
            s.push_back("DOWN");
        }
        else if (lastNode == (finalPath[i] + grid[0].size())){
            s.push_back("UP");
        }
        lastNode = finalPath[i];
        s.push_back("\n");
    }
    //s.pop_back();
    return s;
}

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
//input can be
/*
0 0
b---d
-d--d
--dd-
--d--
----d
 
 1 1
 -d--d
 -d--d
 --dd-
 --d--
 ----d
 
 where b is the bot, and d is dirt
 bot can move horizontally, or vertically.
 display move
 
 when the bot is on a dirty cell, it will still have d on it
 ,but when the next move function is called again it will output 'CLEAN' to clean the cell
 
 */

int main(void) {
    int pos[2];
    vector <string> board;
    cin>>pos[0]>>pos[1];
    for(int i=0;i<5;i++) {
        string s;cin >> s;
        board.push_back(s);
    }
    next_move(pos[0], pos[1], board);
    return 0;
}
