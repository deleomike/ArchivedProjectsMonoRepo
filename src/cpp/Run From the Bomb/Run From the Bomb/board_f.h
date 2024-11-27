//
//  Header.h
//  Run From the Bomb
//
//  Created by Michael DeLeo on 2/10/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#ifndef board_f_h
#define board_f_h

#include <iostream>
#include <string>
#include <random>
#include <utility>

class object
{
public:
    object();
    //Operator''
    
    void setBomb(int move);
    //Precondition: Random value [Left: 0, Right: 1, Up: 2, Down: 3] Postcondition: New Space value [with rules applied]
    
    void setRobot(int move);
    //Precondition: String value [Left, Right, Up, Down] Postcondition: New Space value [with rules applied]
    
    
    void printBoard();
    //Precondition: Nothing | Postcondition: Prints Board
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
     
    void runSimulation();
    //Precondition: Nothing | Postcondition: Uses set functions to change the board one iteration
    
    bool getResult();
    //Precondition: Nothing | Postcondition: False Bomb wins, True Robot Wins
    
    bool gameOverYet();
    //Precondition: Nothing | Postcondition: True Game is over, False Game is still going
    
private:
    
    void setBoardSpace(int bomb, int robot, int gold_1, int gold_2);
    
    std::pair<int,int> getRobot();
    std::pair<int,int> getBomb();
    
    std::string board[4][4];
    //R: Robot | G: Gold | B: Bomb | X: nothing
    
};

#endif /* Header_h */
