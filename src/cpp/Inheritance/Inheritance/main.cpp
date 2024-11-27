//
//  main.cpp
//  Inheritance
//
//  Created by Michael DeLeo on 1/13/18.
//  Copyright © 2018 Michael DeLeo. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;


class Person{
protected:
    string firstName;
    string lastName;
    int id;
public:
    Person(string firstName, string lastName, int identification){
        this->firstName = firstName;
        this->lastName = lastName;
        this->id = identification;
    }
    void printPerson(){
        cout<< "Name: "<< lastName << ", "<< firstName <<"\nID: "<< id << "\n";
    }
    
};

//Person is a student
class Student :  public Person{
private:
    vector<int> testScores;
public:
    /*
     *   Class Constructor
     *
     *   Parameters:
     *   firstName - A string denoting the Person's first name.
     *   lastName - A string denoting the Person's last name.
     *   id - An integer denoting the Person's ID number.
     *   scores - An array of integers denoting the Person's test scores.
     */
    // Write your constructor here
    Student(string firstName, string lastName, int id, vector<int> testScores);
    /*
     *   Function Name: calculate
     *   Return: A character denoting the grade.
     */
    // Write your function here
    char calculate();
};

Student::Student(string firstName, string lastName, int id, vector<int> testScores)
        : Person(firstName,lastName,id) //Explicitly constructs the Person class
{
    this->testScores = testScores;
}
char Student::calculate()
{
    int grade = 0;
    for (int i = 0; i < testScores.size(); i++)
    {grade = grade + testScores.at(i);} //add all scores
    
    grade = grade / testScores.size();  //average
    
    if (grade >= 90 && grade <= 100)
    {return 'O';}//O
    
    else if (grade >= 80 && grade < 90)
    {return 'E';}//E
    
    else if (grade >= 70 && grade < 80)
    {return 'A';}//A
    
    else if (grade >= 55 && grade < 70)
    {return 'P';} //P
    
    else if (grade >= 40 && grade < 55)
    {return 'D';}//D
    else
    {return 'T';}//T
    
}

int main() {
    string firstName;
    string lastName;
    int id;
    int numScores;
    cin >> firstName >> lastName >> id >> numScores;
    vector<int> scores;
    for(int i = 0; i < numScores; i++){
        int tmpScore;
        cin >> tmpScore;
        scores.push_back(tmpScore);
    }
    Student* s = new Student(firstName, lastName, id, scores);
    s->printPerson();
    cout << "Grade: " << s->calculate() << "\n";
    return 0;
}
