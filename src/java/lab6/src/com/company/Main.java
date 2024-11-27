package com.company;

import java.util.*;

public class Main {

    public static void main(String[] args) {
	// write your code here
        HourlyEmployee P1 = new HourlyEmployee(20,20,"Mike","Monday",0,0);
        HourlyEmployee O1 = new HourlyEmployee(5,10,"David","Tuesday",911,412);

        SalariedEmployee P2 = new SalariedEmployee(700000,"Ahmed Sammoud","Sunday",311,102);
        SalariedEmployee O2 = new SalariedEmployee(20000,"Abdallah","Sunday",465,21);

        CommissionedEmployee P3 = new CommissionedEmployee(20,1,"Mrs. Ford","Saturday",901,111);
        CommissionedEmployee O3 = new CommissionedEmployee(5,2,"Kyle","Monday",913,32);

        BasePlusCommissionedEmployee P4 = new BasePlusCommissionedEmployee(50000,100,34,"Dominic","Thursday",12,21);
        BasePlusCommissionedEmployee O4 = new BasePlusCommissionedEmployee(40000,2000,10,"Ben","Friday",121,35);


        Team PennState = new Team();
        Team OhioState = new Team();

        PennState.addTeamMember(P1);
        PennState.addTeamMember(P2);
        PennState.addTeamMember(P3);
        PennState.addTeamMember(P4);

        OhioState.addTeamMember(O1);
        OhioState.addTeamMember(O2);
        OhioState.addTeamMember(O3);
        OhioState.addTeamMember(O4);

        System.out.println(PennState.Team_Members());
        System.out.println(OhioState.Team_Members());
    }
}

class Team{
    String TeamName;
    ArrayList<HourlyEmployee> Hourly;
    ArrayList<SalariedEmployee> Salary;
    ArrayList<CommissionedEmployee> Commissioned;
    ArrayList<BasePlusCommissionedEmployee> BasePlus;

    Team(){
        Hourly = new ArrayList();
        Salary = new ArrayList();
        Commissioned = new ArrayList();
        BasePlus = new ArrayList();
        TeamName = "";
    }

    public void addTeamMember(HourlyEmployee E){ Hourly.add(E); }
    public void addTeamMember(SalariedEmployee E){ Salary.add(E); }
    public void addTeamMember(CommissionedEmployee E){ Commissioned.add(E); }
    public void addTeamMember(BasePlusCommissionedEmployee E){ BasePlus.add(E); }

    public void removeTeamMember(HourlyEmployee E){ Hourly.remove(E); }
    public void removeTeamMember(SalariedEmployee E){ Salary.remove(E); }
    public void removeTeamMember(CommissionedEmployee E){ Commissioned.remove(E); }
    public void removeTeamMember(BasePlusCommissionedEmployee E){ BasePlus.remove(E); }

    public String Team_Members(){
        StringBuilder s = new StringBuilder();
        for (HourlyEmployee iter : Hourly){
            s.append(iter.Name + ", ");
        }
        for (SalariedEmployee iter : Salary){
            s.append(iter.Name + ", ");
        }
        for (CommissionedEmployee iter : Commissioned){
            s.append(iter.Name + ", ");
        }
        for (BasePlusCommissionedEmployee iter : BasePlus){
            s.append(iter.Name + ", ");
        }
        s.delete(s.length()-2,s.length()-1);
        return s.toString();
    }

}

abstract class Employee{
    String Name;
    int ID;
    String StartDate;
    int DepartmentCode;

    Employee(){
        Name = "";
        ID = 0;
        StartDate = "";
        DepartmentCode = 0;
    }

    Employee(String Name, int ID, String StartDate, int DepartmentCode){
        this.Name = Name;
        this.ID = ID;
        this.StartDate = StartDate;
        this.DepartmentCode = DepartmentCode;
    }

    @Override
    abstract public String toString();

    abstract public double wages();



}

class HourlyEmployee extends Employee{
    double payPerHour;
    int numHours;

    HourlyEmployee(double pay, int hours, String Name, String StartDate, int DepartmentCode, int ID){
        super(Name,ID,StartDate,DepartmentCode);
        this.payPerHour = pay;
        this.numHours = hours;
    }


    public double wages(){
        return (payPerHour*numHours);
    }

    public String toString(){
        return Name + " (ID: " + ID + ") Works in Department " + DepartmentCode + ", started on " + StartDate + " and earns $"+ String.valueOf(wages()) + " per week";

    }
}

class SalariedEmployee extends Employee{
    double salary; //monthly

    SalariedEmployee(double salary, String Name, String StartDate, int DepartmentCode, int ID){
        super(Name,ID,StartDate,DepartmentCode);
        this.salary = salary;
    }

    public double wages(){
        return salary;
    }

    public String toString(){
        return Name + " (ID: " + ID + ") Works in Department " + DepartmentCode + ", started on " + StartDate + " and earns $" + String.valueOf(wages()) + "Per Month";
    }

}

class CommissionedEmployee extends Employee{
    double CommissionPerSale;
    int numSales;

    CommissionedEmployee(double CommissionPerSale, int numSales, String Name, String StartDate, int ID, int DepartmentCode){
        super(Name,ID,StartDate,DepartmentCode);
        this.numSales = numSales;
        this.CommissionPerSale = CommissionPerSale;
    }

    public double wages(){
        return CommissionPerSale * numSales;
    }

    public String toString(){
        return Name + " (ID: " + ID + ") Works in Department " + DepartmentCode + ", started on " + StartDate + " and earns $" + String.valueOf(wages());
    }
}

class BasePlusCommissionedEmployee extends CommissionedEmployee{
    double BasePay;

    BasePlusCommissionedEmployee(double BasePay, double CommissionPerSale, int numSales, String Name, String StartDate, int ID, int DepartmentCode){
        super(CommissionPerSale,numSales,Name,StartDate,ID,DepartmentCode);
        this.BasePay = BasePay;
    }

    @Override
    public double wages(){
        return BasePay + super.wages();
    }

    public String toString(){
        return Name + " (ID: " + ID + ") Works in Department " + DepartmentCode + ", started on " + StartDate + " and earns $" + String.valueOf(wages());
    }
}

