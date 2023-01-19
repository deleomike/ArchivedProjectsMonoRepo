package com.company;

import java.io.*;
import java.util.*;
import Files_Operations.*;

public class Main {

    public static void main(String[] args) {

        NN second = loadItems();


	    /*double [][] mat = {{5,3,2,9},{10,-5,3,-1}};

	    Matrix m = new Matrix(mat);

	    Matrix AT = m.Transpose();

	    Matrix AT_A = AT.multiply(m);

	    printMatrix(m);
	    printMatrix(AT);
	    printMatrix(AT_A);
	    printMatrix(m.PseudoInverse());*/

	    NN first = new NN();

	    Matrix test = new Matrix(782,1);
	    //printMatrix(test);
	    first.Train(test,3);
	    first.printOutput();
	    first.Train(test,3);
	    first.printOutput();

	    first.Test(test,0);
	    first.printOutput();

        quitSave(first);

    }

    static void printMatrix(Matrix m){
        for (int i = 0; i < m.sizey(); i++){
            for (int j = 0; j < m.sizex(); j++){
                System.out.printf("%f ",m.getValue(i,j));
            }
            System.out.println();
        }
        System.out.println();
    }

    static NN loadItems(){
        //LOAD DATA
        try (ObjectInputStream obj = new ObjectInputStream(new FileInputStream("data"))) {
            while(true) {
                try {
                    NN it = ((NN) obj.readObject());
                    if (it == null){
                        break;
                    } else{
                        return it;
                    }

                } catch (ClassNotFoundException e) {
                    System.out.println("Error reading binary file");
                }
            }
        }catch(FileNotFoundException e){

        }catch(IOException e){

        }
        return null;
    }

    static void quitSave(NN it){
        try(ObjectOutputStream obj = new ObjectOutputStream(new FileOutputStream("data"))){
            obj.writeObject(it);
            obj.flush();
        }catch(FileNotFoundException e){
            System.out.println("File does not exist");
        }catch(IOException e){

        }
    }
}
