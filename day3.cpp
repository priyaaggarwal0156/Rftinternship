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