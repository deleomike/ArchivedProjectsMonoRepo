package com.company;

import java.util.*;

//can have constructors
enum student_type{
    INTERNATIONAL_STUDENT(9),
    FULL_TIME(6),
    PART_TIME(0);

    int hours;

    student_type(int hours){
        this.hours = hours;
    }
}

class student{
    student_type type_of_student;
    String name;
    int ID;
    double GPA;

    student(){
        this.ID = 0;
        this.GPA = 0;
        this.type_of_student = student_type.PART_TIME;
        name = "";
    }

    student(int id, double gpa, student_type stu, String name){
        this.ID = id;
        this.GPA = gpa;
        this.type_of_student = stu;
        this.name = name;
    }

}

class Course{
    final int MAX_STUDENTS = 10;
    ArrayList<student> roster;

    String name;
    int code;


    Course(int code, String name){
        this.name = name;
        this.code = code;
        roster = new ArrayList<student>();
    }


    void addStudent(student stu){
        if (isFull()){
            System.out.printf("Course %s %d, is full\n",name,code);
        }
        else{
            roster.add(stu);
            System.out.printf("%s has been added to %s %d\n",stu.name,name,code);
        }
    }

    void removeStudent(student stu){
        System.out.printf("%s has been removed from %s %d\n",stu.name,name, code);
        roster.remove(stu);
    }

    student getStudent(int ID){
        student p = new student();
        for (int i = 0; i < roster.size(); i++){
            if (roster.get(i).ID == ID){
                return roster.get(i);
            }
        }
        System.out.printf("Student %d not found in %s %d.\n",ID,name,code);
        return p;
    }

    private boolean isFull(){
        if (roster.size() == 10){
            return true;
        }
        else{
            return false;
        }
    }

}

class Enrollment{
    ArrayList<Course> course_catalog;
    ArrayList<student> student_roster;

    String University;

    Enrollment(){
        this.University = "";
        course_catalog = new ArrayList<Course>();
        student_roster = new ArrayList<student>();
    }

    Enrollment(String name){
        this.University = name;
        course_catalog = new ArrayList<Course>();
        student_roster = new ArrayList<student>();
    }

    void addCourse(String name, int code){
        Course x = new Course(code,name);
        course_catalog.add(x);
        System.out.printf("Course %s %d has been added to %s!\n",name,code,University);
    }
    void addCourse(Course c){
        course_catalog.add(c);
        System.out.printf("Course %s %d has been added to %s!\n",c.name,c.code,University);
    }

    void removeCourse(int name){
        for (int i = 0; i < course_catalog.size(); i++){
            if (course_catalog.get(i).code == name){
                System.out.printf("%s %d has been removed from %s\n",course_catalog.get(i).name,course_catalog.get(i).code,University);
                course_catalog.remove(i);
                return;
            }
        }
        System.out.printf("Course to be removed, with code %d not found\n",name);
    }

    void addStudent(int ID, double GPA, String name, student_type type){
        student p = new student(ID,GPA,type,name);
        student_roster.add(p);
        System.out.printf("%s has been enrolled to %s!\n",name,University);
    }

    void addStudent(student stu){
        student_roster.add(stu);
        System.out.printf("%s has been enrolled to %s!\n",stu.name,University);
    }

    void addStudentCourse(int ID, int course){
        student p = findStudentInRoster(ID);

        if (p.ID == 0){
            System.out.printf("ADD: Student %d does not exist\n",ID);
            return;
        }
        for (int i = 0; i < course_catalog.size(); i++){
            if (course_catalog.get(i).code == course){
                course_catalog.get(i).addStudent(p);
                return;
            }
        }

        System.out.printf("Course %s does not exist\n",course);
    }

    void removeStudentCourse(int ID, int course){
        student p = findStudentInRoster(ID);

        if (p.ID == 0){

            System.out.printf("REMOVE: Student %d does not exist\n",ID);
            return;
        }

        for (int i = 0; i < course_catalog.size(); i++){
            if (course_catalog.get(i).code == course){
                if (p == course_catalog.get(i).getStudent(ID)){
                    course_catalog.get(i).removeStudent(p);
                    return;
                }
            }
        }

        System.out.printf("Course %s does not exist\n",course);
    }

    private student findStudentInRoster(int ID){
        student p = new student();

        for (int i = 0; i < student_roster.size(); i++){
            if (student_roster.get(i).ID == ID){
                p = student_roster.get(i);
                break;
            }
        }
        if (p.ID == 0) {
            System.out.printf("Student %d does not exist\n", ID);
        }
        return p;

    }
}

public class Main {

    public static void main(String[] args) {

        System.out.println("TESTING ENROLLMENT FUNCTIONS\n====================================================");
        Enrollment PSU = new Enrollment("Penn State University");

        student k = new student(10,3.14,student_type.FULL_TIME,"Pi");
        student w = new student(20, 2.0, student_type.PART_TIME, "Cody");
        student y = new student(30, 1.5, student_type.FULL_TIME, "Alexander F.");
        student z = new student(40, 3.5, student_type.INTERNATIONAL_STUDENT, "Morayo");

        Course c = new Course(50,"MATH");
        //Course s = new Course(311, "SWENG");

        c.addStudent(k);
        c.removeStudent(k);

        PSU.addCourse(c);
        PSU.addCourse("SWENG",311);

        PSU.addStudent(k);
        PSU.addStudent(w);
        PSU.addStudent(y);
        PSU.addStudent(z.ID,z.GPA,z.name,z.type_of_student);

        PSU.addStudentCourse(k.ID,c.code);
        PSU.addStudentCourse(w.ID,c.code);
        PSU.addStudentCourse(y.ID,311);
        PSU.addStudentCourse(z.ID,311);

        y.GPA = 1.0;
        PSU.student_roster.set(2,y);
        PSU.removeStudentCourse(y.ID,311);
        PSU.addStudentCourse(y.ID, 311);

        PSU.removeCourse(50);
        PSU.addCourse(c);

        Enrollment GU = new Enrollment();
        GU.University = "Gannon University";


        System.out.println("====================================================\n");

        Scanner scan = new Scanner(System.in);

        int choice = -2;

	    while(choice != -1){
	        System.out.print("MENU\n--------------------------------------------\n1. Enter new student information\n2. Add a new course to the university catalog\n3. Enroll a student into a course\n4. Remove a course from the university catalog\n\nType -1 to stop\n--------------------------------------------\n->");
            choice = scan.nextInt();
            if(choice == 1){
                int ID;
                String name;
                student_type type;
                double GPA;
                System.out.print("Student Enrollment\n====================================================\nEnter ID: ");
                ID = scan.nextInt();
                System.out.print("Enter GPA: ");
                GPA = scan.nextDouble();
                System.out.print("Enter Name: ");
                scan.nextLine();
                name = scan.nextLine();
                System.out.print("Enter Type of Student:\n1. International\n2. Full Time\n 3. Part Time\n->");
                int intType = scan.nextInt();
                if (intType == 1){
                    type = student_type.INTERNATIONAL_STUDENT;
                }
                else if (intType == 2){
                    type = student_type.FULL_TIME;
                }
                else {
                    type = student_type.PART_TIME;
                }
                PSU.addStudent(ID,GPA,name,type);
                System.out.println("====================================================");
            }
            else if (choice == 2){
                int code;
                String name;
                System.out.print("Course Registration\n====================================================\nEnter Course Code: ");
                code = scan.nextInt();
                System.out.print("Enter Course Name: ");
                scan.nextLine();
                name = scan.nextLine();
                PSU.addCourse(name,code);
                System.out.println("====================================================");
            }
            else if (choice == 3){
                int ID;
                int code;
                System.out.print("Course Enrollment\n====================================================\nEnter Student's ID: ");
                ID = scan.nextInt();
                System.out.print("Enter Course Code: ");
                code = scan.nextInt();
                PSU.addStudentCourse(ID,code);
                System.out.println("====================================================");
            }
            else if (choice == 4){
                System.out.print("Course Removal\n====================================================\nEnter Course Code: ");
                PSU.removeCourse(scan.nextInt());
                System.out.println("====================================================");
            }
	    }
    }
}

