#include <iostream>
#include <string>
using namespace std;

class Invoice {
private:
    int    invoiceID;
    string date;
    string* items;
    int    itemCount;
    double totalAmount;

    static int invoiceCounter;   // shared across all objects

public:
    // Parameterized Constructor
    Invoice(const string& invoiceDate, const string itemList[], int count, double amount)
        : date(invoiceDate), itemCount(count), totalAmount(amount)
    {
        invoiceID = ++invoiceCounter;
        items = new string[itemCount];
        for (int i = 0; i < itemCount; i++)
            items[i] = itemList[i];
        cout << "[Constructor] Invoice #" << invoiceID << " created.\n";
    }

    // Copy Constructor
    Invoice(const Invoice& other)
        : date(other.date), itemCount(other.itemCount), totalAmount(other.totalAmount)
    {
        invoiceID = ++invoiceCounter;
        items = new string[itemCount];
        for (int i = 0; i < itemCount; i++)
            items[i] = other.items[i];
        cout << "[Copy Constructor] Invoice #" << invoiceID << " (copy of #" << other.invoiceID << ") created.\n";
    }

    // Copy Assignment Operator
    Invoice& operator=(const Invoice& other) {
        if (this == &other) return *this;
        delete[] items;
        date        = other.date;
        itemCount   = other.itemCount;
        totalAmount = other.totalAmount;
        items = new string[itemCount];
        for (int i = 0; i < itemCount; i++)
            items[i] = other.items[i];
        cout << "[Copy Assignment] Invoice #" << invoiceID << " updated.\n";
        return *this;
    }

    // Destructor
    ~Invoice() {
        cout << "[Destructor] Invoice #" << invoiceID << " destroyed.\n";
        delete[] items;
    }

    // Static function
    static int getTotalInvoices() {
        return invoiceCounter;
    }

    void display() const {
        cout << "\n====== INVOICE ======\n";
        cout << "Invoice ID   : INV-" << invoiceID  << "\n";
        cout << "Date         : "     << date        << "\n";
        cout << "Items        :\n";
        for (int i = 0; i < itemCount; i++)
            cout << "  " << (i+1) << ". " << items[i] << "\n";
        cout << "Total Amount : Rs. " << totalAmount << "\n";
        cout << "=====================\n";
    }
};

int Invoice::invoiceCounter = 0;
