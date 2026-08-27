#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to convert string into uppercase
string toUpperCase(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

int main()
{
    // Create sample log file automatically
    ofstream createFile("log.txt");

    createFile << "ERROR: DISK FULL" << endl;
    createFile << "INFO: STARTED" << endl;
    createFile << "WARNING: LOW MEMORY" << endl;
    createFile << "ERROR: FILE MISSING" << endl;
    createFile << "info: login successful" << endl;
    createFile << "warning: cpu usage high" << endl;
    createFile << "error: network failure" << endl;

    createFile.close();

    // Open log file for reading
    ifstream file("log.txt");

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string line;

    int errorCount = 0;
    int warningCount = 0;
    int infoCount = 0;

    vector<int> errorLines;

    int lineNumber = 0;

    // Read file line by line
    while (getline(file, line))
    {
        lineNumber++;

        // Convert line to uppercase
        string upperLine = toUpperCase(line);

        // Categorize log type
        if (upperLine.find("ERROR") != string::npos)
        {
            errorCount++;
            errorLines.push_back(lineNumber);
        }
        else if (upperLine.find("WARNING") != string::npos)
        {
            warningCount++;
        }
        else if (upperLine.find("INFO") != string::npos)
        {
            infoCount++;
        }
    }

    file.close();

    // Display report
    cout << "\n===== LOG ANALYSIS REPORT =====\n" << endl;

    cout << "ERROR Count   : " << errorCount << endl;
    cout << "WARNING Count : " << warningCount << endl;
    cout << "INFO Count    : " << infoCount << endl;

    // Find most frequent type
    cout << "\nMost Frequent Type : ";

    if (errorCount >= warningCount && errorCount >= infoCount)
    {
        cout << "ERROR";
    }
    else if (warningCount >= errorCount && warningCount >= infoCount)
    {
        cout << "WARNING";
    }
    else
    {
        cout << "INFO";
    }

    // Display ERROR line numbers
    cout << "\n\nLine Numbers of ERROR entries: ";

    for (int i = 0; i < errorLines.size(); i++)
    {
        cout << errorLines[i] << " ";
    }

    cout << endl;

    return 0;
}                

