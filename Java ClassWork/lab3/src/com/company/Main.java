package com.company;

import java.lang.reflect.Array;
import java.util.*;

public class Main {

    public static void main(String[] args) {
	// write your code here
        Scanner scan = new Scanner(System.in);
        ArrayList<MyNum> arr = new ArrayList<MyNum>();
        System.out.println("Enter one number and hit enter. Enter as many as you want. Type -1 to stop.");
        while(true){
            System.out.println("Enter a number. -1 to stop");
            double temp =scan.nextDouble();
            if (temp == -1){
                break;
            }
            MyNum x = new MyNum(temp);
            arr.add(x);
        }

        List_Numbers(arr);

    }

    public static void List_Numbers(ArrayList<MyNum> arr){
        System.out.println("The user entered the following numbers");
        for (int i = 0; i < arr.size(); i++){
            //displays numbers
            System.out.printf("%f\n",arr.get(i).d);
        }
        System.out.println("##################################\nNow Testing all methods of each object.");
        for(int i = 0; i < arr.size(); i++){
            MyNum temp = arr.get(i);
            //do all functions
            if(temp.check_is_even()){
                System.out.printf("%d is even\n",temp.i);
            }
            else{
                System.out.printf("%d is odd\n", temp.i);
            }
            int x = i+1;
            System.out.printf("Using %d for all parameters\n",x);
            System.out.println("Format of object [] is [double int octal hex]");
            temp.print_number();
            System.out.println("Testing the normal print");
            temp.print_number(x);
            System.out.println("Now Testing Hex, and Hex with a parameter");
            temp.print_number_Hex();
            temp.print_number_Hex(x);
            System.out.println("Now Testing Octal, and Octal with a parameter");
            temp.print_number_Octal();
            temp.print_number_octal(x);
            System.out.println("##################################");
        }
        return;
    }
}

class MyNum{

    double d;
    int i;
    short s;
    byte b;

    MyNum(){
        d = 0;
        i = 0;
        s = 0;
        b = 0;
    }

    MyNum(double A){
        d = A;
        i = (int)A;
        s = (short)A;
        b = (byte)A;
    }

    boolean check_is_even(){
        if (i%2 == 0){
            return true;
        }
        else{
            return false;
        }
    }
    void print_number(){
        System.out.printf("[%f %d 0x%o 0x%x]\n",d,i,s,b);
    }

    void print_number(int i){
        System.out.printf("%d\n",i);
    }
    void print_number_Hex(){
        System.out.printf("0x%X\n",b);
    }
    void print_number_Hex(int i){
        byte x = (byte) i;
        System.out.printf("0x%X\n",x);
    }
    void print_number_Octal(){
        System.out.printf("%o\n",s);
    }
    void print_number_octal(int i){
        short x = (short) i;
        System.out.printf("%o\n",x);
    }
}