//
//  support.h
//  MIPS Processor
//
//  Created by Michael DeLeo on 3/2/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#ifndef support_h
#define support_h

#include "Generation.h"
#include <vector>
#include "GHA.h"
#include <string>
#include <sstream>

std::vector<Instruction> getISA(std::fstream & input);
reg reg_convert(std::string token);
int string2int(std::string x);
std::vector<std::vector<Instruction>> getISA_Pipe(std::fstream & input);




//where to place checkdependency!!!!!

#endif /* support_h */
