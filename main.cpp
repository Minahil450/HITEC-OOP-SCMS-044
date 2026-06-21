#include <iostream>
#include <string>
using namespace std;

// ======= Student =======
class Student {
public:
    int    rollNo;
    string name;
    Student() : rollNo(0), name("") {}
    Student(int r, const string& n) : rollNo(r), name(n) {}
    void display() const { cout << "      Roll#" << rollNo << " - " << name << "\n"; }
};

// ======= Room =======
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
    Room(int rNo, const string& t, int f) : roomNumber(rNo), type(t), floor(f), occupantCount(0) {
        for (int i = 0; i < 3; i++) occupants[i] = nullptr;
        if (type == "single") capacity = 1;
        else if (type == "double") capacity = 2;
        else capacity = 3;
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

// ======= HostelBlock =======
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
        for (int i = 0; i < roomCount; i++) { totalOcc += rooms[i].getOccupants(); totalCap += rooms[i].getCapacity(); }
        cout << "  Block: " << blockName << " | Rooms: " << roomCount
             << " | Occupancy: " << totalOcc << "/" << totalCap << "\n";
    }
    string getName() const { return blockName; }
};

// ======= Abstract: Accommodation =======
class Accommodation {
public:
    virtual void allocateRoom(int roomNo, Student* s) = 0;
    virtual void vacateRoom(int roomNo, int rollNo)   = 0;
    virtual ~Accommodation() {}
};

// ======= Abstract: Reportable =======
class Reportable {
public:
    virtual void generateReport() const = 0;
    virtual ~Reportable() {}
};

// ======= HostelManager (Multiple Inheritance) =======
class HostelManager : public Accommodation, public Reportable {
private:
    HostelBlock blocks[5];
    int         blockCount;
public:
    HostelManager() : blockCount(0) {}

    void addBlock(const string& name) {
        if (blockCount >= 5) { cout << "Max blocks reached!\n"; return; }
        blocks[blockCount++] = HostelBlock(name);
        cout << "[HostelManager] Block '" << name << "' added.\n";
    }

    void addRoomToBlock(const string& blockName, int rNo, const string& type, int floor) {
        for (int i = 0; i < blockCount; i++)
            if (blocks[i].getName() == blockName) { blocks[i].addRoom(rNo, type, floor); return; }
        cout << "  Block not found!\n";
    }

    void allocateRoom(int roomNo, Student* s) override {
        for (int i = 0; i < blockCount; i++) {
            Room* r = blocks[i].findRoom(roomNo);
            if (r) { r->addStudent(s); return; }
        }
        cout << "  Room " << roomNo << " not found!\n";
    }

    void vacateRoom(int roomNo, int rollNo) override {
        for (int i = 0; i < blockCount; i++) {
            Room* r = blocks[i].findRoom(roomNo);
            if (r) { r->removeStudent(rollNo); return; }
        }
        cout << "  Room " << roomNo << " not found!\n";
    }

    void generateReport() const override {
        cout << "\n========== OCCUPANCY REPORT ==========\n";
        for (int i = 0; i < blockCount; i++) blocks[i].blockReport();
        cout << "======================================\n";
    }

    void displayAll() const {
        cout << "\n========== HOSTEL DETAILS ==========\n";
        for (int i = 0; i < blockCount; i++) blocks[i].display();
        cout << "=====================================\n";
    }
};

// ======= main() =======
int main() {
    Student s1(101, "Ali Hassan");
    Student s2(102, "Sara Khan");
    Student s3(103, "Umar Farooq");
    Student s4(104, "Zara Ahmed");
    Student s5(105, "Bilal Raza");

    HostelManager hm;

    cout << "\n--- Adding Blocks ---\n";
    hm.addBlock("Block-A");
    hm.addBlock("Block-B");

    cout << "\n--- Adding Rooms ---\n";
    hm.addRoomToBlock("Block-A", 101, "single", 1);
    hm.addRoomToBlock("Block-A", 102, "double", 1);
    hm.addRoomToBlock("Block-A", 103, "triple", 2);
    hm.addRoomToBlock("Block-B", 201, "single", 1);
    hm.addRoomToBlock("Block-B", 202, "double", 2);

    cout << "\n--- Allocating Rooms ---\n";
    hm.allocateRoom(101, &s1);
    hm.allocateRoom(102, &s2);
    hm.allocateRoom(102, &s3);
    hm.allocateRoom(103, &s4);
    hm.allocateRoom(103, &s5);

    hm.displayAll();
    hm.generateReport();

    cout << "\n--- Vacating Student ---\n";
    hm.vacateRoom(102, 102);

    hm.displayAll();
    hm.generateReport();

    cout << "\n===== END =====\n";
    return 0;
}
