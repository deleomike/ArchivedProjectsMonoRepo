package com.company;

import java.util.*;

public class Main {

    public static void main(String[] args) {
	// write your code here
        Editor edit = new Editor();

        System.out.println("HOWTO:\nType ##OPTION## then hit enter to execute an option. You must use the resume operations option\nto continue after using an option\nOPTIONS:\n1. Replace\n2. Delete All Text\n3. Resume Editing\n4. Save To a File\n5. Load a File\n6. Quit");

        Scanner scan = new Scanner(System.in);
        while(true){
            String input;
            //scan.nextLine();
            input = scan.nextLine();

            if (input.matches("##[1-6]##")) {
                int choice = input.charAt(2) - 48;
                if (choice == 1){ edit.Replace();}
                else if (choice == 2){ edit.DeleteAll();}
                else if (choice == 3){ edit.ResumeEditing();}
                else if (choice == 4){ edit.Save();}
                else if (choice == 5){ edit.Load();}
                else { edit.Quit();}
            } else{
                edit.Append(input + "\n");
            }
        }

    }
}
