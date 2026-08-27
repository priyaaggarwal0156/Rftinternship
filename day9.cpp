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

            break;
        }
    }

    return 0;
}