#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// --------------------------------------------------
// 1. Swap using Pass by Value
// --------------------------------------------------
void swapByValue(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "Inside swapByValue(): "
         << "a = " << a << ", b = " << b << '\n';
}

// --------------------------------------------------
// 2. Swap using Pass by Reference
// --------------------------------------------------
void swapByReference(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// --------------------------------------------------
// 3. Return a value from a function
//    Finds the second-largest DISTINCT element
// --------------------------------------------------
int secondLargest(const vector<int>& arr)
{
    if (arr.size() < 2)
        throw invalid_argument("Array must contain at least two elements.");

    int largest = numeric_limits<int>::min();
    int second = numeric_limits<int>::min();

    for (int value : arr)
    {
        if (value > largest)
        {
            second = largest;
            largest = value;
        }
        else if (value > second && value < largest)
        {
            second = value;
        }
    }

    if (second == numeric_limits<int>::min())
        throw invalid_argument("No distinct second-largest element exists.");

    return second;
}

// --------------------------------------------------
// Main Function
// --------------------------------------------------
int main()
{
    // ----------------------------------------------
    // Task 1: Pass by Value
    // ----------------------------------------------
    int x = 10;
    int y = 20;

    cout << "Before swapByValue(): "
         << "x = " << x << ", y = " << y << '\n';

    swapByValue(x, y);

    cout << "After swapByValue():  "
         << "x = " << x << ", y = " << y << '\n';

    cout << "\nWhy didn't the original values change?\n";
    cout << "Because pass by value sends copies of x and y "
         << "to the function.\n";


    // ----------------------------------------------
    // Task 2: Pass by Reference
    // ----------------------------------------------
    cout << "\nBefore swapByReference(): "
         << "x = " << x << ", y = " << y << '\n';

    swapByReference(x, y);

    cout << "After swapByReference():  "
         << "x = " << x << ", y = " << y << '\n';

    cout << "\nWhy did the original values change?\n";
    cout << "Because references allow the function to directly "
         << "modify the original variables.\n";


    // ----------------------------------------------
    // Challenge: Second-largest element
    // ----------------------------------------------
    vector<int> arr = {10, 25, 7, 40, 18, 40, 32};

    cout << "\nArray: ";
    for (int value : arr)
        cout << value << ' ';

    try
    {
        int result = secondLargest(arr);
        cout << "\nSecond-largest element = " << result << '\n';
    }
    catch (const invalid_argument& e)
    {
        cout << "\nError: " << e.what() << '\n';
    }

    return 0;
}