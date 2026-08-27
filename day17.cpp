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