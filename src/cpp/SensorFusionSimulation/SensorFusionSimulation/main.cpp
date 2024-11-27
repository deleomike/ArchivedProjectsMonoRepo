//
//  main.cpp
//  SensorFusionSimulation
//
//  Created by Michael DeLeo on 3/3/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

#include "Matrix.h"


int main() {
    Matrix first(50,50);
    first.setValue(2, 3, 2);
    first.SetIdentityMatrix();
    first.Column(1).Print();
    first.Print();
    first.Transpose();
    first.Print();
    
    Matrix sum = first.AddMatrix(first);
    sum.PrintSparse();
    return 0;
}


