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