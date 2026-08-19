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
