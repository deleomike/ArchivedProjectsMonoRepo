//
//  Matrix.h
//  SensorFusionSimulation
//
//  Created by Michael DeLeo on 3/3/19.
//  Copyright © 2019 Michael DeLeo. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

#include <vector>
#include <iostream>

class Matrix{
public:
    
    Matrix(){}
    
    //Setup matrix n by n, with a filler of 0
    Matrix(int n){
        std::vector<std::vector<float>> MAT;
        mat = MAT;
        float filler = 0;
        for(int i = 0; i < n; i++){
            std::vector<float> temp (n,filler);
            mat.push_back(temp);
        }
    }
    
    Matrix(int len, int height){
        std::vector<std::vector<float>> MAT;
        mat = MAT;
        for(int i = 0; i < height; i++){
            std::vector<float> temp (len);
            mat.push_back(temp);
        }
    }
    
    Matrix(Matrix const & pam){
        std::vector<std::vector<float>> MAT;
        mat = MAT;
        int height = pam.mat.size();
        for(int i = 0; i < height; i++){
            std::vector<float> temp = pam.mat[i];
            mat.push_back(temp);
        }
    }
    
    //returns the column
    Matrix Column(int col);
    //returns the row
    Matrix Row(int row);
    //returns the value
    float ValueAt(int x, int y) { return mat[y][x];}
    
    //This transposes current matrix, and assigns it
    void Transpose();
    //Invert the matrix
    void Invert();
    
    Matrix AddMatrix(Matrix pam);
    Matrix MultMatrix(Matrix pam);
    
    bool SPD();
    
    void LUFactor(Matrix & L, Matrix & U);
    
    void GaussianEliminate();
    
    Matrix Solve();
    
    void SetIdentityMatrix();
    
    void Print();
    void PrintSparse();
    
    void setValue(int col, int row, float value) {mat[row][col] = value;}
private:
    std::vector<std::vector<float>> mat;
    //std::vector<std::vector<int>> permutation;
    
    bool LengthMatches(Matrix pam){return Length() == pam.Length() ? true : false;}
    bool HeightMatches(Matrix pam){return Height() == pam.Height() ? true: false;}
    
    float sumRow(int row, int exceptThisIndex);
    
    int Height() { return mat.size();}
    int Length() { return mat[0].size();}
    
    
    void setRow(std::vector<float> x, int row);
    
    void switchRow();
    
};


#endif /* Matrix_h */
