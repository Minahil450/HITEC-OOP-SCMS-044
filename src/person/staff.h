/**
 * @file    Staff.h
 * @brief   Definition and Implementation of the Staff class
 * @author  [Minahil Qadeer]  |  Roll No: CS-044
 * @course  CS-104L: Object-Oriented Programming
 * @inst    HITEC University Taxila
 * @date    June 2026
 * * OOP Concepts: Single Inheritance, Encapsulation, Runtime Polymorphism
 */

#ifndef STAFF_H
#define STAFF_H

#include "person.h" 

class Staff : public Person {
private:
    string staffID;
    string role;
    double salary;

public:
    
    Staff(string n, string c, int a, string con, string stID, string r, double sal) 
        : Person(n, c, a, con), staffID(stID), role(r), salary(sal) {}
    void displayInfo() const override {
        cout << "\n--- STAFF PROFILE ---"
             << "\nStaff ID: " << staffID 
             << "\nName: " << name 
             << "\nRole: " << role 
             << "\nSalary: Rs. " << salary 
             << "\nContact: " << contact << "\n---------------------\n";
    }
};

#endif 