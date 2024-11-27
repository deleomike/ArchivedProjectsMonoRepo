//
//  Instructions.h
//  MIPS Processor
//
//  Created by Michael DeLeo on 3/4/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#ifndef Instructions_h
#define Instructions_h

#include <vector>
#include <fstream>
#include <iostream>

//Instructions
typedef enum{
    add,
    addi,
    sub,
    subi,
    mul,
    div_,
    rem,
    lw,
    stall,
    none
}instruct_type;

//Registers
typedef enum{
    
    $t0,    //Test registers
    $t1,
    $t2,
    $t3,
    $t4,
    $t5,
    $t6,
    $t7,
    $t8,
    $t9,
    $a0,    //Alpha registers
    $a1,
    $a2,
    $a3,
    $a4,
    $a5,
    $a6,
    $a7,
    $a8,
    $a9,
    $b0,    //Bravo registers
    $b1,
    $b2,
    $b3,
    $b4,
    $b5,
    $b6,
    $b7,
    $b8,
    $b9,
    $c0,    //Charlie registers
    $c1,
    $c2,
    $c3,
    $c4,
    $c5,
    $c6,
    $c7,
    $c8,
    $c9,
    $d0,    //Delta registers
    $d1,
    $d2,
    $d3,
    $d4,
    $d5,
    $d6,
    $d7,
    $d8,
    $d9,
    reg_none
    
}reg;

//pipeline stage
typedef enum{
    IF,
    ID,
    EX,
    MEM,
    WB,
    STALL,
    BLANK
}stage;

typedef enum{
    WAR,
    RAW,
    WAW,
    NO_DATA_HAZARD
}DATA_HAZARD;

//instruction is the data set for desribing one instruction
class Instruction{//no compatability for LW yet
private:
    instruct_type name;
    reg  destination;
    reg source1;
    reg source2;
    int ISA_order;
    
public:
    Instruction();
    
    Instruction(instruct_type name, reg destination, reg source1, reg source2, int place)
    {this->name = name; this->destination=destination;this->source1=source1;this->source2=source2;this->ISA_order=place;}
    
    
    Instruction(instruct_type name) //stall constructor
    {this->name=name;destination=reg_none;source1=reg_none;source2=reg_none;this->ISA_order=-1;}
    
    Instruction(instruct_type name, int level) //stall constructor
    {this->name=name;destination=reg_none;source1=reg_none;source2=reg_none;this->ISA_order=level;}
    
    instruct_type getName();
    reg getDestination();
    reg getSource1();
    reg getSource2();
    int getLevel();
    
};

#endif /* Instructions_h */
