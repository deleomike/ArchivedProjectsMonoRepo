//
//  main.cpp
//  MIPS Processor
//
//  Created by Michael DeLeo on 3/2/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include "support.h"

bool parallel;
int main(){
    
    //NEEDS SUPPORT FOR LW, SW
    
    //the way to utilize this simulation for an algorithm is as such:
    /*
     
     
     */
    
    
    std::fstream input;
    input.open("/Users/michaeldeleo/Documents/workspace/MIPS Processor/MIPS Processor/ISA.txt");
    
    getISA(input);
    input.close();

    input.open("/Users/michaeldeleo/Documents/workspace/MIPS Processor/MIPS Processor/ISA.txt");
    
    if (parallel){
        std::vector<std::vector<Instruction>> sets = getISA_Pipe(input);
        Pipeline a(sets[0]);
        Pipeline b(sets[1]);
        Pipeline c(sets[2]);
        Pipeline d(sets[3]);
        
        input.close();
        std::fstream myfile;
        myfile.open("/Users/michaeldeleo/Documents/workspace/MIPS Processor/MIPS Processor/Pipe.txt");
        
        Generation Israel(a,b,c,d);
        Israel.CheckAllDepencies();
        Israel.PrintGeneration(myfile);
        myfile.close();
    }
    else{
        //single pipeline
        std::vector<Instruction> file_instructions = getISA(input);
        Pipeline C(file_instructions);
        
        input.close();
        std::fstream myfile;
        myfile.open("/Users/michaeldeleo/Documents/workspace/MIPS Processor/MIPS Processor/Pipe.txt");
        
        C.CheckDepencies();
        C.PrintPipeline(myfile);
        myfile.close();
    }

    

//    std::fstream myfile;
//    myfile.open("/Users/michaeldeleo/Documents/workspace/MIPS Processor/MIPS Processor/Pipe.txt");
//
//    
//    //Initialize 4 MIPS Processors
//    //Load in instructions
//    //Load in data
//    
//    //MAKE ASSUMPTION THAT PROCESSORS ARE PRIORITIZED
//    //1>2>3>4
//    
//    //Data set of <instruction>, <destination>, <source1>, <source2>
//    
//    //Data set of vector<enum instruct> column one
//    //for columns >1
//    //ISA
//    Instruction first(add,$a0,$a0,$a1,1);
//    Instruction second(add, $a0, $a0, $b0,2);
//    Instruction third(add, $a0, $a0, $c0,3);        //process a
//    
//    Instruction fourth(add,$b0,$b1,$b0,1);      //process b
//    
//    Instruction fifth(add, $c0, $c0, $c1,1);    //process c
//    Instruction sixth(add, $c0, $c0, $d0,2);
//    
//    Instruction seventh(add, $d0,$d0,$d1,1);    //process d
//    
//    std::vector<Instruction> list1 = {first,second,third};
//    std::vector<Instruction> list2 = {fourth};
//    std::vector<Instruction> list3 = {fifth, sixth};
//    std::vector<Instruction> list4 = {seventh};
//    Pipeline x(list1);
//    Pipeline y(list2);
//    Pipeline z(list3);
//    Pipeline zz(list4);
//    
//    //x.addStall(4);
//    
//    Generation Eden(x,y,z,zz);
//    //x.PrintPipeline(myfile);
//    Eden.CheckAllDepencies();
//    
//    Eden.PrintGeneration(myfile);
//    
//    myfile.close();
    
    return 1;
}

//////////////////////////////////////////////////////////////////////
//Precondition: file stream in
//Postcondition: vector of instructions from file
//Function: gets strings from file and converts them into instructions
//////////////////////////////////////////////////////////////////////
std::vector<Instruction> getISA(std::fstream & input){
    std::vector<Instruction> value;
    instruct_type name = none;
    reg dest = reg_none;
    reg s1 = reg_none;
    reg s2 = reg_none;
    int level = 0;
    
    parallel = false;  //true is parallel, so set up levels
                            //false is not parallel, no levels
    
    std::string   line;
    std::getline(input,line);
    if (line == ".parallel"){
        parallel = true;
    }   //sets up parallel
    
    int alpha = 0;
    int bravo = 0;
    int charlie = 0;
    int delta = 0;
    
    
    int line_number = 1;
   
    while(std::getline(input,line))
    {
        
        // If you then want to tokenize the line use a string stream:
        
        int cursor = 0;
        std::stringstream lineStream(line);
        std::string token;
        while(lineStream >> token)
        {
            
            //token
            switch(cursor){
                case 0:
                    if (token == "add"){
                        name = add;
                    }
                    else if (token == "addi"){
                        name = addi;
                    }
                    else if (token == "sub"){
                        name = sub;
                    }
                    else if (token == "subi"){
                        name = subi;
                    }
                    else if (token == "mul"){
                        name = mul;
                    }
                    else if (token == "div"){
                        name = div_;
                    }
                    else if (token == "rem"){
                        name = rem;
                    }
                    else if (token == "lw"){
                        name = lw;
                    }
                    else if (token == "stall"){
                        name = stall;
                    }
                    else if (token == ".alpha"){
                        name = none;
                        alpha = line_number;
                    }
                    else if (token == ".bravo"){
                        name = none;
                        bravo = line_number;
                    }
                    else if (token == ".charlie"){
                        name = none;
                        charlie = line_number;
                    }
                    else if (token == ".delta"){
                        name = none;
                        delta = line_number;
                    }
                    break;
                    //assigns the name of the instruction
                case 1:
                    token.pop_back();   //remove comma
                    dest = reg_convert(token);
                    //destination register
                    break;
                case 2:
                    token.pop_back();   //remove comma
                    s1 = reg_convert(token);
                    break;
                case 3:
                    token.pop_back();   //remove comma
                    s2 = reg_convert(token);
                    break;
                case 4:
                    level = string2int(token);
                    break;
                default:
                    level = 0;  //not parallel
                    break;
            }
            cursor++;
        }
        if (name == none){
            
        }
        else{
            Instruction temp(name,dest,s1,s2,level);
            if (parallel){
                //do nothing
            }
            else{
                Instruction x(name,dest,s1,s2,-1);
                temp = x;
                //non parallel, single pipeline
            }
            value.push_back(temp);
        }
        line_number++;
        //next line
    }
    Instruction temp(none);
    if (parallel){
        value.insert(value.begin()+bravo-2,temp);
        value.insert(value.begin()+charlie-2,temp);
        value.insert(value.begin()+delta-2,temp);
    }
    return value;
}

//////////////////////////////////////////////////////////////////////
//Precondition: string
//Postcondition: register equivalent
//Function: giant case of converting strings
//////////////////////////////////////////////////////////////////////
reg reg_convert(std::string token){
    reg dest;
    if (token == "$t0"){
        dest = $t0;
    }
    else if (token == "$t1"){
        dest = $t1;
    }
    else if (token == "$t2"){
        dest = $t2;
    }
    else if (token == "$t3"){
        dest = $t3;
    }
    else if (token == "$t4"){
        dest = $t4;
    }
    else if (token == "$t5"){
        dest = $t5;
    }
    else if (token == "$t6"){
        dest = $t6;
    }
    else if (token == "$t7"){
        dest = $t7;
    }
    else if (token == "$t8"){
        dest = $t8;
    }
    else if (token == "$t9"){
        dest = $t9;
    }
    else if (token == "$a0"){
        dest = $a0;
    }
    else if (token == "$a1"){
        dest = $a1;
    }
    else if (token == "$a2"){
        dest = $a2;
    }
    else if (token == "$a3"){
        dest = $a3;
    }
    else if (token == "$a4"){
        dest = $a4;
    }
    else if (token == "$a5"){
        dest = $a5;
    }
    else if (token == "$a6"){
        dest = $a6;
    }
    else if (token == "$a7"){
        dest = $a7;
    }
    else if (token == "$a8"){
        dest = $a8;
    }
    else if (token == "$a9"){
        dest = $a9;
    }
    else if (token == "$b0"){
        dest = $b0;
    }
    else if (token == "$b1"){
        dest = $b1;
    }
    else if (token == "$b2"){
        dest = $b2;
    }
    else if (token == "$b3"){
        dest = $b3;
    }
    else if (token == "$b4"){
        dest = $b4;
    }
    else if (token == "$b5"){
        dest = $b5;
    }
    else if (token == "$b6"){
        dest = $b6;
    }
    else if (token == "$b7"){
        dest = $b7;
    }
    else if (token == "$b8"){
        dest = $b8;
    }
    else if (token == "$b9"){
        dest = $b9;
    }
    else if (token == "$c0"){
        dest = $c0;
    }
    else if (token == "$c1"){
        dest = $c1;
    }
    else if (token == "$c2"){
        dest = $c2;
    }
    else if (token == "$c3"){
        dest = $c3;
    }
    else if (token == "$c4"){
        dest = $c4;
    }
    else if (token == "$c5"){
        dest = $c5;
    }
    else if (token == "$c6"){
        dest = $c6;
    }
    else if (token == "$c7"){
        dest = $c7;
    }
    else if (token == "$c8"){
        dest = $c8;
    }
    else if (token == "$c9"){
        dest = $c9;
    }
    else if (token == "$d0"){
        dest = $d0;
    }
    else if (token == "$d1"){
        dest = $d1;
    }
    else if (token == "$d2"){
        dest = $d2;
    }
    else if (token == "$d3"){
        dest = $d3;
    }
    else if (token == "$d4"){
        dest = $d4;
    }
    else if (token == "$d5"){
        dest = $d5;
    }
    else if (token == "$d6"){
        dest = $d6;
    }
    else if (token == "$d7"){
        dest = $d7;
    }
    else if (token == "$d8"){
        dest = $d8;
    }
    else if (token == "$d9"){
        dest = $d9;
    }
    return dest;
}

//////////////////////////////////////////////////////////////////////
//Precondition: file stream in
//Postcondition: vector vector of instructions
//Function: takes the list of instructions from input, and seperates them into their pipelines
//////////////////////////////////////////////////////////////////////
std::vector<std::vector<Instruction>> getISA_Pipe(std::fstream & input){
    std::vector<Instruction> fullset = getISA(input);
    std::vector<Instruction> a,b,c,d;
    std::vector<std::vector<Instruction>> sets = {a,b,c,d};
    int cursor = 0;
    for (int i = 0; i < fullset.size(); i++){
        if (fullset[i].getName() != none){
            sets[cursor].push_back(fullset[i]);
        }
        else{
            cursor++;
        }
    }
    cursor++;
    return sets;
}

//////////////////////////////////////////////////////////////////////
//Precondition: string
//Postcondition: int
//Function: converts the multiple digit string into an int
//////////////////////////////////////////////////////////////////////
int string2int(std::string x){
    int value = 0;
    value = x.at(0) - 48;   //first value
    for (int i = 1; i < x.size(); i++){
        value = value * 10;
        value = x.at(i) + value;
    }
    return value;
}
