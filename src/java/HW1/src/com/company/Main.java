package com.company;

import java.util.*;

public class Main {

    public static void main(String[] args) {

        int choice=0;







        // Prompt user to input a question number to show the answer

        Scanner scan = new Scanner(System.in);

        // Write code to choose which solution to show
        while(choice != -1){
            System.out.println("Input a question number to view the answer for: 1-4 or any other number to show all\n-1 to stop\n1. Stars\n2. Occurrences in array\n3. Square and sort array\n4. Grouping evens and odds");
            choice = scan.nextInt();

            switch (choice){
                case 1:
                    Q1();
                    break;

                case 2:
                    Q2();
                    break;

                case 3:
                    Q3();
                    break;

                case 4:
                    Q4();
                    break;

                default:
                    //Show all answers
                    Q1();
                    Q2();
                    Q3();
                    Q4();



            }


            // Prompt user to input a question number to answer
        }
    }

    static void Q1(){
        //Enter your Solution to first question
        int max = 8;
        for (int i = 0; i < max; i++){
            for(int j = i; j <max-1; j++){
                System.out.printf(" ");
            }
            for (int j = 1; j < i; j++){
                System.out.printf("*");
            }
            for (int j = 1; j < i; j++){
                System.out.printf("*");
            }
            if(i != 0){
                System.out.printf("*");
            }

            System.out.println("");
        }

        System.out.println("");

        max = 6;
        for (int i = 0; i < max; i++){
            for(int j = i; j <max-1; j++){
                System.out.printf(" ");
            }
            for (int j = 1; j < i; j++){
                System.out.printf("*");
            }
            for (int j = 1; j < i; j++){
                System.out.printf("*");
            }
            if(i != 0){
                System.out.printf("*");
            }

            System.out.println("");
        }
        for (int i = max-1; i >0; i--){
            for(int j = i-1; j <max-1; j++){
                System.out.printf(" ");
            }
            for (int j = i-1; j > 1; j--){
                System.out.printf("*");
            }
            for (int j = i-1; j > 1; j--){
                System.out.printf("*");
            }
            if(i != 1){
                System.out.printf("*");
            }

            System.out.println("");
        }

    }


    static void Q2(){
        //Solution to second question
        System.out.println("Array Input:");
        ArrayList<Integer> arr = getArray();

        System.out.print("The User Input is:\n{");
        printArray(arr);

        // Define a scanner
        Scanner scan = new Scanner(System.in);

        for (int i = 1; i < arr.size(); i++){
            for(int j = 0; j < arr.size(); j++){
                if (i!=j && arr.get(i) == arr.get(j)){
                    //match!
                    System.out.printf("The repeated number is %d with first occurrence of %d and second occurrence of %d",arr.get(i),j,i);
                    break;
                }
            }
        }
    }


    static void Q3(){
        //Solution to thrid question
        System.out.println("Enter an array in non-decreasing order");
        ArrayList<Integer> arr = getArray();
        printArray(arr);
        for (int i = 0; i < arr.size(); i++){
            int temp = arr.get(i);
            arr.set(i,temp*temp);
        }
        arr = sort(arr);
        printArray(arr);
    }


    static void Q4(){
        //Solution to fourth question
        System.out.println("Enter an array");
        ArrayList<Integer> arr = getArray();
        printArray(arr);
        ArrayList<Integer> even = new ArrayList<>();
        ArrayList<Integer> odd = new ArrayList<>();
        for (int i = 0; i < arr.size(); i++){
            int arrx = arr.get(i).intValue();
            if (arrx%2 == 0){
                even.add(arr.get(i));
            }
            else{
                odd.add(arr.get(i));
            }
        }

        for (int i = 0; i < arr.size(); i++){
            if(even.size() > i){
                arr.set(i,even.get(i));
            }
            else{
                arr.set(i,odd.get(i - even.size()));
            }
        }
        System.out.println("The following array has its evens and odds grouped");
        printArray(arr);
    }

    static ArrayList<Integer> getArray(){
        ArrayList<Integer> arr = new ArrayList<>();
        Scanner s = new Scanner(System.in);
        while(true){
            System.out.println("Enter an int. type -1 to stop");
            int x = s.nextInt();
            if(x == -1){
                break;
            }
            arr.add(x);
        }
        return arr;
    }

    static void printArray(ArrayList<Integer> arr){
        String str = "{";
        for (int i = 0; i < arr.size(); i++){
            str += arr.get(i);
            str += ",";
        }
        if (str.length() == 1){}
        else {
            str = str.substring(0, str.length() - 1);
        }
        str += "}\n";
        System.out.print(str);
        return;
    }

    static ArrayList<Integer> sort(ArrayList<Integer> arr){
        int n = arr.size();

        for (int i = 0; i < n-1; i++)
        {

            int minimum_index = i;
            for (int j = i+1; j < n; j++)
                if (arr.get(j) < arr.get(minimum_index))
                    minimum_index = j;

            // Swap the found minimum element with the first
            // element
            int temp = arr.get(minimum_index);
            arr.set(minimum_index,arr.get(i));
            arr.set(i,temp);
        }
        return arr;
    }
}