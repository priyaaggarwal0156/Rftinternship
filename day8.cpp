#include <iostream>
#include <string>
using namespace std;

class ATM {
private:
    string correctPin = "1234";
    double balance;
    int wrongAttempts;
    bool accountLocked;

public:
    // Constructor
    ATM(double initialBalance) {
        balance = initialBalance;
        wrongAttempts = 0;
        accountLocked = false;
    }

    // PIN validation
    bool validatePIN(string enteredPin) {

        if (accountLocked) {
            cout << "\nACCOUNT LOCKED due to 3 wrong PIN attempts.\n";
            return false;
        }

        if (enteredPin == correctPin) {
            cout << "\nLogin Successful!\n";
            wrongAttempts = 0; // reset attempts
            return true;
        }
        else {
            wrongAttempts++;

            cout << "\nInvalid PIN!\n";
            cout << "Failed Attempts: " << wrongAttempts << endl;

            // Logging failed attempts
            cout << "[LOG] Wrong PIN entered.\n";

            if (wrongAttempts >= 3) {
                accountLocked = true;
                cout << "\nToo many wrong attempts!\n";
                cout << "Your account has been LOCKED.\n";
            }

            return false;
        }
    }

    // Balance check
    void checkBalance() {
        cout << "\nCurrent Balance: Rs. " << balance << endl;
    }

    // Deposit money
    void deposit(double amount) {

        try {
            if (amount <= 0) {
                throw invalid_argument("Deposit amount must be positive.");
            }

            balance += amount;

            cout << "\nRs. " << amount << " deposited successfully.\n";
            cout << "Updated Balance: Rs. " << balance << endl;
        }

        catch (exception &e) {
            cout << "\nERROR: " << e.what() << endl;
        }
    }

    // Withdraw money
    void withdraw(double amount) {

        try {
            if (amount <= 0) {
                throw invalid_argument("Withdraw amount must be positive.");
            }

            if (amount > balance) {
                throw runtime_error("Insufficient Balance.");
            }

            balance -= amount;

            cout << "\nRs. " << amount << " withdrawn successfully.\n";
            cout << "Remaining Balance: Rs. " << balance << endl;
        }

        catch (exception &e) {
            cout << "\nERROR: " << e.what() << endl;
        }
    }
};

int main() {

    ATM user1(5000);

    string pin;
    int choice;
    double amount;

    cout << "=========== ATM SIMULATOR ===========\n";

    // PIN Authentication
    cout << "\nEnter ATM PIN: ";
    cin >> pin;

    if (!user1.validatePIN(pin)) {
        return 0;
    }

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            user1.checkBalance();
            break;

        case 2:
            cout << "\nEnter deposit amount: ";
            cin >> amount;
            user1.deposit(amount);
            break;

        case 3:
            cout << "\nEnter withdraw amount: ";
            cin >> amount;
            user1.withdraw(amount);
            break;

        case 4:
            cout << "\nThank You for using ATM!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}