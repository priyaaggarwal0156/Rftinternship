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