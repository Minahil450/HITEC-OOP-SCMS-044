/**
 * @file    main.cpp
 * @brief   Driver program to test Module 1 - Person Hierarchy (SCMS)
 * @author  [Minahil Qadeer]  |  Roll No: CS-044
 * @course  CS-104L: Object-Oriented Programming
 * @inst    HITEC University Taxila
 * @date    June 2026
 * * OOP Concepts: Runtime Polymorphism, Abstract Classes, Single Inheritance
 */

#include <iostream>
#include "student.h"
#include "faculty.h"
#include "staff.h"

using namespace std;

int main() {
    cout << "==================================================\n";
    cout << "     HITEC SMART CAMPUS MANAGEMENT SYSTEM         \n";
    cout << "==================================================\n\n";

    cout << "--- Testing Module 1 (Person Hierarchy) ---\n";

    Person* list[3];
    
    list[0] = new Student("Khadija Manahil", "35202-1234567-1", 20, "0300-1234567", "CS-044", 2, 3.8);
    list[1] = new Faculty("Dr. Hania", "35101-9876543-1", 45, "0321-9876543", "F-102", "CS", "Associate Professor");
    list[2] = new Staff("Sajid Mehmood", "35201-1111111-1", 35, "0333-5555555", "S-501", "Clerk", 45000);
    for (int i = 0; i < 3; i++) {
        list[i]->displayInfo();
        cout << endl;
    }

    delete list[0];
    delete list[1];
    delete list[2];

    cout << "==================================================\n";
    cout << " Module 1 Checked Successfully!\n";
    cout << "==================================================\n";

    return 0;
}