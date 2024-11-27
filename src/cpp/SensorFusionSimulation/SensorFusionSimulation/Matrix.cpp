//
//  Matrix.cpp
//  SensorFusionSimulation
//
//  Created by Michael DeLeo on 3/3/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

#include "Matrix.h"


Matrix Matrix::Column(int col){
    int height = Height();
    
    Matrix Slice(1,height); //length 1, height = height
    
    for (int i = 0; i < height; i++){
        float temp = ValueAt(col, i);
        Slice.mat[i][0] = temp;
    }
    
    return Slice;
}

/*
Matrix Matrix::Row(int row){
    int length = Length();
    
    Matrix Slice(length,1);
    
    for (int i = 0; i < length; i++){
        float temp = ValueAt(i,row);
    }
    
    return Slice;
}*/

void Matrix::SetIdentityMatrix(){
    int height = Height();
    for (int i = 0; i < height; i++){
        setValue(i, i, 1);
    }
}

void Matrix::Print(){
    int height = Height();
    int length = Length();
    for (int i = 0; i < height; i++){
        for (int j = 0; j < length; j++ ){
            std::cout << ValueAt(j,i) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Matrix::PrintSparse(){
    int height = Height();
    int length = Length();
    for (int i = 0; i < height; i++){
        for (int j = 0; j < length; j++){
            if (ValueAt(j,i) != 0){
                std::cout << "(" << j << "," << i << "): " << ValueAt(j, i) << std::endl;
            }
        }
    }
}

void Matrix::Transpose(){
    std::vector<std::vector<float>> temp;
    for (int i = 0; i < mat[0].size(); i++){
        std::vector<float> x(mat.size(),0);
        temp.push_back(x);
    }
    
    for (int i = 0; i < temp.size(); i++){
        for (int j = 0; j < temp[0].size(); j++){
            temp[i][j] = mat[j][i];
        }
    }
    mat = temp;
    
}

/*
//Invert the matrix
void Matrix::Invert(){
    
}

 */
Matrix Matrix::AddMatrix(Matrix pam){
    if (LengthMatches(pam) && HeightMatches(pam)){
        //Matrices match
        int length = Length();
        int height = Height();
        Matrix sum(length,height);
        for (int i = 0; i < length; i++){
            for (int j = 0; j < height; j++){
                float summed = mat[j][i] + pam.mat[j][i];
                sum.setValue(i, j, summed);
            }
        }
        
        return sum;
    }
    else{
        return *this;
    }
}

/*

Matrix Matrix::MultMatrix(Matrix pam){
    
}

bool Matrix::SPD(){
    
}

void Matrix::LUFactor(Matrix & L, Matrix & U){
    
}
 */

//Assume last column is matrix b in the equation
void Matrix::GaussianEliminate(){
    
}

/*
 Matrix Matrix::Solve(){
 }
*/
