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
