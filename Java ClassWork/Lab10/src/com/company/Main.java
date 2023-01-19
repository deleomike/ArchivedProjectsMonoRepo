package com.company;

import java.nio.file.FileAlreadyExistsException;
import java.util.*;
import Files_Operations.*;

public class Main {

    public static void main(String[] args) {
	Scanner scan = new Scanner(System.in);
	while(true){
	    System.out.print("Enter 1 for part 1, and 2 for part 2. any other number to exit.");
	    int choice = scan.nextInt();
	    if(choice == 1) {

	    	StoreFile file = null;

	    	boolean breakout = false;
			while(!breakout) {
				breakout = true;
				try {
					System.out.print("Create File: What is the file name? ");
					scan.nextLine(); //next line character
					String filename = scan.nextLine();
					file = new StoreFile(filename);
				} catch(Exception e){
					breakout = false;
				}
			}

			while(true){
				System.out.print("Enter a string to be sent to the file. This will be one line. Type 'end' to stop");
				String input = scan.nextLine();
				if (input.equals("end")){
					break;
				}
				file.WriteToFile(input);
			}


        }
	    else if(choice == 2){
			ReadFile file = null;

			boolean breakout = false;
			while(!breakout){
				breakout = true;
				try{
					System.out.print("Enter a file name to read from: ");
					scan.nextLine();
					String input = scan.nextLine();
					file = new ReadFile(input);
				} catch(Exception e){
					breakout = false;
					//do not leave yet
				}
			}

			System.out.printf("Number of Words: %d\n",file.numWords());
			System.out.printf("Number of Lines: %d\n",file.numLines());
        }
	    else{
			break;
        }
	}
    }
}
