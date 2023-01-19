package com.company;

import java.util.*;

public class Main {
    public static void main(String[] args) {
	// write your code here




    }

}

class student{

    int id;
    String name;
    double GPA;

}

class team{
    static String teamName;
    String SportType;
    int numPlayers;
    ArrayList<student> players;

    team (){}


    team(String name, String type,ArrayList<student> players){
        this.teamName = name;
        this.SportType = type;
        this.numPlayers = players.size();

        this.players = new ArrayList();
        this.players = players;
    }


    void listPlayers(){
        for (int i = 0; i < players.size(); i++){
            System.out.println(players.get(i).name);
        }
    }
}
