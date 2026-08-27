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