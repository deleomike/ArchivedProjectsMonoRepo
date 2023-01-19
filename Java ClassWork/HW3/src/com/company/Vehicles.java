package com.company;

public class Vehicles extends Shape{
    int stepsize;
    String Name;

    Vehicles(){
        super();
        Name = "";
        stepsize = 0;
    }

    Vehicles(String Name, int stepsize, int x, int y){
        super(x,y);
        this.Name = Name;
        this.stepsize = stepsize;
    }

    public void Move_Forward(int factor){ y += factor*stepsize; }
    public void Move_Backward(int factor){ y -= factor*stepsize; }
    public void Move_Right(int factor){ x += factor*stepsize; }
    public void Move_Left(int factor){ x -= factor*stepsize; }

    public void Draw(){ System.out.print(this.toString()); }
}

class Wagon extends Vehicles{
    Wagon(){
        super();
        stepsize = 20;
    }
    Wagon(String Name,int x, int y){
        super(Name,20,x,y);
    }
    @Override
    public String toString(){
        return "Wagon - " + Name + " is at position (" + x + "," + y + ")";
    }
}

class Car extends Vehicles{
    Car(){
        super();
        stepsize = 30;
    }
    Car(String Name, int x, int y){
        super(Name, 30,x,y);
    }

    @Override
    public String toString(){
        return "Car - " + Name + " is at position (" + x + "," + y + ")";
    }
}

class Truck extends Vehicles{
    Truck(){
        super();
        stepsize = 30;
    }
    Truck(String Name, int x, int y){
        super(Name, 30,x,y);
    }

    @Override
    public String toString(){
        return "Truck - " + Name + " is at position (" + x + "," + y + ")";
    }
}

class Airplane extends Vehicles{
    Airplane(){
        super();
        stepsize = 100;
    }
    Airplane(String Name, int x, int y){
        super(Name,100,x,y);
    }

    @Override
    public String toString(){
        return "Airplane - " + Name + " is at position (" + x + "," + y + ")";
    }
}