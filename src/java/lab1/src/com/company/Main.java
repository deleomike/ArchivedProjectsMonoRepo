package com.company;

import java.util.*;

public class Main {


    public static void main(String[] args) {
	// write your code here
        for (int j = 0; j < 15; j++) {
            for (int i = 0; i < 50; i++) {
                if (j < 9 && i < 12){
                    if ((j % 2) == 0) {
                        if ((i % 2) == 0)
                            System.out.printf("*");
                        else
                            System.out.printf(" ");
                    }
                    else if (i <= 10){
                        if ((i % 2) == 0)
                            System.out.printf(" ");
                        else
                            System.out.printf("*");
                    }
                    else if (i == 11){
                        System.out.printf(" ");
                    }
                }
                else {
                    System.out.printf("=");
                }
            }
            System.out.printf("\n");

        }
        //TODO input

        System.out.println("Enter an Array of 10 Integers:");
        Scanner scan = new Scanner(System.in);

        int arr[] = {0,0,0,0,0,0,0,0,0,0};

        for (int i = 0; i < 10; i++){
            arr[i] = scan.nextInt();
        }

        int sum = 0;
        for (int i = 0; i < 10; i++){
            sum += arr[i];
        }
        System.out.printf("Average: %X\n", sum / 10);


        printArray();
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < i; j++) {
                System.out.print("*");
            }
            for (int j = 8 - i; j > 0; j--) {
                System.out.print("  ");
            }

            for (int j = 0; j < i; j++) {
                System.out.print("*");
            }
            System.out.println("");
        }
        for (int i = 7; i > 0; i--) {
            for (int j = i; j > 0; j--) {
                System.out.print("*");
            }
            for (int j = 8 - i; j > 0; j--) {
                System.out.print("  ");
            }

            for (int j = i; j > 0; j--) {
                System.out.print("*");
            }
            System.out.println("");
        }
    }

    public static void printArray(){
        int i[] = {1,2,3,4,5};
        int j[] = {100,25,355,45,555};
        String titles[] = {"First ","Second","Third ","Fourth","Fifth "};

        for (int k = 0; k < 46; k++){
            System.out.printf("_");
        }
        System.out.printf("\n");
        for (int k = 0; k < 5; k++){
            System.out.printf("| %s ",titles[k]);
        }
        System.out.printf("|\n");
        for (int k = 0; k < 5; k++){
            System.out.printf("|       %d",i[k]);

        }
        System.out.println("|");
        for (int k = 0; k < 5; k++){

            float temp = (float) j[k];
            System.out.printf("| %7.0f",temp);

        }
        System.out.println("|");

        for (int k = 0; k < 46; k++){
            System.out.printf("_");
        }
        System.out.println("");
    }
}