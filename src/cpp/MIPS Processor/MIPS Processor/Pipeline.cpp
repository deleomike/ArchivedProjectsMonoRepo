//
//  Pipeline.cpp
//  MIPS Processor
//
//  Created by Michael DeLeo on 3/4/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>

#include "Pipeline.h"

//////////////////////////////////////////////////////////////////////
//Precondition: stage
//Postcondition: returns instruction from stage in pipeline
//Function: ^^
//////////////////////////////////////////////////////////////////////
Instruction Pipeline::whatIsStage(int stage){
    return instructs.at(stage-1);   //returns instruction at stage s
}

//////////////////////////////////////////////////////////////////////
//Precondition: time of pipeline
//Postcondition: vector list of the stages at that time
//Function: ^^
//////////////////////////////////////////////////////////////////////
std::vector<stage> Pipeline::whatIsTime(int time){
    std::vector<stage> list;
    for (int i = 0; i < instructs.size(); i++){
        list.push_back(pipe[i][time]);  //pushes back stages going down column #time
    }
    
    return list;    //returns the instructions for that time
}

//////////////////////////////////////////////////////////////////////
//Precondition: instruction, and stage of instruction
//Postcondition: nothing
//Function: adds instruction to pipeline
//////////////////////////////////////////////////////////////////////
void Pipeline::addInstruction( Instruction x, int stage){
    std::vector<Instruction>::iterator it;
    it = instructs.begin(); //start  iterator at beginning
    
    for (int i = 0; i< stage; i++){
        it++;
    }
    it--;   //decrement to accomodate for starting at begin()
    instructs.insert(it,x); //insert instruction name
    refreshPipeline(); //refresh pipeline
    
    return;
}

//////////////////////////////////////////////////////////////////////
//Precondition: stage of instruction
//Postcondition: nothing
//Function: inserts a stall in the instruction list
//////////////////////////////////////////////////////////////////////
void Pipeline::addStall(int stage){ //inserts a stall
    if (instructs.size()+1 < stage){
        std::cout << "mismatched stall size";
        return;
    }
    std::vector<Instruction>::iterator it;
    it = instructs.begin(); //start  iterator at beginning
    
    for (int i = 0; i< stage; i++){
        it++;
    }
    Instruction temp(stall);
    if (instructs[stage].getLevel() == -1){
        //do nothing
    }
    else{
        Instruction x(stall,instructs[stage-1].getLevel());
        temp = x;
        //copies the level to the stall
    }

    it--;   //decrement to accomodate for starting at begin()
    instructs.insert(it,temp); //insert stall
    refreshPipeline(); //refresh pipeline
    
    return;
    
}

//////////////////////////////////////////////////////////////////////
//Precondition: pipeline
//Postcondition: nothing
//Function: fixes interpipeline dependencies
//////////////////////////////////////////////////////////////////////
void Pipeline::PipelineDependency(Pipeline & x){
    int max_level_p1 = 0;//max_level is maximum level in the hierarchy of instructions inside a parrallel pipeline
    int max_level_p2 = 0;
    int max_level = 0;
    //iterate through both pipelines and find max level
    for (int i = 0; i < x.instructs.size(); i++){
        Instruction temp = x.instructs[i];
        if (temp.getLevel() > max_level_p2){max_level_p2 = temp.getLevel();}
    }
    for(int i =0; i < instructs.size(); i++){
        Instruction temp = instructs[i];
        if (temp.getLevel() > max_level_p1){max_level_p1 = temp.getLevel();}
    }
    //now we have the maximum level of the hierarchy
    if (max_level_p1 > max_level_p2){max_level = max_level_p1;}
    else{max_level = max_level_p2;}
    //assign the supreme
    
    
    /*is any register used in current level being used in any upper level
    BEGINNING
    if no, no hazard
    if yes, there may be a hazard
          check the depencies of next level
                is it being used consequtively
                      if no, then focus on first hazard
                            fix hazard
                        if yes, then focus on first hazard
                            fix hazards until clean
     loop till clean
     increment next level
     check next level for current level depencies
     
     if next level has surpassed max level of pipeline
        increment current level
            loop back to beginning of checking for hazards. label BEGINNING
     if not, continue with procedure
     
     if done with current level iteration
        switch current level iterator to other pipeline
        switch next level iterator to other pipeline
    
     redo procedure until there are no hazards
    
    */
    std::vector<Pipeline> one_flat;
    std::vector<Pipeline> two_flat;
    for (int i = 0; i < max_level_p1; i++){
        one_flat.push_back(Flatten_Pipeline(i+1));
    }
    for (int i = 0; i < max_level_p2; i++){
        two_flat.push_back(x.Flatten_Pipeline(i+1));
    }
    //stores the levels of the pipelines into two vectors. So each iteration of the vector is a seperate level
    //this is an iteration of the y cooordinate, as in the instruction list, of one part of a
    //flat pipeline and a flat part of another pipeline
    //now iterator one: 1 2 ... max   2 3 4 ... max
    //             two: 0 0 0 ... 0   1 1 1 ... 1
    //continue until the current level is 1 less than the max
    //             one: 0 0 0 ... 0   1 1 1 ... 1
    //             two: 1 2 3 ... max 2 3 4 ... max
    //same here, except the current level is on 'one' pipeline
    //
    
    //within each iteratation there is a flat pipeline represented by the stage in the vector
    //so from there, check depencies as if the flat pipeline that is higher in level is after the lower level pipeline
    //specific example
   /*Pipeline temp = conjoin(one_flat[0],two_flat[1]);
    int new_conjunction = temp.CheckDepencies(one_flat[0].instructs.size());  //gives the conjunction as the size of the first, which is implicitly the start of the second
    std::vector<Pipeline> disjointed_pipelines = disjoin(temp, new_conjunction);
    one_flat[0] = disjointed_pipelines[0];
    two_flat[1] = disjointed_pipelines[1];  //this one isnt even really necessary to reassign
    //and now at these two levels they are working
    */
    
    //assumption that every level has something for the pipeline to do
    for (int i = 0; i < one_flat.size(); i++){
        for (int j = 0; j < two_flat.size(); j++){
            if (i == j || i > j){   //this means that they are on the same level which is non dependent, or that the first one is at a higher level which is with respect non dependent
                //do nothing
            }
            else{
                //i is always less than j
                Pipeline temp = conjoin(one_flat[i],two_flat[j]);
                int new_conjunction = temp.CheckDepencies(one_flat[i].instructs.size());  //gives the conjunction as the size of the first, which is implicitly the start of the second
                std::vector<Pipeline> disjointed_pipelines = disjoin(temp,one_flat[i].instructs.size());
                one_flat[i] = disjointed_pipelines[0];
                two_flat[j] = disjointed_pipelines[1];  //this one isnt even really necessary to reassign
            }
        }
    }
    for (int i = 0; i < two_flat.size(); i++){
        for (int j = 0; j < one_flat.size(); j++){
            if (i == j || i > j){   //this means that they are on the same level which is non dependent, or that the first one is at a higher level which is with respect non dependent
                //do nothing
            }
            else{
                //i is always less than j
                Pipeline temp = conjoin(two_flat[i],one_flat[j]);
                int new_conjunction = temp.CheckDepencies(two_flat[i].instructs.size());  //gives the conjunction as the size of the first, which is implicitly the start of the second
                std::vector<Pipeline> disjointed_pipelines = disjoin(temp, two_flat[i].instructs.size());
                one_flat[j] = disjointed_pipelines[1];
                two_flat[i] = disjointed_pipelines[0];  //this one isnt even really necessary to reassign
            }
        }
    }
    //!!!!!!!!!!!
    //there may be an issue of how the conjunction is placed. as in the stalling is misplaced with interpipelined. to fix, keep conjunction before stalling between the two pipelines
    
    //inject balanced pipelines back in
    for (int i = 0; i < max_level_p1; i++){
        Inject_Flat_Pipeline(one_flat[i],i+1);
    }
    for (int i = 0; i < max_level_p2; i++){
        x.Inject_Flat_Pipeline(two_flat[i],i+1);
    }
    return;
}

//////////////////////////////////////////////////////////////////////
//Precondition: conjoined pipeline, and conjunction point
//Postcondition: vector of the two disjoined pipelines in order
//Function: splits the pipeline at the conjunction
//////////////////////////////////////////////////////////////////////
std::vector<Pipeline> disjoin(Pipeline & x, int conjunction){
    std::vector<Instruction> holder1, holder2;
    for (int i = 0; i < x.instructs.size(); i++){
        if (i < conjunction){
            holder1.push_back(x.instructs[i]);
        }
        else{
            holder2.push_back(x.instructs[i]);
        }
    }
    Pipeline new_1(holder1);
    Pipeline new_2(holder2);
    std::vector<Pipeline> temp = {new_1,new_2};
    return temp;
}

//////////////////////////////////////////////////////////////////////
//Precondition: two pipelines
//Postcondition: returns a conjoined pipeline with respect to the order
//Function: conjoins two pipelines
//////////////////////////////////////////////////////////////////////
Pipeline conjoin(Pipeline & first, Pipeline & second){
    std::vector<Instruction> holder;
    holder = first.instructs;
    for (int i = 0; i < second.instructs.size(); i++){
        holder.push_back(second.instructs[i]);
    }
    Pipeline temp(holder);  //does not check for depencies yet (not speaking in terms of implementation)
    return temp;
}

//////////////////////////////////////////////////////////////////////
//Precondition: creates a pipeline of one level of the hierarchy from caller pipeline, level is given for level of hierarchy to search for
//Postcondition: pipeline with only the given level
//Function: seperates a level of instructions from a pipeline
//////////////////////////////////////////////////////////////////////
Pipeline Pipeline::Flatten_Pipeline(int level){
    std::vector<Instruction> holder;
    bool found_start_of_level = false;
    int end = 0;
    for (int i = 0; i < instructs.size(); i++){
        Instruction temp = instructs.at(i);
        if (temp.getLevel() == level){holder.push_back(temp);}
        //gets all of the instructions of a level from the pipeline
    }
    Pipeline x(holder);
    x.CheckDepencies();
    return x;
}

//////////////////////////////////////////////////////////////////////
//Precondition: pipeline of a single level
//Postcondition: nothing
//Function: inserts the whole flat pipeline's instruction list in place of the current pipeline's level's instruction list. matches the levels and replaces the instruction list with the doctored one
//////////////////////////////////////////////////////////////////////
void Pipeline::Inject_Flat_Pipeline(Pipeline flat, int flat_level){
    //flat is injected into the level of the pipeline that flat represents
    
    int pipe_level_loc = -1; //where that level starts in the pipeline
    int pipe_level_loc_end = -1;    //where the level ends
    //ADD CONDITION FOR THE LEVEL NOT EXISTING
    for (int i = 0; i < instructs.size(); i++){
        if (instructs[i].getLevel() == flat_level && pipe_level_loc == -1){pipe_level_loc = i;}
 
        else if (instructs[i].getLevel() != flat_level && instructs[i].getLevel() != -1 && pipe_level_loc_end == -1 && pipe_level_loc != -1){pipe_level_loc_end = i;}
    }
 
    //range is till the end
    if (pipe_level_loc_end == -1){
        instructs.erase(instructs.begin()+pipe_level_loc, instructs.begin()+instructs.size()-1); //erases end value
        instructs.pop_back();
    }
    else{
        instructs.erase(instructs.begin()+pipe_level_loc, instructs.begin()+pipe_level_loc_end); //erases range of values for the level
    }
    //now insert the flat pipeline into the pipeline starting at the range
    for (int i = flat.instructs.size() -1; i >= 0; i--){
            instructs.insert(instructs.begin()+pipe_level_loc, flat.instructs[i]);
    }
    //should insert the instructions such that the last gets pushed up by last - 1

    //refresh pipeline
    refreshPipeline();
    //check depencies
    CheckDepencies();
    return;
}

//////////////////////////////////////////////////////////////////////
//Precondition: -
//Postcondition: -
//Function: constructor default
//////////////////////////////////////////////////////////////////////
Pipeline::Pipeline(){
    
}

//////////////////////////////////////////////////////////////////////
//Precondition: pipeline
//Postcondition: -
//Function: copy constructor
//////////////////////////////////////////////////////////////////////
Pipeline::Pipeline(Pipeline const & p){
    this-> pipe = p.pipe;
    this-> instructs = p.instructs;
}

//////////////////////////////////////////////////////////////////////
//Precondition: vector of instructions
//Postcondition: -
//Function: constructor for pipeline, sets up pipeline for given instructions
//////////////////////////////////////////////////////////////////////
Pipeline::Pipeline(std::vector<Instruction> x){
    for (int i = 0; i < x.size(); i++){
        instructs.push_back(x.at(i));   //Populate pipeline list
    }
    refreshPipeline();
    
}

//////////////////////////////////////////////////////////////////////
//Precondition: nothing
//Postcondition: nothing
//Function: refreshes the pipeline from the instructions list
//////////////////////////////////////////////////////////////////////
void Pipeline::refreshPipeline(){
    std::vector<std::vector<stage>> eraser;
    pipe = eraser;
    
    for (int i = 0; i < instructs.size(); i++){
        std::vector<stage> temp = {BLANK};
        pipe.push_back(temp);  //assign some sort of value to pipeline so it works
        
        if (instructs[i].getName() == stall){  //INSTRUCTION HERE at i IS A STALL
            int k = 0;//saves the increment indent for later down there. so it only does the indent once
            for (int j = 0; j < 5; j++){
                for (k;k < i; k++){//pushes back i number of spaces, because pipeline is indented
                    pipe[i].push_back(BLANK);
                }
                pipe[i].push_back(STALL);
            }
        }
        else{//INSTRUCTION HERE at i IS NOT A STALL
            int k = 0;//saves the increment indent for later down there. so it only does the indent once
            for (int j = 0; j < 5; j++){
                for (k;k < i; k++){//pushes back i number of spaces, because pipeline is indented
                    pipe[i].push_back(BLANK);
                }
                //pushback the stages into the pipeline
                if (j == 0){
                    pipe[i].push_back(IF);
                }
                else if (j == 1){
                    pipe[i].push_back(ID);
                }
                else if (j == 2){
                    pipe[i].push_back(EX);
                }
                else if (j == 3){
                    pipe[i].push_back(MEM);
                }
                else if (j == 4){
                    pipe[i].push_back(WB);
                }
                else{}
                
            }
        }
    }
    
    for (int i = 0; i < instructs.size();i++){
        std::vector<stage>::iterator it;
        std::vector<stage> temp_ = pipe.at(i);
        it = temp_.begin();
        temp_.erase(it);
        pipe[i]=temp_;  //got rid of the blank space
        
        //THERE IS A BLANK SPACE HERE, and its got your name. erase wont work
    }
    
    //add blank spaces for rows that are mismatched in size
    for (int i = 0; i < pipe.size()-1;i++){
        do {
            pipe[i].push_back(BLANK);
        }while(pipe[i].size() < pipe[instructs.size()-1].size());
    }
    
}

//////////////////////////////////////////////////////////////////////
//Precondition: out filestream
//Postcondition: nothing
//Function: prints the pipeline to a file
//////////////////////////////////////////////////////////////////////
void Pipeline::PrintPipeline(std::fstream& myfile){
    
    myfile.width(21);
    for(int i = 0; i < pipe[0].size(); i++){
        myfile << "t";
        myfile << 1+i;
        myfile.width(4);
    }
    //Sets up time
    
    myfile<<"\n";   //next line
    
    for (int i = 0; i < instructs.size(); i++){
        myfile.width(5);
        if(instructs[i].getName() == add){
            myfile << "add";
        }
        else if(instructs[i].getName() == addi){
            myfile << "addi";
        }
        else if(instructs[i].getName() == sub){
            myfile << "sub";
        }
        
        else if(instructs[i].getName() == subi){
            myfile << "subi";
        }
        
        else if(instructs[i].getName() == mul){
            myfile << "mul";
        }
        
        else if(instructs[i].getName() == div_){
            myfile << "div";
        }
        
        else if(instructs[i].getName() == rem){
            myfile << "rem";
        }
        else if(instructs[i].getName() == lw){
            myfile << "lw";
        }
        
        else if(instructs[i].getName() == stall){
            myfile << "stall";
        }
        else{}
        
        if (instructs[i].getName() == stall){
            myfile.width(12);
            myfile <<" ";
        }
        else{
            myfile << " ";
            myfile.width(3);
            PrintHelper_regs(myfile,instructs.at(i).getDestination());
            myfile<< ",";
            myfile.width(3);
            PrintHelper_regs(myfile,instructs.at(i).getSource1());
            myfile <<",";
            myfile.width(3);
            PrintHelper_regs(myfile,instructs.at(i).getSource2());
        }
        
        //Sets up instruction names
        
        
        for (int j = 0; j < pipe[0].size();j++){
            myfile.width(5);
            
            if(pipe[i][j] == IF){
                myfile << "IF";
            }
            else if(pipe[i][j] == ID){
                myfile << "ID";
            }
            else if(pipe[i][j] == EX){
                myfile << "EX";
            }
            else if(pipe[i][j] == MEM){
                myfile << "MEM";
            }
            else if(pipe[i][j] == WB){
                myfile << "WB";
            }
            else if(pipe[i][j] == STALL){
                myfile << "S";
            }
            else if(pipe[i][j] == BLANK){
                myfile << "     ";
            }
            else{}
        }
        myfile <<"\n";
    }
    myfile <<"\n";
    return;
}

//////////////////////////////////////////////////////////////////////
//Precondition: out file stream, and register
//Postcondition: nothing
//Function: prints to filestream, the register
//////////////////////////////////////////////////////////////////////
void Pipeline::PrintHelper_regs(std::fstream & myfile, reg x){
    switch(x){
        case $t0:
            ///////////////////////////////////////////////////
            myfile << "$t0";
            break;
        case $t1:
            myfile << "$t1";
            break;
        case $t2:
            myfile << "$t2";
            break;
        case $t3:
            myfile << "$t3";
            break;
        case $t4:
            myfile << "$t4";
            break;
        case $t5:
            myfile << "$t5";
            break;
        case $t6:
            myfile << "$t6";
            break;
        case $t7:
            myfile << "$t7";
            break;
        case $t8:
            myfile << "$t8";
            break;
        case $t9:
            myfile << "$t9";
            break;
            /////////////////////////////////////////////////////
        case $a0:
            myfile << "$a0";
            break;
        case $a1:
            myfile << "$a1";
            break;
        case $a2:
            myfile << "$a2";
            break;
        case $a3:
            myfile << "$a3";
            break;
        case $a4:
            myfile << "$a4";
            break;
        case $a5:
            myfile << "$a5";
            break;
        case $a6:
            myfile << "$a6";
            break;
        case $a7:
            myfile << "$a7";
            break;
        case $a8:
            myfile << "$a8";
            break;
        case $a9:
            myfile << "$a9";
            break;
            //////////////////////////////////////////////////////
        case $b0:
            myfile << "$b0";
            break;
        case $b1:
            myfile << "$b1";
            break;
        case $b2:
            myfile << "$b2";
            break;
        case $b3:
            myfile << "$b3";
            break;
        case $b4:
            myfile << "$b4";
            break;
        case $b5:
            myfile << "$b5";
            break;
        case $b6:
            myfile << "$b6";
            break;
        case $b7:
            myfile << "$b7";
            break;
        case $b8:
            myfile << "$b8";
            break;
        case $b9:
            myfile << "$b9";
            break;
            //////////////////////////////////////////////
        case $c0:
            myfile << "$c0";
            break;
        case $c1:
            myfile << "$c1";
            break;
        case $c2:
            myfile << "$c2";
            break;
        case $c3:
            myfile << "$c3";
            break;
        case $c4:
            myfile << "$c4";
            break;
        case $c5:
            myfile << "$c5";
            break;
        case $c6:
            myfile << "$c6";
            break;
        case $c7:
            myfile << "$c7";
            break;
        case $c8:
            myfile << "$c8";
            break;
        case $c9:
            myfile << "$c9";
            break;
            /////////////////////////////////////////////
        case $d0:
            myfile << "$d0";
            break;
        case $d1:
            myfile << "$d1";
            break;
        case $d2:
            myfile << "$d2";
            break;
        case $d3:
            myfile << "$d3";
            break;
        case $d4:
            myfile << "$d4";
            break;
        case $d5:
            myfile << "$d5";
            break;
        case $d6:
            myfile << "$d6";
            break;
        case $d7:
            myfile << "$d7";
            break;
        case $d8:
            myfile << "$d8";
            break;
        case $d9:
            myfile << "$d9";
            break;
        default:;
    }
    
    return;
}

//////////////////////////////////////////////////////////////////////
//Precondition: two instructions
//Postcondition: relevant data hazard
//Function: checks if there are any data hazards between the two instructions
//////////////////////////////////////////////////////////////////////
//x is before y in pipeline
DATA_HAZARD Pipeline::DataisDependent(Instruction x, Instruction y){
    //checks for data hazards
    //Write after read
    if (x.getName() == stall || y.getName() == stall){
        return NO_DATA_HAZARD; //stall
    }
    //Read after write
    else if (x.getDestination() == y.getSource1() || x.getDestination() == y.getSource2()){
        return RAW;
    }
    else if (x.getSource1() == y.getDestination() || x.getSource2() == y.getDestination()){
        return WAR;
    }
    //Write after write
    else if (x.getDestination() == y.getDestination()){
        return WAW;
    }

    return NO_DATA_HAZARD;
}

//////////////////////////////////////////////////////////////////////
//Precondition: nothing
//Postcondition: nothing
//Function: checks the pipeline depencies for Hazards, and fixes them with a stall. TODO control and structural hazards
//////////////////////////////////////////////////////////////////////
void Pipeline::CheckDepencies(){
    bool doesNotPass = false;
    while (!doesNotPass){ //while the instructions adds one stall, recheck
        doesNotPass = true; //if there are no dependencies then the loop will break
        for (int i = 0; i < instructs.size(); i++){ //i is first iterator of pipeline y axis
            for (int j = 0; j < instructs.size(); j++){ //j is second iterator of pipeline y axis
                if (i == j || i > j){}   //do nothing
                else if (DataisDependent(instructs.at(i), instructs.at(j)) ==RAW && abs(i-j) <= 3){
                    addStall(j+1);    //adds a stall inbetween
                    doesNotPass = false;
                    refreshPipeline();
                    i=instructs.size();
                    break;
                
                }
//                else if (DataisDependent(instructs.at(i), instructs.at(j)) == WAW && abs(i-j) <= 0){
//                    addStall(j+1);    //adds a stall inbetween
//                    doesNotPass = false;
//                    refreshPipeline();
//                    i=instructs.size();
//                    break;
//                    
//                }
//                else if (DataisDependent(instructs.at(i), instructs.at(j)) == WAR && abs(i-j) <= 1){
//                    addStall(j+1);    //adds a stall inbetween
//                    doesNotPass = false;
//                    refreshPipeline();
//                    i=instructs.size();
//                    break;
//                    
//                }
            }
        }
    }
    doesNotPass=false;
    //checking for structural hazards
    while (!doesNotPass){ //while the instructions adds one stall, recheck
        doesNotPass = true; //if there are no dependencies then the loop will break
        for (int i = 0; i < pipe.at(0).size(); i++){    //iterates through x axis of pipeline
            std::vector<stage> column_pipe = whatIsTime(i); //get a cross section of the pipeline
            //iterations through column of pipeline
            for (int k = 0; k < column_pipe.size(); k++){   //iterates through y axis at i of x axis
                for (int l = 0; l < column_pipe.size(); l++){   //second iterator through y axis of i at x axis
                    if (k ==l){}       //nothing
                    else if ( (column_pipe.at(k) == column_pipe.at(l)) && column_pipe.at(l) != BLANK && column_pipe.at(l) != STALL){  //same instruction being used
                        addStall(l+1);    //adds a stall inbetween
                        doesNotPass = false;
                        refreshPipeline();
                        i=instructs.size();
                        k = column_pipe.size();
                        //break out of all for loops
                        break;
                    }
                    else if ((column_pipe.at(k) == WB  && column_pipe.at(l) == ID) || (column_pipe.at(k) == ID  && column_pipe.at(l) == WB)){  //read/write structure hazard
                        addStall(l+1);    //adds a stall inbetween
                        doesNotPass = false;
                        refreshPipeline();
                        i=pipe.at(0).size();
                        k = column_pipe.size();
                        //break out of all for loops
                        break;
                    }
                }
            }
        }
    }

}

//////////////////////////////////////////////////////////////////////
//Precondition: stage at which the pipeline is conjoined. this is a pipeline combined with another
//Postcondition: the stage at which the conjuction is now present
//Function: checks the pipeline depencies for Hazards, and fixes them with a stall. TODO control and structural hazards
//////////////////////////////////////////////////////////////////////
int Pipeline::CheckDepencies(int conjunction){
    int new_junction = conjunction;
    bool doesNotPass = false;
    while (!doesNotPass){ //while the instructions adds one stall, recheck
        doesNotPass = true; //if there are no dependencies then the loop will break
        for (int i = 0; i < instructs.size(); i++){ //i is first iterator of pipeline y axis
            for (int j = 0; j < instructs.size(); j++){ //j is second iterator of pipeline y axis
                
                if (i == j || i > j){}   //do nothing
                else if (DataisDependent(instructs.at(i), instructs.at(j)) ==RAW && abs(i-j) <= 3){
                    addStall(j+1);    //adds a stall in-between
                    if (j <= new_junction){
                        new_junction++;
                    }
                    doesNotPass = false;
                    refreshPipeline();
                    i=instructs.size();
                    break;
                    
                }
                else if (DataisDependent(instructs.at(i), instructs.at(j)) == WAW && abs(i-j) <= 0){
                    addStall(j+1);    //adds a stall inbetween
                    if (j <= new_junction){
                        new_junction++;
                    }
                    doesNotPass = false;
                    refreshPipeline();
                    i=instructs.size();
                    break;
                    
                }
                else if (DataisDependent(instructs.at(i), instructs.at(j)) == WAR && abs(i-j) <= 1){
                    addStall(j+1);    //adds a stall inbetween
                    if (j <= new_junction){
                        new_junction++;
                    }
                    doesNotPass = false;
                    refreshPipeline();
                    i=instructs.size();
                    break;
                    
                }
            }
        }
    }
    doesNotPass=false;
    //checking for structural hazards
    while (!doesNotPass){ //while the instructions adds one stall, recheck
        doesNotPass = true; //if there are no dependencies then the loop will break
        for (int i = 0; i < pipe.at(0).size(); i++){    //iterates through x axis of pipeline
            std::vector<stage> column_pipe = whatIsTime(i); //get a cross section of the pipeline
            //iterations through column of pipeline
            for (int k = 0; k < column_pipe.size(); k++){   //iterates through y axis at i of x axis
                for (int l = 0; l < column_pipe.size(); l++){   //second iterator through y axis of i at x axis
                    if (k ==l){}       //nothing
                    else if ( (column_pipe.at(k) == column_pipe.at(l)) && column_pipe.at(l) != BLANK && column_pipe.at(l) != STALL){  //same instruction being used
                        addStall(l+1);    //adds a stall inbetween
                        if (l <= new_junction){
                            new_junction++;
                        }
                        doesNotPass = false;
                        refreshPipeline();
                        i=instructs.size();
                        k = column_pipe.size();
                        //break out of all for loops
                        break;
                    }
                    else if ((column_pipe.at(k) == WB  && column_pipe.at(l) == ID) || (column_pipe.at(k) == ID  && column_pipe.at(l) == WB)){  //read/write structure hazard
                        addStall(l+1);    //adds a stall inbetween
                        if (l <= new_junction){
                            new_junction++;
                        }
                        doesNotPass = false;
                        refreshPipeline();
                        i=pipe.at(0).size();
                        k = column_pipe.size();
                        //break out of all for loops
                        break;
                    }
                }
            }
        }
    }
    return new_junction;
    
}



