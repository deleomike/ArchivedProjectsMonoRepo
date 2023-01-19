package com.company;

import java.util.*;

public class Main {

    public static void main(String[] args) {
	    Move m = new Car("Blue","Michellin",10,"Sedan","Ford",new coordinate(0,0));
        Move m1 = new Car("Red","Michellin",10,"Evantador","Lamborghini",new coordinate(10,-10));
        Move m2 = new Car("White","Michellin",10,"Model X","Tesla",new coordinate(-10,10));

        Draw d = new Humans("Green","Station Rd","01/01/1990","January",new coordinate(0,0));
        Draw d1 = new Humans("Blue","This Rd","02/02/1992","February",new coordinate(0,0));
        Draw d2 = new Humans("Black","That Rd","03/03/1993","March",new coordinate(0,0));

        ArrayList<Move> list1 = new ArrayList();
        list1.add(m);
        list1.add(m1);
        list1.add(m2);

        ArrayList<Draw> list2 = new ArrayList();
        list2.add(d);
        list2.add(d1);
        list2.add(d2);

        for (int i = 0; i < list1.size(); i++){
            list1.get(i).move();
            list1.get(i).move();
        }

        for (int i = 0; i < list2.size(); i++){
            list2.get(i).draw();
        }
    }
}

interface Move {
    void move();
}

interface Draw {
    void draw();
}

abstract class Vehicles implements Draw, Move{
    double acceleration;
    String model;
    String type;

    coordinate c;

    Vehicles(){
        acceleration = 0;
        model = "";
        type = "";
        c = new coordinate(0,0);
    }

    Vehicles(double acc, String model, String type, coordinate c){
        this.acceleration = acc;
        this.model = model;
        this.type = type;
        this.c = c;
    }

    abstract public void Break();
    abstract public void Accelerate();
    @Override
    abstract public void draw();
    @Override
    abstract public void move();

}

abstract class Mammals implements Draw, Move{
    String Birthday;
    String Month_To_Be_Born;

    coordinate c;

    Mammals(){
        Birthday = "";
        Month_To_Be_Born = "";
        c = new coordinate(0,0);
    }

    Mammals(String Birthday, String Month_To_Be_Born,coordinate c){
        this.Birthday = Birthday;
        this.Month_To_Be_Born = Month_To_Be_Born;
        this.c = c;
    }

    @Override
    abstract public void draw();
    @Override
    abstract public void move();
}

class Car extends Vehicles{
    String color;
    String tire_type;

    Car(String color, String tire_type, double acc, String model, String type, coordinate c){
        super(acc,model,type,c);
        this.color = color;
        this.tire_type = tire_type;
    }


    @Override
    public void Break(){
        System.out.println("BREAKING");
    }

    @Override
    public void Accelerate(){
        System.out.println("ACCELERATING");
    }

    @Override
    public void move(){
        Accelerate();
        Random R = new Random();
        Boolean choice = R.nextBoolean();
        if (choice){
            //apply to x direction
            double change = R.nextDouble();
            c.x = c.x + change*acceleration-5;
        }
        else{
            //apply to y direction
            double change = R.nextDouble()%10 - 1;
            c.y = c.y + change*acceleration;
        }
        Break();
    }

    @Override
    public void draw(){
        System.out.printf("The %s car is a %s %s, with %s tires. It is accelerating at %3.2f m/s, and its current position is (%.2f,%.2f) meters.\n",color,model,type,tire_type,acceleration,c.x,c.y);
    }
}

class Humans extends Mammals{
    String eye_color;
    String address;

    Humans(String eye_color, String address, String Birthday, String Month_To_Be_Born, coordinate c){
        super(Birthday,Month_To_Be_Born,c);
        this.eye_color = eye_color;
        this.address = address;
    }

    @Override
    public void move(){
        Random R = new Random();
        Boolean choice = R.nextBoolean();
        if (choice){
            //apply to x
            double change = R.nextDouble()-0.5;
            c.x = c.x + change;
        }
        else{
            //apply to y
            double change = R.nextDouble() -0.5;
            c.y = c.y + change;
        }
    }

    @Override
    public void draw(){
        System.out.printf("The person with %s eyes has an address at %s, with a birthday of %s. Their current position is (%.2f,%.2f) meters.\n",eye_color,address,Birthday,c.x,c.y);
    }
}

class coordinate{
    double x;
    double y;

    coordinate(double x, double y){
        this.x = x;
        this.y = y;
    }
}