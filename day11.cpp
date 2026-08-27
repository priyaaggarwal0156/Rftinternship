#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

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

    string line, word = "", longestWord = "";
    int lines = 0, words = 0, characters = 0;

    while (getline(file, line))
    {
        lines++;

        for (char ch : line)
        {
            characters++;

            if (isalnum(ch))
            {
                word += tolower(ch);
            }
            else
            {
                if (!word.empty())
                {
                    words++;

                    if (word.length() > longestWord.length())
                    {
                        longestWord = word;
                    }

                    word = "";
                }
            }
        }

        if (!word.empty())
        {
            words++;

            if (word.length() > longestWord.length())
            {
                longestWord = word;
            }

            word = "";
        }
    }

    file.close();

    cout << "\n----- FILE ANALYZER -----" << endl;
    cout << "Total Lines      : " << lines << endl;
    cout << "Total Words      : " << words << endl;
    cout << "Total Characters : " << characters << endl;
    cout << "Longest Word     : " << longestWord << endl;

    return 0;
}