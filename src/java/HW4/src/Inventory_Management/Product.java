package Inventory_Management;

import CheckOrder.InvalidOrder;

abstract public class Product {
    private String Name;
    private double Price;
    private int Quantity;

    public Product(){
        Name = "";
        Price = 0;
        Quantity = 0;
    }

    public Product(String Name, double Price, int Quantity){
        this.Name = Name;
        this.Price = Price;
        this.Quantity = Quantity;
    }

    public double getPrice(){ return Price; }

    public String getName(){ return Name; }

    public void setName(String New_Name){ this.Name = New_Name; }

    public void setPrice(double New_Price){ this.Price = New_Price; }

    public void Increment_Quantity(int number){ Quantity += number; }

    public void Decrement_Quantity(int number) throws InvalidOrder {
        if (Quantity - number < 0){
            throw new InvalidOrder(Name,Quantity,number);
        }
        else {
            Quantity -= number;
        }
    }



    @Override
    public String toString(){
        String res = "Product Name: " + Name + ", Quantity: " + Quantity;
        return res;
    }

}
