package com.company;

class Character extends Shape{
    String Name;
    int age;
    int stepsize;

    Character(){
        super();
        Name = "";
        age = 0;
        stepsize = 1;
    }

    Character(String Name, int age, int stepsize, int x, int y){
        super(x,y);
        this.Name = Name;
        this.age = age;
        this.stepsize = stepsize;
    }

    public void Move_Forward(int factor){ y += factor*stepsize; }
    public void Move_Backward(int factor){ y -= factor*stepsize; }
    public void Move_Right(int factor){ x += factor*stepsize; }
    public void Move_Left(int factor){ x -= factor*stepsize; }

    public void Draw(){ System.out.print(this.toString()); }


}

class Fighter extends Character{
    Skill s;
    Tools t;
    Fighter(){
        super();
        s = new Skill();
        t = new Tools();
        stepsize = 5;
    }

    Fighter(Skill s, Tools t, String Name, int age, int x, int y){
        super(Name,age,5,x,y);
        this.s = s;
        this.t = t;
    }

    @Override
    public String toString(){
        String res = "Fighter " + Name + " is " + age + " years old. He/she is at position (" + x + "," + y + ")\nSkill: " + s.toString() + "\nTool: "+t.toString() + "\n";
        return res;
    }

}

class Farmer extends Character{
    Skill [] s = new Skill[5];
    Tools t;

    Farmer(){
        super();
        for (int i = 0; i < 5; i++){
            s[i] = new Skill();
        }
        t = new Tools();
        stepsize = 1;
    }
    Farmer(Skill [] s, Tools t, String Name, int age, int x, int y){
        super(Name,age,1,x,y);
        //if 5 skills were passed as an argument
        if (s.length == 5){ this.s = s; }
        //if 5 skills were not passed, and they are less or more than 5
        if (s.length < 5 || s.length > 5) {
            for (int i = 0; i < 5; i++){
                //skills length is less than 5
                if (i > s.length){
                    this.s[i] = new Skill();
                }
                //continue to get the skills
                else{
                    this.s[i] = s[i];
                }
            }
        }

        this.t = t;

    }

    @Override
    public String toString(){
        String skills = s[0].toString() + ", " + s[1].toString() + ", " + s[2].toString() + ", " + s[3].toString() + ", " + s[4].toString();
        String res = "Farmer " + Name + " is " + age + " years old. He/she is at position (" + x + "," + y + ")\nSkills: " + skills + "\nTool: "+t.toString() + "\n";
        return res;
    }
}

class Builder extends Character{
    Skill [] s = new Skill[3];
    Tools t;

    Builder(){
        super();
        for(int i = 0; i < 3; i++){
            s[i] = new Skill();
        }
        t = new Tools();

        stepsize = 3;
    }

    Builder(Skill [] s, Tools t, String Name, int age, int x, int y){
        super(Name,age,3,x,y);
        //if 3 skills were passed as an argument
        if (s.length == 3){ this.s = s; }
        //if 3 skills were not passed, and they are less or more than 3
        if (s.length < 3 || s.length > 3) {
            for (int i = 0; i < 3; i++){
                //skills length is less than 5
                if (i > s.length){
                    this.s[i] = new Skill();
                }
                //continue to get the skills
                else{
                    this.s[i] = s[i];
                }
            }
        }

        this.t = t;
    }

    @Override
    public String toString(){
        String skills = s[0].toString() + ", " + s[1].toString() + ", " + s[2].toString();
        String res = "Builder " + Name + " is " + age + " years old. He/she is at position (" + x + "," + y + ")\nSkills: " + skills + "\nTool: "+t.toString() + "\n";
        return res;
    }
}