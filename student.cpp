#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    int    rollNo;
    string name;

    Student() : rollNo(0), name("") {}
    Student(int r, const string& n) : rollNo(r), name(n) {}

    void display() const {
        cout << "      Roll#" << rollNo << " - " << name << "\n";
    }
};
