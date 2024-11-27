//
//  main.cpp
//  HW 2
//
//  Created by Michael DeLeo on 3/2/17.
//  Copyright © 2017 Michael DeLeo. All rights reserved.
//

#include "warehouse.h"

int main()
{
    object new_board;
    
    new_board.printBoard();
    
    new_board.runSimulation();
    
    std::cout <<new_board.getTotal() << std::endl;
    
    return 0;
}
