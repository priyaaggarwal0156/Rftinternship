# Rftinternship
This repository consist of code written by me during my C/C++ internship by Ruhil Future Technologies and Gow AI Academy

Day1- 
#include <iostream>
using namespace std;

class Student {
private:
    string name;
    int rollNo;
    float marks;

public:

    void inputDetails() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    char calculateGrade() {
        if (marks >= 75)
            return 'A';
        else if (marks >= 60)
            return 'B';
        else if (marks >= 40)
            return 'C';
        else
            return 'F';
    }

    void displayDetails() {
        cout << "\nName: " << name;
        cout << "\nRoll No: " << rollNo;
        cout << "\nMarks: " << marks;
        cout << "\nGrade: " << calculateGrade() << endl;
    }


    float getMarks() {
        return marks;
    }
};

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student s[n];


    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for student " << i + 1 << ":\n";
        s[i].inputDetails();
    }


    cout << "\n--- Student Records ---\n";
    for (int i = 0; i < n; i++) {
        s[i].displayDetails();
    }

    
    int topperIndex = 0;
    float total = 0;

    for (int i = 0; i < n; i++) {
        total += s[i].getMarks();
        if (s[i].getMarks() > s[topperIndex].getMarks()) {
            topperIndex = i;
        }
    }

    cout << "\n--- Class Topper ---\n";
    s[topperIndex].displayDetails();
    cout << "\nAverage Marks: " << total / n << endl;

    return 0;
}

Day 2:- (Bank account Simulator)
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

Day 3:- Project 3(Library System)
    #include <iostream>
#include <vector>
using namespace std;

class Item {
protected:
    int id;
    string title;
    bool issued;

public:
    Item(int i, string t) : id(i), title(t), issued(false) {}

    virtual void display() {
        cout << "ID: " << id << "\nTitle: " << title;
        cout << "\nStatus: " << (issued ? "Issued" : "Available") << endl;
    }

    void issue() {
        if (!issued) {
            issued = true;
            cout << "Item issued successfully.\n";
        } else {
            cout << "Item already issued.\n";
        }
    }

    void returnItem(int daysLate = 0) {
        if (issued) {
            issued = false;
            cout << "Item returned successfully.\n";

            if (daysLate > 0) {
                int fine = daysLate * 5; // simple fine
                cout << "Fine: Rs. " << fine << endl;
            }
        } else {
            cout << "Item was not issued.\n";
        }
    }

    bool isAvailable() {
        return !issued;
    }

    int getId() {
        return id;
    }
};

class Book : public Item {
    string author;

public:
    Book(int i, string t, string a) : Item(i, t), author(a) {}

    void display() override {
        Item::display();
        cout << "Author: " << author << endl;
    }
};

class Magazine : public Item {
    int issueNumber;

public:
    Magazine(int i, string t, int num) : Item(i, t), issueNumber(num) {}

    void display() override {
        Item::display();
        cout << "Issue Number: " << issueNumber << endl;
    }
};

// Helper function
Item* findItem(vector<Item*>& items, int id) {
    for (auto item : items) {
        if (item->getId() == id)
            return item;
    }
    return nullptr;
}

int main() {
    vector<Item*> library;
    int choice;

    do {
        cout << "\n--- Library Menu ---\n";
        cout << "1. Add Book\n2. Add Magazine\n3. Display All\n";
        cout << "4. Issue Item\n5. Return Item\n";
        cout << "6. Count Available Items\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string title, author;
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);

            library.push_back(new Book(id, title, author));
        }

        else if (choice == 2) {
            int id, issueNo;
            string title;
            cout << "Enter ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Issue Number: ";
            cin >> issueNo;

            library.push_back(new Magazine(id, title, issueNo));
        }

        else if (choice == 3) {
            for (auto item : library) {
                cout << "\n----------------\n";
                item->display();
            }
        }

        else if (choice == 4) {
            int id;
            cout << "Enter Item ID to issue: ";
            cin >> id;

            Item* item = findItem(library, id);
            if (item) item->issue();
            else cout << "Item not found.\n";
        }

        else if (choice == 5) {
            int id, daysLate;
            cout << "Enter Item ID to return: ";
            cin >> id;

            Item* item = findItem(library, id);
            if (item) {
                cout << "Enter days late (0 if none): ";
                cin >> daysLate;
                item->returnItem(daysLate);
            } else {
                cout << "Item not found.\n";
            }
        }

        else if (choice == 6) {
            int count = 0;
            for (auto item : library) {
                if (item->isAvailable()) count++;
            }
            cout << "Available items: " << count << endl;
        }

    } while (choice != 0);

    for (auto item : library)
        delete item;

    return 0;
}

Day 4:- (Employee Salary system)
#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>

using namespace std;

class Employee
{
protected:
    int empID;
    string name;

public:
    Employee(int id, string n)
    {
        empID = id;
        name = n;
    }


    virtual double calculateSalary() = 0;


    virtual void displayDetails()
    {
        cout << "\n-----------------------------------";
        cout << "\nEmployee ID   : " << empID;
        cout << "\nEmployee Name : " << name;
    }


    virtual ~Employee() {}
};

class FullTime : public Employee
{
private:
    double monthlySalary;
    double bonus;

public:
    FullTime(int id, string n, double salary, double b)
        : Employee(id, n)
    {
        monthlySalary = salary;
        bonus = b;
    }

    double calculateSalary() override
    {
        return monthlySalary + bonus;
    }

    void displayDetails() override
    {
        Employee::displayDetails();

        cout << "\nEmployee Type : Full Time";
        cout << "\nBase Salary   : Rs. " << monthlySalary;
        cout << "\nBonus         : Rs. " << bonus;
        cout << "\nTotal Salary  : Rs. " << calculateSalary();
        cout << "\n-----------------------------------\n";
    }
};

class PartTime : public Employee
{
private:
    int hoursWorked;
    double hourlyRate;

public:
    PartTime(int id, string n, int hours, double rate)
        : Employee(id, n)
    {
        hoursWorked = hours;
        hourlyRate = rate;
    }

    double calculateSalary() override
    {
        return hoursWorked * hourlyRate;
    }

    void displayDetails() override
    {
        Employee::displayDetails();

        cout << "\nEmployee Type : Part Time";
        cout << "\nHours Worked  : " << hoursWorked;
        cout << "\nHourly Rate   : Rs. " << hourlyRate;
        cout << "\nTotal Salary  : Rs. " << calculateSalary();
        cout << "\n-----------------------------------\n";
    }
};


int main()
{
    vector<unique_ptr<Employee>> employees;

    int choice, n;

    cout << "========================================";
    cout << "\n     EMPLOYEE SALARY MANAGEMENT SYSTEM";
    cout << "\n========================================";

    cout << "\nEnter number of employees: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int id;
        string name;

        cout << "\nEnter details for Employee " << i + 1;

        cout << "\nEnter Employee ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Employee Name: ";
        getline(cin, name);

        cout << "\n1. Full Time Employee";
        cout << "\n2. Part Time Employee";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            double salary, bonus;

            cout << "Enter Monthly Salary: ";
            cin >> salary;

            cout << "Enter Bonus: ";
            cin >> bonus;

            employees.push_back(
                make_unique<FullTime>(id, name, salary, bonus));
        }
        else if (choice == 2)
        {
            int hours;
            double rate;

            cout << "Enter Hours Worked: ";
            cin >> hours;

            cout << "Enter Hourly Rate: ";
            cin >> rate;

            employees.push_back(
                make_unique<PartTime>(id, name, hours, rate));
        }
        else
        {
            cout << "\nInvalid Choice!";
            i--;
        }
    }

    
    cout << "\n\n========== EMPLOYEE DETAILS ==========\n";

    double highestSalary = 0;
    string highestPaidEmployee;

    for (auto &emp : employees)
    {
        emp->displayDetails();

        if (emp->calculateSalary() > highestSalary)
        {
            highestSalary = emp->calculateSalary();
        }
    }

    cout << fixed << setprecision(2);

    cout << "\n========================================";
    cout << "\nHighest Salary : Rs. " << highestSalary;
    cout << "\n========================================";

    return 0;
}

Day 5:- (Mini Shopping cart System)
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// PRODUCT CLASS 
class Product
{
private:
    int productID;
    string productName;
    double price;
    int quantity;

public:
    Product(int id, string name, double p, int q)
    {
        productID = id;
        productName = name;
        price = p;
        quantity = q;
    }

    // Getters
    int getID() const
    {
        return productID;
    }

    string getName() const
    {
        return productName;
    }

    double getPrice() const
    {
        return price;
    }

    int getQuantity() const
    {
        return quantity;
    }

    // Calculate total price of product
    double getTotalPrice() const
    {
        return price * quantity;
    }

    // Display product details
    void displayProduct() const
    {
        cout << left << setw(10) << productID
             << setw(20) << productName
             << setw(12) << price
             << setw(10) << quantity
             << setw(12) << getTotalPrice()
             << endl;
    }
};

// CART CLASS 
class Cart
{
private:
    vector<Product> cartItems;

public:
    // Add product to cart
    void addProduct(Product p)
    {
        cartItems.push_back(p);
        cout << "\nProduct added successfully!\n";
    }

    // Remove product from cart
    void removeProduct(int id)
    {
        bool found = false;

        for (auto it = cartItems.begin(); it != cartItems.end(); it++)
        {
            if (it->getID() == id)
            {
                cartItems.erase(it);
                found = true;
                cout << "\nProduct removed successfully!\n";
                break;
            }
        }

        if (!found)
        {
            cout << "\nProduct not found!\n";
        }
    }

    // Display cart items
    void displayCart()
    {
        if (cartItems.empty())
        {
            cout << "\nCart is empty!\n";
            return;
        }

        cout << "\n================ SHOPPING CART ================\n";

        cout << left << setw(10) << "ID"
             << setw(20) << "Product"
             << setw(12) << "Price"
             << setw(10) << "Qty"
             << setw(12) << "Total"
             << endl;

        cout << "-------------------------------------------------------------\n";

        for (const auto &item : cartItems)
        {
            item.displayProduct();
        }
    }

    // Calculate total bill
    double calculateBill()
    {
        double total = 0;

        for (const auto &item : cartItems)
        {
            total += item.getTotalPrice();
        }

        return total;
    }

    // Display final bill with discount
    void displayBill()
    {
        double total = calculateBill();
        double discount = 0;

        // Bonus Feature: 10% discount if bill > 1000
        if (total > 1000)
        {
            discount = total * 0.10;
        }

        double finalAmount = total - discount;

        cout << fixed << setprecision(2);

        cout << "\n================ FINAL BILL ================\n";

        displayCart();

        cout << "\n--------------------------------------------";
        cout << "\nTotal Bill      : Rs. " << total;
        cout << "\nDiscount Applied: Rs. " << discount;
        cout << "\nFinal Amount    : Rs. " << finalAmount;
        cout << "\n============================================\n";
    }
};

// MAIN FUNCTION 
int main()
{
    Cart shoppingCart;

    int choice;

    do
    {
        cout << "\n========== MINI SHOPPING CART SYSTEM ==========\n";

        cout << "\n1. Add Product";
        cout << "\n2. Remove Product";
        cout << "\n3. Display Cart";
        cout << "\n4. Display Final Bill";
        cout << "\n5. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int id, quantity;
            string name;
            double price;

            cout << "\nEnter Product ID: ";
            cin >> id;

            cin.ignore();

            cout << "Enter Product Name: ";
            getline(cin, name);

            cout << "Enter Product Price: ";
            cin >> price;

            cout << "Enter Quantity: ";
            cin >> quantity;

            Product p(id, name, price, quantity);

            shoppingCart.addProduct(p);

            break;
        }

        case 2:
        {
            int id;

            cout << "\nEnter Product ID to Remove: ";
            cin >> id;

            shoppingCart.removeProduct(id);

            break;
        }

        case 3:
        {
            shoppingCart.displayCart();
            break;
        }

        case 4:
        {
            shoppingCart.displayBill();
            break;
        }

        case 5:
        {
            cout << "\nThank You for Using Shopping Cart System!\n";
            break;
        }

        default:
        {
            cout << "\nInvalid Choice! Please Try Again.\n";
        }
        }

    } while (choice != 5);

    return 0;
}


Day6:- (Safe calculator)
// PROJECT 6 - SAFE CALCULATOR
// Concepts Used:
// 1. Try-Catch
// 2. Input Validation
// 3. Exception Handling

#include <iostream>
#include <limits>
using namespace std;

// Function to clear invalid input
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    double num1, num2, result;
    char op;
    char choice;

    cout << "=============================\n";
    cout << "       SAFE CALCULATOR\n";
    cout << "=============================\n";

    do
    {
        try
        {
            // Input First Number
            cout << "\nEnter First Number: ";
            if (!(cin >> num1))
            {
                throw "Invalid Input! Please enter numeric values only.";
            }

            // Input Operator
            cout << "Enter Operator (+, -, *, /): ";
            cin >> op;

            // Check valid operator
            if (op != '+' && op != '-' && op != '*' && op != '/')
            {
                throw "Invalid Operator!";
            }

            // Input Second Number
            cout << "Enter Second Number: ";
            if (!(cin >> num2))
            {
                throw "Invalid Input! Please enter numeric values only.";
            }

            // Perform Calculation
            switch (op)
            {
                case '+':
                    result = num1 + num2;
                    break;

                case '-':
                    result = num1 - num2;
                    break;

                case '*':
                    result = num1 * num2;
                    break;

                case '/':
                    if (num2 == 0)
                    {
                        throw "Error! Division by Zero is not allowed.";
                    }
                    result = num1 / num2;
                    break;
            }

            // Display Result
            cout << "\nResult = " << result << endl;
        }

        // Exception Handling
        catch (const char* errorMessage)
        {
            cout << "\nException Caught: " << errorMessage << endl;
            clearInput();
        }

        // Continue Option
        cout << "\nDo you want to continue? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\nThank You for using Safe Calculator!\n";

    return 0;
}

Day 7:- (Secure Login SYSTEM)
#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

// Function to check password strength
bool isStrongPassword(string password)
{
    if (password.length() < 8)
        return false;

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (char ch : password)
    {
        if (isupper(ch))
            hasUpper = true;
        else if (islower(ch))
            hasLower = true;
        else if (isdigit(ch))
            hasDigit = true;
        else
            hasSpecial = true;
    }

    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int main()
{
    const string correctUsername = "admin";
    const string correctPassword = "Admin@123";

    string username, password;

    int attempts = 0;
    const int maxAttempts = 3;

    cout << "==============================" << endl;
    cout << "     SECURE LOGIN SYSTEM" << endl;
    cout << "==============================" << endl;

    // Password strength check
    cout << "\nChecking Password Strength..." << endl;

    if (isStrongPassword(correctPassword))
        cout << "Password is STRONG" << endl;
    else
        cout << "Password is WEAK" << endl;

    while (attempts < maxAttempts)
    {
        try
        {
            cout << "\nEnter Username: ";
            cin >> username;

            cout << "Enter Password: ";
            cin >> password;

            if (username == correctUsername &&
                password == correctPassword)
            {
                cout << "\nLOGIN SUCCESSFUL!" << endl;
                cout << "Welcome, " << username << endl;
                break;
            }
            else
            {
                attempts++;
                throw runtime_error("Invalid Username or Password!");
            }
        }
        catch (runtime_error &e)
        {
            cout << "\nERROR: " << e.what() << endl;

            int remaining = maxAttempts - attempts;

            if (remaining > 0)
            {
                cout << "Remaining Attempts: "
                     << remaining << endl;
            }
            else
            {
                cout << "\nSYSTEM LOCKED!" << endl;
                cout << "Too many failed attempts." << endl;
            }
        }
    }

    return 0;
} 

Day 8:- (ATM Simulator)
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

Day 9: (Student Input Validator)
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

/* ---------- CUSTOM EXCEPTION CLASSES ---------- */

class NameException {
public:
    string msg;
    NameException(string m) {
        msg = m;
    }
};

class AgeException {
public:
    string msg;
    AgeException(string m) {
        msg = m;
    }
};

class MarksException {
public:
    string msg;
    MarksException(string m) {
        msg = m;
    }
};

/* ---------- VALIDATION FUNCTIONS ---------- */

bool isValidName(string name) {

    if(name.empty())
        return false;

    for(char ch : name) {

        // Allow alphabets and spaces only
        if(!isalpha(ch) && ch != ' ') {
            return false;
        }
    }

    return true;
}

/* ---------- MAIN FUNCTION ---------- */

int main() {

    string name;
    int age;
    float marks;

    while(true) {

        vector<string> errors;

        cout << "\n========= STUDENT INPUT VALIDATOR =========\n";

        /* ---------- NAME INPUT ---------- */

        cout << "Enter Name : ";
        getline(cin, name);

        try {

            if(!isValidName(name)) {
                throw NameException(
                    "Name should contain only alphabets."
                );
            }

        }
        catch(NameException e) {
            errors.push_back(e.msg);
        }

        /* ---------- AGE INPUT ---------- */

        cout << "Enter Age : ";

        if(!(cin >> age)) {

            errors.push_back("Age must be a numeric value.");

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {

            try {

                if(age < 5 || age > 100) {

                    throw AgeException(
                        "Age must be between 5 and 100."
                    );
                }

            }
            catch(AgeException e) {
                errors.push_back(e.msg);
            }
        }

        /* ---------- MARKS INPUT ---------- */

        cout << "Enter Marks : ";

        if(!(cin >> marks)) {

            errors.push_back("Marks must be a numeric value.");

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {

            try {

                if(marks < 0 || marks > 100) {

                    throw MarksException(
                        "Marks must be between 0 and 100."
                    );
                }

            }
            catch(MarksException e) {
                errors.push_back(e.msg);
            }
        }

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        /* ---------- DISPLAY ALL ERRORS ---------- */

        if(!errors.empty()) {

            cout << "\n========== VALIDATION ERRORS ==========\n";

            for(string error : errors) {
                cout << "- " << error << endl;
            }

            cout << "\nPlease Re-Enter Correct Details.\n";

        }
        else {

            cout << "\n========== VALID DATA ENTERED ==========\n";

            cout << "Name  : " << name << endl;
            cout << "Age   : " << age << endl;
            cout << "Marks : " << marks << endl;

            cout << "\nStudent Record Saved Successfully!\n";

Day 10:- File based login system

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ================= ENCRYPTION FUNCTION =================
string encryptPassword(string password)
{
    string encrypted = "";

    for (char c : password)
    {
        encrypted += c + 3; // Simple Caesar Cipher Logic
    }

    return encrypted;
}

// ================= CHECK IF USER EXISTS =================
bool userExists(string username)
{
    ifstream file("users.txt");

    string storedUser, storedPass;

    while (file >> storedUser >> storedPass)
    {
        if (storedUser == username)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// ================= REGISTER FUNCTION =================
void registerUser()
{
    string username, password;

    cout << "\n===== REGISTER NEW USER =====\n";

    cout << "Enter Username: ";
    cin >> username;

    // Prevent Duplicate Usernames
    if (userExists(username))
    {
        cout << "ERROR: Username already exists!\n";
        return;
    }

    cout << "Enter Password: ";
    cin >> password;

    // Encrypt Password
    string encryptedPass = encryptPassword(password);

    ofstream file("users.txt", ios::app);

    if (!file)
    {
        cout << "ERROR: Unable to open file!\n";
        return;
    }

    file << username << " " << encryptedPass << endl;

    file.close();

    cout << "User Registered Successfully!\n";
}

// ================= LOGIN FUNCTION =================
void loginUser()
{
    string username, password;

    cout << "\n===== LOGIN SYSTEM =====\n";

    cout << "Enter Username: ";
    cin >> username;

    cout << "Enter Password: ";
    cin >> password;

    // Encrypt entered password
    string encryptedPass = encryptPassword(password);

    ifstream file("users.txt");

    // FILE NOT FOUND ERROR
    if (!file)
    {
        cout << "ERROR: users.txt file not found!\n";
        return;
    }

    // EMPTY FILE ERROR
    file.seekg(0, ios::end);

    if (file.tellg() == 0)
    {
        cout << "ERROR: File is empty!\n";
        file.close();
        return;
    }

    file.seekg(0, ios::beg);

    string storedUser, storedPass;
    bool found = false;

    while (file >> storedUser >> storedPass)
    {
        if (storedUser == username &&
            storedPass == encryptedPass)
        {
            found = true;
            break;
        }
    }

    file.close();

    // WRONG CREDENTIALS ERROR
    if (found)
    {
        cout << "LOGIN SUCCESSFUL!\n";
    }
    else
    {
        cout << "ERROR: Wrong Username or Password!\n";
    }
}

// ================= MAIN FUNCTION =================
int main()
{
    int choice;

    do
    {
        cout << "\n=============================\n";
        cout << " FILE-BASED LOGIN SYSTEM\n";
        cout << "=============================\n";

        cout << "1. Register User\n";
        cout << "2. Login User\n";
        cout << "3. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                cout << "Exiting Program...\n";
                break;

            default:
                cout << "Invalid Choice!\n";
        }

    } while (choice != 3);

    return 0;
}

            break;
        }
    }

    return 0;
}


Day 11:- (Text File Analyzer)
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    string filename;

    cout << "Enter file name: ";
    cin >> filename;

    ifstream file(filename);

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string line, word = "", longestWord = "";
    int lines = 0, words = 0, characters = 0;

    while (getline(file, line))
    {
        lines++;

        for (char ch : line)
        {
            characters++;

            if (isalnum(ch))
            {
                word += tolower(ch);
            }
            else
            {
                if (!word.empty())
                {
                    words++;

                    if (word.length() > longestWord.length())
                    {
                        longestWord = word;
                    }

                    word = "";
                }
            }
        }

        if (!word.empty())
        {
            words++;

            if (word.length() > longestWord.length())
            {
                longestWord = word;
            }

            word = "";
        }
    }

    file.close();

    cout << "\n----- FILE ANALYZER -----" << endl;
    cout << "Total Lines      : " << lines << endl;
    cout << "Total Words      : " << words << endl;
    cout << "Total Characters : " << characters << endl;
    cout << "Longest Word     : " << longestWord << endl;

    return 0;
}

Day 12:- (Student Record Manager (File based))
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student
{
private:
    int rollNo;
    char name[50];
    float marks;

public:
    void input()
    {
        cout << "\nEnter Roll Number : ";
        cin >> rollNo;

        cout << "Enter Name : ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "Enter Marks : ";
        cin >> marks;
    }

    void display()
    {
        cout << "\nRoll No : " << rollNo;
        cout << "\nName    : " << name;
        cout << "\nMarks   : " << marks << endl;
    }

    int getRollNo()
    {
        return rollNo;
    }
};

// Function to check duplicate roll number
bool isDuplicate(int roll)
{
    Student s;
    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.getRollNo() == roll)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Add Student
void addStudent()
{
    Student s;
    int roll;

    cout << "\nEnter Roll Number : ";
    cin >> roll;

    // Check duplicate roll number
    if (isDuplicate(roll))
    {
        cout << "\nRecord with this Roll Number already exists!\n";
        return;
    }

    ofstream file("students.dat", ios::binary | ios::app);

    // Re-enter complete details
    cout << "Enter Name : ";
    cin.ignore();
    char name[50];
    cin.getline(name, 50);

    float marks;
    cout << "Enter Marks : ";
    cin >> marks;

    // Temporary object
    Student temp;

    // Using direct memory assignment
    // Easier method
    *((int*)&temp) = roll;

    // Better method:
    // create properly using input again
    file.close();

    // Simpler approach
    s.input();

    ofstream file2("students.dat", ios::binary | ios::app);
    file2.write((char*)&s, sizeof(s));
    file2.close();

    cout << "\nStudent Record Added Successfully!\n";
}

// View All Students
void viewStudents()
{
    Student s;

    ifstream file("students.dat", ios::binary);

    if (!file)
    {
        cout << "\nFile not found!\n";
        return;
    }

    cout << "\n===== STUDENT RECORDS =====\n";

    while (file.read((char*)&s, sizeof(s)))
    {
        s.display();
    }

    file.close();
}

// Search Student
void searchStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Search : ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.getRollNo() == roll)
        {
            cout << "\nRecord Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nRecord Not Found!\n";
    }
}

// Update Student
void updateStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Update : ";
    cin >> roll;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.getRollNo() == roll)
        {
            cout << "\nEnter New Details:\n";
            s.input();

            int pos = file.tellg();
            file.seekp(pos - sizeof(s));

            file.write((char*)&s, sizeof(s));

            cout << "\nRecord Updated Successfully!\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nRecord Not Found!\n";
    }
}

// Delete Student
void deleteStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Delete : ";
    cin >> roll;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (file.read((char*)&s, sizeof(s)))
    {
        if (s.getRollNo() == roll)
        {
            found = true;
        }
        else
        {
            temp.write((char*)&s, sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "\nRecord Deleted Successfully!\n";
    else
        cout << "\nRecord Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n===== STUDENT RECORD MANAGER =====";
        cout << "\n1. Add Student";
        cout << "\n2. View All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\nEnter Choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            viewStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nExiting Program...\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}

Day 13:- (Log File Analyzer)
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to convert string into uppercase
string toUpperCase(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

int main()
{
    // Create sample log file automatically
    ofstream createFile("log.txt");

    createFile << "ERROR: DISK FULL" << endl;
    createFile << "INFO: STARTED" << endl;
    createFile << "WARNING: LOW MEMORY" << endl;
    createFile << "ERROR: FILE MISSING" << endl;
    createFile << "info: login successful" << endl;
    createFile << "warning: cpu usage high" << endl;
    createFile << "error: network failure" << endl;

    createFile.close();

    // Open log file for reading
    ifstream file("log.txt");

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string line;

    int errorCount = 0;
    int warningCount = 0;
    int infoCount = 0;

    vector<int> errorLines;

    int lineNumber = 0;

    // Read file line by line
    while (getline(file, line))
    {
        lineNumber++;

        // Convert line to uppercase
        string upperLine = toUpperCase(line);

        // Categorize log type
        if (upperLine.find("ERROR") != string::npos)
        {
            errorCount++;
            errorLines.push_back(lineNumber);
        }
        else if (upperLine.find("WARNING") != string::npos)
        {
            warningCount++;
        }
        else if (upperLine.find("INFO") != string::npos)
        {
            infoCount++;
        }
    }

    file.close();

    // Display report
    cout << "\n===== LOG ANALYSIS REPORT =====\n" << endl;

    cout << "ERROR Count   : " << errorCount << endl;
    cout << "WARNING Count : " << warningCount << endl;
    cout << "INFO Count    : " << infoCount << endl;

    // Find most frequent type
    cout << "\nMost Frequent Type : ";

    if (errorCount >= warningCount && errorCount >= infoCount)
    {
        cout << "ERROR";
    }
    else if (warningCount >= errorCount && warningCount >= infoCount)
    {
        cout << "WARNING";
    }
    else
    {
        cout << "INFO";
    }

    // Display ERROR line numbers
    cout << "\n\nLine Numbers of ERROR entries: ";

    for (int i = 0; i < errorLines.size(); i++)
    {
        cout << errorLines[i] << " ";
    }

    cout << endl;

    return 0;
}                

Day 14:- (Mini Search  Engine)
// PROJECT 4 - MINI SEARCH ENGINE (FILE-BASED)

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Function to convert string to lowercase
string toLowerCase(string str)
{
    for (char &c : str)
    {
        c = tolower(c);
    }
    return str;
}

// Function to remove punctuation
string cleanWord(string word)
{
    string cleaned = "";

    for (char c : word)
    {
        if (isalnum(c))
        {
            cleaned += tolower(c);
        }
    }

    return cleaned;
}

int main()
{
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    ifstream file(filename);

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    vector<string> lines;
    map<string, int> frequency;

    string line;
    int lineNumber = 0;

    // Read file and store lines
    while (getline(file, line))
    {
        lines.push_back(line);
        lineNumber++;

        stringstream ss(line);
        string word;

        while (ss >> word)
        {
            word = cleanWord(word);

            if (!word.empty())
            {
                frequency[word]++;
            }
        }
    }

    file.close();

    int choice;

    do
    {
        cout << "\n===== MINI SEARCH ENGINE =====" << endl;
        cout << "1. Search Single Word" << endl;
        cout << "2. Search Multiple Words" << endl;
        cout << "3. Show Top 5 Most Frequent Words" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        cin.ignore();

        if (choice == 1)
        {
            string searchWord;

            cout << "Enter word to search: ";
            getline(cin, searchWord);

            searchWord = cleanWord(searchWord);

            int count = 0;
            vector<int> foundLines;

            for (int i = 0; i < lines.size(); i++)
            {
                string temp = toLowerCase(lines[i]);

                stringstream ss(temp);
                string word;

                bool found = false;

                while (ss >> word)
                {
                    word = cleanWord(word);

                    if (word == searchWord)
                    {
                        count++;

                        if (!found)
                        {
                            foundLines.push_back(i + 1);
                            found = true;
                        }
                    }
                }
            }

            cout << "\nWord Found " << count << " times." << endl;

            if (count > 0)
            {
                cout << "Appears in line numbers: ";

                for (int num : foundLines)
                {
                    cout << num << " ";
                }

                cout << endl;
            }
            else
            {
                cout << "Word not found." << endl;
            }
        }

        else if (choice == 2)
        {
            string input;

            cout << "Enter multiple words: ";
            getline(cin, input);

            stringstream ss(input);
            string searchWord;

            while (ss >> searchWord)
            {
                searchWord = cleanWord(searchWord);

                int count = 0;

                cout << "\nSearching for: " << searchWord << endl;

                for (int i = 0; i < lines.size(); i++)
                {
                    string temp = toLowerCase(lines[i]);

                    stringstream lineSS(temp);
                    string word;

                    while (lineSS >> word)
                    {
                        word = cleanWord(word);

                        if (word == searchWord)
                        {
                            count++;
                        }
                    }
                }

                cout << "Occurrences: " << count << endl;
            }
        }

        else if (choice == 3)
        {
            vector<pair<string, int>> freqList;

            for (auto x : frequency)
            {
                freqList.push_back(x);
            }

            sort(freqList.begin(), freqList.end(),
                 [](pair<string, int> a, pair<string, int> b)
                 {
                     return a.second > b.second;
                 });

            cout << "\nTop 5 Most Frequent Words:\n";

            for (int i = 0; i < 5 && i < freqList.size(); i++)
            {
                cout << i + 1 << ". "
                     << freqList[i].first
                     << " --> "
                     << freqList[i].second
                     << " times" << endl;
            }
        }

        else if (choice == 4)
        {
            cout << "Program Exited." << endl;
        }

        else
        {
            cout << "Invalid Choice!" << endl;
        }

    } while (choice != 4);

    return 0;
}

Day 15:- (Custom stack implementation)
#include <iostream>
using namespace std;

class Stack {
private:
    int arr[100];
    int top;
    int maxSize;

public:
    // Constructor
    Stack(int size) {
        maxSize = size;
        top = -1;
    }

    // Push function
    void push(int x) {
        if (top == maxSize - 1) {
            cout << "Stack Overflow! Cannot push " << x << endl;
            return;
        }

        top++;
        arr[top] = x;
        cout << x << " pushed into stack." << endl;
    }

    // Pop function
    void pop() {
        if (top == -1) {
            cout << "Stack Underflow! Stack is empty." << endl;
            return;
        }

        cout << arr[top] << " popped from stack." << endl;
        top--;
    }

    // Peek function
    void peek() {
        if (top == -1) {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Top element: " << arr[top] << endl;
    }

    // Check if stack is empty
    bool isEmpty() {
        return (top == -1);
    }

    // Display stack
    void display() {
        if (top == -1) {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Stack elements are: ";
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Current size
    int currentSize() {
        return top + 1;
    }
};

int main() {
    int size;

    cout << "Enter stack size: ";
    cin >> size;

    Stack s(size);

    int choice, value;

    do {
        cout << "\n===== STACK MENU =====" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Peek" << endl;
        cout << "4. Check Empty" << endl;
        cout << "5. Display Stack" << endl;
        cout << "6. Current Size" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter value to push: ";
            cin >> value;
            s.push(value);
            break;

        case 2:
            s.pop();
            break;

        case 3:
            s.peek();
            break;

        case 4:
            if (s.isEmpty())
                cout << "Stack is empty." << endl;
            else
                cout << "Stack is not empty." << endl;
            break;

        case 5:
            s.display();
            break;

        case 6:
            cout << "Current stack size: "
                 << s.currentSize() << endl;
            break;

        case 7:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 7);

    return 0;
}

Day 16 (Queue Simulation Ticket System)
#include <iostream>
#include <string>
using namespace std;

class TicketQueue
{
private:
    int front;
    int rear;
    int size;
    int capacity;
    string *queue;

public:
    // Constructor
    TicketQueue(int cap)
    {
        capacity = cap;
        queue = new string[capacity];
        front = 0;
        rear = -1;
        size = 0;
    }

    // Check if queue is empty
    bool isEmpty()
    {
        return size == 0;
    }

    // Check if queue is full
    bool isFull()
    {
        return size == capacity;
    }

    // Add customer to queue
    void enqueue(string customer)
    {
        if (isFull())
        {
            cout << "\nQUEUE FULL! Cannot add more customers.\n";
            return;
        }

        rear = (rear + 1) % capacity; // Circular Queue Logic
        queue[rear] = customer;
        size++;

        cout << "\nCustomer Added Successfully!";
        cout << "\nTicket Issued To: " << customer << endl;
    }

    // Remove customer from queue
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "\nQUEUE EMPTY! No customers in queue.\n";
            return;
        }

        cout << "\nServing Customer: " << queue[front] << endl;

        front = (front + 1) % capacity; // Circular Queue Logic
        size--;
    }

    // Display queue
    void displayQueue()
    {
        if (isEmpty())
        {
            cout << "\nQUEUE EMPTY!\n";
            return;
        }

        cout << "\n===== CURRENT TICKET QUEUE =====\n";

        int index = front;

        for (int i = 0; i < size; i++)
        {
            cout << i + 1 << ". " << queue[index] << endl;
            index = (index + 1) % capacity;
        }
    }

    // Display front customer
    void frontCustomer()
    {
        if (isEmpty())
        {
            cout << "\nQUEUE EMPTY!\n";
            return;
        }

        cout << "\nNext Customer To Be Served: " << queue[front] << endl;
    }

    // Current queue size
    void currentSize()
    {
        cout << "\nCurrent Queue Size: " << size << endl;
    }

    // Destructor
    ~TicketQueue()
    {
        delete[] queue;
    }
};

int main()
{
    int capacity;

    cout << "=====================================\n";
    cout << "     TICKET COUNTER QUEUE SYSTEM     \n";
    cout << "=====================================\n";

    cout << "\nEnter Maximum Queue Capacity: ";
    cin >> capacity;

    TicketQueue tq(capacity);

    int choice;
    string customer;

    do
    {
        cout << "\n\n========= MENU =========\n";
        cout << "1. Add Customer (Enqueue)\n";
        cout << "2. Serve Customer (Dequeue)\n";
        cout << "3. Display Queue\n";
        cout << "4. Next Customer\n";
        cout << "5. Queue Size\n";
        cout << "6. Exit\n";
        cout << "========================\n";

        cout << "Enter Choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "\nEnter Customer Name: ";
            getline(cin, customer);

            tq.enqueue(customer);
            break;

        case 2:
            tq.dequeue();
            break;

        case 3:
            tq.displayQueue();
            break;

        case 4:
            tq.frontCustomer();
            break;

        case 5:
            tq.currentSize();
            break;

        case 6:
            cout << "\nExiting Ticket System...\n";
            cout << "Thank You!\n";
            break;

        default:
            cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}

Day 17:- {Contact book(Search + Delete)}
#include <iostream>
#include <string>

using namespace std;

class Contact {
public:
    string name;
    string phone;
};

class ContactBook {
private:
    Contact contacts[100];
    int count;

public:
    ContactBook() {
        count = 0;
    }

    // Add Contact
    void addContact() {
        if (count >= 100) {
            cout << "Contact Book Full!\n";
            return;
        }

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, contacts[count].name);

        cout << "Enter Phone Number: ";
        getline(cin, contacts[count].phone);

        count++;

        cout << "Contact Added Successfully!\n";
    }

    // Display All Contacts
    void displayContacts() {
        if (count == 0) {
            cout << "No Contacts Available!\n";
            return;
        }

        cout << "\n------ CONTACT LIST ------\n";

        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". "
                 << contacts[i].name
                 << " - "
                 << contacts[i].phone << endl;
        }
    }

    // Search Contact by Exact Name
    void searchContact() {
        if (count == 0) {
            cout << "No Contacts Available!\n";
            return;
        }

        cin.ignore();

        string searchName;
        bool found = false;

        cout << "Enter Name to Search: ";
        getline(cin, searchName);

        for (int i = 0; i < count; i++) {
            if (contacts[i].name == searchName) {
                cout << "\nContact Found!\n";
                cout << "Name  : " << contacts[i].name << endl;
                cout << "Phone : " << contacts[i].phone << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "Contact Not Found!\n";
        }
    }

    // Partial Name Search
    void partialSearch() {
        if (count == 0) {
            cout << "No Contacts Available!\n";
            return;
        }

        cin.ignore();

        string keyword;
        bool found = false;

        cout << "Enter Partial Name: ";
        getline(cin, keyword);

        cout << "\nMatching Contacts:\n";

        for (int i = 0; i < count; i++) {
            if (contacts[i].name.find(keyword) != string::npos) {
                cout << contacts[i].name
                     << " - "
                     << contacts[i].phone << endl;

                found = true;
            }
        }

        if (!found) {
            cout << "No Matching Contacts Found!\n";
        }
    }

    // Delete Contact
    void deleteContact() {
        if (count == 0) {
            cout << "No Contacts Available!\n";
            return;
        }

        cin.ignore();

        string deleteName;
        bool found = false;

        cout << "Enter Name to Delete: ";
        getline(cin, deleteName);

        for (int i = 0; i < count; i++) {
            if (contacts[i].name == deleteName) {

                // Shift Contacts Left
                for (int j = i; j < count - 1; j++) {
                    contacts[j] = contacts[j + 1];
                }

                count--;

                cout << "Contact Deleted Successfully!\n";

                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Contact Not Found!\n";
        }
    }

    // Sort Contacts Alphabetically
    void sortContacts() {
        if (count == 0) {
            cout << "No Contacts Available!\n";
            return;
        }

        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {

                if (contacts[i].name > contacts[j].name) {
                    Contact temp = contacts[i];
                    contacts[i] = contacts[j];
                    contacts[j] = temp;
                }
            }
        }

        cout << "Contacts Sorted Alphabetically!\n";
    }
};

int main() {

    ContactBook book;

    int choice;

    do {
        cout << "\n========== CONTACT BOOK ==========\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Partial Name Search\n";
        cout << "5. Delete Contact\n";
        cout << "6. Sort Contacts Alphabetically\n";
        cout << "7. Exit\n";

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            book.addContact();
            break;

        case 2:
            book.displayContacts();
            break;

        case 3:
            book.searchContact();
            break;

        case 4:
            book.partialSearch();
            break;

        case 5:
            book.deleteContact();
            break;

        case 6:
            book.sortContacts();
            break;

        case 7:
            cout << "Exiting Program...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}

Day 18:- Stack Application
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Stack {
private:
    int top;
    int arr[100];

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == 99;
    }

    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++top] = value;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return -1;
        }
        return arr[top--];
    }

    int peek() {
        if (isEmpty()) {
            return -1;
        }
        return arr[top];
    }

    int size() {
        return top + 1;
    }
};

// Function to perform operations
int performOperation(int op1, int op2, char symbol) {
    switch(symbol) {
        case '+':
            return op1 + op2;

        case '-':
            return op1 - op2;

        case '*':
            return op1 * op2;

        case '/':
            if(op2 == 0) {
                cout << "Division by zero error!" << endl;
                return 0;
            }
            return op1 / op2;

        case '%':
            return op1 % op2;

        default:
            cout << "Invalid Operator!" << endl;
            return 0;
    }
}

// Function to evaluate postfix expression
int evaluatePostfix(string expression) {
    Stack st;

    for (int i = 0; i < expression.length(); i++) {

        // Ignore spaces
        if (expression[i] == ' ')
            continue;

        // If digit found (supports multi-digit numbers)
        if (isdigit(expression[i])) {

            int number = 0;

            while (i < expression.length() && isdigit(expression[i])) {
                number = number * 10 + (expression[i] - '0');
                i++;
            }

            i--; // adjust index after loop
            st.push(number);
        }

        // If operator found
        else {

            // Invalid expression check
            if (st.size() < 2) {
                cout << "Invalid Expression!" << endl;
                return -1;
            }

            int op2 = st.pop();
            int op1 = st.pop();

            int result = performOperation(op1, op2, expression[i]);

            st.push(result);
        }
    }

    // Final validation
    if (st.size() != 1) {
        cout << "Invalid Expression!" << endl;
        return -1;
    }

    return st.pop();
}

int main() {

    string expression;

    cout << "===================================" << endl;
    cout << " POSTFIX EXPRESSION EVALUATOR " << endl;
    cout << "===================================" << endl;

    cout << "\nEnter Postfix Expression: ";
    getline(cin, expression);

    int result = evaluatePostfix(expression);

    if (result != -1) {
        cout << "\nResult = " << result << endl;
    }

    return 0;
}

Day 19:- (SIMPLE BROWSER HISTORY (STACK + LOGIC))
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class BrowserHistory {
private:
    stack<string> backStack;
    stack<string> forwardStack;

    string currentPage;
    int historyLimit;

public:
    // Constructor
    BrowserHistory(int limit = 5) {
        currentPage = "Home";
        historyLimit = limit;
    }

    // Visit New Page
    void visitPage(string url) {

        // Push current page into back stack
        if (currentPage != "") {

            // Limit history size
            if (backStack.size() >= historyLimit) {
                removeOldestHistory();
            }

            backStack.push(currentPage);
        }

        // New visit clears forward history
        clearForwardStack();

        currentPage = url;

        cout << "Visited: " << currentPage << endl;
    }

    // Go Back
    void goBack() {

        if (backStack.empty()) {
            cout << "No previous page available!" << endl;
            return;
        }

        forwardStack.push(currentPage);

        currentPage = backStack.top();
        backStack.pop();

        cout << "Went Back To: " << currentPage << endl;
    }

    // Go Forward
    void goForward() {

        if (forwardStack.empty()) {
            cout << "No forward page available!" << endl;
            return;
        }

        backStack.push(currentPage);

        currentPage = forwardStack.top();
        forwardStack.pop();

        cout << "Went Forward To: " << currentPage << endl;
    }

    // Display Current Page
    void displayCurrentPage() {
        cout << "\nCurrent Page: " << currentPage << endl;
    }

    // Display Full History
    void displayHistory() {

        cout << "\n===== BROWSER HISTORY =====" << endl;

        // Display Back History
        stack<string> tempBack = backStack;

        cout << "Back Stack: ";
        if (tempBack.empty()) {
            cout << "Empty";
        }

        while (!tempBack.empty()) {
            cout << tempBack.top() << " ";
            tempBack.pop();
        }

        cout << endl;

        // Current Page
        cout << "Current Page: " << currentPage << endl;

        // Display Forward History
        stack<string> tempForward = forwardStack;

        cout << "Forward Stack: ";
        if (tempForward.empty()) {
            cout << "Empty";
        }

        while (!tempForward.empty()) {
            cout << tempForward.top() << " ";
            tempForward.pop();
        }

        cout << endl;
    }

private:

    // Clear Forward Stack
    void clearForwardStack() {

        while (!forwardStack.empty()) {
            forwardStack.pop();
        }
    }

    // Remove Oldest History (Advanced Feature)
    void removeOldestHistory() {

        stack<string> temp;

        // Reverse stack
        while (!backStack.empty()) {
            temp.push(backStack.top());
            backStack.pop();
        }

        // Remove oldest page
        if (!temp.empty()) {
            temp.pop();
        }

        // Restore stack
        while (!temp.empty()) {
            backStack.push(temp.top());
            temp.pop();
        }
    }
};

int main() {

    BrowserHistory browser(5);

    int choice;
    string url;

    do {

        cout << "\n========== SIMPLE BROWSER ==========" << endl;
        cout << "1. Visit New Page" << endl;
        cout << "2. Go Back" << endl;
        cout << "3. Go Forward" << endl;
        cout << "4. Display Current Page" << endl;
        cout << "5. Display Full History" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter URL/Page Name: ";
            cin >> url;

            browser.visitPage(url);
            break;

        case 2:
            browser.goBack();
            break;

        case 3:
            browser.goForward();
            break;

        case 4:
            browser.displayCurrentPage();
            break;

        case 5:
            browser.displayHistory();
            break;

        case 6:
            cout << "Exiting Browser..." << endl;
            break;

        default:
            cout << "Invalid Choice!" << endl;
        }

    } while (choice != 6);

    return 0;
}

Day 20:-
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Student
{
private:
    int rollNo;
    char name[50];
    float marks;

public:
    void input()
    {
        cout << "\nEnter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display()
    {
        cout << "\n--------------------------------";
        cout << "\nRoll Number : " << rollNo;
        cout << "\nName        : " << name;
        cout << "\nMarks       : " << marks;
        cout << "\n--------------------------------";
    }

    int getRollNo()
    {
        return rollNo;
    }

    void writeToFile(ofstream &file)
    {
        file << rollNo << endl;
        file << name << endl;
        file << marks << endl;
    }

    void readFromFile(ifstream &file)
    {
        file >> rollNo;
        file.ignore();

        file.getline(name, 50);

        file >> marks;
        file.ignore();
    }
};

// FUNCTION DECLARATIONS
void addStudent(Student students[], int &count);
void displayStudents(Student students[], int count);
void searchStudent(Student students[], int count);
void deleteStudent(Student students[], int &count);
void saveToFile(Student students[], int count);
void loadFromFile(Student students[], int &count);

int main()
{
    Student students[100];
    int count = 0;
    int choice;

    // Load existing records at start
    loadFromFile(students, count);

    do
    {
        cout << "\n\n========== STUDENT MANAGEMENT SYSTEM ==========";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Save Records to File";
        cout << "\n6. Load Records from File";
        cout << "\n7. Exit";
        cout << "\n===============================================";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent(students, count);
            break;

        case 2:
            displayStudents(students, count);
            break;

        case 3:
            searchStudent(students, count);
            break;

        case 4:
            deleteStudent(students, count);
            break;

        case 5:
            saveToFile(students, count);
            break;

        case 6:
            loadFromFile(students, count);
            break;

        case 7:
            saveToFile(students, count);
            cout << "\nData Saved Successfully.";
            cout << "\nExiting Program...";
            break;

        default:
            cout << "\nInvalid Choice! Try Again.";
        }

    } while (choice != 7);

    return 0;
}

// FUNCTION DEFINITIONS

void addStudent(Student students[], int &count)
{
    if (count >= 100)
    {
        cout << "\nArray Full! Cannot Add More Students.";
        return;
    }

    cout << "\nEnter Student Details";
    students[count].input();
    count++;

    cout << "\nStudent Added Successfully.";
}

void displayStudents(Student students[], int count)
{
    if (count == 0)
    {
        cout << "\nNo Student Records Found.";
        return;
    }

    cout << "\n\n===== STUDENT RECORDS =====";

    for (int i = 0; i < count; i++)
    {
        students[i].display();
    }
}

void searchStudent(Student students[], int count)
{
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    for (int i = 0; i < count; i++)
    {
        if (students[i].getRollNo() == roll)
        {
            cout << "\nStudent Found!";
            students[i].display();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "\nStudent Not Found.";
    }
}

void deleteStudent(Student students[], int &count)
{
    int roll;
    bool found = false;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    for (int i = 0; i < count; i++)
    {
        if (students[i].getRollNo() == roll)
        {
            for (int j = i; j < count - 1; j++)
            {
                students[j] = students[j + 1];
            }

            count--;
            found = true;

            cout << "\nStudent Deleted Successfully.";
            break;
        }
    }

    if (!found)
    {
        cout << "\nStudent Not Found.";
    }
}

void saveToFile(Student students[], int count)
{
    ofstream file("students.txt");

    if (!file)
    {
        cout << "\nError Opening File.";
        return;
    }

    file << count << endl;

    for (int i = 0; i < count; i++)
    {
        students[i].writeToFile(file);
    }

    file.close();

    cout << "\nRecords Saved To File Successfully.";
}

void loadFromFile(Student students[], int &count)
{
    ifstream file("students.txt");

    if (!file)
    {
        return;
    }

    file >> count;
    file.ignore();

    for (int i = 0; i < count; i++)
    {
        students[i].readFromFile(file);
    }

    file.close();
}

Day 21:- (Code)
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// --------------------------------------------------
// 1. Swap using Pass by Value
// --------------------------------------------------
void swapByValue(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "Inside swapByValue(): "
         << "a = " << a << ", b = " << b << '\n';
}

// --------------------------------------------------
// 2. Swap using Pass by Reference
// --------------------------------------------------
void swapByReference(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// --------------------------------------------------
// 3. Return a value from a function
//    Finds the second-largest DISTINCT element
// --------------------------------------------------
int secondLargest(const vector<int>& arr)
{
    if (arr.size() < 2)
        throw invalid_argument("Array must contain at least two elements.");

    int largest = numeric_limits<int>::min();
    int second = numeric_limits<int>::min();

    for (int value : arr)
    {
        if (value > largest)
        {
            second = largest;
            largest = value;
        }
        else if (value > second && value < largest)
        {
            second = value;
        }
    }

    if (second == numeric_limits<int>::min())
        throw invalid_argument("No distinct second-largest element exists.");

    return second;
}

// --------------------------------------------------
// Main Function
// --------------------------------------------------
int main()
{
    // ----------------------------------------------
    // Task 1: Pass by Value
    // ----------------------------------------------
    int x = 10;
    int y = 20;

    cout << "Before swapByValue(): "
         << "x = " << x << ", y = " << y << '\n';

    swapByValue(x, y);

    cout << "After swapByValue():  "
         << "x = " << x << ", y = " << y << '\n';

    cout << "\nWhy didn't the original values change?\n";
    cout << "Because pass by value sends copies of x and y "
         << "to the function.\n";


    // ----------------------------------------------
    // Task 2: Pass by Reference
    // ----------------------------------------------
    cout << "\nBefore swapByReference(): "
         << "x = " << x << ", y = " << y << '\n';

    swapByReference(x, y);

    cout << "After swapByReference():  "
         << "x = " << x << ", y = " << y << '\n';

    cout << "\nWhy did the original values change?\n";
    cout << "Because references allow the function to directly "
         << "modify the original variables.\n";


    // ----------------------------------------------
    // Challenge: Second-largest element
    // ----------------------------------------------
    vector<int> arr = {10, 25, 7, 40, 18, 40, 32};

    cout << "\nArray: ";
    for (int value : arr)
        cout << value << ' ';

    try
    {
        int result = secondLargest(arr);
        cout << "\nSecond-largest element = " << result << '\n';
    }
    catch (const invalid_argument& e)
    {
        cout << "\nError: " << e.what() << '\n';
    }

    return 0;
}

Day 22:- (Smart Library Management System)
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <limits>

using namespace std;

// ============================================================
// CONSTANTS
// ============================================================

const int LOAN_DAYS = 14;
const double FINE_PER_DAY = 2.0;

// ============================================================
// HELPER FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getCurrentDate()
{
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    stringstream ss;
    ss << setfill('0')
       << setw(2) << localTime->tm_mday << "-"
       << setw(2) << localTime->tm_mon + 1 << "-"
       << localTime->tm_year + 1900;

    return ss.str();
}

time_t dateToTime(const string& date)
{
    int day, month, year;
    char separator;

    stringstream ss(date);
    ss >> day >> separator >> month >> separator >> year;

    tm timeInfo = {};
    timeInfo.tm_mday = day;
    timeInfo.tm_mon = month - 1;
    timeInfo.tm_year = year - 1900;
    timeInfo.tm_hour = 12;

    return mktime(&timeInfo);
}

int daysBetween(const string& startDate, const string& endDate)
{
    time_t start = dateToTime(startDate);
    time_t end = dateToTime(endDate);

    double difference = difftime(end, start);
    return static_cast<int>(difference / (60 * 60 * 24));
}

// ============================================================
// BOOK BASE CLASS
// ============================================================

class Book
{
protected:
    int id;
    string title;
    string author;
    bool issued;
    int issuedTo;
    string issueDate;

public:

    Book(int id, string title, string author)
        : id(id),
          title(title),
          author(author),
          issued(false),
          issuedTo(-1),
          issueDate("")
    {
    }

    virtual ~Book() = default;

    // -------- Getters --------

    int getId() const
    {
        return id;
    }

    string getTitle() const
    {
        return title;
    }

    string getAuthor() const
    {
        return author;
    }

    bool isIssued() const
    {
        return issued;
    }

    int getIssuedTo() const
    {
        return issuedTo;
    }

    string getIssueDate() const
    {
        return issueDate;
    }

    // -------- Issue Book --------

    bool issueBook(int memberId)
    {
        if (issued)
            return false;

        issued = true;
        issuedTo = memberId;
        issueDate = getCurrentDate();

        return true;
    }

    // -------- Return Book --------

    int returnBook()
    {
        if (!issued)
            return -1;

        string returnDate = getCurrentDate();

        int borrowedDays = daysBetween(issueDate, returnDate);

        int overdueDays = max(0, borrowedDays - LOAN_DAYS);

        issued = false;
        issuedTo = -1;
        issueDate = "";

        return overdueDays;
    }

    // -------- Polymorphic Functions --------

    virtual string getType() const = 0;

    virtual void display() const
    {
        cout << left
             << setw(6) << id
             << setw(28) << title
             << setw(22) << author
             << setw(15) << getType()
             << setw(15)
             << (issued ? "Issued" : "Available")
             << endl;
    }

    // -------- File Handling --------

    virtual string serialize() const
    {
        stringstream ss;

        ss << getType() << "|"
           << id << "|"
           << title << "|"
           << author << "|"
           << issued << "|"
           << issuedTo << "|"
           << issueDate;

        return ss.str();
    }

    void restoreIssueData(bool issuedStatus,
                          int memberId,
                          const string& date)
    {
        issued = issuedStatus;
        issuedTo = memberId;
        issueDate = date;
    }
};

// ============================================================
// DERIVED CLASS - PRINTED BOOK
// ============================================================

class PrintedBook : public Book
{
public:

    PrintedBook(int id, string title, string author)
        : Book(id, title, author)
    {
    }

    string getType() const override
    {
        return "Printed";
    }
};

// ============================================================
// DERIVED CLASS - E-BOOK
// ============================================================

class EBook : public Book
{
public:

    EBook(int id, string title, string author)
        : Book(id, title, author)
    {
    }

    string getType() const override
    {
        return "E-Book";
    }
};

// ============================================================
// MEMBER CLASS
// ============================================================

class Member
{
private:
    int id;
    string name;
    string password;

public:

    Member(int id, string name, string password)
        : id(id), name(name), password(password)
    {
    }

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    bool login(const string& enteredPassword) const
    {
        return password == enteredPassword;
    }

    string serialize() const
    {
        return to_string(id) + "|" + name + "|" + password;
    }
};

// ============================================================
// LIBRARY CLASS
// ============================================================

class Library
{
private:

    vector<unique_ptr<Book>> books;
    vector<Member> members;

    const string BOOK_FILE = "books.txt";
    const string MEMBER_FILE = "members.txt";

public:

    // ========================================================
    // FILE HANDLING
    // ========================================================

    void loadBooks()
    {
        ifstream file(BOOK_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string type;
            string idStr;
            string title;
            string author;
            string issuedStr;
            string issuedToStr;
            string issueDate;

            getline(ss, type, '|');
            getline(ss, idStr, '|');
            getline(ss, title, '|');
            getline(ss, author, '|');
            getline(ss, issuedStr, '|');
            getline(ss, issuedToStr, '|');
            getline(ss, issueDate, '|');

            int id = stoi(idStr);
            bool issued = stoi(issuedStr);
            int issuedTo = stoi(issuedToStr);

            if (type == "Printed")
            {
                books.push_back(
                    make_unique<PrintedBook>(id, title, author)
                );
            }
            else if (type == "E-Book")
            {
                books.push_back(
                    make_unique<EBook>(id, title, author)
                );
            }

            books.back()->restoreIssueData(
                issued,
                issuedTo,
                issueDate
            );
        }

        file.close();
    }

    void saveBooks()
    {
        ofstream file(BOOK_FILE);

        for (const auto& book : books)
        {
            file << book->serialize() << '\n';
        }

        file.close();
    }

    void loadMembers()
    {
        ifstream file(MEMBER_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string idStr;
            string name;
            string password;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, password, '|');

            members.emplace_back(
                stoi(idStr),
                name,
                password
            );
        }

        file.close();
    }

    void saveMembers()
    {
        ofstream file(MEMBER_FILE);

        for (const auto& member : members)
        {
            file << member.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // ADD BOOK
    // ========================================================

    void addBook()
    {
        int id;
        string title;
        string author;
        int type;

        cout << "\nEnter Book ID: ";
        cin >> id;

        if (findBook(id) != nullptr)
        {
            cout << "Book ID already exists.\n";
            return;
        }

        clearInput();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        cout << "\nSelect Book Type:\n";
        cout << "1. Printed Book\n";
        cout << "2. E-Book\n";
        cout << "Enter choice: ";
        cin >> type;

        if (type == 1)
        {
            books.push_back(
                make_unique<PrintedBook>(id, title, author)
            );
        }
        else if (type == 2)
        {
            books.push_back(
                make_unique<EBook>(id, title, author)
            );
        }
        else
        {
            cout << "Invalid book type.\n";
            return;
        }

        saveBooks();

        cout << "\nBook added successfully!\n";
    }

    // ========================================================
    // ADD MEMBER
    // ========================================================

    void addMember()
    {
        int id;
        string name;
        string password;

        cout << "\nEnter Member ID: ";
        cin >> id;

        if (findMember(id) != nullptr)
        {
            cout << "Member ID already exists.\n";
            return;
        }

        clearInput();

        cout << "Enter Member Name: ";
        getline(cin, name);

        cout << "Create Password: ";
        getline(cin, password);

        members.emplace_back(id, name, password);

        saveMembers();

        cout << "\nMember registered successfully!\n";
    }

    // ========================================================
    // FIND BOOK
    // ========================================================

    Book* findBook(int id)
    {
        for (auto& book : books)
        {
            if (book->getId() == id)
                return book.get();
        }

        return nullptr;
    }

    // ========================================================
    // FIND MEMBER
    // ========================================================

    Member* findMember(int id)
    {
        for (auto& member : members)
        {
            if (member.getId() == id)
                return &member;
        }

        return nullptr;
    }

    // ========================================================
    // DISPLAY ALL BOOKS
    // ========================================================

    void displayBooks()
    {
        if (books.empty())
        {
            cout << "\nNo books available in library.\n";
            return;
        }

        cout << "\n";
        cout << left
             << setw(6) << "ID"
             << setw(28) << "Title"
             << setw(22) << "Author"
             << setw(15) << "Type"
             << setw(15) << "Status"
             << '\n';

        cout << string(86, '-') << '\n';

        for (const auto& book : books)
        {
            book->display();
        }
    }

    // ========================================================
    // SEARCH BOOK
    // ========================================================

    void searchBooks()
    {
        if (books.empty())
        {
            cout << "\nNo books available.\n";
            return;
        }

        clearInput();

        string keyword;

        cout << "\nEnter title or author to search: ";
        getline(cin, keyword);

        transform(
            keyword.begin(),
            keyword.end(),
            keyword.begin(),
            ::tolower
        );

        bool found = false;

        cout << "\nSearch Results:\n";

        cout << left
             << setw(6) << "ID"
             << setw(28) << "Title"
             << setw(22) << "Author"
             << setw(15) << "Type"
             << setw(15) << "Status"
             << '\n';

        cout << string(86, '-') << '\n';

        for (const auto& book : books)
        {
            string title = book->getTitle();
            string author = book->getAuthor();

            transform(
                title.begin(),
                title.end(),
                title.begin(),
                ::tolower
            );

            transform(
                author.begin(),
                author.end(),
                author.begin(),
                ::tolower
            );

            if (title.find(keyword) != string::npos ||
                author.find(keyword) != string::npos)
            {
                book->display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No matching books found.\n";
        }
    }

    // ========================================================
    // ISSUE BOOK
    // ========================================================

    void issueBook(int memberId)
    {
        int bookId;

        cout << "\nEnter Book ID to issue: ";
        cin >> bookId;

        Book* book = findBook(bookId);

        if (book == nullptr)
        {
            cout << "Book not found.\n";
            return;
        }

        if (book->isIssued())
        {
            cout << "Book is already issued.\n";
            return;
        }

        if (book->issueBook(memberId))
        {
            saveBooks();

            cout << "\nBook issued successfully!\n";
            cout << "Issue Date: "
                 << book->getIssueDate() << '\n';

            cout << "Due Date: "
                 << "14 days from issue date.\n";
        }
    }

    // ========================================================
    // RETURN BOOK
    // ========================================================

    void returnBook(int memberId)
    {
        int bookId;

        cout << "\nEnter Book ID to return: ";
        cin >> bookId;

        Book* book = findBook(bookId);

        if (book == nullptr)
        {
            cout << "Book not found.\n";
            return;
        }

        if (!book->isIssued())
        {
            cout << "This book is not currently issued.\n";
            return;
        }

        if (book->getIssuedTo() != memberId)
        {
            cout << "This book was not issued to your account.\n";
            return;
        }

        int overdueDays = book->returnBook();

        double fine = overdueDays * FINE_PER_DAY;

        saveBooks();

        cout << "\nBook returned successfully!\n";

        if (overdueDays > 0)
        {
            cout << "Overdue Days : "
                 << overdueDays << '\n';

            cout << "Fine         : Rs. "
                 << fixed << setprecision(2)
                 << fine << '\n';
        }
        else
        {
            cout << "No fine. Book returned on time.\n";
        }
    }

    // ========================================================
    // AVAILABILITY REPORT
    // ========================================================

    void availabilityReport()
    {
        int total = books.size();
        int available = 0;
        int issued = 0;

        for (const auto& book : books)
        {
            if (book->isIssued())
                issued++;
            else
                available++;
        }

        cout << "\n====================================\n";
        cout << "       BOOK AVAILABILITY REPORT\n";
        cout << "====================================\n";

        cout << "Total Books     : " << total << '\n';
        cout << "Available Books : " << available << '\n';
        cout << "Issued Books    : " << issued << '\n';

        if (total > 0)
        {
            double percentage =
                (available * 100.0) / total;

            cout << "Availability    : "
                 << fixed << setprecision(2)
                 << percentage << "%\n";
        }

        cout << "====================================\n";
    }

    // ========================================================
    // MEMBER LOGIN
    // ========================================================

    int memberLogin()
    {
        int id;
        string password;

        cout << "\n========== MEMBER LOGIN ==========\n";

        cout << "Member ID: ";
        cin >> id;

        clearInput();

        cout << "Password: ";
        getline(cin, password);

        Member* member = findMember(id);

        if (member != nullptr &&
            member->login(password))
        {
            cout << "\nLogin successful!\n";
            cout << "Welcome, "
                 << member->getName()
                 << "!\n";

            return id;
        }

        cout << "\nInvalid Member ID or Password.\n";

        return -1;
    }

    // ========================================================
    // MEMBER MENU
    // ========================================================

    void memberMenu(int memberId)
    {
        int choice;

        do
        {
            cout << "\n====================================\n";
            cout << "          MEMBER DASHBOARD\n";
            cout << "====================================\n";

            cout << "1. Display All Books\n";
            cout << "2. Search Books\n";
            cout << "3. Issue Book\n";
            cout << "4. Return Book\n";
            cout << "5. Availability Report\n";
            cout << "6. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    displayBooks();
                    break;

                case 2:
                    searchBooks();
                    break;

                case 3:
                    issueBook(memberId);
                    break;

                case 4:
                    returnBook(memberId);
                    break;

                case 5:
                    availabilityReport();
                    break;

                case 6:
                    cout << "\nLogged out successfully.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 6);
    }

    // ========================================================
    // ADMIN MENU
    // ========================================================

    void adminMenu()
    {
        string password;

        clearInput();

        cout << "\nEnter Admin Password: ";
        getline(cin, password);

        if (password != "admin123")
        {
            cout << "Incorrect admin password.\n";
            return;
        }

        int choice;

        do
        {
            cout << "\n====================================\n";
            cout << "            ADMIN PANEL\n";
            cout << "====================================\n";

            cout << "1. Add Book\n";
            cout << "2. Register Member\n";
            cout << "3. Display All Books\n";
            cout << "4. Search Books\n";
            cout << "5. Availability Report\n";
            cout << "6. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    addBook();
                    break;

                case 2:
                    addMember();
                    break;

                case 3:
                    displayBooks();
                    break;

                case 4:
                    searchBooks();
                    break;

                case 5:
                    availabilityReport();
                    break;

                case 6:
                    cout << "\nLogged out successfully.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 6);
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        loadBooks();
        loadMembers();

        int choice;

        do
        {
            cout << "\n\n";
            cout << "============================================\n";
            cout << "       SMART LIBRARY MANAGEMENT SYSTEM\n";
            cout << "============================================\n";

            cout << "1. Member Login\n";
            cout << "2. Admin Login\n";
            cout << "3. Display Books\n";
            cout << "4. Search Books\n";
            cout << "5. Availability Report\n";
            cout << "6. Exit\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                {
                    int memberId = memberLogin();

                    if (memberId != -1)
                    {
                        memberMenu(memberId);
                    }

                    break;
                }

                case 2:
                    adminMenu();
                    break;

                case 3:
                    displayBooks();
                    break;

                case 4:
                    searchBooks();
                    break;

                case 5:
                    availabilityReport();
                    break;

                case 6:
                    saveBooks();
                    saveMembers();

                    cout << "\nThank you for using Smart Library!\n";
                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 6);
    }
};

// ============================================================
// MAIN
// ============================================================

int main()
{
    Library library;

    library.run();

    return 0;
}

Day 23:- (Bank Management System)
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

Day 24:- (Hospital Patient Management System)
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

// ============================================================
// FILES
// ============================================================

const string PATIENT_FILE = "patients.txt";
const string DOCTOR_FILE = "doctors.txt";
const string APPOINTMENT_FILE = "appointments.txt";
const string BILL_FILE = "bills.txt";

// ============================================================
// CONSTANTS
// ============================================================

const double REGISTRATION_FEE = 200.0;
const double BED_CHARGE_PER_DAY = 1500.0;
const double CONSULTATION_FEE = 500.0;

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string currentDate()
{
    time_t now = time(nullptr);
    tm* local = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << local->tm_mday
       << "-"
       << setw(2) << local->tm_mon + 1
       << "-"
       << local->tm_year + 1900;

    return ss.str();
}

string currentTime()
{
    time_t now = time(nullptr);
    tm* local = localtime(&now);

    stringstream ss;

    ss << setfill('0')
       << setw(2) << local->tm_hour
       << ":"
       << setw(2) << local->tm_min
       << ":"
       << setw(2) << local->tm_sec;

    return ss.str();
}

time_t dateToTime(const string& date)
{
    int day, month, year;
    char separator;

    stringstream ss(date);

    ss >> day >> separator >> month >> separator >> year;

    tm t = {};
    t.tm_mday = day;
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;
    t.tm_hour = 12;

    return mktime(&t);
}

int daysBetween(const string& start, const string& end)
{
    time_t startTime = dateToTime(start);
    time_t endTime = dateToTime(end);

    double difference =
        difftime(endTime, startTime);

    int days =
        static_cast<int>(
            difference / (60 * 60 * 24)
        );

    return max(1, days);
}

// ============================================================
// DOCTOR CLASS
// ============================================================

class Doctor
{
private:
    int id;
    string name;
    string specialization;
    bool available;

public:

    Doctor()
    {
        id = 0;
        available = true;
    }

    Doctor(
        int id,
        const string& name,
        const string& specialization,
        bool available = true)
        :
        id(id),
        name(name),
        specialization(specialization),
        available(available)
    {
    }

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    string getSpecialization() const
    {
        return specialization;
    }

    bool isAvailable() const
    {
        return available;
    }

    void setAvailability(bool status)
    {
        available = status;
    }

    void display() const
    {
        cout << left
             << setw(8) << id
             << setw(25) << name
             << setw(25) << specialization
             << setw(15)
             << (available ? "Available" : "Busy")
             << '\n';
    }

    string serialize() const
    {
        stringstream ss;

        ss << id << "|"
           << name << "|"
           << specialization << "|"
           << available;

        return ss.str();
    }
};

// ============================================================
// PATIENT CLASS
// ============================================================

class Patient
{
private:

    int id;
    string name;
    int age;
    string gender;
    string phone;
    string disease;

    int doctorId;
    bool admitted;

    string admissionDate;
    string dischargeDate;

    // Emergency priority
    int priority;

public:

    Patient()
    {
        id = 0;
        age = 0;
        doctorId = -1;
        admitted = false;
        priority = 5;
    }

    Patient(
        int id,
        const string& name,
        int age,
        const string& gender,
        const string& phone,
        const string& disease,
        int priority)
        :
        id(id),
        name(name),
        age(age),
        gender(gender),
        phone(phone),
        disease(disease),
        doctorId(-1),
        admitted(false),
        admissionDate(""),
        dischargeDate(""),
        priority(priority)
    {
    }

    // ========================================================
    // GETTERS
    // ========================================================

    int getId() const
    {
        return id;
    }

    string getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    string getGender() const
    {
        return gender;
    }

    string getPhone() const
    {
        return phone;
    }

    string getDisease() const
    {
        return disease;
    }

    int getDoctorId() const
    {
        return doctorId;
    }

    bool isAdmitted() const
    {
        return admitted;
    }

    string getAdmissionDate() const
    {
        return admissionDate;
    }

    string getDischargeDate() const
    {
        return dischargeDate;
    }

    int getPriority() const
    {
        return priority;
    }

    // ========================================================
    // DOCTOR ASSIGNMENT
    // ========================================================

    void assignDoctor(int id)
    {
        doctorId = id;
    }

    // ========================================================
    // ADMIT
    // ========================================================

    void admit()
    {
        admitted = true;
        admissionDate = currentDate();
        dischargeDate = "";
    }

    // ========================================================
    // DISCHARGE
    // ========================================================

    void discharge()
    {
        admitted = false;
        dischargeDate = currentDate();
    }

    // ========================================================
    // DISPLAY
    // ========================================================

    void display() const
    {
        cout << "\n============================================\n";
        cout << "              PATIENT RECORD\n";
        cout << "============================================\n";

        cout << "Patient ID       : " << id << '\n';
        cout << "Name             : " << name << '\n';
        cout << "Age              : " << age << '\n';
        cout << "Gender           : " << gender << '\n';
        cout << "Phone            : " << phone << '\n';
        cout << "Disease          : " << disease << '\n';

        cout << "Doctor ID        : ";

        if (doctorId == -1)
            cout << "Not Assigned\n";
        else
            cout << doctorId << '\n';

        cout << "Emergency Level  : "
             << priority << '\n';

        cout << "Status           : "
             << (admitted ? "Admitted" : "Not Admitted")
             << '\n';

        cout << "Admission Date   : "
             << (admissionDate.empty()
                 ? "N/A"
                 : admissionDate)
             << '\n';

        cout << "Discharge Date   : "
             << (dischargeDate.empty()
                 ? "N/A"
                 : dischargeDate)
             << '\n';

        cout << "============================================\n";
    }

    // ========================================================
    // FILE SERIALIZATION
    // ========================================================

    string serialize() const
    {
        stringstream ss;

        ss << id << "|"
           << name << "|"
           << age << "|"
           << gender << "|"
           << phone << "|"
           << disease << "|"
           << doctorId << "|"
           << admitted << "|"
           << admissionDate << "|"
           << dischargeDate << "|"
           << priority;

        return ss.str();
    }

    void restore(
        int doctor,
        bool admissionStatus,
        const string& admission,
        const string& discharge)
    {
        doctorId = doctor;
        admitted = admissionStatus;
        admissionDate = admission;
        dischargeDate = discharge;
    }
};

// ============================================================
// APPOINTMENT STRUCT
// ============================================================

struct Appointment
{
    int patientId;
    int doctorId;
    string date;
    string time;
    int priority;
};

// Priority queue comparator
struct AppointmentCompare
{
    bool operator()(
        const Appointment& a,
        const Appointment& b) const
    {
        // Lower priority number = higher priority

        if (a.priority != b.priority)
            return a.priority > b.priority;

        if (a.date != b.date)
            return a.date > b.date;

        return a.time > b.time;
    }
};

// ============================================================
// BILL CLASS
// ============================================================

class Bill
{
private:

    int patientId;
    double registrationFee;
    double consultationFee;
    double bedCharges;
    double total;

public:

    Bill(
        int patientId,
        double registrationFee,
        double consultationFee,
        double bedCharges)
        :
        patientId(patientId),
        registrationFee(registrationFee),
        consultationFee(consultationFee),
        bedCharges(bedCharges)
    {
        total =
            registrationFee +
            consultationFee +
            bedCharges;
    }

    double getTotal() const
    {
        return total;
    }

    void display() const
    {
        cout << "\n============================================\n";
        cout << "               PATIENT BILL\n";
        cout << "============================================\n";

        cout << "Patient ID          : "
             << patientId << '\n';

        cout << fixed << setprecision(2);

        cout << "Registration Fee    : Rs. "
             << registrationFee << '\n';

        cout << "Consultation Fee    : Rs. "
             << consultationFee << '\n';

        cout << "Bed Charges         : Rs. "
             << bedCharges << '\n';

        cout << "--------------------------------------------\n";

        cout << "TOTAL BILL          : Rs. "
             << total << '\n';

        cout << "============================================\n";
    }

    string serialize() const
    {
        stringstream ss;

        ss << patientId << "|"
           << registrationFee << "|"
           << consultationFee << "|"
           << bedCharges << "|"
           << total;

        return ss.str();
    }
};

// ============================================================
// HOSPITAL CLASS
// ============================================================

class Hospital
{
private:

    vector<Patient> patients;
    vector<Doctor> doctors;

    priority_queue<
        Appointment,
        vector<Appointment>,
        AppointmentCompare
    > appointmentQueue;

    int nextPatientId = 1001;

public:

    // ========================================================
    // LOAD PATIENTS
    // ========================================================

    void loadPatients()
    {
        ifstream file(PATIENT_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string idStr;
            string name;
            string ageStr;
            string gender;
            string phone;
            string disease;
            string doctorStr;
            string admittedStr;
            string admissionDate;
            string dischargeDate;
            string priorityStr;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, ageStr, '|');
            getline(ss, gender, '|');
            getline(ss, phone, '|');
            getline(ss, disease, '|');
            getline(ss, doctorStr, '|');
            getline(ss, admittedStr, '|');
            getline(ss, admissionDate, '|');
            getline(ss, dischargeDate, '|');
            getline(ss, priorityStr, '|');

            Patient patient(
                stoi(idStr),
                name,
                stoi(ageStr),
                gender,
                phone,
                disease,
                stoi(priorityStr)
            );

            patient.restore(
                stoi(doctorStr),
                stoi(admittedStr),
                admissionDate,
                dischargeDate
            );

            patients.push_back(patient);

            if (patient.getId() >= nextPatientId)
                nextPatientId = patient.getId() + 1;
        }

        file.close();
    }

    // ========================================================
    // SAVE PATIENTS
    // ========================================================

    void savePatients()
    {
        ofstream file(PATIENT_FILE);

        for (const auto& patient : patients)
        {
            file << patient.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD DOCTORS
    // ========================================================

    void loadDoctors()
    {
        ifstream file(DOCTOR_FILE);

        if (!file)
        {
            // Default doctors
            doctors.emplace_back(
                1,
                "Dr. Sharma",
                "General Medicine"
            );

            doctors.emplace_back(
                2,
                "Dr. Mehta",
                "Cardiology"
            );

            doctors.emplace_back(
                3,
                "Dr. Verma",
                "Neurology"
            );

            doctors.emplace_back(
                4,
                "Dr. Singh",
                "Orthopedics"
            );

            doctors.emplace_back(
                5,
                "Dr. Kapoor",
                "Pediatrics"
            );

            saveDoctors();

            return;
        }

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string idStr;
            string name;
            string specialization;
            string availabilityStr;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, specialization, '|');
            getline(ss, availabilityStr, '|');

            doctors.emplace_back(
                stoi(idStr),
                name,
                specialization,
                stoi(availabilityStr)
            );
        }

        file.close();
    }

    // ========================================================
    // SAVE DOCTORS
    // ========================================================

    void saveDoctors()
    {
        ofstream file(DOCTOR_FILE);

        for (const auto& doctor : doctors)
        {
            file << doctor.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // SAVE BILL
    // ========================================================

    void saveBill(const Bill& bill)
    {
        ofstream file(
            BILL_FILE,
            ios::app
        );

        file << bill.serialize() << '\n';

        file.close();
    }

    // ========================================================
    // FIND PATIENT
    // ========================================================

    Patient* findPatient(int patientId)
    {
        for (auto& patient : patients)
        {
            if (patient.getId() == patientId)
                return &patient;
        }

        return nullptr;
    }

    // ========================================================
    // FIND DOCTOR
    // ========================================================

    Doctor* findDoctor(int doctorId)
    {
        for (auto& doctor : doctors)
        {
            if (doctor.getId() == doctorId)
                return &doctor;
        }

        return nullptr;
    }

    // ========================================================
    // REGISTER PATIENT
    // ========================================================

    void registerPatient()
    {
        string name;
        int age;
        string gender;
        string phone;
        string disease;
        int priority;

        clearInput();

        cout << "\n============================================\n";
        cout << "             PATIENT REGISTRATION\n";
        cout << "============================================\n";

        cout << "Enter Patient Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        clearInput();

        cout << "Enter Gender: ";
        getline(cin, gender);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        cout << "Enter Disease/Problem: ";
        getline(cin, disease);

        // Emergency priority
        cout << "\nEmergency Priority:\n";
        cout << "1 - Critical Emergency\n";
        cout << "2 - Serious\n";
        cout << "3 - Moderate\n";
        cout << "4 - Mild\n";
        cout << "5 - Normal\n";

        do
        {
            cout << "Enter Priority Level: ";
            cin >> priority;

            if (priority < 1 || priority > 5)
                cout << "Please enter a value between 1 and 5.\n";

        } while (priority < 1 || priority > 5);

        Patient patient(
            nextPatientId,
            name,
            age,
            gender,
            phone,
            disease,
            priority
        );

        patients.push_back(patient);

        savePatients();

        cout << "\nPatient registered successfully!\n";

        cout << "Patient ID: "
             << nextPatientId << '\n';

        nextPatientId++;
    }

    // ========================================================
    // DISPLAY DOCTORS
    // ========================================================

    void displayDoctors()
    {
        cout << "\n";
        cout << "========================================================\n";
        cout << "                    DOCTOR LIST\n";
        cout << "========================================================\n";

        cout << left
             << setw(8) << "ID"
             << setw(25) << "Name"
             << setw(25) << "Specialization"
             << setw(15) << "Status"
             << '\n';

        cout << string(73, '-') << '\n';

        for (const auto& doctor : doctors)
        {
            doctor.display();
        }

        cout << "========================================================\n";
    }

    // ========================================================
    // ASSIGN DOCTOR
    // ========================================================

    void assignDoctor()
    {
        int patientId;
        int doctorId;

        cout << "\nEnter Patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found.\n";
            return;
        }

        displayDoctors();

        cout << "\nEnter Doctor ID: ";
        cin >> doctorId;

        Doctor* doctor = findDoctor(doctorId);

        if (doctor == nullptr)
        {
            cout << "Doctor not found.\n";
            return;
        }

        if (!doctor->isAvailable())
        {
            cout << "Doctor is currently busy.\n";
            return;
        }

        patient->assignDoctor(doctorId);

        doctor->setAvailability(false);

        savePatients();
        saveDoctors();

        cout << "\nDoctor assigned successfully!\n";

        cout << "Doctor: "
             << doctor->getName()
             << '\n';
    }

    // ========================================================
    // ADMIT PATIENT
    // ========================================================

    void admitPatient()
    {
        int patientId;

        cout << "\nEnter Patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found.\n";
            return;
        }

        if (patient->isAdmitted())
        {
            cout << "Patient is already admitted.\n";
            return;
        }

        patient->admit();

        savePatients();

        cout << "\nPatient admitted successfully!\n";

        cout << "Admission Date: "
             << patient->getAdmissionDate()
             << '\n';
    }

    // ========================================================
    // DISCHARGE PATIENT
    // ========================================================

    void dischargePatient()
    {
        int patientId;

        cout << "\nEnter Patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found.\n";
            return;
        }

        if (!patient->isAdmitted())
        {
            cout << "Patient is not currently admitted.\n";
            return;
        }

        patient->discharge();

        // Make assigned doctor available
        if (patient->getDoctorId() != -1)
        {
            Doctor* doctor =
                findDoctor(patient->getDoctorId());

            if (doctor != nullptr)
            {
                doctor->setAvailability(true);
            }
        }

        savePatients();
        saveDoctors();

        cout << "\nPatient discharged successfully!\n";

        cout << "Discharge Date: "
             << patient->getDischargeDate()
             << '\n';

        // Generate bill
        generateBill(patient);
    }

    // ========================================================
    // SEARCH PATIENT
    // ========================================================

    void searchPatient()
    {
        int patientId;

        cout << "\nEnter Patient ID: ";
        cin >> patientId;

        Patient* patient = findPatient(patientId);

        if (patient == nullptr)
        {
            cout << "Patient not found.\n";
            return;
        }

        patient->display();
    }

    // ========================================================
    // DISPLAY ALL PATIENTS
    // ========================================================

    void displayPatients()
    {
        if (patients.empty())
        {
            cout << "\nNo patient records available.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================================\n";
        cout << "                       PATIENT RECORDS\n";
        cout << "====================================================================\n";

        cout << left
             << setw(8) << "ID"
             << setw(22) << "Name"
             << setw(6) << "Age"
             << setw(15) << "Disease"
             << setw(12) << "Doctor"
             << setw(12) << "Status"
             << setw(8) << "Priority"
             << '\n';

        cout << string(83, '-') << '\n';

        for (const auto& patient : patients)
        {
            cout << left
                 << setw(8) << patient.getId()
                 << setw(22) << patient.getName()
                 << setw(6) << patient.getAge()
                 << setw(15) << patient.getDisease();

            if (patient.getDoctorId() == -1)
                cout << setw(12) << "None";
            else
                cout << setw(12) << patient.getDoctorId();

            cout << setw(12)
                 << (patient.isAdmitted()
                     ? "Admitted"
                     : "Discharged");

            cout << setw(8)
                 << patient.getPriority()
                 << '\n';
        }

        cout << "====================================================================\n";
    }

    // ========================================================
    // GENERATE BILL
    // ========================================================

    void generateBill(Patient* patient)
    {
        double bedCharges = 0;

        if (!patient->getAdmissionDate().empty())
        {
            string dischargeDate =
                patient->getDischargeDate();

            int days =
                daysBetween(
                    patient->getAdmissionDate(),
                    dischargeDate
                );

            bedCharges =
                days * BED_CHARGE_PER_DAY;
        }

        Bill bill(
            patient->getId(),
            REGISTRATION_FEE,
            CONSULTATION_FEE,
            bedCharges
        );

        bill.display();

        saveBill(bill);
    }

    // ========================================================
    // APPOINTMENT QUEUE
    // ========================================================

    void addAppointment()
    {
        int patientId;
        int doctorId;
        string date;
        string time;

        cout << "\nEnter Patient ID: ";
        cin >> patientId;

        if (findPatient(patientId) == nullptr)
        {
            cout << "Patient not found.\n";
            return;
        }

        displayDoctors();

        cout << "\nEnter Doctor ID: ";
        cin >> doctorId;

        if (findDoctor(doctorId) == nullptr)
        {
            cout << "Doctor not found.\n";
            return;
        }

        clearInput();

        cout << "Enter Appointment Date (DD-MM-YYYY): ";
        getline(cin, date);

        cout << "Enter Appointment Time (HH:MM): ";
        getline(cin, time);

        Patient* patient =
            findPatient(patientId);

        Appointment appointment;

        appointment.patientId = patientId;
        appointment.doctorId = doctorId;
        appointment.date = date;
        appointment.time = time;
        appointment.priority =
            patient->getPriority();

        appointmentQueue.push(appointment);

        saveAppointment(appointment);

        cout << "\nAppointment added successfully!\n";
    }

    // ========================================================
    // SAVE APPOINTMENT
    // ========================================================

    void saveAppointment(
        const Appointment& appointment)
    {
        ofstream file(
            APPOINTMENT_FILE,
            ios::app
        );

        file << appointment.patientId << "|"
             << appointment.doctorId << "|"
             << appointment.date << "|"
             << appointment.time << "|"
             << appointment.priority
             << '\n';

        file.close();
    }

    // ========================================================
    // LOAD APPOINTMENTS
    // ========================================================

    void loadAppointments()
    {
        ifstream file(APPOINTMENT_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string patientStr;
            string doctorStr;
            string date;
            string time;
            string priorityStr;

            getline(ss, patientStr, '|');
            getline(ss, doctorStr, '|');
            getline(ss, date, '|');
            getline(ss, time, '|');
            getline(ss, priorityStr, '|');

            Appointment appointment;

            appointment.patientId =
                stoi(patientStr);

            appointment.doctorId =
                stoi(doctorStr);

            appointment.date = date;
            appointment.time = time;

            appointment.priority =
                stoi(priorityStr);

            appointmentQueue.push(appointment);
        }

        file.close();
    }

    // ========================================================
    // VIEW APPOINTMENT QUEUE
    // ========================================================

    void displayAppointmentQueue()
    {
        if (appointmentQueue.empty())
        {
            cout << "\nNo appointments in queue.\n";
            return;
        }

        // Copy queue so original remains unchanged
        auto temp = appointmentQueue;

        cout << "\n";
        cout << "============================================================\n";
        cout << "                 APPOINTMENT QUEUE\n";
        cout << "============================================================\n";

        cout << left
             << setw(12) << "Patient ID"
             << setw(12) << "Doctor ID"
             << setw(15) << "Date"
             << setw(10) << "Time"
             << setw(10) << "Priority"
             << '\n';

        cout << string(59, '-') << '\n';

        while (!temp.empty())
        {
            Appointment appointment =
                temp.top();

            temp.pop();

            cout << left
                 << setw(12)
                 << appointment.patientId
                 << setw(12)
                 << appointment.doctorId
                 << setw(15)
                 << appointment.date
                 << setw(10)
                 << appointment.time
                 << setw(10)
                 << appointment.priority
                 << '\n';
        }

        cout << "============================================================\n";
    }

    // ========================================================
    // SERVE NEXT APPOINTMENT
    // ========================================================

    void serveNextAppointment()
    {
        if (appointmentQueue.empty())
        {
            cout << "\nNo appointments waiting.\n";
            return;
        }

        Appointment next =
            appointmentQueue.top();

        appointmentQueue.pop();

        cout << "\n============================================\n";
        cout << "          NEXT PATIENT TO SERVE\n";
        cout << "============================================\n";

        cout << "Patient ID : "
             << next.patientId << '\n';

        cout << "Doctor ID  : "
             << next.doctorId << '\n';

        cout << "Date       : "
             << next.date << '\n';

        cout << "Time       : "
             << next.time << '\n';

        cout << "Priority   : "
             << next.priority << '\n';

        cout << "============================================\n";

        cout << "Patient served and removed from queue.\n";
    }

    // ========================================================
    // EMERGENCY PRIORITY LIST
    // ========================================================

    void emergencyPriorityList()
    {
        vector<Patient> emergencyPatients;

        for (const auto& patient : patients)
        {
            emergencyPatients.push_back(patient);
        }

        sort(
            emergencyPatients.begin(),
            emergencyPatients.end(),
            [](const Patient& a, const Patient& b)
            {
                return a.getPriority() <
                       b.getPriority();
            }
        );

        cout << "\n";
        cout << "============================================================\n";
        cout << "              EMERGENCY PRIORITY SYSTEM\n";
        cout << "============================================================\n";

        cout << left
             << setw(10) << "Priority"
             << setw(12) << "Patient ID"
             << setw(25) << "Name"
             << setw(20) << "Disease"
             << setw(15) << "Status"
             << '\n';

        cout << string(82, '-') << '\n';

        for (const auto& patient :
             emergencyPatients)
        {
            cout << left
                 << setw(10)
                 << patient.getPriority()
                 << setw(12)
                 << patient.getId()
                 << setw(25)
                 << patient.getName()
                 << setw(20)
                 << patient.getDisease()
                 << setw(15)
                 << (patient.isAdmitted()
                     ? "Admitted"
                     : "Waiting")
                 << '\n';
        }

        cout << "============================================================\n";

        cout << "\nPriority Meaning:\n";
        cout << "1 = Critical Emergency\n";
        cout << "2 = Serious\n";
        cout << "3 = Moderate\n";
        cout << "4 = Mild\n";
        cout << "5 = Normal\n";
    }

    // ========================================================
    // ADMIN MENU
    // ========================================================

    void adminMenu()
    {
        string password;

        clearInput();

        cout << "\nEnter Admin Password: ";
        getline(cin, password);

        if (password != "hospital123")
        {
            cout << "Incorrect password.\n";
            return;
        }

        int choice;

        do
        {
            cout << "\n============================================\n";
            cout << "              HOSPITAL ADMIN PANEL\n";
            cout << "============================================\n";

            cout << "1. Display All Patients\n";
            cout << "2. Display Doctors\n";
            cout << "3. Search Patient\n";
            cout << "4. Appointment Queue\n";
            cout << "5. Emergency Priority List\n";
            cout << "6. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    displayPatients();
                    break;

                case 2:
                    displayDoctors();
                    break;

                case 3:
                    searchPatient();
                    break;

                case 4:
                    displayAppointmentQueue();
                    break;

                case 5:
                    emergencyPriorityList();
                    break;

                case 6:
                    cout << "\nAdmin logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 6);
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        loadPatients();
        loadDoctors();
        loadAppointments();

        int choice;

        do
        {
            cout << "\n\n";
            cout << "================================================\n";
            cout << "       HOSPITAL PATIENT MANAGEMENT SYSTEM\n";
            cout << "================================================\n";

            cout << "1. Register Patient\n";
            cout << "2. Assign Doctor\n";
            cout << "3. Admit Patient\n";
            cout << "4. Discharge Patient\n";
            cout << "5. Search Patient\n";
            cout << "6. Display Patient Records\n";
            cout << "7. Display Doctors\n";
            cout << "8. Generate Patient Bill\n";
            cout << "9. Add Appointment\n";
            cout << "10. View Appointment Queue\n";
            cout << "11. Serve Next Appointment\n";
            cout << "12. Emergency Priority System\n";
            cout << "13. Admin Panel\n";
            cout << "14. Exit\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    registerPatient();
                    break;

                case 2:
                    assignDoctor();
                    break;

                case 3:
                    admitPatient();
                    break;

                case 4:
                    dischargePatient();
                    break;

                case 5:
                    searchPatient();
                    break;

                case 6:
                    displayPatients();
                    break;

                case 7:
                    displayDoctors();
                    break;

                case 8:
                {
                    int patientId;

                    cout << "\nEnter Patient ID: ";
                    cin >> patientId;

                    Patient* patient =
                        findPatient(patientId);

                    if (patient == nullptr)
                    {
                        cout << "Patient not found.\n";
                    }
                    else
                    {
                        generateBill(patient);
                    }

                    break;
                }

                case 9:
                    addAppointment();
                    break;

                case 10:
                    displayAppointmentQueue();
                    break;

                case 11:
                    serveNextAppointment();
                    break;

                case 12:
                    emergencyPriorityList();
                    break;

                case 13:
                    adminMenu();
                    break;

                case 14:
                    savePatients();
                    saveDoctors();

                    cout << "\n============================================\n";
                    cout << " Thank you for using Hospital Management System!\n";
                    cout << "============================================\n";

                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 14);
    }
};

// ============================================================
// MAIN
// ============================================================

int main()
{
    Hospital hospital;

    hospital.run();

    return 0;
}

Day 25:- (Railway Reservation System)
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <ctime>
#include <cctype>

using namespace std;

// ============================================================
// FILES
// ============================================================

const string TRAIN_FILE = "trains.txt";
const string PASSENGER_FILE = "passengers.txt";
const string TICKET_FILE = "tickets.txt";

// ============================================================
// CONSTANTS
// ============================================================

const int MAX_WAITING_LIST = 10;

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "railway123";

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Generate current date
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

// ============================================================
// TRAIN CLASS
// ============================================================

class Train
{
private:

    int trainNumber;
    string trainName;
    string source;
    string destination;

    int totalSeats;
    int availableSeats;

    double farePerSeat;

public:

    Train()
    {
        trainNumber = 0;
        totalSeats = 0;
        availableSeats = 0;
        farePerSeat = 0;
    }

    Train(
        int trainNumber,
        const string& trainName,
        const string& source,
        const string& destination,
        int totalSeats,
        double farePerSeat)
        :
        trainNumber(trainNumber),
        trainName(trainName),
        source(source),
        destination(destination),
        totalSeats(totalSeats),
        availableSeats(totalSeats),
        farePerSeat(farePerSeat)
    {
    }

    // ========================================================
    // GETTERS
    // ========================================================

    int getTrainNumber() const
    {
        return trainNumber;
    }

    string getTrainName() const
    {
        return trainName;
    }

    string getSource() const
    {
        return source;
    }

    string getDestination() const
    {
        return destination;
    }

    int getTotalSeats() const
    {
        return totalSeats;
    }

    int getAvailableSeats() const
    {
        return availableSeats;
    }

    double getFare() const
    {
        return farePerSeat;
    }

    // ========================================================
    // SEAT OPERATIONS
    // ========================================================

    bool bookSeat()
    {
        if (availableSeats <= 0)
            return false;

        availableSeats--;
        return true;
    }

    void cancelSeat()
    {
        if (availableSeats < totalSeats)
            availableSeats++;
    }

    // ========================================================
    // DISPLAY
    // ========================================================

    void display() const
    {
        cout << left
             << setw(10) << trainNumber
             << setw(25) << trainName
             << setw(20) << source
             << setw(20) << destination
             << setw(12) << totalSeats
             << setw(15) << availableSeats
             << setw(12)
             << fixed << setprecision(2)
             << farePerSeat
             << '\n';
    }

    // ========================================================
    // FILE SERIALIZATION
    // ========================================================

    string serialize() const
    {
        stringstream ss;

        ss << trainNumber << "|"
           << trainName << "|"
           << source << "|"
           << destination << "|"
           << totalSeats << "|"
           << availableSeats << "|"
           << farePerSeat;

        return ss.str();
    }
};

// ============================================================
// PASSENGER CLASS
// ============================================================

class Passenger
{
private:

    int passengerId;
    string name;
    int age;
    string gender;
    string phone;

public:

    Passenger()
    {
        passengerId = 0;
        age = 0;
    }

    Passenger(
        int passengerId,
        const string& name,
        int age,
        const string& gender,
        const string& phone)
        :
        passengerId(passengerId),
        name(name),
        age(age),
        gender(gender),
        phone(phone)
    {
    }

    int getPassengerId() const
    {
        return passengerId;
    }

    string getName() const
    {
        return name;
    }

    int getAge() const
    {
        return age;
    }

    string getGender() const
    {
        return gender;
    }

    string getPhone() const
    {
        return phone;
    }

    void display() const
    {
        cout << left
             << setw(10) << passengerId
             << setw(25) << name
             << setw(8) << age
             << setw(12) << gender
             << setw(18) << phone
             << '\n';
    }

    string serialize() const
    {
        stringstream ss;

        ss << passengerId << "|"
           << name << "|"
           << age << "|"
           << gender << "|"
           << phone;

        return ss.str();
    }
};

// ============================================================
// TICKET CLASS
// ============================================================

class Ticket
{
private:

    long long pnr;

    int passengerId;
    int trainNumber;

    string passengerName;

    int seatNumber;

    double fare;

    string bookingDate;

    string status;

    // Status:
    // CONFIRMED
    // WAITING
    // CANCELLED

public:

    Ticket()
    {
        pnr = 0;
        passengerId = 0;
        trainNumber = 0;
        seatNumber = -1;
        fare = 0;
        status = "WAITING";
    }

    Ticket(
        long long pnr,
        int passengerId,
        int trainNumber,
        const string& passengerName,
        int seatNumber,
        double fare,
        const string& bookingDate,
        const string& status)
        :
        pnr(pnr),
        passengerId(passengerId),
        trainNumber(trainNumber),
        passengerName(passengerName),
        seatNumber(seatNumber),
        fare(fare),
        bookingDate(bookingDate),
        status(status)
    {
    }

    // ========================================================
    // GETTERS
    // ========================================================

    long long getPNR() const
    {
        return pnr;
    }

    int getPassengerId() const
    {
        return passengerId;
    }

    int getTrainNumber() const
    {
        return trainNumber;
    }

    string getPassengerName() const
    {
        return passengerName;
    }

    int getSeatNumber() const
    {
        return seatNumber;
    }

    double getFare() const
    {
        return fare;
    }

    string getStatus() const
    {
        return status;
    }

    string getBookingDate() const
    {
        return bookingDate;
    }

    void setSeatNumber(int seat)
    {
        seatNumber = seat;
    }

    void setStatus(const string& newStatus)
    {
        status = newStatus;
    }

    void setFare(double newFare)
    {
        fare = newFare;
    }

    // ========================================================
    // DISPLAY
    // ========================================================

    void display() const
    {
        cout << "\n============================================\n";
        cout << "                 TICKET\n";
        cout << "============================================\n";

        cout << "PNR            : " << pnr << '\n';
        cout << "Passenger ID   : " << passengerId << '\n';
        cout << "Passenger Name : " << passengerName << '\n';
        cout << "Train Number   : " << trainNumber << '\n';

        if (seatNumber == -1)
            cout << "Seat Number    : Waiting List\n";
        else
            cout << "Seat Number    : " << seatNumber << '\n';

        cout << "Fare           : Rs. "
             << fixed << setprecision(2)
             << fare << '\n';

        cout << "Booking Date   : " << bookingDate << '\n';
        cout << "Status         : " << status << '\n';

        cout << "============================================\n";
    }

    // ========================================================
    // FILE SERIALIZATION
    // ========================================================

    string serialize() const
    {
        stringstream ss;

        ss << pnr << "|"
           << passengerId << "|"
           << trainNumber << "|"
           << passengerName << "|"
           << seatNumber << "|"
           << fare << "|"
           << bookingDate << "|"
           << status;

        return ss.str();
    }
};

// ============================================================
// WAITING LIST ENTRY
// ============================================================

struct WaitingPassenger
{
    long long pnr;
    int passengerId;
    int trainNumber;
};

// ============================================================
// RAILWAY RESERVATION SYSTEM
// ============================================================

class RailwaySystem
{
private:

    vector<Train> trains;
    vector<Passenger> passengers;
    vector<Ticket> tickets;

    // Waiting lists are maintained separately for each train
    vector<WaitingPassenger> waitingList;

    long long nextPNR = 1000000001;
    int nextPassengerId = 1001;

public:

    // ========================================================
    // FIND TRAIN
    // ========================================================

    Train* findTrain(int trainNumber)
    {
        for (auto& train : trains)
        {
            if (train.getTrainNumber() == trainNumber)
                return &train;
        }

        return nullptr;
    }

    // ========================================================
    // FIND PASSENGER
    // ========================================================

    Passenger* findPassenger(int passengerId)
    {
        for (auto& passenger : passengers)
        {
            if (passenger.getPassengerId() == passengerId)
                return &passenger;
        }

        return nullptr;
    }

    // ========================================================
    // FIND TICKET
    // ========================================================

    Ticket* findTicket(long long pnr)
    {
        for (auto& ticket : tickets)
        {
            if (ticket.getPNR() == pnr)
                return &ticket;
        }

        return nullptr;
    }

    // ========================================================
    // FILE HANDLING - TRAINS
    // ========================================================

    void loadTrains()
    {
        ifstream file(TRAIN_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string numberStr;
            string name;
            string source;
            string destination;
            string totalSeatsStr;
            string availableSeatsStr;
            string fareStr;

            getline(ss, numberStr, '|');
            getline(ss, name, '|');
            getline(ss, source, '|');
            getline(ss, destination, '|');
            getline(ss, totalSeatsStr, '|');
            getline(ss, availableSeatsStr, '|');
            getline(ss, fareStr, '|');

            Train train(
                stoi(numberStr),
                name,
                source,
                destination,
                stoi(totalSeatsStr),
                stod(fareStr)
            );

            int booked =
                stoi(totalSeatsStr) -
                stoi(availableSeatsStr);

            for (int i = 0; i < booked; i++)
                train.bookSeat();

            trains.push_back(train);
        }

        file.close();
    }

    // ========================================================
    // SAVE TRAINS
    // ========================================================

    void saveTrains()
    {
        ofstream file(TRAIN_FILE);

        for (const auto& train : trains)
        {
            file << train.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD PASSENGERS
    // ========================================================

    void loadPassengers()
    {
        ifstream file(PASSENGER_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string idStr;
            string name;
            string ageStr;
            string gender;
            string phone;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, ageStr, '|');
            getline(ss, gender, '|');
            getline(ss, phone, '|');

            Passenger passenger(
                stoi(idStr),
                name,
                stoi(ageStr),
                gender,
                phone
            );

            passengers.push_back(passenger);

            if (passenger.getPassengerId() >= nextPassengerId)
            {
                nextPassengerId =
                    passenger.getPassengerId() + 1;
            }
        }

        file.close();
    }

    // ========================================================
    // SAVE PASSENGERS
    // ========================================================

    void savePassengers()
    {
        ofstream file(PASSENGER_FILE);

        for (const auto& passenger : passengers)
        {
            file << passenger.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD TICKETS
    // ========================================================

    void loadTickets()
    {
        ifstream file(TICKET_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string pnrStr;
            string passengerIdStr;
            string trainNumberStr;
            string passengerName;
            string seatNumberStr;
            string fareStr;
            string bookingDate;
            string status;

            getline(ss, pnrStr, '|');
            getline(ss, passengerIdStr, '|');
            getline(ss, trainNumberStr, '|');
            getline(ss, passengerName, '|');
            getline(ss, seatNumberStr, '|');
            getline(ss, fareStr, '|');
            getline(ss, bookingDate, '|');
            getline(ss, status, '|');

            Ticket ticket(
                stoll(pnrStr),
                stoi(passengerIdStr),
                stoi(trainNumberStr),
                passengerName,
                stoi(seatNumberStr),
                stod(fareStr),
                bookingDate,
                status
            );

            tickets.push_back(ticket);

            if (ticket.getPNR() >= nextPNR)
                nextPNR = ticket.getPNR() + 1;
        }

        file.close();

        // Rebuild waiting list
        for (const auto& ticket : tickets)
        {
            if (ticket.getStatus() == "WAITING")
            {
                waitingList.push_back(
                    {
                        ticket.getPNR(),
                        ticket.getPassengerId(),
                        ticket.getTrainNumber()
                    }
                );
            }
        }
    }

    // ========================================================
    // SAVE TICKETS
    // ========================================================

    void saveTickets()
    {
        ofstream file(TICKET_FILE);

        for (const auto& ticket : tickets)
        {
            file << ticket.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // ADD TRAIN
    // ========================================================

    void addTrain()
    {
        int trainNumber;
        string trainName;
        string source;
        string destination;
        int totalSeats;
        double fare;

        clearInput();

        cout << "\n============================================\n";
        cout << "              ADD TRAIN DETAILS\n";
        cout << "============================================\n";

        cout << "Enter Train Number: ";
        cin >> trainNumber;

        if (findTrain(trainNumber) != nullptr)
        {
            cout << "Train number already exists.\n";
            return;
        }

        clearInput();

        cout << "Enter Train Name: ";
        getline(cin, trainName);

        cout << "Enter Source: ";
        getline(cin, source);

        cout << "Enter Destination: ";
        getline(cin, destination);

        cout << "Enter Total Seats: ";
        cin >> totalSeats;

        cout << "Enter Fare Per Seat: Rs. ";
        cin >> fare;

        if (totalSeats <= 0 || fare < 0)
        {
            cout << "Invalid train details.\n";
            return;
        }

        trains.emplace_back(
            trainNumber,
            trainName,
            source,
            destination,
            totalSeats,
            fare
        );

        saveTrains();

        cout << "\nTrain added successfully!\n";
    }

    // ========================================================
    // DISPLAY TRAINS
    // ========================================================

    void displayTrains()
    {
        if (trains.empty())
        {
            cout << "\nNo trains available.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================================================\n";
        cout << "                              TRAIN DETAILS\n";
        cout << "====================================================================================\n";

        cout << left
             << setw(10) << "Number"
             << setw(25) << "Train Name"
             << setw(20) << "Source"
             << setw(20) << "Destination"
             << setw(12) << "Total"
             << setw(15) << "Available"
             << setw(12) << "Fare"
             << '\n';

        cout << string(114, '-') << '\n';

        for (const auto& train : trains)
        {
            train.display();
        }

        cout << "====================================================================================\n";
    }

    // ========================================================
    // REGISTER PASSENGER
    // ========================================================

    void registerPassenger()
    {
        string name;
        int age;
        string gender;
        string phone;

        clearInput();

        cout << "\n============================================\n";
        cout << "            PASSENGER REGISTRATION\n";
        cout << "============================================\n";

        cout << "Enter Passenger Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        clearInput();

        cout << "Enter Gender: ";
        getline(cin, gender);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        if (name.empty() || age <= 0)
        {
            cout << "Invalid passenger details.\n";
            return;
        }

        Passenger passenger(
            nextPassengerId,
            name,
            age,
            gender,
            phone
        );

        passengers.push_back(passenger);

        savePassengers();

        cout << "\nPassenger registered successfully!\n";

        cout << "Passenger ID: "
             << nextPassengerId
             << '\n';

        nextPassengerId++;
    }

    // ========================================================
    // FARE CALCULATION
    // ========================================================

    double calculateFare(
        const Train& train,
        int numberOfPassengers)
    {
        return train.getFare() *
               numberOfPassengers;
    }

    // ========================================================
    // SEAT AVAILABILITY
    // ========================================================

    void checkSeatAvailability()
    {
        int trainNumber;

        cout << "\nEnter Train Number: ";
        cin >> trainNumber;

        Train* train =
            findTrain(trainNumber);

        if (train == nullptr)
        {
            cout << "Train not found.\n";
            return;
        }

        cout << "\n============================================\n";
        cout << "           SEAT AVAILABILITY\n";
        cout << "============================================\n";

        cout << "Train Number    : "
             << train->getTrainNumber()
             << '\n';

        cout << "Train Name      : "
             << train->getTrainName()
             << '\n';

        cout << "Total Seats     : "
             << train->getTotalSeats()
             << '\n';

        cout << "Available Seats : "
             << train->getAvailableSeats()
             << '\n';

        cout << "Waiting List    : "
             << countWaitingPassengers(trainNumber)
             << '\n';

        cout << "Fare Per Seat   : Rs. "
             << fixed << setprecision(2)
             << train->getFare()
             << '\n';

        cout << "============================================\n";
    }

    // ========================================================
    // COUNT WAITING PASSENGERS
    // ========================================================

    int countWaitingPassengers(int trainNumber)
    {
        int count = 0;

        for (const auto& ticket : tickets)
        {
            if (ticket.getTrainNumber() == trainNumber &&
                ticket.getStatus() == "WAITING")
            {
                count++;
            }
        }

        return count;
    }

    // ========================================================
    // BOOK TICKET
    // ========================================================

    void bookTicket()
    {
        int passengerId;
        int trainNumber;

        cout << "\nEnter Passenger ID: ";
        cin >> passengerId;

        Passenger* passenger =
            findPassenger(passengerId);

        if (passenger == nullptr)
        {
            cout << "Passenger not found.\n";
            cout << "Please register the passenger first.\n";
            return;
        }

        displayTrains();

        cout << "\nEnter Train Number: ";
        cin >> trainNumber;

        Train* train =
            findTrain(trainNumber);

        if (train == nullptr)
        {
            cout << "Train not found.\n";
            return;
        }

        // ----------------------------------------------------
        // Confirmed ticket
        // ----------------------------------------------------

        if (train->getAvailableSeats() > 0)
        {
            int seatNumber =
                train->getTotalSeats() -
                train->getAvailableSeats() +
                1;

            train->bookSeat();

            double fare =
                calculateFare(*train, 1);

            Ticket ticket(
                nextPNR,
                passengerId,
                trainNumber,
                passenger->getName(),
                seatNumber,
                fare,
                getCurrentDate(),
                "CONFIRMED"
            );

            tickets.push_back(ticket);

            saveTickets();
            saveTrains();

            cout << "\n============================================\n";
            cout << "          TICKET BOOKED SUCCESSFULLY\n";
            cout << "============================================\n";

            cout << "PNR        : "
                 << nextPNR << '\n';

            cout << "Seat Number: "
                 << seatNumber << '\n';

            cout << "Fare       : Rs. "
                 << fixed << setprecision(2)
                 << fare << '\n';

            cout << "Status     : CONFIRMED\n";

            cout << "============================================\n";

            nextPNR++;
        }

        // ----------------------------------------------------
        // Waiting List
        // ----------------------------------------------------

        else
        {
            int waitingCount =
                countWaitingPassengers(trainNumber);

            if (waitingCount >= MAX_WAITING_LIST)
            {
                cout << "\nWaiting list is full.\n";
                return;
            }

            double fare =
                calculateFare(*train, 1);

            Ticket ticket(
                nextPNR,
                passengerId,
                trainNumber,
                passenger->getName(),
                -1,
                fare,
                getCurrentDate(),
                "WAITING"
            );

            tickets.push_back(ticket);

            waitingList.push_back(
                {
                    nextPNR,
                    passengerId,
                    trainNumber
                }
            );

            saveTickets();

            cout << "\n============================================\n";
            cout << "          ADDED TO WAITING LIST\n";
            cout << "============================================\n";

            cout << "PNR    : "
                 << nextPNR << '\n';

            cout << "Status : WAITING\n";

            cout << "Waiting Position: "
                 << waitingCount + 1
                 << '\n';

            cout << "============================================\n";

            nextPNR++;
        }
    }

    // ========================================================
    // PROMOTE WAITING PASSENGER
    // ========================================================

    void promoteWaitingPassenger(
        int trainNumber,
        int freedSeat)
    {
        for (size_t i = 0;
             i < tickets.size();
             i++)
        {
            Ticket& ticket = tickets[i];

            if (ticket.getTrainNumber() == trainNumber &&
                ticket.getStatus() == "WAITING")
            {
                ticket.setSeatNumber(freedSeat);
                ticket.setStatus("CONFIRMED");

                Train* train =
                    findTrain(trainNumber);

                if (train != nullptr)
                {
                    // The freed seat is immediately allocated,
                    // so available count does not increase.
                }

                removeFromWaitingList(
                    ticket.getPNR()
                );

                cout << "\nWaiting passenger promoted!\n";

                cout << "PNR: "
                     << ticket.getPNR()
                     << '\n';

                cout << "Seat: "
                     << freedSeat
                     << '\n';

                return;
            }
        }
    }

    // ========================================================
    // REMOVE FROM WAITING LIST
    // ========================================================

    void removeFromWaitingList(long long pnr)
    {
        waitingList.erase(
            remove_if(
                waitingList.begin(),
                waitingList.end(),
                [pnr](const WaitingPassenger& entry)
                {
                    return entry.pnr == pnr;
                }
            ),
            waitingList.end()
        );
    }

    // ========================================================
    // CANCEL TICKET
    // ========================================================

    void cancelTicket()
    {
        long long pnr;

        cout << "\nEnter PNR to cancel: ";
        cin >> pnr;

        Ticket* ticket =
            findTicket(pnr);

        if (ticket == nullptr)
        {
            cout << "Ticket not found.\n";
            return;
        }

        if (ticket->getStatus() == "CANCELLED")
        {
            cout << "Ticket is already cancelled.\n";
            return;
        }

        Train* train =
            findTrain(ticket->getTrainNumber());

        if (train == nullptr)
        {
            cout << "Associated train not found.\n";
            return;
        }

        // ----------------------------------------------------
        // If confirmed ticket is cancelled
        // ----------------------------------------------------

        if (ticket->getStatus() == "CONFIRMED")
        {
            int freedSeat =
                ticket->getSeatNumber();

            ticket->setStatus("CANCELLED");

            // First check waiting list
            bool waitingExists = false;

            for (const auto& waitingTicket : tickets)
            {
                if (waitingTicket.getTrainNumber() ==
                        ticket->getTrainNumber() &&
                    waitingTicket.getStatus() ==
                        "WAITING")
                {
                    waitingExists = true;
                    break;
                }
            }

            if (waitingExists)
            {
                promoteWaitingPassenger(
                    ticket->getTrainNumber(),
                    freedSeat
                );
            }
            else
            {
                train->cancelSeat();
            }
        }

        // ----------------------------------------------------
        // If waiting ticket is cancelled
        // ----------------------------------------------------

        else if (ticket->getStatus() == "WAITING")
        {
            ticket->setStatus("CANCELLED");

            removeFromWaitingList(
                ticket->getPNR()
            );
        }

        saveTickets();
        saveTrains();

        cout << "\nTicket cancelled successfully.\n";
    }

    // ========================================================
    // SEARCH TICKET BY PNR
    // ========================================================

    void searchTicket()
    {
        long long pnr;

        cout << "\nEnter PNR: ";
        cin >> pnr;

        Ticket* ticket =
            findTicket(pnr);

        if (ticket == nullptr)
        {
            cout << "\nNo ticket found for this PNR.\n";
            return;
        }

        ticket->display();

        Train* train =
            findTrain(ticket->getTrainNumber());

        if (train != nullptr)
        {
            cout << "Train Name    : "
                 << train->getTrainName()
                 << '\n';

            cout << "Route         : "
                 << train->getSource()
                 << " -> "
                 << train->getDestination()
                 << '\n';
        }
    }

    // ========================================================
    // DISPLAY ALL TICKETS
    // ========================================================

    void displayAllTickets()
    {
        if (tickets.empty())
        {
            cout << "\nNo tickets found.\n";
            return;
        }

        cout << "\n";
        cout << "================================================================================\n";
        cout << "                            ALL TICKETS\n";
        cout << "================================================================================\n";

        cout << left
             << setw(14) << "PNR"
             << setw(12) << "Passenger"
             << setw(12) << "Train"
             << setw(10) << "Seat"
             << setw(15) << "Fare"
             << setw(15) << "Status"
             << setw(15) << "Date"
             << '\n';

        cout << string(93, '-') << '\n';

        for (const auto& ticket : tickets)
        {
            cout << left
                 << setw(14)
                 << ticket.getPNR()
                 << setw(12)
                 << ticket.getPassengerName()
                 << setw(12)
                 << ticket.getTrainNumber()
                 << setw(10);

            if (ticket.getSeatNumber() == -1)
                cout << "WAITING";
            else
                cout << ticket.getSeatNumber();

            cout << setw(15)
                 << fixed << setprecision(2)
                 << ticket.getFare()

                 << setw(15)
                 << ticket.getStatus()

                 << setw(15)
                 << ticket.getBookingDate()

                 << '\n';
        }

        cout << "================================================================================\n";
    }

    // ========================================================
    // DISPLAY PASSENGERS
    // ========================================================

    void displayPassengers()
    {
        if (passengers.empty())
        {
            cout << "\nNo passengers registered.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================================\n";
        cout << "                       PASSENGER LIST\n";
        cout << "====================================================================\n";

        cout << left
             << setw(10) << "ID"
             << setw(25) << "Name"
             << setw(8) << "Age"
             << setw(12) << "Gender"
             << setw(18) << "Phone"
             << '\n';

        cout << string(73, '-') << '\n';

        for (const auto& passenger : passengers)
        {
            passenger.display();
        }

        cout << "====================================================================\n";
    }

    // ========================================================
    // ADMIN LOGIN
    // ========================================================

    bool adminLogin()
    {
        string username;
        string password;

        clearInput();

        cout << "\n============================================\n";
        cout << "                 ADMIN LOGIN\n";
        cout << "============================================\n";

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
    // ADMIN PANEL
    // ========================================================

    void adminPanel()
    {
        if (!adminLogin())
            return;

        int choice;

        do
        {
            cout << "\n============================================\n";
            cout << "              RAILWAY ADMIN PANEL\n";
            cout << "============================================\n";

            cout << "1. Add Train\n";
            cout << "2. Display All Trains\n";
            cout << "3. Display Passengers\n";
            cout << "4. Display All Tickets\n";
            cout << "5. Search Ticket by PNR\n";
            cout << "6. Display Waiting List\n";
            cout << "7. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    addTrain();
                    break;

                case 2:
                    displayTrains();
                    break;

                case 3:
                    displayPassengers();
                    break;

                case 4:
                    displayAllTickets();
                    break;

                case 5:
                    searchTicket();
                    break;

                case 6:
                    displayWaitingList();
                    break;

                case 7:
                    cout << "\nAdmin logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 7);
    }

    // ========================================================
    // DISPLAY WAITING LIST
    // ========================================================

    void displayWaitingList()
    {
        bool found = false;

        cout << "\n";
        cout << "============================================================\n";
        cout << "                     WAITING LIST\n";
        cout << "============================================================\n";

        cout << left
             << setw(14) << "PNR"
             << setw(15) << "Passenger ID"
             << setw(15) << "Train Number"
             << '\n';

        cout << string(44, '-') << '\n';

        for (const auto& entry : waitingList)
        {
            Ticket* ticket =
                findTicket(entry.pnr);

            if (ticket != nullptr &&
                ticket->getStatus() == "WAITING")
            {
                found = true;

                cout << left
                     << setw(14)
                     << entry.pnr
                     << setw(15)
                     << entry.passengerId
                     << setw(15)
                     << entry.trainNumber
                     << '\n';
            }
        }

        if (!found)
        {
            cout << "Waiting list is empty.\n";
        }

        cout << "============================================================\n";
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        loadTrains();
        loadPassengers();
        loadTickets();

        int choice;

        do
        {
            cout << "\n\n";
            cout << "================================================\n";
            cout << "          RAILWAY RESERVATION SYSTEM\n";
            cout << "================================================\n";

            cout << "1. Add Train Details\n";
            cout << "2. Display Trains\n";
            cout << "3. Register Passenger\n";
            cout << "4. Book Ticket\n";
            cout << "5. Cancel Ticket\n";
            cout << "6. Check Seat Availability\n";
            cout << "7. Search Ticket by PNR\n";
            cout << "8. Display Waiting List\n";
            cout << "9. Admin Panel\n";
            cout << "10. Exit\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    addTrain();
                    break;

                case 2:
                    displayTrains();
                    break;

                case 3:
                    registerPassenger();
                    break;

                case 4:
                    bookTicket();
                    break;

                case 5:
                    cancelTicket();
                    break;

                case 6:
                    checkSeatAvailability();
                    break;

                case 7:
                    searchTicket();
                    break;

                case 8:
                    displayWaitingList();
                    break;

                case 9:
                    adminPanel();
                    break;

                case 10:
                    saveTrains();
                    savePassengers();
                    saveTickets();

                    cout << "\n============================================\n";
                    cout << " Thank you for using Railway Reservation System!\n";
                    cout << "============================================\n";

                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 10);
    }
};

// ============================================================
// MAIN
// ============================================================

int main()
{
    RailwaySystem railway;

    railway.run();

    return 0;
}

Day 26:- Courier & Parcel Tracking System
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <ctime>

using namespace std;

// ============================================================
// FILE NAMES
// ============================================================

const string CUSTOMER_FILE = "customers.txt";
const string PARCEL_FILE   = "parcels.txt";
const string HISTORY_FILE  = "history.txt";

// ============================================================
// ADMIN CREDENTIALS
// ============================================================

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "courier123";

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ------------------------------------------------------------
// Get current date
// ------------------------------------------------------------

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

// ============================================================
// CUSTOMER CLASS
// ============================================================

class Customer
{
private:

    int customerId;
    string name;
    string phone;
    string email;
    string address;

public:

    Customer()
    {
        customerId = 0;
    }

    Customer(
        int id,
        const string& name,
        const string& phone,
        const string& email,
        const string& address)
        :
        customerId(id),
        name(name),
        phone(phone),
        email(email),
        address(address)
    {
    }

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------

    int getId() const
    {
        return customerId;
    }

    string getName() const
    {
        return name;
    }

    string getPhone() const
    {
        return phone;
    }

    string getEmail() const
    {
        return email;
    }

    string getAddress() const
    {
        return address;
    }

    // --------------------------------------------------------
    // Display
    // --------------------------------------------------------

    void display() const
    {
        cout << left
             << setw(10) << customerId
             << setw(25) << name
             << setw(16) << phone
             << setw(28) << email
             << setw(30) << address
             << '\n';
    }

    // --------------------------------------------------------
    // File serialization
    // --------------------------------------------------------

    string serialize() const
    {
        stringstream ss;

        ss << customerId << "|"
           << name << "|"
           << phone << "|"
           << email << "|"
           << address;

        return ss.str();
    }
};

// ============================================================
// PARCEL CLASS
// ============================================================

class Parcel
{
private:

    long long trackingId;

    int senderId;
    int receiverId;

    string senderName;
    string receiverName;

    string source;
    string destination;

    double weight;

    string deliveryType;

    double deliveryCharge;

    string bookingDate;

    string status;

public:

    Parcel()
    {
        trackingId = 0;
        senderId = 0;
        receiverId = 0;
        weight = 0;
        deliveryCharge = 0;
        status = "Booked";
    }

    Parcel(
        long long trackingId,
        int senderId,
        int receiverId,
        const string& senderName,
        const string& receiverName,
        const string& source,
        const string& destination,
        double weight,
        const string& deliveryType,
        double deliveryCharge,
        const string& bookingDate,
        const string& status)
        :
        trackingId(trackingId),
        senderId(senderId),
        receiverId(receiverId),
        senderName(senderName),
        receiverName(receiverName),
        source(source),
        destination(destination),
        weight(weight),
        deliveryType(deliveryType),
        deliveryCharge(deliveryCharge),
        bookingDate(bookingDate),
        status(status)
    {
    }

    // --------------------------------------------------------
    // Getters
    // --------------------------------------------------------

    long long getTrackingId() const
    {
        return trackingId;
    }

    int getSenderId() const
    {
        return senderId;
    }

    int getReceiverId() const
    {
        return receiverId;
    }

    string getSenderName() const
    {
        return senderName;
    }

    string getReceiverName() const
    {
        return receiverName;
    }

    string getSource() const
    {
        return source;
    }

    string getDestination() const
    {
        return destination;
    }

    double getWeight() const
    {
        return weight;
    }

    string getDeliveryType() const
    {
        return deliveryType;
    }

    double getCharge() const
    {
        return deliveryCharge;
    }

    string getBookingDate() const
    {
        return bookingDate;
    }

    string getStatus() const
    {
        return status;
    }

    // --------------------------------------------------------
    // Setter
    // --------------------------------------------------------

    void setStatus(const string& newStatus)
    {
        status = newStatus;
    }

    // --------------------------------------------------------
    // Display
    // --------------------------------------------------------

    void display() const
    {
        cout << "\n";
        cout << "============================================\n";
        cout << "             PARCEL DETAILS\n";
        cout << "============================================\n";

        cout << "Tracking ID     : " << trackingId << '\n';
        cout << "Sender ID       : " << senderId << '\n';
        cout << "Sender Name     : " << senderName << '\n';

        cout << "Receiver ID     : " << receiverId << '\n';
        cout << "Receiver Name   : " << receiverName << '\n';

        cout << "Source          : " << source << '\n';
        cout << "Destination     : " << destination << '\n';

        cout << "Weight          : "
             << fixed << setprecision(2)
             << weight << " kg\n";

        cout << "Delivery Type   : " << deliveryType << '\n';

        cout << "Delivery Charge : Rs. "
             << fixed << setprecision(2)
             << deliveryCharge << '\n';

        cout << "Booking Date    : " << bookingDate << '\n';

        cout << "Status          : " << status << '\n';

        cout << "============================================\n";
    }

    // --------------------------------------------------------
    // File serialization
    // --------------------------------------------------------

    string serialize() const
    {
        stringstream ss;

        ss << trackingId << "|"
           << senderId << "|"
           << receiverId << "|"
           << senderName << "|"
           << receiverName << "|"
           << source << "|"
           << destination << "|"
           << weight << "|"
           << deliveryType << "|"
           << deliveryCharge << "|"
           << bookingDate << "|"
           << status;

        return ss.str();
    }
};

// ============================================================
// DELIVERY HISTORY CLASS
// ============================================================

class DeliveryHistory
{
private:

    long long trackingId;
    string date;
    string status;
    string remarks;

public:

    DeliveryHistory()
    {
        trackingId = 0;
    }

    DeliveryHistory(
        long long trackingId,
        const string& date,
        const string& status,
        const string& remarks)
        :
        trackingId(trackingId),
        date(date),
        status(status),
        remarks(remarks)
    {
    }

    long long getTrackingId() const
    {
        return trackingId;
    }

    string getDate() const
    {
        return date;
    }

    string getStatus() const
    {
        return status;
    }

    string getRemarks() const
    {
        return remarks;
    }

    void display() const
    {
        cout << left
             << setw(16) << trackingId
             << setw(15) << date
             << setw(22) << status
             << setw(35) << remarks
             << '\n';
    }

    string serialize() const
    {
        stringstream ss;

        ss << trackingId << "|"
           << date << "|"
           << status << "|"
           << remarks;

        return ss.str();
    }
};

// ============================================================
// COURIER MANAGEMENT SYSTEM
// ============================================================

class CourierSystem
{
private:

    vector<Customer> customers;
    vector<Parcel> parcels;
    vector<DeliveryHistory> history;

    int nextCustomerId = 1001;
    long long nextTrackingId = 5000000001LL;

public:

    // ========================================================
    // FIND CUSTOMER
    // ========================================================

    Customer* findCustomer(int id)
    {
        for (auto& customer : customers)
        {
            if (customer.getId() == id)
                return &customer;
        }

        return nullptr;
    }

    // ========================================================
    // FIND PARCEL
    // ========================================================

    Parcel* findParcel(long long trackingId)
    {
        for (auto& parcel : parcels)
        {
            if (parcel.getTrackingId() == trackingId)
                return &parcel;
        }

        return nullptr;
    }

    // ========================================================
    // FILE HANDLING - CUSTOMERS
    // ========================================================

    void loadCustomers()
    {
        ifstream file(CUSTOMER_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string idStr;
            string name;
            string phone;
            string email;
            string address;

            getline(ss, idStr, '|');
            getline(ss, name, '|');
            getline(ss, phone, '|');
            getline(ss, email, '|');
            getline(ss, address, '|');

            Customer customer(
                stoi(idStr),
                name,
                phone,
                email,
                address
            );

            customers.push_back(customer);

            if (customer.getId() >= nextCustomerId)
            {
                nextCustomerId =
                    customer.getId() + 1;
            }
        }

        file.close();
    }

    // ========================================================
    // SAVE CUSTOMERS
    // ========================================================

    void saveCustomers()
    {
        ofstream file(CUSTOMER_FILE);

        for (const auto& customer : customers)
        {
            file << customer.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // FILE HANDLING - PARCELS
    // ========================================================

    void loadParcels()
    {
        ifstream file(PARCEL_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string trackingIdStr;
            string senderIdStr;
            string receiverIdStr;
            string senderName;
            string receiverName;
            string source;
            string destination;
            string weightStr;
            string deliveryType;
            string chargeStr;
            string bookingDate;
            string status;

            getline(ss, trackingIdStr, '|');
            getline(ss, senderIdStr, '|');
            getline(ss, receiverIdStr, '|');
            getline(ss, senderName, '|');
            getline(ss, receiverName, '|');
            getline(ss, source, '|');
            getline(ss, destination, '|');
            getline(ss, weightStr, '|');
            getline(ss, deliveryType, '|');
            getline(ss, chargeStr, '|');
            getline(ss, bookingDate, '|');
            getline(ss, status, '|');

            Parcel parcel(
                stoll(trackingIdStr),
                stoi(senderIdStr),
                stoi(receiverIdStr),
                senderName,
                receiverName,
                source,
                destination,
                stod(weightStr),
                deliveryType,
                stod(chargeStr),
                bookingDate,
                status
            );

            parcels.push_back(parcel);

            if (parcel.getTrackingId() >= nextTrackingId)
            {
                nextTrackingId =
                    parcel.getTrackingId() + 1;
            }
        }

        file.close();
    }

    // ========================================================
    // SAVE PARCELS
    // ========================================================

    void saveParcels()
    {
        ofstream file(PARCEL_FILE);

        for (const auto& parcel : parcels)
        {
            file << parcel.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // LOAD HISTORY
    // ========================================================

    void loadHistory()
    {
        ifstream file(HISTORY_FILE);

        if (!file)
            return;

        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string trackingIdStr;
            string date;
            string status;
            string remarks;

            getline(ss, trackingIdStr, '|');
            getline(ss, date, '|');
            getline(ss, status, '|');
            getline(ss, remarks, '|');

            history.emplace_back(
                stoll(trackingIdStr),
                date,
                status,
                remarks
            );
        }

        file.close();
    }

    // ========================================================
    // SAVE HISTORY
    // ========================================================

    void saveHistory()
    {
        ofstream file(HISTORY_FILE);

        for (const auto& record : history)
        {
            file << record.serialize() << '\n';
        }

        file.close();
    }

    // ========================================================
    // ADD HISTORY RECORD
    // ========================================================

    void addHistory(
        long long trackingId,
        const string& status,
        const string& remarks)
    {
        history.emplace_back(
            trackingId,
            getCurrentDate(),
            status,
            remarks
        );

        saveHistory();
    }

    // ========================================================
    // REGISTER CUSTOMER
    // ========================================================

    void registerCustomer()
    {
        string name;
        string phone;
        string email;
        string address;

        clearInput();

        cout << "\n============================================\n";
        cout << "             CUSTOMER REGISTRATION\n";
        cout << "============================================\n";

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        cout << "Enter Email: ";
        getline(cin, email);

        cout << "Enter Address: ";
        getline(cin, address);

        if (name.empty() || phone.empty())
        {
            cout << "\nInvalid customer details.\n";
            return;
        }

        Customer customer(
            nextCustomerId,
            name,
            phone,
            email,
            address
        );

        customers.push_back(customer);

        saveCustomers();

        cout << "\nCustomer registered successfully!\n";
        cout << "Customer ID: "
             << nextCustomerId
             << '\n';

        nextCustomerId++;
    }

    // ========================================================
    // DISPLAY CUSTOMERS
    // ========================================================

    void displayCustomers()
    {
        if (customers.empty())
        {
            cout << "\nNo customers registered.\n";
            return;
        }

        cout << "\n";
        cout << "=======================================================================================\n";
        cout << "                              CUSTOMER LIST\n";
        cout << "=======================================================================================\n";

        cout << left
             << setw(10) << "ID"
             << setw(25) << "Name"
             << setw(16) << "Phone"
             << setw(28) << "Email"
             << setw(30) << "Address"
             << '\n';

        cout << string(109, '-') << '\n';

        for (const auto& customer : customers)
        {
            customer.display();
        }

        cout << "=======================================================================================\n";
    }

    // ========================================================
    // CALCULATE DELIVERY CHARGE
    // ========================================================

    double calculateDeliveryCharge(
        double weight,
        const string& deliveryType)
    {
        /*
            Normal:
            Base charge = Rs. 50
            First 1 kg = Rs. 50
            Every additional kg = Rs. 30

            Express:
            2x normal charge
        */

        double charge = 50.0;

        if (weight > 1.0)
        {
            charge +=
                (weight - 1.0) * 30.0;
        }

        if (deliveryType == "Express")
        {
            charge *= 2.0;
        }

        return charge;
    }

    // ========================================================
    // BOOK PARCEL
    // ========================================================

    void bookParcel()
    {
        int senderId;
        int receiverId;

        string receiverName;
        string source;
        string destination;

        double weight;

        int deliveryChoice;

        cout << "\n============================================\n";
        cout << "               BOOK PARCEL\n";
        cout << "============================================\n";

        cout << "Enter Sender Customer ID: ";
        cin >> senderId;

        Customer* sender =
            findCustomer(senderId);

        if (sender == nullptr)
        {
            cout << "\nSender not found.\n";
            cout << "Please register the customer first.\n";
            return;
        }

        cout << "Enter Receiver Customer ID: ";
        cin >> receiverId;

        Customer* receiver =
            findCustomer(receiverId);

        if (receiver == nullptr)
        {
            cout << "\nReceiver not found.\n";
            return;
        }

        clearInput();

        cout << "Enter Receiver Name: ";
        getline(cin, receiverName);

        cout << "Enter Source City: ";
        getline(cin, source);

        cout << "Enter Destination City: ";
        getline(cin, destination);

        cout << "Enter Parcel Weight (kg): ";
        cin >> weight;

        if (weight <= 0)
        {
            cout << "\nInvalid weight.\n";
            return;
        }

        cout << "\nDelivery Type:\n";
        cout << "1. Normal Delivery\n";
        cout << "2. Express Delivery\n";

        cout << "Enter choice: ";
        cin >> deliveryChoice;

        string deliveryType;

        if (deliveryChoice == 1)
        {
            deliveryType = "Normal";
        }
        else if (deliveryChoice == 2)
        {
            deliveryType = "Express";
        }
        else
        {
            cout << "\nInvalid delivery type.\n";
            return;
        }

        double charge =
            calculateDeliveryCharge(
                weight,
                deliveryType
            );

        Parcel parcel(
            nextTrackingId,
            senderId,
            receiverId,
            sender->getName(),
            receiverName,
            source,
            destination,
            weight,
            deliveryType,
            charge,
            getCurrentDate(),
            "Booked"
        );

        parcels.push_back(parcel);

        saveParcels();

        addHistory(
            nextTrackingId,
            "Booked",
            "Parcel successfully booked"
        );

        cout << "\n============================================\n";
        cout << "          PARCEL BOOKED SUCCESSFULLY\n";
        cout << "============================================\n";

        cout << "Tracking ID     : "
             << nextTrackingId
             << '\n';

        cout << "Sender          : "
             << sender->getName()
             << '\n';

        cout << "Receiver        : "
             << receiverName
             << '\n';

        cout << "Delivery Type   : "
             << deliveryType
             << '\n';

        cout << "Weight          : "
             << fixed << setprecision(2)
             << weight
             << " kg\n";

        cout << "Delivery Charge : Rs. "
             << fixed << setprecision(2)
             << charge
             << '\n';

        cout << "Status          : Booked\n";

        cout << "============================================\n";

        nextTrackingId++;
    }

    // ========================================================
    // TRACK SHIPMENT
    // ========================================================

    void trackShipment()
    {
        long long trackingId;

        cout << "\nEnter Tracking ID: ";
        cin >> trackingId;

        Parcel* parcel =
            findParcel(trackingId);

        if (parcel == nullptr)
        {
            cout << "\nParcel not found.\n";
            return;
        }

        parcel->display();

        cout << "\nDelivery History:\n";

        cout << string(85, '-') << '\n';

        cout << left
             << setw(16) << "Tracking ID"
             << setw(15) << "Date"
             << setw(22) << "Status"
             << setw(35) << "Remarks"
             << '\n';

        cout << string(85, '-') << '\n';

        bool found = false;

        for (const auto& record : history)
        {
            if (record.getTrackingId() ==
                trackingId)
            {
                record.display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No history available.\n";
        }

        cout << string(85, '-') << '\n';
    }

    // ========================================================
    // UPDATE DELIVERY STATUS
    // ========================================================

    void updateDeliveryStatus()
    {
        long long trackingId;

        cout << "\nEnter Tracking ID: ";
        cin >> trackingId;

        Parcel* parcel =
            findParcel(trackingId);

        if (parcel == nullptr)
        {
            cout << "\nParcel not found.\n";
            return;
        }

        cout << "\nCurrent Status: "
             << parcel->getStatus()
             << '\n';

        cout << "\nSelect New Status:\n";

        cout << "1. Booked\n";
        cout << "2. Picked Up\n";
        cout << "3. In Transit\n";
        cout << "4. Out for Delivery\n";
        cout << "5. Delivered\n";
        cout << "6. Delivery Failed\n";
        cout << "7. Cancelled\n";

        int choice;

        cout << "\nEnter choice: ";
        cin >> choice;

        string newStatus;

        switch (choice)
        {
            case 1:
                newStatus = "Booked";
                break;

            case 2:
                newStatus = "Picked Up";
                break;

            case 3:
                newStatus = "In Transit";
                break;

            case 4:
                newStatus = "Out for Delivery";
                break;

            case 5:
                newStatus = "Delivered";
                break;

            case 6:
                newStatus = "Delivery Failed";
                break;

            case 7:
                newStatus = "Cancelled";
                break;

            default:
                cout << "\nInvalid choice.\n";
                return;
        }

        clearInput();

        string remarks;

        cout << "Enter remarks: ";
        getline(cin, remarks);

        parcel->setStatus(newStatus);

        saveParcels();

        addHistory(
            trackingId,
            newStatus,
            remarks
        );

        cout << "\nDelivery status updated successfully!\n";
    }

    // ========================================================
    // SEARCH PARCEL BY TRACKING ID
    // ========================================================

    void searchParcel()
    {
        long long trackingId;

        cout << "\nEnter Tracking ID: ";
        cin >> trackingId;

        Parcel* parcel =
            findParcel(trackingId);

        if (parcel == nullptr)
        {
            cout << "\nNo parcel found for Tracking ID "
                 << trackingId
                 << ".\n";

            return;
        }

        parcel->display();
    }

    // ========================================================
    // DISPLAY DELIVERY HISTORY
    // ========================================================

    void displayHistory()
    {
        if (history.empty())
        {
            cout << "\nNo delivery history available.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================================================\n";
        cout << "                         DELIVERY HISTORY\n";
        cout << "====================================================================================\n";

        cout << left
             << setw(16) << "Tracking ID"
             << setw(15) << "Date"
             << setw(22) << "Status"
             << setw(35) << "Remarks"
             << '\n';

        cout << string(88, '-') << '\n';

        for (const auto& record : history)
        {
            record.display();
        }

        cout << "====================================================================================\n";
    }

    // ========================================================
    // DISPLAY ALL PARCELS
    // ========================================================

    void displayAllParcels()
    {
        if (parcels.empty())
        {
            cout << "\nNo parcels available.\n";
            return;
        }

        cout << "\n";
        cout << "========================================================================================================\n";
        cout << "                                  ALL PARCELS\n";
        cout << "========================================================================================================\n";

        cout << left
             << setw(16) << "Tracking ID"
             << setw(20) << "Sender"
             << setw(20) << "Receiver"
             << setw(18) << "Destination"
             << setw(12) << "Weight"
             << setw(15) << "Type"
             << setw(20) << "Status"
             << '\n';

        cout << string(121, '-') << '\n';

        for (const auto& parcel : parcels)
        {
            cout << left
                 << setw(16)
                 << parcel.getTrackingId()

                 << setw(20)
                 << parcel.getSenderName()

                 << setw(20)
                 << parcel.getReceiverName()

                 << setw(18)
                 << parcel.getDestination()

                 << setw(12)
                 << fixed << setprecision(2)
                 << parcel.getWeight()

                 << setw(15)
                 << parcel.getDeliveryType()

                 << setw(20)
                 << parcel.getStatus()

                 << '\n';
        }

        cout << "========================================================================================================\n";
    }

    // ========================================================
    // ADMIN LOGIN
    // ========================================================

    bool adminLogin()
    {
        string username;
        string password;

        clearInput();

        cout << "\n============================================\n";
        cout << "                ADMIN LOGIN\n";
        cout << "============================================\n";

        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if (username == ADMIN_USERNAME &&
            password == ADMIN_PASSWORD)
        {
            cout << "\nLogin successful!\n";
            return true;
        }

        cout << "\nInvalid username or password.\n";

        return false;
    }

    // ========================================================
    // ADMIN DASHBOARD
    // ========================================================

    void adminDashboard()
    {
        if (!adminLogin())
            return;

        int choice;

        do
        {
            cout << "\n============================================\n";
            cout << "            COURIER ADMIN DASHBOARD\n";
            cout << "============================================\n";

            cout << "1. Display Customers\n";
            cout << "2. Display All Parcels\n";
            cout << "3. Update Delivery Status\n";
            cout << "4. Search Parcel\n";
            cout << "5. Delivery History\n";
            cout << "6. Logout\n";

            cout << "\nEnter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    displayCustomers();
                    break;

                case 2:
                    displayAllParcels();
                    break;

                case 3:
                    updateDeliveryStatus();
                    break;

                case 4:
                    searchParcel();
                    break;

                case 5:
                    displayHistory();
                    break;

                case 6:
                    cout << "\nAdmin logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 6);
    }

    // ========================================================
    // MAIN MENU
    // ========================================================

    void run()
    {
        // Load saved data
        loadCustomers();
        loadParcels();
        loadHistory();

        int choice;

        do
        {
            cout << "\n\n";

            cout << "================================================\n";
            cout << "         COURIER & PARCEL TRACKING SYSTEM\n";
            cout << "================================================\n";

            cout << "1. Register Customer\n";
            cout << "2. Display Customers\n";
            cout << "3. Book Parcel\n";
            cout << "4. Track Shipment\n";
            cout << "5. Update Delivery Status\n";
            cout << "6. Search Parcel by Tracking ID\n";
            cout << "7. Delivery History\n";
            cout << "8. Calculate Delivery Charges\n";
            cout << "9. Admin Dashboard\n";
            cout << "10. Exit\n";

            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    registerCustomer();
                    break;

                case 2:
                    displayCustomers();
                    break;

                case 3:
                    bookParcel();
                    break;

                case 4:
                    trackShipment();
                    break;

                case 5:
                    updateDeliveryStatus();
                    break;

                case 6:
                    searchParcel();
                    break;

                case 7:
                    displayHistory();
                    break;

                case 8:
                {
                    double weight;
                    int choice;

                    cout << "\nEnter parcel weight (kg): ";
                    cin >> weight;

                    cout << "\n1. Normal Delivery\n";
                    cout << "2. Express Delivery\n";

                    cout << "Enter choice: ";
                    cin >> choice;

                    if (weight <= 0 ||
                        (choice != 1 && choice != 2))
                    {
                        cout << "\nInvalid input.\n";
                        break;
                    }

                    string type =
                        (choice == 1)
                        ? "Normal"
                        : "Express";

                    double charge =
                        calculateDeliveryCharge(
                            weight,
                            type
                        );

                    cout << "\n============================================\n";
                    cout << "        DELIVERY CHARGE CALCULATOR\n";
                    cout << "============================================\n";

                    cout << "Weight        : "
                         << fixed << setprecision(2)
                         << weight
                         << " kg\n";

                    cout << "Delivery Type : "
                         << type
                         << '\n';

                    cout << "Charge        : Rs. "
                         << fixed << setprecision(2)
                         << charge
                         << '\n';

                    cout << "============================================\n";

                    break;
                }

                case 9:
                    adminDashboard();
                    break;

                case 10:

                    // Save everything before exiting
                    saveCustomers();
                    saveParcels();
                    saveHistory();

                    cout << "\n============================================\n";
                    cout << " Thank you for using Courier Tracking System!\n";
                    cout << "============================================\n";

                    break;

                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 10);
    }
};

// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    CourierSystem system;

    system.run();

    return 0;
}
