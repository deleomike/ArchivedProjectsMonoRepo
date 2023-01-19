package com.company;

import javafx.scene.transform.MatrixType;

import java.io.Serializable;

public class NN implements Serializable {
    private Layer InputLayer = null;
    private Layer HiddenLayer1;
    private Layer HiddenLayer2;
    private Matrix OutputLayer = null;

    //Save State constructor
    NN(Layer In, Layer Hid1, Layer Hid2, Matrix Out){
        InputLayer = In;
        HiddenLayer1 = Hid1;
        HiddenLayer2 = Hid2;
        OutputLayer = Out;
    }

    NN(Layer Hid1, Layer Hid2){
        HiddenLayer1 = Hid1;
        HiddenLayer2 = Hid2;
    }

    public NN(){
        //everything is set to 0

        //1x782 nodes
        Matrix in = new Matrix(782,1);
        //16x782 weights
        Matrix w3 = new Matrix(16,782);
        InputLayer = new Layer(in,w3);

        //1x16 hidden layer nodes
        Matrix n1 = new Matrix(16,1);
        //16x16 hidden layer weights
        Matrix w1 = new Matrix(16);
        HiddenLayer1 = new Layer(n1,w1);

        Matrix n2 = new Matrix(16,1);
        //1x10 final output = 1x16 nodes * 16x10 weights
        Matrix w2 = new Matrix(10,16);
        HiddenLayer2 = new Layer(n2,w2);

    }


    /**
     *
     */
    public void Reset(){
        //TODO
    }

    /**
     *
     * @param Input
     */
    private void newInput(Matrix Input){
        //TODO Throw exception for improper size

        if (InputLayer != null){
            InputLayer.setNodes(Input);
        }
        else{
            //Has not been created yet
            Matrix W = new Matrix(Input.sizey()*16);
            InputLayer = new Layer(Input,W);
        }
    }

    /**
     *
     */
    private void FeedForward(){
        //Do the operation for the input layer
        Matrix Hidden = InputLayer.multiply();
        //Then set that matrix as the nodes of the first hidden layer
        HiddenLayer1.setNodes(Hidden);
        //Then propogate to the second layer
        Matrix Hidden2 = HiddenLayer1.multiply();

        HiddenLayer2.setNodes(Hidden2);
        //now assign to the output
        OutputLayer = HiddenLayer2.multiply();

    }

    /**
     *
     * @param correctValue
     */
    private void backPropagate(int correctValue){
        //This process is very iterative, and can be simplified if the layers are in arrays instead of discrete

        //First, calculate error of output layer
        Matrix sigmaPrime = OutputLayer.sigmoidPrime(); //sigma prime is a 10x10 matrix with the diagonal being
        //sigmoid prime(Z)

        Matrix costGradient = Cost(correctValue);

        try {

            Matrix delta3 = sigmaPrime.HadamardProduct(costGradient);   //the error of the output layer

            //////////////////////////////////////////////////
            //Find the second hidden layer delta
            Matrix weights2 = HiddenLayer2.getWeights().Transpose(); //get transpose of the weights
            Matrix nodes2 = HiddenLayer2.getNodes().sigmoidPrime();
            //Matrix nodes2 = HiddenLayer2.getNodes().sigmaPrime(); //get sigmaprime(nodes)
            Matrix delta2 = nodes2.HadamardProduct(weights2.multiply(delta3)); //the error for the second hidden layer
            /////////////////////////////////////////////////
            //Find the first hidden layer delta
            Matrix weights1 = HiddenLayer1.getWeights().Transpose(); //get transpose of the weights
            Matrix nodes1 = HiddenLayer1.getNodes().sigmoidPrime();
            //Matrix nodes1 = HiddenLayer1.getNodes().sigmaPrime(); //get sigmaprime(nodes)
            Matrix delta1 = nodes1.HadamardProduct(weights1.multiply(delta2)); //the error for the second hidden layer
            /////////////////////////////////////////////////
            //Find the input layer delta
            Matrix weights0 = InputLayer.getWeights().Transpose(); //get transpose of the weights
            Matrix nodes0 = InputLayer.getNodes().sigmoidPrime();
            //Matrix nodes0 = InputLayer.getNodes().sigmaPrime(); //get sigmaprime(nodes)
            Matrix delta0 = nodes0.HadamardProduct(weights0.multiply(delta1)); //the error for the second hidden layer
            ////////////////////////////////////////////////


            //Now apply the changes to the weights and biases
            //First the biases
            ////////////////////////////////////////////////
            Matrix inputBiases = InputLayer.getBiases();
            Matrix Hidden1Biases = HiddenLayer1.getBiases();
            Matrix Hidden2Biases = HiddenLayer2.getBiases();

            //Add the delta to the biases
            inputBiases = inputBiases.add(delta0);
            Hidden1Biases = Hidden1Biases.add(delta1);
            Hidden2Biases = Hidden2Biases.add(delta2);

            //set the biases back into the layers
            InputLayer.setBiases(inputBiases);
            HiddenLayer1.setBiases(Hidden1Biases);
            HiddenLayer2.setBiases(Hidden2Biases);
            ///////////////////////////////////////////////

            //Now the weights
            ///////////////////////////////////////////////
            Matrix inputWeights = InputLayer.getWeights();
            Matrix Hidden1Weights = HiddenLayer1.getWeights();
            Matrix Hidden2Weights = HiddenLayer2.getWeights();

            inputWeights = inputWeights.add(InputLayer.getNodes().VectorCross(delta1));
            Hidden1Weights = Hidden1Weights.add(HiddenLayer1.getNodes().VectorCross(delta2));
            Hidden2Weights = Hidden2Weights.add(HiddenLayer2.getNodes().VectorCross(delta3));

            InputLayer.setWeights(inputWeights);
            HiddenLayer1.setWeights(Hidden1Weights);
            HiddenLayer2.setWeights(Hidden2Weights);
            //////////////////////////////////////////////
        } catch(MatrixDimensions m){
            System.out.println(m.toString());
        }


    }

    //calculates cost of guessed values
    private Matrix Cost(int correctValue){
        Matrix c = OutputLayer;
        double guess = c.getValue(correctValue,0);
        c.setValue(correctValue,0,guess-correctValue);
        return c;
    }

    /**
     *
     * @param value
     * @return
     */
    private boolean IsOutput(int value){
        //look for the highest output. if it is it, then it is correct
        Double max = new Double(0);
        int index = 0;
        for (int i = 0; i < OutputLayer.sizey(); i++){
            if (OutputLayer.getValue(i,0) > max){
                max = OutputLayer.getValue(i,0);
                index = i;
            }
        }
        //If it is the highest value then it is true
        if (index == value){ return true;}
        else { return false;}
    }

    /**
     *
     * @param Input
     * @param correctValue
     * the error at layer l neuron j is given by the partial of the cost function with respect to the partial of the
     * neuron at layer l neuron j
     */
    public boolean Train(Matrix Input, int correctValue){
        //Assign the input
        newInput(Input);
        //Propagate the data
        FeedForward();
        boolean res = IsOutput(correctValue);
        //Correct the mistakes
        backPropagate(correctValue);

        return res;
    }

    /**
     *
     * @param Input
     * @param correctValue
     * @return
     */
    public boolean Test(Matrix Input, int correctValue){
        //Assign the input
        newInput(Input);
        //Propagate the data
        FeedForward();
        return IsOutput(correctValue);
    }

    public void printOutput(){
        for (int i = 0; i < OutputLayer.sizey(); i++){
            System.out.printf("%f \n",OutputLayer.getValue(i,0));
        }
        System.out.println();
    }
}