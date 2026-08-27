#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

// ============================================================
// CONSTANTS
// ============================================================

const string ACCOUNT_FILE = "accounts.txt";
const string TRANSACTION_FILE = "transactions.txt";

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Get current date: DD-MM-YYYY
string getCurrentDate()
{
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << localTime->tm_mday
       << "-"
       << setw(2) << localTime->tm_mon + 1
       << "-"
       << localTime->tm_year + 1900;

    return ss.str();
}

// Get current time: HH:MM:SS
string getCurrentTime()
{
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << localTime->tm_hour
       << ":"
       << setw(2) << localTime->tm_min
       << ":"
       << setw(2) << localTime->tm_sec;

    return ss.str();
}

// Get current month and year: MM-YYYY
string getCurrentMonth()
{
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << localTime->tm_mon + 1
       << "-"
       << localTime->tm_year + 1900;

    return ss.str();
}

// ============================================================
// TRANSACTION CLASS
// ============================================================

class Transaction
{
private:
    long long accountNumber;
    string date;
    string time;
    string type;
    double amount;
    double balanceAfter;

public:

    Transaction(
        long long accountNumber,
        const string& date,
        const string& time,
        const string& type,
        double amount,
        double balanceAfter)
        :
        accountNumber(accountNumber),
        date(date),
        time(time),
        type(type),
        amount(amount),
        balanceAfter(balanceAfter)
    {
    }

    long long getAccountNumber() const
    {
        return accountNumber;
    }

    string getDate() const
    {
        return date;
    }

    string getTime() const
    {
        return time;
    }

    string getType() const
    {
        return type;
    }

    double getAmount() const
    {
        return amount;
    }

    double getBalanceAfter() const
    {
        return balanceAfter;
    }

    // Convert transaction into file format
    string serialize() const
    {
        stringstream ss;

        ss << accountNumber << "|"
           << date << "|"
           << time << "|"
           << type << "|"
           << fixed << setprecision(2)
           << amount << "|"
           << balanceAfter;

        return ss.str();
    }
};

// ============================================================
// ACCOUNT CLASS
// ============================================================

class Account
{
private:

    long long accountNumber;
    string name;
    string phone;
    string address;
    string pin;
    double balance;

public:

    Account()
    {
        accountNumber = 0;
        balance = 0;
    }

    Account(
        long long accountNumber,
        const string& name,
        const string& phone,
        const string& address,
        const string& pin,
        double balance = 0.0)
        :
        accountNumber(accountNumber),
        name(name),
        phone(phone),
        address(address),
        pin(pin),
        balance(balance)
    {
    }

    // ========================================================
    // GETTERS
    // ========================================================

    long long getAccountNumber() const
    {
        return accountNumber;
    }

    string getName() const
    {
        return name;
    }

    string getPhone() const
    {
        return phone;
    }

    string getAddress() const
    {
        return address;
    }

    double getBalance() const
    {
        return balance;
    }

    // ========================================================
    // PIN AUTHENTICATION
    // ========================================================

    bool verifyPIN(const string& enteredPIN) const
    {
        return pin == enteredPIN;
    }

    void changePIN(const string& newPIN)
    {
        pin = newPIN;
    }

    // ========================================================
    // DEPOSIT
    // ========================================================

    bool deposit(double amount)
    {
        if (amount <= 0)
            return false;

        balance += amount;
        return true;
    }

    // ========================================================
    // WITHDRAW
    // ========================================================

    bool withdraw(double amount)
    {
        if (amount <= 0 || amount > balance)
            return false;

        balance -= amount;
        return true;
    }

    // ========================================================
    // DISPLAY ACCOUNT
    // ========================================================

    void display() const
    {
        cout << "\n========================================\n";
        cout << "          ACCOUNT DETAILS\n";
        cout << "========================================\n";

        cout << "Account Number : " << accountNumber << '\n';
        cout << "Account Holder : " << name << '\n';
        cout << "Phone          : " << phone << '\n';
        cout << "Address        : " << address << '\n';

        cout << "Balance        : Rs. "
             << fixed << setprecision(2)
             << balance << '\n';

        cout << "========================================\n";
    }

    // ========================================================
    // FILE SERIALIZATION
    // ========================================================

    string serialize() const
    {
        stringstream ss;

        ss << accountNumber << "|"
           << name << "|"
           << phone << "|"
           << address << "|"
           << pin << "|"
           << fixed << setprecision(2)
           << balance;

        return ss.str();
    }
};

// ============================================================
// BANK CLASS
// ============================================================

class Bank
{
private:

    vector<Account> accounts;
    vector<Transaction> transactions;

    long long nextAccountNumber = 100001;

public:

    // ========================================================
    // FILE HANDLING - LOAD ACCOUNTS
    // ========================================================

    void loadAccounts()
    {
        ifstream file(ACCOUNT_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string accountStr;
            string name;
            string phone;
            string address;
            string pin;
            string balanceStr;

            getline(ss, accountStr, '|');
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, address, '|');
            getline(ss, pin, '|');
            getline(ss, balanceStr, '|');

            long long accountNumber = stoll(accountStr);
            double balance = stod(balanceStr);

            accounts.emplace_back(
                accountNumber,
                name,
                phone,
                address,
                pin,
                balance
            );

            if (accountNumber >= nextAccountNumber)
                nextAccountNumber = accountNumber + 1;
        }

        file.close();
    }

    // ========================================================
    // FILE HANDLING - SAVE ACCOUNTS
    // ========================================================

    void saveAccounts()
    {
        ofstream file(ACCOUNT_FILE);

        for (const auto& account : accounts)
        {
            file << account.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD TRANSACTIONS
    // ========================================================

    void loadTransactions()
    {
        ifstream file(TRANSACTION_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string accountStr;
            string date;
            string time;
            string type;
            string amountStr;
            string balanceStr;

            getline(ss, accountStr, '|');
            getline(ss, date, '|');
            getline(ss, time, '|');
            getline(ss, type, '|');
            getline(ss, amountStr, '|');
            getline(ss, balanceStr, '|');

            transactions.emplace_back(
                stoll(accountStr),
                date,
                time,
                type,
                stod(amountStr),
                stod(balanceStr)
            );
        }

        file.close();
    }

    // ========================================================
    // SAVE TRANSACTION
    // ========================================================

    void saveTransaction(const Transaction& transaction)
    {
        ofstream file(
            TRANSACTION_FILE,
            ios::app
        );

        file << transaction.serialize() << '\n';

        file.close();

        transactions.push_back(transaction);
    }

    // ========================================================
    // FIND ACCOUNT
    // ========================================================

    Account* findAccount(long long accountNumber)
    {
        for (auto& account : accounts)
        {
            if (account.getAccountNumber() == accountNumber)
                return &account;
        }

        return nullptr;
    }

    // ========================================================
    // CREATE ACCOUNT
    // ========================================================

    void createAccount()
    {
        string name;
        string phone;
        string address;
        string pin;

        clearInput();

        cout << "\n========================================\n";
        cout << "          CREATE NEW ACCOUNT\n";
        cout << "========================================\n";

        cout << "Enter Full Name: ";
        getline(cin, name);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        cout << "Enter Address: ";
        getline(cin, address);

        do
        {
            cout << "Create 4-digit PIN: ";
            getline(cin, pin);

            if (pin.length() != 4 ||
                !all_of(pin.begin(), pin.end(), ::isdigit))
            {
                cout << "PIN must contain exactly 4 digits.\n";
            }

        } while (pin.length() != 4 ||
                 !all_of(pin.begin(), pin.end(), ::isdigit));

        Account newAccount(
            nextAccountNumber,
            name,
            phone,
            address,
            pin,
            0.0
        );

        accounts.push_back(newAccount);

        saveAccounts();

        cout << "\nAccount created successfully!\n";

        cout << "Your Account Number is: "
             << nextAccountNumber << '\n';

        cout << "Please remember your Account Number and PIN.\n";

        nextAccountNumber++;
    }

    // ========================================================
    // ACCOUNT LOGIN
    // ========================================================

    Account* accountLogin()
    {
        long long accountNumber;
        string pin;

        cout << "\n========================================\n";
        cout << "            ACCOUNT LOGIN\n";
        cout << "========================================\n";

        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cout << "Enter 4-digit PIN: ";
        cin >> pin;

        Account* account = findAccount(accountNumber);

        if (account != nullptr &&
            account->verifyPIN(pin))
        {
            cout << "\nLogin successful!\n";
            cout << "Welcome, "
                 << account->getName()
                 << "!\n";

            return account;
        }

        cout << "\nInvalid Account Number or PIN.\n";

        return nullptr;
    }

    // ========================================================
    // DEPOSIT
    // ========================================================

    void deposit(Account* account)
    {
        double amount;

        cout << "\nEnter amount to deposit: Rs. ";
        cin >> amount;

        if (!account->deposit(amount))
        {
            cout << "Invalid deposit amount.\n";
            return;
        }

        Transaction transaction(
            account->getAccountNumber(),
            getCurrentDate(),
            getCurrentTime(),
            "DEPOSIT",
            amount,
            account->getBalance()
        );

        saveTransaction(transaction);
        saveAccounts();

        cout << "\nDeposit successful!\n";

        cout << "Amount Deposited : Rs. "
             << fixed << setprecision(2)
             << amount << '\n';

        cout << "New Balance     : Rs. "
             << account->getBalance() << '\n';
    }

    // ========================================================
    // WITHDRAW
    // ========================================================

    void withdraw(Account* account)
    {
        double amount;

        cout << "\nEnter amount to withdraw: Rs. ";
        cin >> amount;

        if (amount <= 0)
        {
            cout << "Invalid withdrawal amount.\n";
            return;
        }

        if (amount > account->getBalance())
        {
            cout << "Insufficient balance.\n";
            return;
        }

        account->withdraw(amount);

        Transaction transaction(
            account->getAccountNumber(),
            getCurrentDate(),
            getCurrentTime(),
            "WITHDRAW",
            amount,
            account->getBalance()
        );

        saveTransaction(transaction);
        saveAccounts();

        cout << "\nWithdrawal successful!\n";

        cout << "Amount Withdrawn : Rs. "
             << fixed << setprecision(2)
             << amount << '\n';

        cout << "Remaining Balance: Rs. "
             << account->getBalance() << '\n';
    }

    // ========================================================
    // BALANCE INQUIRY
    // ========================================================

    void balanceInquiry(Account* account)
    {
        cout << "\n========================================\n";
        cout << "             BALANCE INQUIRY\n";
        cout << "========================================\n";

        cout << "Account Number : "
             << account->getAccountNumber()
             << '\n';

        cout << "Account Holder : "
             << account->getName()
             << '\n';

        cout << "Available Balance : Rs. "
             << fixed << setprecision(2)
             << account->getBalance()
             << '\n';

        cout << "========================================\n";
    }

    // ========================================================
    // TRANSACTION HISTORY
    // ========================================================

    void transactionHistory(Account* account)
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                  TRANSACTION HISTORY\n";
        cout << "============================================================\n";

        cout << left
             << setw(13) << "Date"
             << setw(10) << "Time"
             << setw(15) << "Type"
             << setw(15) << "Amount"
             << setw(15) << "Balance"
             << '\n';

        cout << string(68, '-') << '\n';

        bool found = false;

        for (const auto& transaction : transactions)
        {
            if (transaction.getAccountNumber() ==
                account->getAccountNumber())
            {
                found = true;

                cout << left
                     << setw(13) << transaction.getDate()
                     << setw(10) << transaction.getTime()
                     << setw(15) << transaction.getType()
                     << setw(15)
                     << fixed << setprecision(2)
                     << transaction.getAmount()
                     << setw(15)
                     << transaction.getBalanceAfter()
                     << '\n';
            }
        }

        if (!found)
        {
            cout << "No transactions found.\n";
        }

        cout << "============================================================\n";
    }

    // ========================================================
    // CHANGE PIN
    // ========================================================

    void changePIN(Account* account)
    {
        string oldPIN;
        string newPIN;

        cout << "\nEnter current PIN: ";
        cin >> oldPIN;

        if (!account->verifyPIN(oldPIN))
        {
            cout << "Incorrect current PIN.\n";
            return;
        }

        cout << "Enter new 4-digit PIN: ";
        cin >> newPIN;

        if (newPIN.length() != 4 ||
            !all_of(newPIN.begin(), newPIN.end(), ::isdigit))
        {
            cout << "PIN must contain exactly 4 digits.\n";
            return;
        }

        account->changePIN(newPIN);

        saveAccounts();

        cout << "\nPIN changed successfully!\n";
    }

    // ========================================================
    // MONTHLY STATEMENT
    // ========================================================

    void monthlyStatement(Account* account)
    {
        string month;

        cout << "\nEnter month for statement (MM-YYYY)\n";
        cout << "Example: 08-2026\n";
        cout << "Press 0 for current month.\n";

        cout << "Enter choice: ";
        cin >> month;

        if (month == "0")
            month = getCurrentMonth();

        string fileName =
            "Statement_" +
            to_string(account->getAccountNumber()) +
            "_" +
            month +
            ".txt";

        ofstream file(fileName);

        file << "==============================================\n";
        file << "             MONTHLY BANK STATEMENT\n";
        file << "==============================================\n";

        file << "Account Number : "
             << account->getAccountNumber()
             << '\n';

        file << "Account Holder : "
             << account->getName()
             << '\n';

        file << "Statement Month: "
             << month
             << '\n';

        file << "==============================================\n\n";

        file << left
             << setw(13) << "Date"
             << setw(10) << "Time"
             << setw(15) << "Type"
             << setw(15) << "Amount"
             << setw(15) << "Balance"
             << '\n';

        file << string(68, '-') << '\n';

        bool found = false;

        double totalDeposits = 0;
        double totalWithdrawals = 0;

        for (const auto& transaction : transactions)
        {
            if (transaction.getAccountNumber() ==
                    account->getAccountNumber() &&
                transaction.getDate().substr(3, 7) == month)
            {
                found = true;

                file << left
                     << setw(13) << transaction.getDate()
                     << setw(10) << transaction.getTime()
                     << setw(15) << transaction.getType()
                     << setw(15)
                     << fixed << setprecision(2)
                     << transaction.getAmount()
                     << setw(15)
                     << transaction.getBalanceAfter()
                     << '\n';

                if (transaction.getType() == "DEPOSIT")
                {
                    totalDeposits +=
                        transaction.getAmount();
                }
                else if (transaction.getType() == "WITHDRAW")
                {
                    totalWithdrawals +=
                        transaction.getAmount();
                }
            }
        }

        if (!found)
        {
            file << "No transactions found for this month.\n";
        }

        file << "\n==============================================\n";

        file << "Total Deposits    : Rs. "
             << fixed << setprecision(2)
             << totalDeposits
             << '\n';

        file << "Total Withdrawals : Rs. "
             << totalWithdrawals
             << '\n';

        file << "Current Balance   : Rs. "
             << account->getBalance()
             << '\n';

        file << "==============================================\n";

        file.close();

        cout << "\nMonthly statement generated successfully!\n";
        cout << "File: " << fileName << '\n';
    }

    // ========================================================
    // ADMIN LOGIN
    // ========================================================

    bool adminLogin()
    {
        string username;
        string password;

        clearInput();

        cout << "\n========================================\n";
        cout << "             ADMIN LOGIN\n";
        cout << "========================================\n";

        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if (username == ADMIN_USERNAME &&
            password == ADMIN_PASSWORD)
        {
            cout << "\nAdmin login successful!\n";
            return true;
        }

        cout << "\nInvalid admin credentials.\n";
        return false;
    }

    // ========================================================
    // ADMIN - DISPLAY ALL ACCOUNTS
    // ========================================================

    void displayAllAccounts()
    {
        cout << "\n";
        cout << "============================================================\n";
        cout << "                    ALL ACCOUNTS\n";
        cout << "============================================================\n";

        cout << left
             << setw(15) << "Account No."
             << setw(25) << "Name"
             << setw(18) << "Phone"
             << setw(15) << "Balance"
             << '\n';

        cout << string(73, '-') << '\n';

        for (const auto& account : accounts)
        {
            cout << left
                 << setw(15)
                 << account.getAccountNumber()
                 << setw(25)
                 << account.getName()
                 << setw(18)
                 << account.getPhone()
                 << setw(15)
                 << fixed << setprecision(2)
                 << account.getBalance()
                 << '\n';
        }

        cout << "============================================================\n";
    }

    // ========================================================
    // ADMIN - SEARCH ACCOUNT
    // ========================================================

    void searchAccount()
    {
        long long accountNumber;

        cout << "\nEnter Account Number: ";
        cin >> accountNumber;

        Account* account = findAccount(accountNumber);

        if (account == nullptr)
        {
            cout << "Account not found.\n";
            return;
        }

        account->display();
    }

    // ========================================================
    // ADMIN - TOTAL BANK BALANCE
    // ========================================================

    void bankSummary()
    {
        double totalBalance = 0;

        for (const auto& account : accounts)
        {
            totalBalance += account.getBalance();
        }

        cout << "\n========================================\n";
        cout << "             BANK SUMMARY\n";
        cout << "========================================\n";

        cout << "Total Accounts : "
             << accounts.size()
             << '\n';

        cout << "Total Deposits : Rs. "
             << fixed << setprecision(2)
             << totalBalance
             << '\n';

        cout << "Total Transactions : "
             << transactions.size()
             << '\n';

        cout << "========================================\n";
    }

    // ========================================================
    // ADMIN PANEL
    // ========================================================

    void adminPanel()
    {
        if (!adminLogin())
            return;

        int choice;

        do
        {
            cout << "\n========================================\n";
            cout << "             ADMIN PANEL\n";
            cout << "========================================\n";

            cout << "1. Display All Accounts\n";
            cout << "2. Search Account\n";
            cout << "3. Bank Summary\n";
            cout << "4. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    displayAllAccounts();
                    break;

                case 2:
                    searchAccount();
                    break;

                case 3:
                    bankSummary();
                    break;

                case 4:
                    cout << "\nAdmin logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 4);
    }

    // ========================================================
    // CUSTOMER MENU
    // ========================================================

    void customerMenu(Account* account)
    {
        int choice;

        do
        {
            cout << "\n========================================\n";
            cout << "           CUSTOMER DASHBOARD\n";
            cout << "========================================\n";

            cout << "Account: "
                 << account->getAccountNumber()
                 << '\n';

            cout << "\n";
            cout << "1. Deposit Money\n";
            cout << "2. Withdraw Money\n";
            cout << "3. Balance Inquiry\n";
            cout << "4. Transaction History\n";
            cout << "5. Generate Monthly Statement\n";
            cout << "6. Change PIN\n";
            cout << "7. Account Details\n";
            cout << "8. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    deposit(account);
                    break;

                case 2:
                    withdraw(account);
                    break;

                case 3:
                    balanceInquiry(account);
                    break;

                case 4:
                    transactionHistory(account);
                    break;

                case 5:
                    monthlyStatement(account);
                    break;

                case 6:
                    changePIN(account);
                    break;

                case 7:
                    account->display();
                    break;

                case 8:
                    cout << "\nLogged out successfully.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 8);
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        loadAccounts();
        loadTransactions();

        int choice;

        do
        {
            cout << "\n\n";
            cout << "============================================\n";
            cout << "         SMART BANK MANAGEMENT SYSTEM\n";
            cout << "============================================\n";

            cout << "1. Create Account\n";
            cout << "2. Customer Login\n";
            cout << "3. Admin Panel\n";
            cout << "4. Exit\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    createAccount();
                    break;

                case 2:
                {
                    Account* account = accountLogin();

                    if (account != nullptr)
                    {
                        customerMenu(account);
                    }

                    break;
                }

                case 3:
                    adminPanel();
                    break;

                case 4:
                    saveAccounts();

                    cout << "\n============================================\n";
                    cout << " Thank you for using Smart Bank System!\n";
                    cout << "============================================\n";

                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 4);
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    Bank bank;

    bank.run();

    return 0;
}