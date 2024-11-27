package Inventory_Management;

import CheckOrder.*;

import java.util.*;

public class Inventory_System {
    private ArrayList<Product> products;

    public Inventory_System(){
        products = new ArrayList();
    }

    public Inventory_System(ArrayList<Product> products){
        this.products = products;
    }

    public void addProduct(Product p){ products.add(p);}
    public void removeProduct(Product p){ products.remove(p); }

    public void Purchase_Product(String product, int quantity) throws ProductNotFound,InvalidOrder{
        for(int i = 0; i < products.size(); i++){
            if (products.get(i).getName().equals(product)){
                products.get(i).Decrement_Quantity(quantity); //InvalidOrder is thrown here if the quantity is less than 0
                return;
            }
        }
        throw new ProductNotFound(product);
    }

    public void Return_Product(String product, int quantity) throws ProductNotFound{
        for(int i = 0; i < products.size(); i++){
            if (products.get(i).getName().equals(product)){
                products.get(i).Increment_Quantity(quantity);
                return;
            }
        }
        //This will also throw an exception in case the product doesnt exist
        throw new ProductNotFound(product);
    }

    @Override
    public String toString(){
        StringBuilder res = new StringBuilder();
        for (int i = 0; i < products.size(); i++){
            res.append(products.get(i).toString() + "\n");
        }
        return res.toString();
    }
}
