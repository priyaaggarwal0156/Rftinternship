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