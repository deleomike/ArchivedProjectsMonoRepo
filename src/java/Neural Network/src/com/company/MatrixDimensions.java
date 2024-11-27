package com.company;

import java.io.Serializable;

public class MatrixDimensions extends Exception{
    int Matrix1_N,Matrix1_M,Matrix2_N,Matrix2_M;

    MatrixDimensions(){
        Matrix1_N = Matrix2_N = Matrix2_M = Matrix1_M = 0;
    }

    MatrixDimensions(Matrix M, Matrix N){
        Matrix1_N = M.sizex();
        Matrix1_M = M.sizey();

        Matrix2_N = N.sizex();
        Matrix2_M = N.sizey();
    }

    @Override
    public String toString(){
        return String.format("Incorrect Dimensions for M, N: M(%d,%d) N(%d,%d)",Matrix1_N,Matrix1_M,Matrix2_N,Matrix2_M);
    }

}