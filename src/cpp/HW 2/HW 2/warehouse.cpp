//
//  warehouse.cpp
//  HW 2
//
//  Created by Michael DeLeo on 3/2/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#include "warehouse.h"


object::object()
{
    total = 0;
    std::random_device rd;
    
    int bomb_place = rd() % 100;
    int robot_place = rd() % 100;
    while (robot_place == bomb_place)
    {
        robot_place = rd() % 100;
    }
    
    int gold[10];
    
    for (int i = 0; i < 10; i++)
    {
        
        gold[i] = rd() % 100;
        for (int j = i; j >=0; j--)
        {
            while ((gold[i] == gold[j] && i!=j) || robot_place == gold[i] || bomb_place==gold[i] )
            {
                gold[i] = rd()%100;
            }
        }
    }
    //Makes sure the starting values are not the same
    
    setBoardSpace(bomb_place,robot_place,gold);
    
    
}

void object::setBoardSpace(int bomb, int robot, int gold[])
{
    std::string temp[100];
    for (int i = 0; i < 100; i++)
    {
        temp[i] = "X";
    }
    
    temp[bomb] = "P";
    temp[robot] = "R";
    for (int i = 0; i < 10; i++)
    {
        temp[gold[i]] = "O";
    }
    
    int counter = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            board[i][j] = temp[counter];
            counter++;
            
        }
    }
    
    return;
}

#include <random>
void object::runSimulation()
{
    std::random_device rd;
    
   
    setPerson(rd() %4, (rd()%2 + 1));
    
    int bomb_temp = rd() % 4;
    //Random Input
    setRobot(bomb_temp, (rd()%3 + 1));
    
    //Takes bomb input
    //Takes robot input
    
    printBoard();
    
    //Analyzes board
    
    //TODO MIKE
    
    
    //Person is 1-2
    //Robot is 2-3
    
    return;
}

bool object::gameOverYet()
{
    bool gold_checker = true;
    bool robot_checker = true;
    for (int i = 0; i <4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == "G")
            {
                //Robot hasn't won yet
                gold_checker = false;
            }
            else if (board[i][j] == "R")
            {
                //Bomb hasn't won yet
                robot_checker = false;
            }
        }
    }
    
    if (gold_checker || robot_checker)
    {
        //Game is Over
        return true;
    }
    else{
        //Game is not over
        return false;
    }
    
}

bool object::getResult()
{
    
    bool gold_checker = true;
    bool robot_checker = true;
    for (int i = 0; i <4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == "G")
            {
                //Robot hasn't won yet
                gold_checker = false;
            }
            else if (board[i][j] == "R")
            {
                //Bomb hasn't won yet
                robot_checker = false;
            }
        }
    }
    if (robot_checker)
    {
        return false;
    }
    else if (gold_checker)
    {
        return true;
    }
    else{
        //getResult has been called too early
        std::cout << "ERROR IN getResult()" << std::endl;
        return false;
    }
    //Placeholder for return value
}

void object::printBoard()
{
    /*Example:
     
     _ _ _ _
     |B X X X |
     |X R X X |
     |X X G X |
     |G X X X |
     - - - -
     For the user, the Bomb and the two golds should be hidden until stepped on
     Spaces stepped on by the robot turn into "O"
     
     */
    
    std::cout << " _ _ _ _ _ _ _ _ _ _" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        std::cout << "|";
        for (int j = 0; j < 10; j++)
        {
            /*
             if (board[i][j] == "B" || board[i][j] == "G" || board[i][j] == "X")
             {
             std::cout << "X ";
             }
             
             
             else
             */
            //For Testing
            std::cout << board[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << " - - - - - - - - - -" << std::endl;
    
}

void object::setPerson(int move, int speed)
{
    int x_direc = 0;
    //-1 left | 1 right | 0 x is constant
    int y_direc = 0;
    //-1 down | 1 up | 0 y is constant
    if (move == 0)
    {
        x_direc = -1;
    }
    else if (move == 1)
    {
        x_direc = 1;
    }
    else if (move == 2)
    {
        y_direc = 1;
    }
    else
    {
        y_direc = -1;
    }
    
    std::pair<int,int> current_loc = getPerson();
    
    board[current_loc.first][current_loc.second] = "X";
    
    for (int i = 0; i<=  speed; i++)
    {
        
        if(board[current_loc.first - y_direc * i][current_loc.second - x_direc * i] == "O")
        {
            addToTotal(-4);
            board[current_loc.first - y_direc * i][current_loc.second - x_direc * i] = "X";
            
        }
        
        if(((current_loc.first - y_direc * i >= 9) || (current_loc.first - x_direc * i <=0)) && i!= speed)
        {
            board[current_loc.first - y_direc * i][current_loc.second - x_direc * i] = "R";
            i = speed;
        }
        
        //Assuming this is right
    }
    
    board[current_loc.first - y_direc * speed][current_loc.second - x_direc * speed] = "P";

    

    //TODO
}

void object::setRobot(int move, int speed)
{
    int x_direc = 0;
    //-1 left | 1 right | 0 x is constant
    int y_direc = 0;
    //-1 down | 1 up | 0 y is constant
    if (move == 0)
    {
        x_direc = -1;
    }
    else if (move == 1)
    {
        x_direc = 1;
    }
    else if (move == 2)
    {
        y_direc = 1;
    }
    else
    {
        y_direc = -1;
    }
    
    std::pair<int,int> current_loc = getRobot();
    
    board[current_loc.first][current_loc.second] = "X";
    
    for (int i = 0; i<=  speed; i++)
    {
        
        if(board[current_loc.first - y_direc * i][current_loc.second - x_direc * i] == "O")
        {
            addToTotal(10);
            board[current_loc.first - y_direc * i][current_loc.second - x_direc * i] = "X";
            
        }
        
        if(((current_loc.first - y_direc * i >= 9) || (current_loc.first - x_direc * i <=0)) && i!= speed)
        {
            board[current_loc.first - y_direc * i][current_loc.second - x_direc * i] = "R";
            i = speed;
            return;
        }
        
        //Assuming this is right
    }
    
    board[current_loc.first - y_direc * speed][current_loc.second - x_direc * speed] = "R";
    
    return;
    //TODO
    
}

std::pair<int,int> object::getRobot()
{
    std::pair<int,int> temp;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board[i][j] == "R")
            {
                temp.first = i;
                temp.second = j;
                
                return temp;
            }
        }
    }
    std::cout <<"ERROR in getRobot()" << std::endl;
    return std::pair<int,int> (0,0);
}

std::pair<int,int> object::getPerson()
{
    std::pair<int,int> temp;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (board[i][j] == "P")
            {
                temp.first = i;
                temp.second = j;
                
                return temp;
            }
        }
    }
    std::cout << "ERROR in getPerson()"<< std::endl;
    return std::pair<int,int> (0,0);
}

int object::getTotal()
{
    return total;
}

void object::addToTotal(int amount)
{
    total = total + amount;
    return;
}
