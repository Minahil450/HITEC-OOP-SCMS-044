/**
 * @file    Module3_LibrarySystem.cpp
 * @brief   Module 3 - Library System (Simple Version)
 * @author  [Minahil Qadeer]  |  Roll No: CS-044
 * @course  CS-104L: Object-Oriented Programming
 * @inst    HITEC University Taxila
 * @date    June 2026
 *
 * OOP Concepts: Abstract classes, Arrays of objects, File I/O, Exceptions
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ============================================================
// Custom Exceptions (simple version)
// ============================================================
class CapacityExceededException {
public:
    string message;
    CapacityExceededException(string courseCode) {
        message = "Course '" + courseCode + "' is full!";
    }
};

class OverdueException {
public:
    string message;
    double fine;
    OverdueException(string itemID, double f) {
        fine = f;
        message = "Item '" + itemID + "' is overdue. Fine: Rs. " + to_string((int)f);
    }
};

// ============================================================
// LibraryItem (Abstract Base Class)
// ============================================================
class LibraryItem {
public:
    string itemID;
    string title;
    string author;
    int publicationYear;

    LibraryItem(string id, string t, string a, int year) {
        itemID = id;
        title = t;
        author = a;
        publicationYear = year;
    }

    virtual void checkout() = 0;          // pure virtual
    virtual void displayInfo() = 0;       // pure virtual
    virtual string saveLine() = 0;        // pure virtual: returns line to write in file

    string getTitle() {
        return title;
    }

    string getItemID() {
        return itemID;
    }
};

// ============================================================
// Book class
// ============================================================
class Book : public LibraryItem {
public:
    string ISBN;
    string genre;
    int copiesAvailable;

    Book(string id, string t, string a, int year, string isbn, string g, int copies)
        : LibraryItem(id, t, a, year) {
        ISBN = isbn;
        genre = g;
        copiesAvailable = copies;
    }

    void checkout() override {
        if (copiesAvailable > 0) {
            copiesAvailable = copiesAvailable - 1;
        }
    }

    void displayInfo() override {
        cout << "\n--- BOOK ---" << endl;
        cout << "Item ID: " << itemID << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << publicationYear << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "Genre: " << genre << endl;
        cout << "Copies Available: " << copiesAvailable << endl;
        cout << "------------" << endl;
    }

    string saveLine() override {
        return "BOOK|" + itemID + "|" + title + "|" + author + "|" +
               to_string(publicationYear) + "|" + ISBN + "|" + genre + "|" +
               to_string(copiesAvailable);
    }
};

// ============================================================
// Journal class
// ============================================================
class Journal : public LibraryItem {
public:
    string ISSN;
    int volume;
    int issueNumber;

    Journal(string id, string t, string a, int year, string issn, int vol, int issue)
        : LibraryItem(id, t, a, year) {
        ISSN = issn;
        volume = vol;
        issueNumber = issue;
    }

    void checkout() override {
        cout << "Journal '" << title << "' issued for reading." << endl;
    }

    void displayInfo() override {
        cout << "\n--- JOURNAL ---" << endl;
        cout << "Item ID: " << itemID << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << publicationYear << endl;
        cout << "ISSN: " << ISSN << endl;
        cout << "Volume: " << volume << endl;
        cout << "Issue No: " << issueNumber << endl;
        cout << "---------------" << endl;
    }

    string saveLine() override {
        return "JOURNAL|" + itemID + "|" + title + "|" + author + "|" +
               to_string(publicationYear) + "|" + ISSN + "|" +
               to_string(volume) + "|" + to_string(issueNumber);
    }
};

// ============================================================
// Simple struct to track issued items
// ============================================================
struct IssuedRecord {
    string rollNo;
    string itemID;
    int daysOut;
};

// ============================================================
// Library class
// ============================================================
class Library {
public:
    LibraryItem* catalog[100];  
    int itemCount;

    IssuedRecord issuedItems[100];
    int issuedCount;

    Library() {
        itemCount = 0;
        issuedCount = 0;
    }
    void addItem(LibraryItem* item) {
        catalog[itemCount] = item;
        itemCount = itemCount + 1;
    }
    LibraryItem* searchByTitle(string title) {
        for (int i = 0; i < itemCount; i++) {
            if (catalog[i]->getTitle() == title) {
                return catalog[i];
            }
        }
        return NULL; 
    }
    void displayCatalog() {
        for (int i = 0; i < itemCount; i++) {
            catalog[i]->displayInfo();
        }
    }
    void issueItem(string rollNo, string itemID) {
        issuedItems[issuedCount].rollNo = rollNo;
        issuedItems[issuedCount].itemID = itemID;
        issuedItems[issuedCount].daysOut = 0;
        issuedCount = issuedCount + 1;
    }
    void returnItem(string itemID) {
        int limit = 14;        
        double finePerDay = 10; 

        for (int i = 0; i < issuedCount; i++) {
            if (issuedItems[i].itemID == itemID) {
                int daysOut = issuedItems[i].daysOut;

                // remove this record by shifting everything left
                for (int j = i; j < issuedCount - 1; j++) {
                    issuedItems[j] = issuedItems[j + 1];
                }
                issuedCount = issuedCount - 1;

                if (daysOut > limit) {
                    double fine = (daysOut - limit) * finePerDay;
                    throw OverdueException(itemID, fine);
                }
                return;
            }
        }
        cout << "No issued record found for item: " << itemID << endl;
    }
    void saveToFile(string filename) {
        ofstream outFile(filename);

        for (int i = 0; i < itemCount; i++) {
            outFile << catalog[i]->saveLine() << endl;
        }

        outFile.close();
        cout << "Catalog saved to " << filename << endl;
    }
    void loadFromFile(string filename) {
        ifstream inFile(filename);
        itemCount = 0;

        string type, id, title, author, yearStr, f1, f2, f3;

        while (getline(inFile, type, '|')) {
            getline(inFile, id, '|');
            getline(inFile, title, '|');
            getline(inFile, author, '|');
            getline(inFile, yearStr, '|');
            getline(inFile, f1, '|');
            getline(inFile, f2, '|');
            getline(inFile, f3);  // last field goes till end of line

            int year = stoi(yearStr);

            if (type == "BOOK") {
                int copies = stoi(f3);
                addItem(new Book(id, title, author, year, f1, f2, copies));
            } else if (type == "JOURNAL") {
                int vol = stoi(f2);
                int issue = stoi(f3);
                addItem(new Journal(id, title, author, year, f1, vol, issue));
            }
        }

        inFile.close();
        cout << "Catalog loaded from " << filename << " (" << itemCount << " items)." << endl;
    }
};

// ============================================================
// main() — demo of all Module 3 features
// ============================================================
int main() {
    cout << "===== Module 3: Library System =====" << endl << endl;

    Library library;
    library.addItem(new Book("B001", "Introduction to C++", "Bjarne", 2020,
                              "978-0136083221", "Programming", 3));
    library.addItem(new Book("B002", "Data Structures Made Easy", "william", 2018,
                              "978-8192107592", "Computer Science", 2));
    library.addItem(new Journal("J001", "ACM Computing Surveys", "ACM", 2024,
                                 "0360-0300", 56, 4));

    cout << "Full catalog:" << endl;
    library.displayCatalog();
    LibraryItem* found = library.searchByTitle("Data Structures Made Easy");
    cout << "\nSearch result for 'Data Structures Made Easy':" << endl;
    if (found != NULL) {
        found->displayInfo();
    } else {
        cout << "Not found." << endl;
    }
    library.saveToFile("library_catalog.txt");
    library.issueItem("21F-0001", "B001");
    library.issuedItems[0].daysOut = 20; 

    try {
        library.returnItem("B001");
    } catch (OverdueException ex) {
        cout << "Caught exception: " << ex.message << endl;
    }

    library.loadFromFile("library_catalog.txt");
    cout << "\nCatalog after reloading from file:" << endl;
    library.displayCatalog();

    cout << "\n===== End of Module 3 Demo =====" << endl;
    return 0;
}