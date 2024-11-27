//
//  main.cpp
//  FFT_CSVtoTXTFORMAT
//
//  Created by Michael DeLeo on 6/10/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ifstream file;
    file.open("/Users/michaeldeleo/Documents/workspace/FFT_CSVtoTXTFORMAT/FFT_CSVtoTXTFORMAT/fftdata.csv");
    std::vector<std::string> data;
    for (int i = 0; i < 64; i++){
        std::string temp;
        getline(file,temp);
        
        if (i == 0){
            temp.erase(temp.begin()+2);
        }//first case, has {{
        //everything else has { to start with
        else{temp.erase(temp.begin()+1);} //delete the first comma that is before a number
        if (i == 63){}//do not delete everything at end
        else{
            temp.erase(temp.end()-6, temp.end());
            temp.append("},\n");//format ends of everything else
        }
        data.push_back(temp);
        std::cout << temp;
    }
    file.close();
    std::ofstream fill;
    fill.open("/Users/michaeldeleo/Documents/workspace/FFT_CSVtoTXTFORMAT/FFT_CSVtoTXTFORMAT/fftdata.txt");
    for (int i =0; i < data.size(); i++){
        fill << data.at(i);
    }
    fill.close();
}
