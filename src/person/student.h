/**
 * @file    Student.h
 * @brief   Definition and Implementation of the Student class
 * @author  [Minahil Qadeer]  |  Roll No: CS-044
 * @course  CS-104L: Object-Oriented Programming
 * @inst    HITEC University Taxila
 * @date    June 2026
 * * OOP Concepts: Single Inheritance, Encapsulation, Runtime Polymorphism
 */

#ifndef STUDENT_H
#define STUDENT_H

#include "person.h" 

class Student : public Person {
private:
    string rollNo;
    int semester;
    double gpa;

public:
    Student(string n, string c, int a, string con, string r, int sem, double g) 
        : Person(n, c, a, con), rollNo(r), semester(sem), gpa(g) {}

    void displayInfo() const override {
        cout << "\n--- STUDENT PROFILE ---"
             << "\nRoll No: " << rollNo 
             << "\nName: " << name 
             << "\nSemester: " << semester
             << "\nGPA: " << gpa 
             << "\nGrade: " << calculateGrade() 
             << "\nContact: " << contact << "\n-----------------------\n";
    }

    char calculateGrade() const {
        if (gpa >= 3.5) return 'A';
        if (gpa >= 3.0) return 'B';
        if (gpa >= 2.0) return 'C';
        return 'F';
    }

    string getRollNo() const { return rollNo; }
};

#endif 