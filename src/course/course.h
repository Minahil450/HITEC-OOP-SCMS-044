/**
 * @file    Course.h
 * @brief   Definition and Implementation of the Course class
 * @author  [Minahil Qadeer]  |  Roll No: CS-044
 * @course  CS-104L: Object-Oriented Programming
 * @inst    HITEC University Taxila
 * @date    June 2026
 *
 * OOP Concepts: Encapsulation, Operator Overloading (==, <<, +),
 *               Friend Functions, Custom Exception Classes, Aggregation
 */

#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>
#include "../person/faculty.h"
#include "../person/student.h"
#include "../utils/Exceptions.h"
using namespace std;

class Course {
private:
    string courseCode;
    string courseName;
    int creditHours;
    Faculty* instructor;     // Aggregation: Course holds a Faculty* reference
    int maxCapacity;
    int enrolledCount;

    // Array-based waiting list (Array-based Collection requirement)
    static const int MAX_WAITLIST = 50;
    Student* waitingList[MAX_WAITLIST];
    int waitlistCount;

public:
    // Default constructor
    Course()
        : courseCode("N/A"), courseName("Unnamed"), creditHours(0),
          instructor(nullptr), maxCapacity(0), enrolledCount(0), waitlistCount(0) {
        for (int i = 0; i < MAX_WAITLIST; i++) waitingList[i] = nullptr;
    }

    // Parameterized constructor
    Course(string code, string name, int credits, Faculty* fac, int maxCap)
        : courseCode(code), courseName(name), creditHours(credits),
          instructor(fac), maxCapacity(maxCap), enrolledCount(0), waitlistCount(0) {
        for (int i = 0; i < MAX_WAITLIST; i++) waitingList[i] = nullptr;
    }

    // ---------------- Getters / Setters (Encapsulation) ----------------
    string getCourseCode() const { return courseCode; }
    string getCourseName() const { return courseName; }
    int getCreditHours() const { return creditHours; }
    Faculty* getInstructor() const { return instructor; }
    int getMaxCapacity() const { return maxCapacity; }
    int getEnrolledCount() const { return enrolledCount; }

    void setCourseName(const string& n) { courseName = n; }
    void setCreditHours(int hours) { creditHours = hours; }
    void setInstructor(Faculty* fac) { instructor = fac; }
    void setMaxCapacity(int cap) { maxCapacity = cap; }

    // ---------------- Enrollment logic ----------------
    // Throws CapacityExceededException if course is already full
    void enrollStudent(Student* student) {
        if (enrolledCount >= maxCapacity) {
            if (waitlistCount < MAX_WAITLIST) {
                waitingList[waitlistCount++] = student;
            }
            throw CapacityExceededException(courseCode);
        }
        enrolledCount++;
    }

    Student** getWaitingList() { return waitingList; }
    int getWaitlistCount() const { return waitlistCount; }

    // ---------------- Operator Overloading ----------------

    // Overload == : compare two Course objects by courseCode
    bool operator==(const Course& other) const {
        return this->courseCode == other.courseCode;
    }

    // Overload + : merge two course waiting lists, returns array of Student pointers
    // Caller is responsible for delete[]-ing the returned array.
    Student** operator+(const Course& other) const {
        int totalSize = this->waitlistCount + other.waitlistCount;
        Student** merged = new Student*[totalSize > 0 ? totalSize : 1];

        int index = 0;
        for (int i = 0; i < this->waitlistCount; i++) {
            merged[index++] = this->waitingList[i];
        }
        for (int i = 0; i < other.waitlistCount; i++) {
            merged[index++] = other.waitingList[i];
        }
        return merged;
    }

    // Friend function: overload << to print course details (cout or file via ostream)
    friend ostream& operator<<(ostream& os, const Course& c);
};

inline ostream& operator<<(ostream& os, const Course& c) {
    os << "Course Code   : " << c.courseCode << "\n"
       << "Course Name   : " << c.courseName << "\n"
       << "Credit Hours  : " << c.creditHours << "\n"
       << "Instructor    : " << (c.instructor ? c.instructor->getName() : "Unassigned") << "\n"
       << "Enrolled      : " << c.enrolledCount << " / " << c.maxCapacity << "\n"
       << "Waitlist size : " << c.waitlistCount << "\n";
    return os;
}

#endif