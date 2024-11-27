//
//  MIPS_Architecture.hpp
//  MIPS Processor
//
//  Created by Michael DeLeo on 3/2/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#ifndef MIPS_Architecture_hpp
#define MIPS_Architecture_hpp

#include <stdio.h>

    class MIPS{
        //8bit
    private:
        //IMEM Instructions();    //instruction memory
        int ProgramCounter;
    public:
        uint8_t ALU(uint8_t first, uint8_t second);
        
        
        MIPS();
        
    };

    //Includes ports
    struct IMEM{
        uint32_t read_address;  //Read address line
        uint32_t Instruction;    //32 bit instruction
    };

    struct REGMEM{
        //in
        uint8_t read_register_1, read_register_2;   //Each are 5 bits ports
        uint8_t write_register; //5 bit port
        bool reg_write;
        //write data
        //out
        uint32_t read_data1,read_data2; //Each are 32 bit ports
        
        
        
        
    };

    struct reg_mux{
        bool REGDST;
        
    };

    struct reg_mux32{
        bool REGDST;
        uint32_t in1,in2;   //32 bit input ports
        uint32_t out_;      //32 bit output port
        
    };


    struct sign_extend{
        uint16_t input; //port
        uint32_t output;//port
    };

struct ALU_control{
    uint8_t input;  //6 bit input port
    uint8_t ouput;  //UNKNOWN PORT SIZE
};

struct ALU_data{
    //input ports
    uint32_t in1,in2;
    uint8_t  control;
    //output ports
    uint32_t zero;
    uint32_t result;
};

struct Data_Memory{
    //input ports
    uint32_t address;
    uint32_t write_data;
    //output ports
    uint32_t read_data;
};

struct data_mux{
    //input ports
    uint32_t in1,in2;
    //output ports
    uint32_t out_;
};

struct add_mux{
    //input ports
    uint8_t in1,in2;
    //output ports
    uint8_t out_;
};

struct sll2{
    //input ports
    uint32_t in1;
    //output ports
    uint32_t out_;
};


#endif /* MIPS_Architecture_hpp */
