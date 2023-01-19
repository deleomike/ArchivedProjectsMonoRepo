package com.company;

import Files_Operations.*;

import java.nio.file.Path;
import java.util.*;

import java.util.Formatter;
import java.nio.file.Files;

public class Editor {

    StringBuilder sb;
    Boolean resumed;

    Editor(){
        sb = new StringBuilder();
        resumed = true;
    }

    Editor(String text){
        sb = new StringBuilder(text);
        resumed = true;
    }

    public void Append(String text){
        if (resumed){
            sb.append(text);
        } else{
            System.out.println("Editor needs to be resumed");
        }

    }

    public void Replace(){
        resumed = false;
        String find,replace;

        String text = sb.toString();

        Scanner scan = new Scanner(System.in);
        System.out.print("Word to Replace: ");
        find = scan.nextLine();

        if (!text.contains(find)){return;} //the word to find doesnt exist, return

        System.out.print("Word to Replace with: ");
        replace = scan.nextLine();

        sb.replace(0,sb.length(),text.replace(find,replace));


    }

    public void DeleteAll(){
        sb.delete(0,sb.length());
        resumed = false;
    }

    public void ResumeEditing(){
        resumed = true;
    }

    public void Save(){
        String file;
        Scanner scan = new Scanner(System.in);
        StoreFile store;
        //continue till acceptable input
        while(true){
            System.out.print("Save to what file?: ");
            file = scan.nextLine();

            try{
                store = new StoreFile(file);
                //try to get the file

                break;
            } catch(Exception e){

            }

        }

        store.WriteToFile(sb.toString());

        store.close();

        System.out.println("Sucessfully saved");
        resumed = false;


    }

    public void Load(){
        String file;
        Scanner scan = new Scanner(System.in);
        ReadFile read;

        while(true){
            System.out.print("Read from what file?: ");
            file = scan.nextLine();

            try{
                read = new ReadFile(file);
                //try to get the file

                break;
            } catch(Exception e){

            }

        }

        read.Read();
        sb = new StringBuilder(read.toString());

        resumed = false;
    }

    public void Quit(){
        System.exit(0);
    }

}
