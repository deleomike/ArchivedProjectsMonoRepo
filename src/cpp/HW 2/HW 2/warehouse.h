//
//  warehouse.h
//  HW 2
//
//  Created by Michael DeLeo on 3/2/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#ifndef warehouse_h
#define warehouse_h

#include <iostream>
#include <string>
#include <random>
#include <vector>

class object
{
public:
    object();
    //Operator''
    
    void setPerson(int move, int speed);
    //Precondition: Random value [Left: 0, Right: 1, Up: 2, Down: 3] Postcondition: New Space value [with rules applied]
    
    void setRobot(int move, int speed);
    //Precondition: String value [Left, Right, Up, Down] Postcondition: New Space value [with rules applied]
    
    //Speed is number of blocks moved. top speed is 5
    
    void printBoard();
    //Precondition: Nothing | Postcondition: Prints Board
    /*Example:
     
     _ _ _ _
     |P X X X |
     |X R X X |
     |X X O X |
     |O X X X |
     - - - -
   
     
     */
    
    void runSimulation();
    //Precondition: Nothing | Postcondition: Uses set functions to change the board one iteration
    
    bool getResult();
    //Precondition: Nothing | Postcondition: False Bomb wins, True Robot Wins
    
    bool gameOverYet();
    //Precondition: Nothing | Postcondition: True Game is over, False Game is still going
    
    int getTotal();
    
private:
    
    void setBoardSpace(int bomb, int robot, int gold[]);
    std::pair<int,int> getRobot();
    std::pair<int,int> getPerson();
    
    void addToTotal(int amount);
    
    int total;
    
    std::string board[10][10];
    //R: Robot | G: Gold | B: Bomb | X: nothing
    
};


#endif /* warehouse_h */
