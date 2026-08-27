#include <iostream>
using namespace std;

class Stack {
private:
    int arr[100];
    int top;
    int maxSize;

public:
    // Constructor
    Stack(int size) {
        maxSize = size;
        top = -1;
    }

    // Push function
    void push(int x) {
        if (top == maxSize - 1) {
            cout << "Stack Overflow! Cannot push " << x << endl;
            return;
        }

        top++;
        arr[top] = x;
        cout << x << " pushed into stack." << endl;
    }

    // Pop function
    void pop() {
        if (top == -1) {
            cout << "Stack Underflow! Stack is empty." << endl;
            return;
        }

        cout << arr[top] << " popped from stack." << endl;
        top--;
    }

    // Peek function
    void peek() {
        if (top == -1) {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Top element: " << arr[top] << endl;
    }

    // Check if stack is empty
    bool isEmpty() {
        return (top == -1);
    }

    // Display stack
    void display() {
        if (top == -1) {
            cout << "Stack is empty." << endl;
            return;
        }

        cout << "Stack elements are: ";
        for (int i = top; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Current size
    int currentSize() {
        return top + 1;
    }
};

int main() {
    int size;

    cout << "Enter stack size: ";
    cin >> size;

    Stack s(size);

    int choice, value;

    do {
        cout << "\n===== STACK MENU =====" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Peek" << endl;
        cout << "4. Check Empty" << endl;
        cout << "5. Display Stack" << endl;
        cout << "6. Current Size" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            cout << "Enter value to push: ";
            cin >> value;
            s.push(value);
            break;

        case 2:
            s.pop();
            break;

        case 3:
            s.peek();
            break;

        case 4:
            if (s.isEmpty())
                cout << "Stack is empty." << endl;
            else
                cout << "Stack is not empty." << endl;
            break;

        case 5:
            s.display();
            break;

        case 6:
            cout << "Current stack size: "
                 << s.currentSize() << endl;
            break;

        case 7:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 7);

    return 0;
}