#include <iostream>
#include <stack>
#include <string>

using namespace std;

class BrowserHistory {
private:
    stack<string> backStack;
    stack<string> forwardStack;

    string currentPage;
    int historyLimit;

public:
    // Constructor
    BrowserHistory(int limit = 5) {
        currentPage = "Home";
        historyLimit = limit;
    }

    // Visit New Page
    void visitPage(string url) {

        // Push current page into back stack
        if (currentPage != "") {

            // Limit history size
            if (backStack.size() >= historyLimit) {
                removeOldestHistory();
            }

            backStack.push(currentPage);
        }

        // New visit clears forward history
        clearForwardStack();

        currentPage = url;

        cout << "Visited: " << currentPage << endl;
    }

    // Go Back
    void goBack() {

        if (backStack.empty()) {
            cout << "No previous page available!" << endl;
            return;
        }

        forwardStack.push(currentPage);

        currentPage = backStack.top();
        backStack.pop();

        cout << "Went Back To: " << currentPage << endl;
    }

    // Go Forward
    void goForward() {

        if (forwardStack.empty()) {
            cout << "No forward page available!" << endl;
            return;
        }

        backStack.push(currentPage);

        currentPage = forwardStack.top();
        forwardStack.pop();

        cout << "Went Forward To: " << currentPage << endl;
    }

    // Display Current Page
    void displayCurrentPage() {
        cout << "\nCurrent Page: " << currentPage << endl;
    }

    // Display Full History
    void displayHistory() {

        cout << "\n===== BROWSER HISTORY =====" << endl;

        // Display Back History
        stack<string> tempBack = backStack;

        cout << "Back Stack: ";
        if (tempBack.empty()) {
            cout << "Empty";
        }

        while (!tempBack.empty()) {
            cout << tempBack.top() << " ";
            tempBack.pop();
        }

        cout << endl;

        // Current Page
        cout << "Current Page: " << currentPage << endl;

        // Display Forward History
        stack<string> tempForward = forwardStack;

        cout << "Forward Stack: ";
        if (tempForward.empty()) {
            cout << "Empty";
        }

        while (!tempForward.empty()) {
            cout << tempForward.top() << " ";
            tempForward.pop();
        }

        cout << endl;
    }

private:

    // Clear Forward Stack
    void clearForwardStack() {

        while (!forwardStack.empty()) {
            forwardStack.pop();
        }
    }

    // Remove Oldest History (Advanced Feature)
    void removeOldestHistory() {

        stack<string> temp;

        // Reverse stack
        while (!backStack.empty()) {
            temp.push(backStack.top());
            backStack.pop();
        }

        // Remove oldest page
        if (!temp.empty()) {
            temp.pop();
        }

        // Restore stack
        while (!temp.empty()) {
            backStack.push(temp.top());
            temp.pop();
        }
    }
};

int main() {

    BrowserHistory browser(5);

    int choice;
    string url;

    do {

        cout << "\n========== SIMPLE BROWSER ==========" << endl;
        cout << "1. Visit New Page" << endl;
        cout << "2. Go Back" << endl;
        cout << "3. Go Forward" << endl;
        cout << "4. Display Current Page" << endl;
        cout << "5. Display Full History" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter URL/Page Name: ";
            cin >> url;

            browser.visitPage(url);
            break;

        case 2:
            browser.goBack();
            break;

        case 3:
            browser.goForward();
            break;

        case 4:
            browser.displayCurrentPage();
            break;

        case 5:
            browser.displayHistory();
            break;

        case 6:
            cout << "Exiting Browser..." << endl;
            break;

        default:
            cout << "Invalid Choice!" << endl;
        }

    } while (choice != 6);

    return 0;
}