package com.company;

import com.company.Matrix;

import java.io.Serializable;

public class Layer implements Serializable {
    private Matrix nodes;
    private Matrix weights;
    private Matrix biases;

    Layer(){
        nodes = null;
        weights = null;
        biases = null;
    }

    Layer(Matrix N, Matrix W, Matrix B){
        nodes = N;
        weights = W;
        biases = B;
    }

    Layer(Matrix N, Matrix W){
        nodes = N;
        weights = W;
        biases = new Matrix(W.sizey(),1);
    }

    Layer(Matrix W){
        nodes = null;
        biases = new Matrix(W.sizey(),1);
        weights = W;
    }

    public Matrix getNodes(){ return nodes;}
    public Matrix getWeights(){ return weights;}
    public Matrix getBiases(){ return biases; }

    public void setNodes(Matrix N){ nodes = N;}
    public void setWeights(Matrix W){ weights = W;}
    public void setBiases(Matrix B){ biases = B; }

    public Matrix multiply(){
        try{
            return (weights.multiply(nodes)).sigmoid();
            //e.g.) 16x782 * 782x1 = 16 x 1
        } catch(MatrixDimensions m){
            System.out.println(m.toString());
            return null;
        }

    }

}