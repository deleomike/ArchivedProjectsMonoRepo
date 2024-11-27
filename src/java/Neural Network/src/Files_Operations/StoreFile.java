package Files_Operations;

import java.io.IOException;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Formatter;
import java.util.Scanner;

public class StoreFile {
    Path fileName;
    Formatter f;


    public StoreFile(String fileName) throws Exception {
        this.fileName = Paths.get(fileName);
        try {
            Files.createFile(this.fileName);
        } catch (FileAlreadyExistsException e) {
            System.out.printf("File %s already exists. Overwrite? (y/n) ", fileName);
            Scanner scan = new Scanner(System.in);
            if (scan.nextLine().equals("n")){
                throw new Exception();
            }
            //new input is needed, dont leave yet
        } catch (IOException e) {
            System.out.printf("IO error creating file %s. Error with file name or directory. Input different file name.\n", fileName);
            throw new Exception();
        }

        f = new Formatter(fileName);

    }

    public void WriteToFile(String str) {
        f.format(str);
        f.format(System.lineSeparator());
        f.flush();
    }
}
