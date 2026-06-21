/**
 * @file    Enrollment.h
 * @brief   Definition and Implementation of the Enrollment class
 * @author  [Minahil Qadeer]  |  Roll No: CS-044
 * @course  CS-104L: Object-Oriented Programming
 * @inst    HITEC University Taxila
 * @date    June 2026
 *
 * OOP Concepts: Encapsulation, Composition (links Student & Course)
 */

#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>
#include <iostream>
#include "../person/student.h"
#include "Course.h"
using namespace std;

class Enrollment {
private:
    Student* student;
    Course* course;
    string enrollmentDate;
    char grade; 

public:
    Enrollment(Student* s, Course* c, string date)
        : student(s), course(c), enrollmentDate(date), grade('-') {}

    // Getters / Setters
    Student* getStudent() const { return student; }
    Course* getCourse() const { return course; }
    string getEnrollmentDate() const { return enrollmentDate; }
    char getGrade() const { return grade; }
    void setGrade(char g) { grade = g; }

    void displayEnrollment() const {
        cout << "Student: " << (student ? student->getName() : "N/A")
             << " | Roll No: " << (student ? student->getRollNo() : "N/A")
             << " | Course: " << (course ? course->getCourseCode() : "N/A")
             << " | Date: " << enrollmentDate
             << " | Grade: " << grade << "\n";
    }
};

#endif