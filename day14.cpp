// PROJECT 4 - MINI SEARCH ENGINE (FILE-BASED)

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Function to convert string to lowercase
string toLowerCase(string str)
{
    for (char &c : str)
    {
        c = tolower(c);
    }
    return str;
}

// Function to remove punctuation
string cleanWord(string word)
{
    string cleaned = "";

    for (char c : word)
    {
        if (isalnum(c))
        {
            cleaned += tolower(c);
        }
    }

    return cleaned;
}

int main()
{
    string filename;
    cout << "Enter file name: ";
    cin >> filename;

    ifstream file(filename);

    if (!file)
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    vector<string> lines;
    map<string, int> frequency;

    string line;
    int lineNumber = 0;

    // Read file and store lines
    while (getline(file, line))
    {
        lines.push_back(line);
        lineNumber++;

        stringstream ss(line);
        string word;

        while (ss >> word)
        {
            word = cleanWord(word);

            if (!word.empty())
            {
                frequency[word]++;
            }
        }
    }

    file.close();

    int choice;

    do
    {
        cout << "\n===== MINI SEARCH ENGINE =====" << endl;
        cout << "1. Search Single Word" << endl;
        cout << "2. Search Multiple Words" << endl;
        cout << "3. Show Top 5 Most Frequent Words" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        cin.ignore();

        if (choice == 1)
        {
            string searchWord;

            cout << "Enter word to search: ";
            getline(cin, searchWord);

            searchWord = cleanWord(searchWord);

            int count = 0;
            vector<int> foundLines;

            for (int i = 0; i < lines.size(); i++)
            {
                string temp = toLowerCase(lines[i]);

                stringstream ss(temp);
                string word;

                bool found = false;

                while (ss >> word)
                {
                    word = cleanWord(word);

                    if (word == searchWord)
                    {
                        count++;

                        if (!found)
                        {
                            foundLines.push_back(i + 1);
                            found = true;
                        }
                    }
                }
            }

            cout << "\nWord Found " << count << " times." << endl;

            if (count > 0)
            {
                cout << "Appears in line numbers: ";

                for (int num : foundLines)
                {
                    cout << num << " ";
                }

                cout << endl;
            }
            else
            {
                cout << "Word not found." << endl;
            }
        }

        else if (choice == 2)
        {
            string input;

            cout << "Enter multiple words: ";
            getline(cin, input);

            stringstream ss(input);
            string searchWord;

            while (ss >> searchWord)
            {
                searchWord = cleanWord(searchWord);

                int count = 0;

                cout << "\nSearching for: " << searchWord << endl;

                for (int i = 0; i < lines.size(); i++)
                {
                    string temp = toLowerCase(lines[i]);

                    stringstream lineSS(temp);
                    string word;

                    while (lineSS >> word)
                    {
                        word = cleanWord(word);

                        if (word == searchWord)
                        {
                            count++;
                        }
                    }
                }

                cout << "Occurrences: " << count << endl;
            }
        }

        else if (choice == 3)
        {
            vector<pair<string, int>> freqList;

            for (auto x : frequency)
            {
                freqList.push_back(x);
            }

            sort(freqList.begin(), freqList.end(),
                 [](pair<string, int> a, pair<string, int> b)
                 {
                     return a.second > b.second;
                 });

            cout << "\nTop 5 Most Frequent Words:\n";

            for (int i = 0; i < 5 && i < freqList.size(); i++)
            {
                cout << i + 1 << ". "
                     << freqList[i].first
                     << " --> "
                     << freqList[i].second
                     << " times" << endl;
            }
        }

        else if (choice == 4)
        {
            cout << "Program Exited." << endl;
        }

        else
        {
            cout << "Invalid Choice!" << endl;
        }

    } while (choice != 4);

    return 0;
}