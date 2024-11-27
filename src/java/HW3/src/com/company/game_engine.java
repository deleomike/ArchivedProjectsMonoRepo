package com.company;

import java.util.*;

public class game_engine {

    public static void main(String[] args) {
        //Skill - fighters
        ////////////////////////////////////
        Skill Block = new Skill("Block");
        Skill Stab = new Skill("Stab");
        Skill Parry = new Skill("Parry");
        Skill Esponiage = new Skill("Espionage");
        //Skill - Farmers
        //////////
        Skill Patience = new Skill("Patience");
        Skill Endurance = new Skill("Endurance");
        Skill Intellect = new Skill("Intellect");
        Skill Crafting = new Skill("Crafting");
        Skill Healing = new Skill("Healing");
        Skill Yeet = new Skill("Yeet");
        //Skill - Builders
        //////////
        Skill SteadyHand = new Skill("SteadyHand");
        Skill Programming = new Skill("Programming");
        Skill Strength = new Skill("Strength");
        Skill Dexterity = new Skill("Dexterity");
        Skill SpySpotter = new Skill("SpySpotter");
        ////////////////////////////////////


        //Tools
        ////////////////////////////////////
        Tools Hammer = new Tools("Hammer",0,0);
        Tools Sword = new Tools("Sword",0,0);
        Tools Knife = new Tools("Knife",0,0);
        Tools Gun = new Tools("Gun",0,0);
        Tools Shield = new Tools("Shield",0,0);
        Tools Scythe = new Tools("Scythe",0,0);
        Tools Bible = new Tools("Bible",0,0);


        Skill [] set1 = {Patience,SpySpotter,Endurance,Yeet,Healing};
        Skill [] set2 = {SteadyHand,Programming,Dexterity};

        Fighter [] UgandaKnuckles = new Fighter[3];
        {
            UgandaKnuckles[0] = new Fighter(Block,Shield,"Knuckles Jr.",10,0,10);
            UgandaKnuckles[1] = new Fighter(Stab,Sword,"Knuckles Col.", 20,10,10);
            UgandaKnuckles[2] = new Fighter(Esponiage,Knife,"Commander Knuckles",30,20,-5);
        }

        Builder BigChungus = new Builder(set2,Hammer,"Big Chungus",2000,0,0);
        Farmer DrPhil = new Farmer(set1,Bible,"Dr. Phil",65,0,0);

        Wagon townWagon = new Wagon("Town Wagon",50,50);
        Car Ford = new Car("Ford Sedan",0,-10);
        Truck AssaultTruck = new Truck("Assault Truck",-100,-100);
        Airplane bomber = new Airplane("Bomber",500,500);


        Shape[] objects =  {UgandaKnuckles[0],UgandaKnuckles[1],UgandaKnuckles[2],BigChungus,DrPhil,townWagon,Ford,AssaultTruck,bomber};
        Drive_game(objects);
    }

    static void Drive_game(Shape[] s){
        Scanner scan = new Scanner(System.in);
        while(true){
            //Draw each object, and ask if it should be moved
            for (int i = 0; i <s.length; i++){
                System.out.println("=======================================");
                s[i].Draw();
                System.out.print("\nDo you want to Move?\n0: No\n1: Move Forward\n2: Move Backwards\n3: Move Right\n4. Move Left\n->");
                int choice = scan.nextInt();
                if (choice > 0 && choice < 5){
                    System.out.println("Choose Speed:\n1: Slow\n2: Average\n3: Fast\n->");
                    //Correct the speed input
                    int speed = scan.nextInt();
                    if (speed < 1 || speed > 3){ speed = 3; }

                    if (choice == 1){ s[i].Move_Forward(speed); }
                    if (choice == 2){ s[i].Move_Backward(speed); }
                    if (choice == 3){ s[i].Move_Right(speed); }
                    if (choice == 4){ s[i].Move_Left(speed); }
                }

                //Increment location of each object
                s[i].Increment_Location();
            }


            //Ask to continue or not
            System.out.println("Would you like to continue?\n0: No\n1: Yes");
            if (scan.nextInt() == 0){
                break;
            }
        }

    }
}

interface Movable{
    void Move_Forward(int factor);
    void Move_Backward(int factor);
    void Move_Right(int factor);
    void Move_Left(int factor);
}

interface Drawable{
    void Draw();
}


abstract class Shape implements Movable, Drawable{
    int x,y;

    Shape(){
        x = 0;
        y = 0;
    }

    Shape(int x, int y){
        this.x = x;
        this.y = y;
    }



    void Increment_Location(){
        x++;
    }

}


class Skill{
    private String s;

    Skill(){
        s = "NULL";
    }

    Skill(String s){
        this.s = s;
    }

    void setSkill(String s){this.s = s;}

    @Override
    public String toString(){ return this.s;}
}


class Tools extends Shape{
    private String s;

    Tools(){
        super();
        s = "NULL";
    }

    Tools(String s, int x, int y){
        super(x,y);
        this.s = s;
    }

    void setTool(String s){this.s = s;}

    void addTool(String s){this.s += " " + s;}

    @Override
    public String toString(){ return this.s;}

    public void Move_Forward(int factor){ }
    public void Move_Backward(int factor){ }
    public void Move_Right(int factor){ }
    public void Move_Left(int factor){ }

    public void Draw(){ System.out.print(this.toString()); }

}




