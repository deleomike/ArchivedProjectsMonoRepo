//
//  main.cpp
//  Run From the Bomb
//
//  Created by Michael DeLeo on 2/10/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

//Reminder: Take out comment in printBoard()

#include "board_f.h"

using namespace std;

int main()
{
    object new_board;
    //Board 4x4
    //Contains Bomb and Robot
    
   // while ()
    new_board.printBoard();
  
   
    while(!(new_board.gameOverYet()))
    {
        new_board.runSimulation();
        
    }
    //Iterates simulations
    //Pauses with a input
    if (new_board.getResult())
    {
        cout << "Happy Ending! Robot Won!" << endl;
    }
    else{
        cout << "Kabum: Game Over! Bomb killed the Robot" << endl;
    }
    
    return 0;
}
