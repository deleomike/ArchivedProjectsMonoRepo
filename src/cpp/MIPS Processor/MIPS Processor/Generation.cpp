//
//  Generation.cpp
//  MIPS Processor
//
//  Created by Michael DeLeo on 3/4/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <stdio.h>

#include "Generation.h"

//////////////////////////////////////////////////////////////////////
//Precondition: out file stream
//Postcondition: nothing
//Function: prints all four pipelines of the generation
//////////////////////////////////////////////////////////////////////
void Generation::PrintGeneration(std::fstream& myfile){
    //myfile.width(7);
    //yfile<<"ALPHA";
    Alpha.PrintPipeline(myfile);
    //myfile.width(7);
    //myfile<<"BRAVO";
    Bravo.PrintPipeline(myfile);
    //myfile.width(7);
    //myfile<<"CHARLIE";
    Charlie.PrintPipeline(myfile);
    //myfile.width(7);
    //myfile<<"DELTA";
    Delta.PrintPipeline(myfile);
    
    
}

//////////////////////////////////////////////////////////////////////
//Precondition: 4 pipelines
//Postcondition: -
//Function: constructor for generation
//////////////////////////////////////////////////////////////////////
Generation::Generation(Pipeline Alpha_, Pipeline Bravo_, Pipeline Charlie_, Pipeline Delta_){
    //   {this->Alpha=Alpha_;this->Bravo=Bravo_;this->Charlie=Charlie_;this->Delta=Delta_;}
    
    
    
    Pipeline temp1(Alpha_);
    Pipeline temp2(Bravo_);
    Pipeline temp3(Charlie_);
    Pipeline temp4(Delta_);
    Alpha = Alpha_;
    Bravo = temp2;
    Charlie = temp3;
    Delta = temp4;
    dependencies =0;
    time_Alpha = 0;
    time_Bravo = 0;
    time_Charlie = 0;
    time_Delta = 0;
    time_elapsed = 0;
}




//////////////////////////////////////////////////////////////////////
//Precondition: nothing
//Postcondition: nothing
//Function: checks all internal depencies. TODO check interpipeline dependencies
//////////////////////////////////////////////////////////////////////
void Generation::CheckAllDepencies(){
    Alpha.CheckDepencies();
    Bravo.CheckDepencies();
    Charlie.CheckDepencies();
    Delta.CheckDepencies();
    //does not account for depencdencies across pipelines yet

    Alpha.PipelineDependency(Bravo);
    Alpha.PipelineDependency(Charlie);
    Alpha.PipelineDependency(Delta);
    Bravo.PipelineDependency(Charlie);
    Bravo.PipelineDependency(Delta);
    Charlie.PipelineDependency(Delta);
}


//template of conditions
//////////////////////////////////////////////////////////////////////
//Precondition:
//Postcondition:
//Function:
//////////////////////////////////////////////////////////////////////


