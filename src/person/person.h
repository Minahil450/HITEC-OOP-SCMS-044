/**
 * @file    Person.h
 * @brief   Definition of the Abstract Base Class Person
 * @author  [Minahil Qadeer]  |  Roll No: CS-044
 * @course  CS-104L: Object-Oriented Programming
 * @inst    HITEC University Taxila
 * @date    June 2026
 * * OOP Concepts: Abstract Classes, Pure Virtual Functions, Encapsulation
 */

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;

class Person {
protected:
    string name;
    string cnic;
    int age;
    string contact;

public:
    Person(string n, string c, int a, string con) 
        : name(n), cnic(c), age(a), contact(con) {}
        
    virtual ~Person() = default;
    virtual void displayInfo() const = 0; 
    string getName() const { return name; }
    string getCNIC() const { return cnic; }
    int getAge() const { return age; }
    string getContact() const { return contact; }
};

#endif 