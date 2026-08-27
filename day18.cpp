#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Stack {
private:
    int top;
    int arr[100];

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == 99;
    }

    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++top] = value;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return -1;
        }
        return arr[top--];
    }

    int peek() {
        if (isEmpty()) {
            return -1;
        }
        return arr[top];
    }

    int size() {
        return top + 1;
    }
};

// Function to perform operations
int performOperation(int op1, int op2, char symbol) {
    switch(symbol) {
        case '+':
            return op1 + op2;

        case '-':
            return op1 - op2;

        case '*':
            return op1 * op2;

        case '/':
            if(op2 == 0) {
                cout << "Division by zero error!" << endl;
                return 0;
            }
            return op1 / op2;

        case '%':
            return op1 % op2;

        default:
            cout << "Invalid Operator!" << endl;
            return 0;
    }
}

// Function to evaluate postfix expression
int evaluatePostfix(string expression) {
    Stack st;

    for (int i = 0; i < expression.length(); i++) {

        // Ignore spaces
        if (expression[i] == ' ')
            continue;

        // If digit found (supports multi-digit numbers)
        if (isdigit(expression[i])) {

            int number = 0;

            while (i < expression.length() && isdigit(expression[i])) {
                number = number * 10 + (expression[i] - '0');
                i++;
            }

            i--; // adjust index after loop
            st.push(number);
        }

        // If operator found
        else {

            // Invalid expression check
            if (st.size() < 2) {
                cout << "Invalid Expression!" << endl;
                return -1;
            }

            int op2 = st.pop();
            int op1 = st.pop();

            int result = performOperation(op1, op2, expression[i]);

            st.push(result);
        }
    }

    // Final validation
    if (st.size() != 1) {
        cout << "Invalid Expression!" << endl;
        return -1;
    }

    return st.pop();
}

int main() {

    string expression;

    cout << "===================================" << endl;
    cout << " POSTFIX EXPRESSION EVALUATOR " << endl;
    cout << "===================================" << endl;

    cout << "\nEnter Postfix Expression: ";
    getline(cin, expression);

    int result = evaluatePostfix(expression);

    if (result != -1) {
        cout << "\nResult = " << result << endl;
    }

    return 0;
}