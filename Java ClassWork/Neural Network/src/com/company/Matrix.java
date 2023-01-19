package com.company;

import java.io.Serializable;
import java.util.*;

public class Matrix implements Serializable {
    private Double [][] mat;
    private int Rows,Columns; //sizes

    /////////////////////////////////////////
    //Constructors
    Matrix(){
        mat = new Double[0][0];
        Rows = 0;
        Columns = 0;
    }

    Matrix(int n){
        Rows = n;
        Columns = n;
        mat = new Double[n][n];
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                mat[i][j] = new Double(0);
            }
        }
    }

    Matrix(int n, int m){
        Rows = n;
        Columns = m;
        mat = new Double[n][m];

        for (int i = 0;i < n; i++){
            for (int j = 0; j < m; j++){
                mat[i][j] = new Double(0);
            }
        }
    }

    public Matrix(double [] x){
        this(x.length,1);


        for (int i = 0; i < Rows; i++){
            setValue(i,0,x[i]);
        }

    }

    Matrix(Matrix m){
        this(m.Rows,m.Columns);
        this.Rows = m.Rows;
        this.Columns = m.Columns;
        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Columns; j++){
                mat[i][j] = m.getValue(i,j);
            }
        }
    }




    ///////////////////////////////////

    public Matrix sigmoid(){
        Matrix res = new Matrix(this);

        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Columns; j++){
                double x= getValue(i,j).doubleValue();
                res.setValue(i,j,(1/( 1 + Math.pow(Math.E,(-1*x)))));
            }
        }
        return res;
    }

    public Matrix sigmoidPrime(){
        Matrix res = new Matrix(this);

        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Columns; j++){
                double x = getValue(i,j);
                double ex = Math.pow(Math.E,-1*x);

                x = ex * Math.pow(1+ex,2);

                res.setValue(i,j,x);
            }
        }
        return res;
    }

//    public Matrix sigmaPrime(){
//        //Requires a nx1 matrix
//        //returns a diagonalized nxn matrix with the diagonal being simoidprime(input)
//
//        Matrix res = new Matrix(this.Rows);
//
//        Matrix outputSigmoidPrime = this.sigmoidPrime();
//        for (int i = 0; i < this.Rows; i++){
//            res.setValue(i,i,outputSigmoidPrime.getValue(i,0));
//        }
//        //set the values of sigmoidprime(output) to the diagonal
//
//        return res;
//    }

    public Matrix HadamardProduct(Matrix m) throws MatrixDimensions{
        Matrix res = new Matrix(this);

        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Columns; j++){
                double product = getValue(i,j) * m.getValue(i,j);
                res.setValue(i,j,product);
            }
        }

        return res;
    }



    public void setValue(int row, int col, Double val){
        try{
            mat[row][col] = val;
        } catch (IndexOutOfBoundsException e){
            System.out.printf("Out of bounds - Height: %d, Width: %d\n",this.Rows,this.Columns);
        }
    }

    public Double getValue(int row, int col){
        try{
            return mat[row][col];
        } catch(IndexOutOfBoundsException e){
            return Double.NaN;
        }
    }

    //this matrix is on the left, the given matrix is on the right
    public Matrix multiply(Matrix m) throws MatrixDimensions{

        if (this.Columns != m.Rows){ throw new MatrixDimensions(this,m); }

        Matrix res = new Matrix(this.Rows,m.Columns);

        //A is nxm and B is mxp
        //i = 1..n, j = 1..p
        for (int i = 0; i< this.Rows; i++){
            for (int j = 0; j < m.Columns; j++){
                Double weightedSum = new Double(0);
                for (int k = 0; k < this.Columns; k++){
                    //do the summation of the values
                    weightedSum += this.getValue(i,k)*m.getValue(k,j);

                }
                //do the sigmoid operation
                weightedSum = new Double(weightedSum);
                res.setValue(i,j,weightedSum);

            }
        }

        return res;

    }

    public Matrix add(Matrix m) throws MatrixDimensions{
        Matrix res = new Matrix(m.Rows,m.Columns);

        if (this.Rows != m.Rows || this.Columns != m.Columns){ throw new MatrixDimensions(this,m);}

        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Columns; j++){
                res.setValue(i,j,this.getValue(i,j) + m.getValue(i,j));
            }
        }

        return res;
    }


    public int sizex(){ return Columns;}
    public int sizey(){ return Rows;}


    Matrix Transpose(){
        Matrix res = new Matrix(Columns,Rows);
        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Columns; j++){
                Double temp = getValue(i,j);
                res.setValue(j,i,temp);
            }
        }
        return res;
    }

    Matrix VectorCross(Matrix m){
        Matrix res = new Matrix(m.Rows,this.Rows);

        for (int i = 0; i < m.Rows; i++){
            for (int j = 0; j < this.Rows; j++){
                res.setValue(i,j,getValue(j,0)*m.getValue(i,0));
            }
        }
        return res;
    }

    Matrix Inverse(){
        //TODO Exception for non square matrix
        Matrix res = new Matrix(Rows,Columns);
        if (isDiagonal()){
            for (int i = 0; i < Rows; i++){
                try{
                    res.setValue(i,i,1/res.getValue(i,i));  //do the inverse
                }catch (ArithmeticException e){
                    res.setValue(i,i,new Double(0));    //this value is 0
                }
            }
        }
        else{
            //TODO Square normal matrix
        }
        return res;
    }

    boolean isDiagonal(){
        for (int i = 0; i < Rows; i++){
            for (int j = 0; j < Columns; j++){
                if (i!=j && getValue(i,j)!=0){
                    return false;
                }
            }
        }
        return true;
    }

    //Inverse for a non-square matrix
    Matrix PseudoInverse(){
        try {
            Matrix AT = Transpose(); //Get transpose
            Matrix A_inverse = (multiply(AT)).Inverse();    //(AT * A) ^-1
            return AT.multiply(A_inverse);
        } catch(MatrixDimensions m){
            return null;
        }
    }
}