package com.company;

import java.util.*;

public class Main{

    //Instructions. make coffee enum variable. set it. make a coffeetype variable and pass it the coffee enum variable
    public static void main(String[] args) {
	// write your code here
        ArrayList<coffeeType> c = new ArrayList();
        coffee e = coffee.ESPRESSO;
        coffeeType k = new coffeeType(e);

        c.add(k);
        c.add(k);

        System.out.println(Total_Grounded_Coffee(c));

    }

    static double Total_Grounded_Coffee(ArrayList<coffeeType> x){
        double sum = 0;
        for (int i = 0; i < x.size(); i++){
            sum = sum + x.get(i).CoffeeAmount();
        }

        return sum;
    }
}

class coffeeType{
    coffee cup;

    coffeeType(coffee cup){
        this.cup = cup;
    }


    double CoffeeAmount(){
        return cup.amount;
    }
}

enum coffee{
    ESPRESSO(6),
    RISTRETTO(8),
    CAFELATTE(5);

    double amount;

    coffee(double amount){
        this.amount = amount;
    }
}