package com.company;

import java.util.*;

public class Main {

    public static void main(String[] args) {
	// write your code here

        System.out.println("##################################################");
        int arr1[] = {5,1,1,9,2,6,10};

        System.out.println("Hello, let us play a game type a number and I will tell you if it is in my array. Type -1 to stop");
        int input = 0;
        Scanner scan = new Scanner(System.in);
        while (input != -1){
            System.out.printf("-> ");
            input = scan.nextInt();
            if (input == -1){}
            else if (find(input,arr1)){
                System.out.printf("Your number %d matches a number in my array\n",input);
            }
            else{
                System.out.printf("Your number %d does not match any numbers in my array\n", input);
            }

        }
        System.out.println("##################################################");


        System.out.println("That was fun! Let's play another. Give me a number and I'll decrement by 5 till 0...come on now!");
        System.out.printf("->");
        input = scan.nextInt();

        for (int i = input; i > 0; i = i - 5){
            if (i < 0){
                i = 0;
            }
            System.out.printf("%d\n", i);
        }
        System.out.printf("0\n");
        System.out.println("##################################################");

        int arr2[] = {10,20,30,40,50};
        {
            int temp = arr2[0];
            arr2[0] = arr2[4];
            arr2[4] = temp;

            temp = arr2[1];
            arr2[1] = arr2[3];
            arr2[3] = temp;
        }
        for (int i = 0; i < 5; i++){
            System.out.printf("%d,",arr2[i]);
        }

        System.out.println("\n##################################################");

        System.out.println("{10,20,30,40,10,20,50}");
        int arr[] = {10,20,30,40,10,20,50};
        int duplicates[] = {0,0,0,0,0,0,0,0};
        int dupCount = 0;
        //check for duplicates
        for (int i = 0; i < 7; i++){
            for (int j = 0; j < 7; j++){
                if ( i != j){
                    if (arr[i] == arr[j] && !find(arr[i],duplicates)){
                        System.out.printf("%d is a duplicate\n",arr[i]);
                        duplicates[dupCount] = arr[i];
                        dupCount++;
                        //save duplicate
                    }
                }
            }
        }
        System.out.println("##################################################");
    }

    static boolean find(int num, int arr[]){

        for (int i = 0; i < 7; i++){
            if (arr[i] == num){
                return true;
            }
        }

        return false;

    }
}
