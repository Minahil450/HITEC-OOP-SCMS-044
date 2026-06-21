#include <iostream>
#include <string>
using namespace std;

// ======= FeeRecord Class =======
class FeeRecord {
private:
    string* studentRef;
    double semesterFee;
    double hostelFee;
    double libraryFine;
    double totalPaid;
    double balance;

public:
    FeeRecord(const string& name, double semFee, double hostFee, double libFine)
        : semesterFee(semFee), hostelFee(hostFee), libraryFine(libFine), totalPaid(0.0)
    {
        studentRef = new string(name);
        balance = semesterFee + hostelFee + libraryFine;
        cout << "[Constructor] FeeRecord created for: " << *studentRef << "\n";
    }

    FeeRecord(const FeeRecord& other)
        : semesterFee(other.semesterFee), hostelFee(other.hostelFee),
          libraryFine(other.libraryFine), totalPaid(other.totalPaid), balance(other.balance)
    {
        studentRef = new string(*other.studentRef);
        cout << "[Copy Constructor] Copied record for: " << *studentRef << "\n";
    }

    FeeRecord& operator=(const FeeRecord& other) {
        if (this == &other) return *this;
        delete studentRef;
        studentRef  = new string(*other.studentRef);
        semesterFee = other.semesterFee;
        hostelFee   = other.hostelFee;
        libraryFine = other.libraryFine;
        totalPaid   = other.totalPaid;
        balance     = other.balance;
        cout << "[Copy Assignment] Assigned record for: " << *studentRef << "\n";
        return *this;
    }

    ~FeeRecord() {
        cout << "[Destructor] FeeRecord destroyed for: " << *studentRef << "\n";
        delete studentRef;
    }

    FeeRecord& operator-=(double payment) {
        if (payment <= 0) { cout << "  [Warning] Payment must be positive.\n"; return *this; }
        if (payment > balance) { cout << "  [Warning] Amount exceeds balance!\n"; payment = balance; }
        totalPaid += payment;
        balance   -= payment;
        cout << "  [Payment] Rs. " << payment << " paid. Remaining: Rs. " << balance << "\n";
        return *this;
    }

    void display() const {
        cout << "\n====== FEE RECORD ======\n";
        cout << "Student      : " << *studentRef << "\n";
        cout << "Semester Fee : Rs. " << semesterFee << "\n";
        cout << "Hostel Fee   : Rs. " << hostelFee   << "\n";
        cout << "Library Fine : Rs. " << libraryFine << "\n";
        cout << "Total Paid   : Rs. " << totalPaid   << "\n";
        cout << "Balance      : Rs. " << balance     << "\n";
        cout << "========================\n";
    }

    double getBalance() const { return balance; }
};


// ======= Invoice Class =======
class Invoice {
private:
    int    invoiceID;
    string date;
    string* items;
    int    itemCount;
    double totalAmount;

    static int invoiceCounter;

public:
    Invoice(const string& invoiceDate, const string itemList[], int count, double amount)
        : date(invoiceDate), itemCount(count), totalAmount(amount)
    {
        invoiceID = ++invoiceCounter;
        items = new string[itemCount];
        for (int i = 0; i < itemCount; i++)
            items[i] = itemList[i];
        cout << "[Constructor] Invoice #" << invoiceID << " created.\n";
    }

    Invoice(const Invoice& other)
        : date(other.date), itemCount(other.itemCount), totalAmount(other.totalAmount)
    {
        invoiceID = ++invoiceCounter;
        items = new string[itemCount];
        for (int i = 0; i < itemCount; i++)
            items[i] = other.items[i];
        cout << "[Copy Constructor] Invoice #" << invoiceID << " created.\n";
    }

    Invoice& operator=(const Invoice& other) {
        if (this == &other) return *this;
        delete[] items;
        date = other.date; itemCount = other.itemCount; totalAmount = other.totalAmount;
        items = new string[itemCount];
        for (int i = 0; i < itemCount; i++)
            items[i] = other.items[i];
        cout << "[Copy Assignment] Invoice #" << invoiceID << " updated.\n";
        return *this;
    }

    ~Invoice() {
        cout << "[Destructor] Invoice #" << invoiceID << " destroyed.\n";
        delete[] items;
    }

    static int getTotalInvoices() { return invoiceCounter; }

    void display() const {
        cout << "\n====== INVOICE ======\n";
        cout << "Invoice ID   : INV-" << invoiceID << "\n";
        cout << "Date         : "     << date       << "\n";
        cout << "Items        :\n";
        for (int i = 0; i < itemCount; i++)
            cout << "  " << (i+1) << ". " << items[i] << "\n";
        cout << "Total Amount : Rs. " << totalAmount << "\n";
        cout << "=====================\n";
    }
};

int Invoice::invoiceCounter = 0;


// ======= MAIN =======
int main() {

    // ---- FeeRecord Tests ----
    cout << "\n===== FEERECORD TESTS =====\n";

    FeeRecord rec1("Ali Hassan", 45000, 12000, 500);
    rec1.display();

    cout << "\n-- Payments --\n";
    rec1 -= 20000;
    rec1 -= 10000;
    rec1.display();

    cout << "\n-- Copy Constructor --\n";
    FeeRecord rec2 = rec1;
    rec2 -= 5000;
    cout << "rec1 balance: Rs. " << rec1.getBalance() << "\n";
    cout << "rec2 balance: Rs. " << rec2.getBalance() << "\n";

    cout << "\n-- Copy Assignment --\n";
    FeeRecord rec3("Temp", 0, 0, 0);
    rec3 = rec1;
    rec3.display();


    // ---- Invoice Tests ----
    cout << "\n===== INVOICE TESTS =====\n";

    string items1[] = {"Semester Fee - Rs.45000", "Hostel Fee - Rs.12000", "Library Fine - Rs.500"};
    Invoice inv1("2025-01-15", items1, 3, 57500);
    inv1.display();

    string items2[] = {"Lab Fee - Rs.8000", "Transport - Rs.3000"};
    Invoice inv2("2025-02-01", items2, 2, 11000);
    inv2.display();

    cout << "\nTotal Invoices: " << Invoice::getTotalInvoices() << "\n";

    cout << "\n-- Copy Constructor --\n";
    Invoice inv3 = inv1;
    inv3.display();

    cout << "\nTotal Invoices after copy: " << Invoice::getTotalInvoices() << "\n";

    cout << "\n===== END =====\n";
    return 0;
}
