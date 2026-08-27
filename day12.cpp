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