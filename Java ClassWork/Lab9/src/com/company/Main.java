package com.company;

import validation.*;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        CheckValidInput c = new CheckValidInput();
        ModifiedCheck m = new ModifiedCheck();

        Scanner scan = new Scanner(System.in);
        System.out.println("CheckValidInput:");
        System.out.print("Input only Letters: ");
        boolean input = c.Check_OnlyLetters(scan.nextLine());
        System.out.println(input);

        System.out.print("Input only Numbers: ");
        input = c.Check_OnlyNumber(scan.nextLine());
        System.out.println(input);

        System.out.print("Input a Date: ");
        input = c.Check_DateFormat(scan.nextLine());
        System.out.println(input);

        System.out.print("Input an email: ");
        input = c.Check_EmailFormat(scan.nextLine());
        System.out.println(input);

        System.out.println("\nModifiedCheck: ");
        System.out.print("Input only Letters: ");
        input = m.Check_OnlyLetters(scan.nextLine());
        System.out.println();
        System.out.println(input);

        System.out.print("Input only Numbers: ");
        input = m.Check_OnlyNumber(scan.nextLine());
        System.out.println(input);

        System.out.print("Input a Date: ");
        input = m.Check_DateFormat(scan.nextLine());
        System.out.println(input);

        System.out.print("Input an email: ");
        input = m.Check_EmailFormat(scan.nextLine());
        System.out.println(input);



        /* UNCOMMENT THESE IF YOU WANT A FAST CHECK*/

        //System.out.println(c.Check_EmailFormat("mad6068@psu.edu"));
        //System.out.println(c.Check_EmailFormat("m@psu.ed"));
        //System.out.println(c.Check_EmailFormat("mad6068@p.edu"));

//        System.out.println(c.Check_DateFormat("01/2/1990"));
//        System.out.println(c.Check_DateFormat("1/02/1990"));
//        System.out.println(c.Check_DateFormat("01/02/1990"));
//        System.out.println(c.Check_DateFormat("01/02/990"));
//        System.out.println(c.Check_DateFormat("1/2/1990"));

//        System.out.println(c.Check_OnlyNumber("013214423"));
//        System.out.println(c.Check_OnlyLetters("fHh"));



//        System.out.println(m.Check_DateFormat("01 2 1990"));
//        System.out.println(m.Check_OnlyNumber("hello1"));
//        System.out.println(m.Check_DateFormat("01"));
//        System.out.println(m.Check_DateFormat("h"));
//        System.out.println(m.Check_DateFormat("0"));
//        System.out.println(m.Check_DateFormat("hwudwdw wweei 131 13ndb 31ndq 321"));



	// write your code here
    }
}
