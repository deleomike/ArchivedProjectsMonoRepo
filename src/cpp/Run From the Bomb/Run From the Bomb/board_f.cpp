//
//  board_f.cpp
//  Run From the Bomb
//
//  Created by Michael DeLeo on 2/10/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#include "board_f.h"


object::object()
{
    std::random_device rd;
    
    int bomb_place = rd() % 16;
    int robot_place = rd() % 16;
    while (robot_place == bomb_place)
    {
        robot_place = rd() % 16;
    }
    int gold_1 =  rd() % 16;
    while (gold_1 == robot_place || gold_1 == bomb_place)
    {
        gold_1 = rd() % 16;
    }
    int gold_2 = rd() % 16;
    while (gold_2 == gold_1 || gold_2 == robot_place || gold_2 == bomb_place)
    {
        gold_2 = rd() % 16;
    }
    //Makes sure the starting values are not the same
    
    setBoardSpace(bomb_place,robot_place,gold_1,gold_2);
    
    
}

void object::setBoardSpace(int bomb, int robot, int gold_1, int gold_2)
{
    std::string temp[16];
    for (int i = 0; i < 16; i++)
    {
        temp[i] = "X";
    }
    
    temp[bomb] = "B";
    temp[robot] = "R";
    temp[gold_1]= "G";
    temp[gold_2]= "G";
    
    int counter = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
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
    
    for (int i = 0; i < 2; i++)
    {
        if (gameOverYet())
        {
            return;
        }
        int robot_temp = rd() % 9;
        setRobot(robot_temp);
       printBoard();
    }
    //Robot moves twice
    
    int bomb_temp = rd() % 9;
    
    //Random Input
    setBomb(bomb_temp);
    
    //Takes bomb input
    //Takes robot input
    
    printBoard();
    
    //Analyzes board
    
    //TODO MIKE
    
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
    
    std::cout << " _ _ _ _" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << "|";
        for (int j = 0; j < 4; j++)
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
    std::cout << " - - - -" << std::endl;
    
}

void object::setBomb(int move)
{
    
    int x_direc = 0;
    //-1 left | 1 right | 0 x is constant
    int y_direc = 0;
    //-1 down | 1 up | 0 y is constant
    if (move == 0)
    {
        x_direc = 0;
        y_direc = 0;
    }
    else if (move == 1)
    {
        y_direc = 1;
    }
    else if (move == 2)
    {
        y_direc = 1;
        x_direc = 1;
    }
    else if (move == 3)
    {
        x_direc = 1;
    }
    else if (move == 4)
    {
        x_direc = 1;
        y_direc = -1;
    }
    else if (move == 5)
    {
        y_direc = -1;
    }
    
    else if (move == 6)
    {
        x_direc = -1;
        y_direc = -1;
    }
    else if (move == 7)
    {
        x_direc = -1;
    }
    else if (move == 8)
    {
        x_direc = -1;
        y_direc = 1;
    }
    
    std::pair<int,int> current_loc = getBomb();
    
    board[current_loc.first][current_loc.second] = "X";
    
    
    if ((current_loc.first - y_direc > 3) || current_loc.first - y_direc <0 ||
        (current_loc.second - x_direc < 0) || current_loc.second - x_direc > 3)
    {
        board[current_loc.first] [current_loc.second] = "B";
    }
    
    else if (board[current_loc.first - y_direc][current_loc.second - x_direc] == "X")
    {
        board[current_loc.first - y_direc][current_loc.second - x_direc] = "B";
    }
    
    else if (board[current_loc.first - y_direc][current_loc.second - x_direc] == "G")
    {
        board[current_loc.first][current_loc.second] = "B";
    }
    else if (board[current_loc.first - y_direc][current_loc.second - x_direc] == "R")
    {
        board[current_loc.first - y_direc][current_loc.second - x_direc] = "B";
    }
    
    else{
        board[current_loc.first][current_loc.second] = "Q";
    }
    
    //Assuming this is right
    
    
    //board[current_loc.first - y_direc][current_loc.second - x_direc] = "R";
    
    return;
    //TODO
}

void object::setRobot(int move)
{
    int x_direc = 0;
    //-1 left | 1 right | 0 x is constant
    int y_direc = 0;
    //-1 down | 1 up | 0 y is constant
    if (move == 0)
    {
        x_direc = 0;
        y_direc = 0;
    }
    else if (move == 1)
    {
        y_direc = 1;
    }
    else if (move == 2)
    {
        y_direc = 1;
        x_direc = 1;
    }
    else if (move == 3)
    {
        x_direc = 1;
    }
    else if (move == 4)
    {
        x_direc = 1;
        y_direc = -1;
    }
    else if (move == 5)
    {
        y_direc = -1;
    }
    
    else if (move == 6)
    {
        x_direc = -1;
        y_direc = -1;
    }
    else if (move == 7)
    {
        x_direc = -1;
    }
    else if (move == 8)
    {
        x_direc = -1;
        y_direc = 1;
    }
    
    std::pair<int,int> current_loc = getRobot();
    
    board[current_loc.first][current_loc.second] = "X";
    
    if (current_loc.first - y_direc < 0 || current_loc.first - y_direc > 3
        || current_loc.second - x_direc < 0 || current_loc.second - x_direc > 3)
    {
        std::random_device rd;
        board[current_loc.first] [current_loc.second] = "R";
        int temp = rd() % 9;
        setRobot(temp);
        
        
    }
    
    else if(board[current_loc.first - y_direc][current_loc.second - x_direc] == "X")
    {
        board[current_loc.first - y_direc][current_loc.second - x_direc] = "R";
    }
    
    else if (board[current_loc.first - y_direc][current_loc.second - x_direc] == "G")
    {
        board[current_loc.first - y_direc][current_loc.second - x_direc] = "R";
    }
    
    else if (board[current_loc.first - y_direc][current_loc.second - x_direc] == "B")
    {
        board[current_loc.first - y_direc][current_loc.second - x_direc] = "B";
    }
    
    
    
    //board[current_loc.first - y_direc * speed][current_loc.second - x_direc] = "R";
    
    return;
    //TODO
    
}

std::pair<int,int> object::getRobot()
{
    std::pair<int,int> temp;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
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

std::pair<int,int> object::getBomb()
{
    std::pair<int,int> temp;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == "B")
            {
                temp.first = i;
                temp.second = j;
                
                return temp;
            }
        }
    }
    std::cout <<"ERROR in getBomb()" << std::endl;
    return std::pair<int,int> (0,0);
    
}

