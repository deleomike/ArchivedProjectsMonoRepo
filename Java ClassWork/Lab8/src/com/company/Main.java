package com.company;

import com.sun.tools.corba.se.idl.constExpr.Not;

import java.util.*;

public class Main {

    public static void main(String[] args) {

        Scanner scan = new Scanner(System.in);
        System.out.print("Enter initial bank balance: ");
        double balance = scan.nextDouble();
        System.out.print("Enter withdraw amount: ");
        double withdraw = scan.nextDouble();
        System.out.print("Enter period to calculate yearly returns: ");
        double period = scan.nextDouble();

        BankAccount b = new BankAccount(balance);
        try{
            System.out.printf("\nNew balance: %f\n",b.Withdraw(withdraw));
        } catch(NotEnoughBalance e){
            System.out.printf("\nNot enough funds. Account overdrawn by: %f\n",e.amount);
        }

        System.out.printf("Dividend: %f",b.Dividend(period));
    }
}


class BankAccount{
    double Balance;
    double Dividend;

    BankAccount(double Balance){
        this.Balance = Balance;
        this.Dividend = 0;
    }

    public void Deposit(double amount){ Balance += amount;}

    public double Withdraw(double amount) throws NotEnoughBalance{
        if (Balance - amount < 0){
            throw new NotEnoughBalance(Balance-amount,"Balance is not enough");
        }
        else{
            return Balance - amount;
        }
    }

    public double Dividend(double period){
        double dividend = Balance/period;
        try{
            if (Double.isFinite(dividend ) && dividend != 0){
                Dividend = dividend;
                return dividend;
            }
            else{
                throw new ArithmeticException();
            }

        } catch(ArithmeticException e){
            System.out.println("Arithmetic Exception in Dividend()");
            e.printStackTrace();
            Dividend = 0;
            return 0;
        }
    }

}

class NotEnoughBalance extends Throwable{
    double amount;

    NotEnoughBalance(double amount, Throwable cause){
        super(cause);
        this.amount = amount;
    }

    NotEnoughBalance(double amount, String message, Throwable cause){
        super(message,cause);
        this.amount = amount;
    }

    NotEnoughBalance(double amount, String message){
        super(message);
        this.amount = amount;
    }

    NotEnoughBalance(){
        amount = 0;
    }
}