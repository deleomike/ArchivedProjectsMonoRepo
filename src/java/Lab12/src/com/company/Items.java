package com.company;

import java.io.Serializable;

public class Items implements Serializable {
    private String Name;
    private Boolean Completed;

    Items(){
        Name = "";
        Completed = false;
    }

    Items(String Name){
        this.Name = Name;
        Completed = false;
    }

    public void markCompleted(){Completed = true;}

    @Override
    public String toString(){
        String res = Name + " :: Completed: " + Completed + "\n";
        return res;
    }
}
