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

class Room {
private:
    int      roomNumber;
    string   type;
    int      floor;
    Student* occupants[3];
    int      occupantCount;
    int      capacity;

public:
    Room() : roomNumber(0), type("single"), floor(0), occupantCount(0), capacity(1) {
        for (int i = 0; i < 3; i++) occupants[i] = nullptr;
    }
    Room(int rNo, const string& t, int f)
        : roomNumber(rNo), type(t), floor(f), occupantCount(0)
    {
        for (int i = 0; i < 3; i++) occupants[i] = nullptr;
        if      (type == "single") capacity = 1;
        else if (type == "double") capacity = 2;
        else                       capacity = 3;
    }
    bool addStudent(Student* s) {
        if (occupantCount >= capacity) { cout << "  [Room " << roomNumber << "] Full!\n"; return false; }
        occupants[occupantCount++] = s;
        cout << "  [Room " << roomNumber << "] " << s->name << " allocated.\n";
        return true;
    }
    bool removeStudent(int rollNo) {
        for (int i = 0; i < occupantCount; i++) {
            if (occupants[i] && occupants[i]->rollNo == rollNo) {
                cout << "  [Room " << roomNumber << "] " << occupants[i]->name << " vacated.\n";
                for (int j = i; j < occupantCount - 1; j++) occupants[j] = occupants[j+1];
                occupants[--occupantCount] = nullptr;
                return true;
            }
        }
        cout << "  [Room " << roomNumber << "] Student not found.\n";
        return false;
    }
    void display() const {
        cout << "    Room " << roomNumber << " | Type: " << type
             << " | Floor: " << floor << " | Occupants: " << occupantCount << "/" << capacity << "\n";
        for (int i = 0; i < occupantCount; i++) if (occupants[i]) occupants[i]->display();
    }
    int getRoomNumber() const { return roomNumber; }
    int getOccupants()  const { return occupantCount; }
    int getCapacity()   const { return capacity; }
};

class HostelBlock {
private:
    string blockName;
    Room   rooms[10];
    int    roomCount;

public:
    HostelBlock() : blockName(""), roomCount(0) {}
    HostelBlock(const string& name) : blockName(name), roomCount(0) {}

    void addRoom(int rNo, const string& type, int floor) {
        if (roomCount >= 10) { cout << "  Block full!\n"; return; }
        rooms[roomCount++] = Room(rNo, type, floor);
        cout << "  [Block " << blockName << "] Room " << rNo << " added.\n";
    }

    Room* findRoom(int roomNo) {
        for (int i = 0; i < roomCount; i++)
            if (rooms[i].getRoomNumber() == roomNo) return &rooms[i];
        return nullptr;
    }

    void display() const {
        cout << "\n  === Block: " << blockName << " ===\n";
        for (int i = 0; i < roomCount; i++) rooms[i].display();
    }

    void blockReport() const {
        int totalOcc = 0, totalCap = 0;
        for (int i = 0; i < roomCount; i++) {
            totalOcc += rooms[i].getOccupants();
            totalCap += rooms[i].getCapacity();
        }
        cout << "  Block: " << blockName << " | Rooms: " << roomCount
             << " | Occupancy: " << totalOcc << "/" << totalCap << "\n";
    }

    string getName() const { return blockName; }
};
