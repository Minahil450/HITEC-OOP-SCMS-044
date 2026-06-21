/**
 * @file    main.cpp
 * @brief   Driver program testing Module 1 (Person Hierarchy) +
 *          Module 2 (Course & Enrollment Management) together
 * @author  [Minahil Qadeer]  |  Roll No: CS-044
 * @course  CS-104L: Object-Oriented Programming
 * @inst    HITEC University Taxila
 * @date    June 2026
 */

#include "../person/student.h"
#include "../person/faculty.h"
#include "../person/staff.h"
#include "Course.h"
#include "Enrollment.h"
#include "../utils/Exceptions.h"

using namespace std;

int main() {
    cout << "==================================================\n";
    cout << "     HITEC SMART CAMPUS MANAGEMENT SYSTEM         \n";
    cout << "==================================================\n\n";

    // ---------------- Module 1: Person Hierarchy ----------------
    cout << "--- Testing Module 1 (Person Hierarchy) ---\n";

    Person* list[3];
    list[0] = new Student("Khadija Manahil", "35202-1234567-1", 20, "0300-1234567", "CS-044", 2, 3.8);
    list[1] = new Faculty("Dr. Hania", "35101-9876543-1", 45, "0321-9876543", "F-102", "CS", "Associate Professor");
    list[2] = new Staff("Sajid Mehmood", "35201-1111111-1", 35, "0333-5555555", "S-501", "Clerk", 45000);

    for (int i = 0; i < 3; i++) {
        list[i]->displayInfo();
    }

    // ---------------- Module 2: Course & Enrollment ----------------
    cout << "\n--- Testing Module 2 (Course & Enrollment Management) ---\n";

    // Reuse the Faculty object from Module 1 as the course instructor
    Faculty* drHania = dynamic_cast<Faculty*>(list[1]);

    Course oop("CS104L", "Object-Oriented Programming", 3, drHania, 2); // small capacity to demo exception
    Course dsa("CS105L", "Data Structures & Algorithms", 4, drHania, 3);

    cout << "\n" << oop << "\n";

    Student s1("Ayesha", "352781111111-1", 21, "0300-1111111", "21F-0001", 4, 3.6);
    Student s2("Sara Khan",  "35202-2222222-1", 20, "0300-2222222", "21F-0002", 4, 3.2);
    Student s3("Bilal Tariq", "35202-3333333-1", 22, "0300-3333333", "21F-0003", 4, 2.8);
    Student s4("Hina Aslam", "35202-4444444-1", 21, "0300-4444444", "21F-0004", 4, 3.9);

    try {
        oop.enrollStudent(&s1);
        oop.enrollStudent(&s2);
        cout << "Enrolled s1 (Ahmad) and s2 (Sara) successfully.\n";

        oop.enrollStudent(&s3); // exceeds maxCapacity of 2 -> goes to waitlist + throws
    } catch (const CapacityExceededException& ex) {
        cout << "Caught exception: " << ex.what() << "\n";
    }

    cout << "\n--- Updated Course Info ---\n" << oop << "\n";

    // Demonstrate operator==
    Course oopDuplicateCode("CS104L", "OOP (Section B)", 3, drHania, 5);
    if (oop == oopDuplicateCode) {
        cout << "oop and oopDuplicateCode have the SAME course code.\n";
    } else {
        cout << "oop and oopDuplicateCode have DIFFERENT course codes.\n";
    }
    try {
        dsa.enrollStudent(&s4); 
    } catch (...) {
        
    }

    Student** merged = oop + dsa;
    int mergedSize = oop.getWaitlistCount() + dsa.getWaitlistCount();
    cout << "\n--- Merged Waiting List (oop + dsa) ---\n";
    for (int i = 0; i < mergedSize; i++) {
        if (merged[i]) {
            cout << " - " << merged[i]->getName() << " (" << merged[i]->getRollNo() << ")\n";
        }
    }
    delete[] merged;

    // Demonstrate Enrollment class
    Enrollment e1(&s1, &oop, "2026-02-10");
    e1.setGrade(s1.calculateGrade());
    cout << "\n--- Enrollment Record ---\n";
    e1.displayEnrollment();
    delete list[0];
    delete list[1];
    delete list[2];

    cout << "\n==================================================\n";
    cout << " Modules 1 & 2 Checked Successfully!\n";
    cout << "==================================================\n";

    return 0;
}