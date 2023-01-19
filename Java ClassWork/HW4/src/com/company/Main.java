package com.company;

import CheckOrder.*;
import Inventory_Management.*;

import java.time.Month;

public class Main {

    static Inventory_System watson;

    public static void main(String[] args) {
	    Phone apple = new Phone(1000);
	    Monitor hp = new Monitor(250);

	    watson = new Inventory_System();
	    handlePurchase(apple,1);

	    watson.addProduct(apple);
	    watson.addProduct(hp);

	    handlePurchase(apple,1);
	    handlePurchase(hp,1);
	    handlePurchase(apple,1);
	    System.out.println("You: Hey Watson, just returning this junk monitor I bought");
	    try{
	        watson.Return_Product(hp.getName(),1);
	        System.out.println("Watson: Approved transaction");
        } catch(ProductNotFound e){
	        System.out.printf("Watson: That %s is not a product here",e.Name);
        }
        System.out.println("======================================");
	    handlePurchase(apple,1);

        watson.removeProduct(apple);
        watson.removeProduct(hp);


	    System.out.println("Watson: *plots world domination*");

        }


    public static void handlePurchase(Product p, int quantity){
        System.out.println("Watson: Welcome to the online IBM gift shop, I am watson. What'll it be?\n" + watson.toString());
        try{
            System.out.println("You: Hello Watson, I'd Like to purchase " + quantity + " " + p.getName());
            watson.Purchase_Product(p.getName(),quantity);
            System.out.println("Watson: Here you go! That will be $" + p.getPrice() * quantity);
        } catch(ProductNotFound e){
            System.out.printf("Watson: Go Away. We dont have %s\n",e.Name);
            System.out.printf("Watson: This is what we have: %s\n",watson.toString());
        } catch(InvalidOrder e){
            System.out.printf("Watson: We don't have enough %s, this is how much we have %d and you asked for %d. smh\n",e.Name,e.QuantityAvail,e.QuantityReq);
            System.out.println("Watson: This is what we have: \n" + watson.toString());
        }
        System.out.println("======================================");
    }


}


class Phone extends Product{

    Phone(){
        super("Phone",0,1);
    }

    Phone(double Price){
        super("Phone",Price,1);
    }
}

class Monitor extends Product{

    Monitor(){
        super("Monitor",0,2);
    }

    Monitor(double Price){
        super("Monitor",Price,2);
    }
}