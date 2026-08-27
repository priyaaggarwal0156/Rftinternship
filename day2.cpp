#include <iostream>
using namespace std;

class BankAccount {
private:
    int accNo;
    string name;
    double balance;
    const double MIN_BAL = 500;

public:
    // Constructor
    BankAccount(int a, string n, double b) {
        accNo = a;
        name = n;
        balance = b;
    }

    void deposit() {
        double amt;
        cout << "Enter amount to deposit: ";
        cin >> amt;

        if (amt > 0) {
            balance += amt;
            cout << "Deposit successful!\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    void withdraw() {
        double amt;
        cout << "Enter amount to withdraw: ";
        cin >> amt;

        if (amt > balance) {
            cout << "Insufficient balance!\n";
        }
        else if (balance - amt < MIN_BAL) {
            cout << "Minimum balance of 500 must be maintained!\n";
        }
        else {
            balance -= amt;
            cout << "Withdrawal successful!\n";
        }
    }

    void display() {
        cout << "\nAccount No: " << accNo
             << "\nName: " << name
             << "\nBalance: " << balance << endl;
    }
};

int main() {
    int n;
    cout << "Enter number of accounts: ";
    cin >> n;

    BankAccount* acc[n];

    // Input (separate prompts)
    for (int i = 0; i < n; i++) {
        int a;
        string name;
        double bal;

        cout << "\n--- Account " << i + 1 << " ---\n";

        cout << "Enter Account Number: ";
        cin >> a;

        cout << "Enter Holder Name: ";
        cin >> name;

        cout << "Enter Initial Balance: ";
        cin >> bal;

        acc[i] = new BankAccount(a, name, bal);
    }

    int choice, index;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Display Account\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            cout << "Enter account index (1-" << n << "): ";
            cin >> index;

            if (index < 1 || index > n) {
                cout << "Invalid index!\n";
                continue;
            }
        }

        switch (choice) {
            case 1:
                acc[index - 1]->deposit();
                break;

            case 2:
                acc[index - 1]->withdraw();
                break;

            case 3:
                acc[index - 1]->display();
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}