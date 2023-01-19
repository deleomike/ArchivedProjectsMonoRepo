package Files_Operations;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.*;
import java.util.*;

public class ReadFile {
    Path fileName;
    Scanner scan;

    String file_buffer;

    public ReadFile(String fileName) throws Exception{
        this.fileName = Paths.get(fileName);
        try {
            scan = new Scanner(this.fileName);
        } catch(FileNotFoundException e){
            System.out.printf("File %s not found. Choose different file",fileName);
            throw new Exception();

        } catch(IOException e){
            System.out.printf("IO Exception. Choose different file.",fileName);
            throw new Exception();
        }

    }



    public int numLines(){
        if (!scan.hasNext()){
            try {
                scan = new Scanner(this.fileName);
            } catch(IOException e){
                System.out.println("IOException. Something Has gone terribly wrong in this function: numLines.");
                return 0;
            }
        }

        int lines = 0;
        while(scan.hasNext()){
            scan.nextLine();
            lines++;
        }
        return lines;
    }

    public int numWords(){
        if (!scan.hasNext()){
            try{
                scan = new Scanner(this.fileName);
            } catch(IOException e){
                System.out.println("IOException. Something has gone terribly wrong in this function: numWords");
                return 0;
            }
        }
        int words = 0;
        while(scan.hasNext()){
            scan.next();
            words++;
        }

        return words;
    }
}
