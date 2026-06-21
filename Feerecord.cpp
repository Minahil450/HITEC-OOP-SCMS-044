#include <iostream>
#include <string>
using namespace std;

class FeeRecord {
private:
    string* studentRef;
    double semesterFee;
    double hostelFee;
    double libraryFine;
    double totalPaid;
    double balance;

public:
    // Parameterized Constructor
    FeeRecord(const string& name, double semFee, double hostFee, double libFine)
        : semesterFee(semFee), hostelFee(hostFee), libraryFine(libFine), totalPaid(0.0)
    {
        studentRef = new string(name);
        balance = semesterFee + hostelFee + libraryFine;
        cout << "[Constructor] FeeRecord created for: " << *studentRef << "\n";
    }

    // Copy Constructor
    FeeRecord(const FeeRecord& other)
        : semesterFee(other.semesterFee), hostelFee(other.hostelFee),
          libraryFine(other.libraryFine), totalPaid(other.totalPaid), balance(other.balance)
    {
        studentRef = new string(*other.studentRef);
        cout << "[Copy Constructor] Copied record for: " << *studentRef << "\n";
    }

    // Copy Assignment Operator
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

    // Destructor
    ~FeeRecord() {
        cout << "[Destructor] FeeRecord destroyed for: " << *studentRef << "\n";
        delete studentRef;
    }

    // -= Operator (Payment)
    FeeRecord& operator-=(double payment) {
        if (payment <= 0) {
            cout << "  [Warning] Payment must be positive.\n";
            return *this;
        }
        if (payment > balance) {
            cout << "  [Warning] Amount exceeds balance!\n";
            payment = balance;
        }
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
