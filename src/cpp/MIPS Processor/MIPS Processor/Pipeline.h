//
//  Pipeline.h
//  MIPS Processor
//
//  Created by Michael DeLeo on 3/4/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#ifndef Pipeline_h
#define Pipeline_h

#include "Instruction.h"

//Pipeline is the data set for a set of time t against n instructions
class Pipeline : public Instruction{
private:
    std::vector<std::vector<stage>> pipe; //pipeline
    std::vector<Instruction> instructs; //List of instructions in pipeline
    
    void PrintHelper_regs(std::fstream & myfile, reg x);
    
    void addInstruction(Instruction x, int stage);
    void addStall(int stage);//at time t, and at stage s insert 5 stalls, and move instruction back
    Instruction whatIsStage(int stage);
    std::vector<stage> whatIsTime(int time);
    void refreshPipeline(); //refreshes pipeline with instructions available
    
    DATA_HAZARD DataisDependent(Instruction x, Instruction y);     //TODO
    bool StructureisDependent(Instruction x, Instruction y);//TODO
    bool ControlisDependent(Instruction x, Instruction y);//TODO
    
    void Inject_Flat_Pipeline(Pipeline flat, int flat_level);
    Pipeline Flatten_Pipeline(int level);
public:
    Pipeline();
    Pipeline(std::vector<Instruction> x);
    Pipeline(Pipeline const & p);

    
    void PipelineDependency(Pipeline & x);    //checks for depencies on the other pipeline
    
    void CheckDepencies();
    int CheckDepencies(int conjunction);
    
    void PrintPipeline(std::fstream& myfile);
    
    friend Pipeline conjoin(Pipeline & first, Pipeline & second);
    friend std::vector<Pipeline> disjoin (Pipeline & x, int conjunction);
};


#endif /* Pipeline_h */
