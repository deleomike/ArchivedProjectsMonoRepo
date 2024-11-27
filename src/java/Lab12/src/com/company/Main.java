package com.company;

import java.io.*;
import java.util.*;


public class Main {

    static ArrayList<Items> items = new ArrayList();

    public static void main(String[] args) {

        loadItems();
        printAllItems();
        Scanner scan = new Scanner(System.in);
        while(true){
            printDivider();
            System.out.print("Choose an action:\n1. Add item\n2. Remove Item\n3. Mark Item as Completed\n4. Print All Items\n5. Load Items\n6. Quit and Save\n->");
            int choice =scan.nextInt();
            printDivider();
            if (choice == 1){
                //Add item
                System.out.print("Enter a phrase for your item: ");
                scan.nextLine();
                String input = scan.nextLine();
                addItem(input);
            }
            else if (choice == 2){
                //Remove Item
                printAllItems();
                System.out.print("Choose an item # to delete: ");
                int index = scan.nextInt();
                removeItem(index);
            }
            else if (choice == 3){
                //Mark as completed
                printAllItems();
                System.out.print("Choose an item # to mark as completed: ");
                int index = scan.nextInt();
                markAsCompleted(index);
            }
            else if (choice == 4){
                //Print all items
                printAllItems();
            }
            else if (choice == 5){
                loadItems();
            }
            else if (choice == 6){
                quitSave();
                break;
            }
        }





    }

    static void addItem(String it){
        Items item = new Items(it);
        items.add(item);
    }
    static void removeItem(int index) { items.remove(index); }
    static void markAsCompleted(int index) {items.get(index).markCompleted();}
    static void printAllItems(){
        for (int i = 0; i < items.size(); i++){
            System.out.print(i + ". " + items.get(i).toString());
        }
    }

    static void printDivider(){ System.out.println("=========================================="); }

    static void loadItems(){
        //LOAD DATA
        try (ObjectInputStream obj = new ObjectInputStream(new FileInputStream("data"))) {
            while(true) {
                try {
                    Items it = ((Items) obj.readObject());
                    if (it == null){
                        break;
                    } else{
                        items.add(it);
                    }

                } catch (ClassNotFoundException e) {
                    System.out.println("Error reading binary file");
                }
            }
        }catch(FileNotFoundException e){

        }catch(IOException e){

        }
    }

    static void quitSave(){
        try(ObjectOutputStream obj = new ObjectOutputStream(new FileOutputStream("data"))){
            for(int i = 0; i < items.size(); i++){
                obj.writeObject(items.get(i));
            }
            obj.flush();
        }catch(FileNotFoundException e){
            System.out.println("File does not exist");
        }catch(IOException e){

        }
    }
}
