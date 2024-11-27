//
//  main.cpp
//  Second Bounty
//
//  Created by Michael DeLeo on 4/5/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>

//Literal Node Network
//OR
//List of node combinations with the distance as the value


int main()
{
    //nodes A, B, C, D, E, F, G;
    //G and F are switched here
    
    const int numNodes = 4;
    int distance[numNodes][numNodes] = {
        {0	,432	,1436,	2509},
        { 432	,0,	1779,	2852},
        {1436	,1779,	0,	1317},
        {2509	,2852	,1317	,0}
    };
    //  A   B   C   D   E   F   G
    //A 0   4   3   -   7   -   -
    //B 4   0   6   5   -   -   -
    //C 3   6   0   11  8   -   -
    //D -   5   11  0   2   10  2
    //E 7   -   8   2   0   5   -
    //F -   -   -   10  5   0   3
    //G -   -   -   2   -   3   0
    
    int elements = numNodes;
    //Number of nodes
    std::vector<int> nodes;
    //Elements
    for (int i = 1; i <= elements; i++)
    {
        nodes.push_back(i);
    }
       //Array of the elements
    
    std::vector<int> elementDistance;
    //newest newDistance
    
    
    std::vector<int> WinCase = {1,2,4,7};
    std::vector<std::vector<int>> combinations;
    
    for (int i = 0; i < 4; i++)
    {
        while(next_permutation(nodes.begin(),nodes.end()))
        {
            std::vector<int> temp;
            for (int j = 0; j < nodes.size(); j++)
            {
                temp.push_back(nodes[j]);
            }
            
            combinations.push_back(temp);
            
            if (temp == WinCase)
            {
                std::cout<<"FOUND" << std::endl;
            }
        }
    }
    
    for(int z = 0; z < combinations.size(); z++)
    {
        //Needs something that will let the loop iterate through every possibility 1-7 not just every permutation 1-7
        do
        {
            std::vector<int> copy;
            for (int i = 0; i < combinations[z].size(); i++)
            {
                copy.push_back(combinations[z].at(i));
            }
            
            int a = 0;;
            int b = 0;
            int newDistance = 0;
            for (int i = 1; i < copy.size(); i++)
            {
                a = copy[i-1]-1;
                b = copy[i] - 1;
                newDistance = newDistance + distance[a][b];
                // std::cout << "First, Second" << a << ", " << b << std::endl;
            }
            //To find the length of distance
            
            if (elementDistance.empty())
            {
                elementDistance.push_back(newDistance);
                for (int i = 0; i < copy.size(); i++)
                {
                    std::cout << copy[i] << "->";
                }
                std::cout << std::endl;
                std::cout << elementDistance.back() << std::endl;
            }
            
            else if (copy.front() == 1)
            {
                elementDistance.push_back(newDistance);
                
                for (int i = 0; i < copy.size(); i++)
                {
                    std::cout << copy[i] << "->";
                }
                std::cout << std::endl;
                std::cout << elementDistance.back() << std::endl;
            }
            // std::cout << newDistance << "-" << std::endl;
            // std::cout << elementDistance.back() << std::endl;
            
        }while(next_permutation(std::next(combinations[z].begin()),std::prev(combinations[z].end())));
    }
    std::sort(elementDistance.begin(), elementDistance.end());
    
    for (int i = elementDistance.size()-1; i >= 0; i--)
    {
        std::cout << elementDistance[i] << std::endl;
    }
    
    
    std::cout << "Worst: " << elementDistance.back() << std::endl;
    std::cout << "Best: " << elementDistance.front() << std::endl;
    
    
    //What i had tried for Dijrstka
    /*
    int node[numNodes] = {0, 1000, 1000, 1000, 1000, 1000, 1000};
    //1 A , 2 B ... 7 G
    //Values
    
    std::vector<int> class1 = {1};
    std::vector<int> class2 = {2,3,4,5,6,7};
    
    int nodeToFind = 7;
    bool isNode = true;
    int iterations = 0;
    while (isNode)
    {
        for (int i = 0; i < class2.size(); i++)
        {
            if (class2[i] == nodeToFind)
            {
                i = class2.size();
                isNode = true;
            }
            else{
                isNode = false;
            }
        }
        int pivot = class1.back();
        //Most recent node added
        
        std::vector<int> connections;
        //Nodes that are conneced to pivot
        
        for (int i = 0; i < numNodes; i++)
        {
        
            if (distance[pivot-1][i] == 1000 || distance[pivot-1][i] == 0)
            {}
            else{
                connections.push_back(i+1);
            }
        }
        //finds the immediate connections to the pivot
        
        std::vector<int> pivotDist;
        for (int i = 0; i < connections.size(); i++)
        {
            pivotDist.push_back(    distance[pivot-1][connections[i]-1] );
        }
        //finds the distances for the immediate connections to the pivot
        
        int min = connections[0];
        for (int i = 0; i < connections.size(); i++)
        {
            if (distance[pivot-1][min-1] > distance[pivot-1][connections[i]-1])
            {
                min = connections[i];
            }
        }
        //Finds the node with the min distance
     
    
        std::vector<int> temp_;
        //Compensates for replacement vector
        for (int i = 0; i < class2.size(); i++)
        {
            if (class2[i] == connections[i])
            {}
            else{
                temp_.push_back(class2[i]);
            }
        }
        class2.clear();
        for (int i = 0; i < temp_.size(); i++)
        {
            class2.push_back(temp_[i]);
        }
        //Removes the connections from class 2, and also adds connections to class 1
        
        int temp = 0;
        for (int i = 0; i < numNodes; i++)
        {
            if (node[i] == 1000)
            {}
            else{
                temp = node[i] + temp;
            }
        }
        node[min] = temp;
        //Sets the min distance to that value for the node
        
        iterations++;
    }
    
    //Start of spath_all
    
    int ** D = new int*[numNodes];
    for (int i = 0; i < numNodes; i++)
    {
        D[i] = new int[numNodes];
        for (int j = 0; j < numNodes; j++)
        {
            D[i][j] = distance[i][j];
        }
    }
    //Sets D^0
    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            
        }
    }
     */
    //End of spath_all
    
}
