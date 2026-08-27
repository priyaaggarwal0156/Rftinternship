// PROJECT 6 - SAFE CALCULATOR
// Concepts Used:
// 1. Try-Catch
// 2. Input Validation
// 3. Exception Handling

#include <iostream>
#include <limits>
using namespace std;

// Function to clear invalid input
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    double num1, num2, result;
    char op;
    char choice;

    cout << "=============================\n";
    cout << "       SAFE CALCULATOR\n";
    cout << "=============================\n";

    do
    {
        try
        {
            // Input First Number
            cout << "\nEnter First Number: ";
            if (!(cin >> num1))
            {
                throw "Invalid Input! Please enter numeric values only.";
            }

            // Input Operator
            cout << "Enter Operator (+, -, *, /): ";
            cin >> op;

            // Check valid operator
            if (op != '+' && op != '-' && op != '*' && op != '/')
            {
                throw "Invalid Operator!";
            }

            // Input Second Number
            cout << "Enter Second Number: ";
            if (!(cin >> num2))
            {
                throw "Invalid Input! Please enter numeric values only.";
            }

            // Perform Calculation
            switch (op)
            {
                case '+':
                    result = num1 + num2;
                    break;

                case '-':
                    result = num1 - num2;
                    break;

                case '*':
                    result = num1 * num2;
                    break;

                case '/':
                    if (num2 == 0)
                    {
                        throw "Error! Division by Zero is not allowed.";
                    }
                    result = num1 / num2;
                    break;
            }

            // Display Result
            cout << "\nResult = " << result << endl;
        }

        // Exception Handling
        catch (const char* errorMessage)
        {
            cout << "\nException Caught: " << errorMessage << endl;
            clearInput();
        }

        // Continue Option
        cout << "\nDo you want to continue? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "\nThank You for using Safe Calculator!\n";

    return 0;
}