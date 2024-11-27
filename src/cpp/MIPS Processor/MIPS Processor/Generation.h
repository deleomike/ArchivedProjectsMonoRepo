//
//  Generation.h
//  MIPS Processor
//
//  Created by Michael DeLeo on 3/4/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#ifndef Generation_h
#define Generation_h

#include "Pipeline.h"


//Generation is the data set for 4 pipelines. This is an AI, it holds the order for the 4 pipelines
class Generation : public Pipeline{
private:
    Pipeline Alpha;
    Pipeline Bravo;
    Pipeline Charlie;
    Pipeline Delta;
    //4 pipelines
    int dependencies;
    int time_Alpha,time_Bravo,time_Charlie,time_Delta;
    int time_elapsed;
public:
    void countDependencies();
    void countPipelineTime();
    void countTime();
    
    Generation(Pipeline Alpha, Pipeline Bravo, Pipeline Charlie, Pipeline Delta);
    
    void CheckAllDepencies();
    
    
    void PrintGeneration(std::fstream& myfile);
    
};



#endif /* Generation_h */
