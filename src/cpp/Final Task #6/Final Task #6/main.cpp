//
//  main.cpp
//  Final Task #6
//
//  Created by Michael DeLeo on 4/26/17.
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

template <typename Iterator>
inline bool next_combination(const Iterator first, Iterator k, const Iterator last);

int main()
{
    //nodes A, B, C, D, E, F, G;
    //G and F are switched here
    
    const int numNodes = 14;
    double distance[numNodes][numNodes] = {
        {0,	5471.52,	5091.57,	5392.82	,5416.45,	4584.33	,4904.83,	3851.73,	4477.41,	5260.73,	4842.61	,5930.14,	3690.71	,3763.14},
        {5471.52,	0,	1315.28	,927.35	,1505.11	,944.4	,1157.42,	1945.42,	7224.89	,1126.72,	687.11,	458.63	,2801.21,	3108.01},
        { 5091.57	,1315.28,	0	,2166,	2724.01	,1571.76,	293.52	,1240.77	,6029.37	,235.7,	1489.43,	1542.05	,1741.71	,1970.09},
        {5392.82,	927.35,	2166,	0,	577.85,	973.23,	1947.28	,2422.32,	7792.75,	2010.47,	819.41,	1096.09,	3377.44,	3722.45},
        {5416.45,	1505.11,	2724.01,	577.85,	0,	1366.63	,2490.97,	2838.62,	8171.81,	2578.59,	1295.31,	1635.65,	3809.81,	4166.43},
        { 4584.33	,944.4	,1571.76,	973.23,	1366.63,	0,	1290.15	,1474.26,	6831.68,	1510.62,	263.13,	1387.45,	2443.78	,2799.8},
        {4904.83,	1157.42,	293.52,	1947.28	,2490.97,	1290.15,	0,	1064.41,	6094.11,	362.26,	1227.71,	1458.17,	1718.42,	1990.08},
        {3851.73,	1945.42,	1240.77,	2422.32,	2838.62,	1474.26,	1064.41,	0,	5371.4,	1412.4,	1605.23,	2356.14,	972.84,	1334.99},
        {4477.41,	7224.89,	6029.37,	7792.75,	8171.81	,6831.68,	6094.11,	5371.4,	0	,6263.11,	6976.62,	7551.16	,4435.43,	4116.99},
        {5260.73,	1126.72	,235.7	,2010.47,	2578.59,	1510.62,	362.26,	1412.4,	6263.11,	0,	1391.77,	1319.11,	1971.57,	2205.12},
        {4842.61,	687.11,	1489.43,	819.41,	1295.31,	263.13	,1227.71,	1605.23	,6976.62,	1391.77,	0,	1125.24	,2558.04,	2903.98},
        {5930.14,	458.63,	1542.05	,1096.09,	1635.65,	1387.45,	1458.17	,2356.14,	7551.16	,1319.11	,1125.24	,0,	3161.62,	3446.86},
        {3690.71,	2801.21,	1741.71,	3377.44,	3809.81	,2443.78	,1718.42	,972.84	,4435.43,	1971.57,	2558.04	,3161.62,	0,	367.91},
        { 3763.14	,3108.01,	1970.09,	3722.45,	4166.43,	2799.8,	1990.08,	1334.99,	4116.99,	2205.12	,2903.98,	3446.86,	367.91,	0}
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
    
    for (int i = 1; i < 14; i++){
    while(next_combination(nodes.begin(), nodes.begin() + i, nodes.end()))
        {
            std::vector<int> temp;
            for (int j = 0; j < nodes.size(); j++)
            {
                temp.push_back(nodes[j]);
            }
            
            combinations.push_back(temp);
            
        }
    }
    
   // for(int z = 0; z < combinations.size(); z++)
   // {
        //Needs something that will let the loop iterate through every possibility 1-7 not just every permutation 1-7
        do
        {
            std::vector<int> copy;
            for (int i = 0; i < combinations[0].size(); i++)
            {
                copy.push_back(combinations[0].at(i));
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
            
            else
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
            
        }while(next_combination((combinations[0].begin()), combinations[0].begin() + 1,(combinations[0].end())));
   // }
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

template <typename Iterator>
inline bool next_combination(const Iterator first, Iterator k, const Iterator last)
{
    /* Credits: Thomas Draper */
    if ((first == last) || (first == k) || (last == k))
        return false;
    Iterator itr1 = first;
    Iterator itr2 = last;
    ++itr1;
    if (last == itr1)
        return false;
    itr1 = last;
    --itr1;
    itr1 = k;
    --itr2;
    while (first != itr1)
    {
        if (*--itr1 < *itr2)
        {
            Iterator j = k;
            while (!(*itr1 < *j)) ++j;
            std::iter_swap(itr1,j);
            ++itr1;
            ++j;
            itr2 = k;
            std::rotate(itr1,j,last);
            while (last != j)
            {
                ++j;
                ++itr2;
            }
            std::rotate(k,itr2,last);
            return true;
        }
    }
    std::rotate(first,k,last);
    return false;
}
