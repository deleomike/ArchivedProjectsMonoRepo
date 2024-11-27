package com.company;

import java.util.*;

public class Main {

    public static void main(String[] args) {
        StringLabSolutions test1 = new StringLabSolutions();
        System.out.println(test1.marsExploration("SOSSOS"));
        System.out.println(test1.marsExploration("TTTSOSSOTSSS"));

        CheckValidInput test2 = new CheckValidInput();

        Scanner scan = new Scanner(System.in);
        EditorClass test3 = new EditorClass();
        int choice = 0;
        while(true){
            System.out.print("1. Replace: Replace a string with another one.\n2. Append: Add more text to the current text.\n   1. Will continue to accept text till user enters 'end'\n3. Delete: Delete all text\n4. Exit: Exit the program\n->");
            choice = scan.nextInt();
            if (choice == 1){
                test3.Replace_text();
            }
            else if (choice == 2){
                test3.Append_text();
            }
            else if (choice == 3){
                test3.Delete();
            }
            else if(choice == 4){
                System.exit(1);
            }
            else{}
        }

    }

}

class StringLabSolutions{
    int marsExploration(String s){
        if (s.matches("SOS*")){
            return 0;
        }
        int count = 0;
        String matcher = new String("SOS");
        for (int i = 0; i < s.length(); i = i + 3){
            if (!s.regionMatches(i,"SOS",0,3)){
                count += marsRover(s,matcher,i);
            }
        }

        return count;
    }

    int marsRover(String s, String matcher, int start){
        int count = 0;
        for (int i = start; i < start+3; i++){
            if (s.charAt(i) != matcher.charAt(i%3)) {
                count++;
            }
        }
        return count;
    }
}

class EditorClass{
    StringBuilder sb;

    EditorClass(){
        sb = new StringBuilder();
    }

    void Replace_text(){
        String searchTerm, replacement;
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter String to search for: ");
        searchTerm = scan.nextLine();

        System.out.print("Enter String to replace with: ");
        replacement = scan.nextLine();

        String copy = sb.toString();
        copy.replaceFirst(searchTerm,replacement);
        Delete();
        sb.append(copy);
    }
    void Append_text(){
        System.out.println("Begin Typing. Type 'end' to stop");
        Scanner scan = new Scanner(System.in);


        while(true){
            String s = new String(scan.nextLine());
            if (s.equals("end")){
                return;
            }
            sb.append(s);
        }
    }
    void Delete(){
        sb.delete(0,sb.length());
        return;
    }
}

class CheckValidInput{
    boolean Check_FirstName(String name){
        return name.matches("[A-Za-z]*");
    }
    boolean Check_LastName(String name){
        return name.matches("[A-Za-z'-]*");
    }
    boolean Check_Email(String email){
        return email.matches("[A-Za-z]*@[A-Za-z]*.\\w{3}");
    }
    boolean Check_Date(String date){
        return date.matches("\\d{2}-\\d{2}-\\d{4}");
    }
}
