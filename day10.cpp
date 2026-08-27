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