/**
 * @file    Faculty.h
 * @brief   Definition and Implementation of the Faculty class
 * @author  [Minahil Qadeer]  |  Roll No: CS-044
 * @course  CS-104L: Object-Oriented Programming
 * @inst    HITEC University Taxila
 * @date    June 2026
 * * OOP Concepts: Single Inheritance, Encapsulation, Runtime Polymorphism
 */

#ifndef FACULTY_H
#define FACULTY_H

#include "person.h" 

class Faculty : public Person {
private:
    string employeeID;
    string department;
    string designation;

public:

    Faculty(string n, string c, int a, string con, string empID, string dept, string desig) 
        : Person(n, c, a, con), employeeID(empID), department(dept), designation(desig) {}

    void displayInfo() const override {
        cout << "\n--- FACULTY PROFILE ---"
             << "\nEmployee ID: " << employeeID 
             << "\nName: " << name 
             << "\nDesignation: " << designation 
             << "\nDepartment: " << department 
             << "\nContact: " << contact << "\n-----------------------\n";
    }

    string getEmployeeID() const { return employeeID; }
};

#endif 