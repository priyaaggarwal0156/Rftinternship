#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <cstdint>
#include <limits>

using namespace std;
namespace fs = std::filesystem;

// ============================================================
// HUFFMAN NODE
// ============================================================

struct HuffmanNode
{
    unsigned char character;
    uint64_t frequency;

    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(
        unsigned char ch,
        uint64_t freq)
        : character(ch),
          frequency(freq),
          left(nullptr),
          right(nullptr)
    {
    }

    HuffmanNode(
        HuffmanNode* l,
        HuffmanNode* r)
        : character(0),
          frequency(l->frequency + r->frequency),
          left(l),
          right(r)
    {
    }

    bool isLeaf() const
    {
        return left == nullptr &&
               right == nullptr;
    }
};

// ============================================================
// PRIORITY QUEUE COMPARATOR
// ============================================================

struct CompareNodes
{
    bool operator()(
        HuffmanNode* a,
        HuffmanNode* b)
    {
        return a->frequency >
               b->frequency;
    }
};

// ============================================================
// DELETE HUFFMAN TREE
// ============================================================

void deleteTree(HuffmanNode* root)
{
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

// ============================================================
// FILE COMPRESSOR CLASS
// ============================================================

class FileCompressor
{
private:

    unordered_map<unsigned char, uint64_t> frequency;

    unordered_map<unsigned char, string> huffmanCodes;

    HuffmanNode* root = nullptr;

    // --------------------------------------------------------
    // Build Huffman Tree
    // --------------------------------------------------------

    void buildTree()
    {
        priority_queue<
            HuffmanNode*,
            vector<HuffmanNode*>,
            CompareNodes
        > pq;

        for (const auto& pair : frequency)
        {
            pq.push(
                new HuffmanNode(
                    pair.first,
                    pair.second
                )
            );
        }

        // Empty file
        if (pq.empty())
        {
            root = nullptr;
            return;
        }

        // File containing only one unique character
        if (pq.size() == 1)
        {
            HuffmanNode* only =
                pq.top();

            pq.pop();

            root = new HuffmanNode(
                only,
             new HuffmanNode(static_cast<unsigned char>(0), static_cast<uint64_t>(0))
            );

            return;
        }

        while (pq.size() > 1)
        {
            HuffmanNode* left =
                pq.top();

            pq.pop();

            HuffmanNode* right =
                pq.top();

            pq.pop();

            HuffmanNode* parent =
                new HuffmanNode(
                    left,
                    right
                );

            pq.push(parent);
        }

        root = pq.top();
    }

    // --------------------------------------------------------
    // Generate Huffman Codes
    // --------------------------------------------------------

    void generateCodes(
        HuffmanNode* node,
        const string& code)
    {
        if (node == nullptr)
            return;

        if (node->isLeaf())
        {
            // Single-character case
            if (code.empty())
                huffmanCodes[node->character] = "0";
            else
                huffmanCodes[node->character] = code;

            return;
        }

        generateCodes(
            node->left,
            code + "0"
        );

        generateCodes(
            node->right,
            code + "1"
        );
    }

    // --------------------------------------------------------
    // Analyze Character Frequency
    // --------------------------------------------------------

    bool analyzeFile(
        const string& inputFile)
    {
        ifstream file(
            inputFile,
            ios::binary
        );

        if (!file)
        {
            cout << "\nERROR: Unable to open input file.\n";
            return false;
        }

        frequency.clear();

        unsigned char byte;

        while (
            file.read(
                reinterpret_cast<char*>(&byte),
                sizeof(byte)
            )
        )
        {
            frequency[byte]++;
        }

        file.close();

        return true;
    }

    // --------------------------------------------------------
    // Display Frequency Table
    // --------------------------------------------------------

    void displayFrequency()
    {
        cout << "\n";
        cout << "====================================================\n";
        cout << "             CHARACTER FREQUENCY\n";
        cout << "====================================================\n";

        cout << left
             << setw(15)
             << "Character"
             << "Frequency\n";

        cout << "----------------------------------------------------\n";

        for (const auto& pair : frequency)
        {
            unsigned char ch =
                pair.first;

            cout << left
                 << setw(15);

            if (ch == ' ')
                cout << "[SPACE]";
            else if (ch == '\n')
                cout << "[NEWLINE]";
            else if (ch == '\t')
                cout << "[TAB]";
            else
                cout << "'" << ch << "'";

            cout << pair.second
                 << '\n';
        }

        cout << "====================================================\n";
    }

    // --------------------------------------------------------
    // Write 32-bit Integer
    // --------------------------------------------------------

    void writeUint32(
        ofstream& out,
        uint32_t value)
    {
        out.write(
            reinterpret_cast<const char*>(&value),
            sizeof(value)
        );
    }

    // --------------------------------------------------------
    // Write 64-bit Integer
    // --------------------------------------------------------

    void writeUint64(
        ofstream& out,
        uint64_t value)
    {
        out.write(
            reinterpret_cast<const char*>(&value),
            sizeof(value)
        );
    }

    // --------------------------------------------------------
    // Read 32-bit Integer
    // --------------------------------------------------------

    bool readUint32(
        ifstream& in,
        uint32_t& value)
    {
        return static_cast<bool>(
            in.read(
                reinterpret_cast<char*>(&value),
                sizeof(value)
            )
        );
    }

    // --------------------------------------------------------
    // Read 64-bit Integer
    // --------------------------------------------------------

    bool readUint64(
        ifstream& in,
        uint64_t& value)
    {
        return static_cast<bool>(
            in.read(
                reinterpret_cast<char*>(&value),
                sizeof(value)
            )
        );
    }

public:

    // ========================================================
    // CONSTRUCTOR
    // ========================================================

    FileCompressor() = default;

    // ========================================================
    // DESTRUCTOR
    // ========================================================

    ~FileCompressor()
    {
        deleteTree(root);
    }

    // ========================================================
    // COMPRESS
    // ========================================================

    bool compress(
        const string& inputFile,
        const string& outputFile)
    {
        if (!fs::exists(inputFile))
        {
            cout << "\nERROR: Input file does not exist.\n";
            return false;
        }

        if (!fs::is_regular_file(inputFile))
        {
            cout << "\nERROR: Input path is not a valid file.\n";
            return false;
        }

        if (!analyzeFile(inputFile))
            return false;

        uint64_t originalSize =
            fs::file_size(inputFile);

        // Empty file
        if (originalSize == 0)
        {
            cout << "\nERROR: Cannot compress an empty file.\n";
            return false;
        }

        displayFrequency();

        deleteTree(root);
        root = nullptr;

        huffmanCodes.clear();

        buildTree();

        generateCodes(
            root,
            ""
        );

        // ----------------------------------------------------
        // Open files
        // ----------------------------------------------------

        ifstream input(
            inputFile,
            ios::binary
        );

        ofstream output(
            outputFile,
            ios::binary
        );

        if (!input)
        {
            cout << "\nERROR: Failed to read input file.\n";
            return false;
        }

        if (!output)
        {
            cout << "\nERROR: Failed to create compressed file.\n";
            return false;
        }

        // ----------------------------------------------------
        // HEADER
        // ----------------------------------------------------
        //
        // Format:
        //
        // 4 bytes  -> MAGIC "HUF1"
        // 8 bytes  -> original file size
        // 2 bytes  -> number of unique characters
        // For each character:
        // 1 byte   -> character
        // 8 bytes  -> frequency
        //
        // Remaining bytes = compressed bit stream
        //
        // ----------------------------------------------------

        output.write(
            "HUF1",
            4
        );

        writeUint64(
            output,
            originalSize
        );

        uint16_t uniqueCharacters =
            static_cast<uint16_t>(
                frequency.size()
            );

        output.write(
            reinterpret_cast<const char*>(
                &uniqueCharacters
            ),
            sizeof(uniqueCharacters)
        );

        for (const auto& pair : frequency)
        {
            unsigned char character =
                pair.first;

            output.write(
                reinterpret_cast<const char*>(
                    &character
                ),
                sizeof(character)
            );

            writeUint64(
                output,
                pair.second
            );
        }

        // ----------------------------------------------------
        // Encode data
        // ----------------------------------------------------

        unsigned char inputByte;

        uint8_t buffer = 0;

        int bitCount = 0;

        while (
            input.read(
                reinterpret_cast<char*>(&inputByte),
                sizeof(inputByte)
            )
        )
        {
            const string& code =
                huffmanCodes[inputByte];

            for (char bit : code)
            {
                buffer <<= 1;

                if (bit == '1')
                    buffer |= 1;

                bitCount++;

                if (bitCount == 8)
                {
                    output.put(
                        static_cast<char>(buffer)
                    );

                    buffer = 0;
                    bitCount = 0;
                }
            }
        }

        // Remaining bits
        if (bitCount > 0)
        {
            buffer <<= (8 - bitCount);

            output.put(
                static_cast<char>(buffer)
            );
        }

        input.close();
        output.close();

        uint64_t compressedSize =
            fs::file_size(outputFile);

        double ratio =
            static_cast<double>(compressedSize)
            /
            static_cast<double>(originalSize)
            * 100.0;

        double saving =
            100.0 - ratio;

        cout << "\n";
        cout << "====================================================\n";
        cout << "             COMPRESSION SUCCESSFUL\n";
        cout << "====================================================\n";

        cout << "Original File       : "
             << inputFile << '\n';

        cout << "Compressed File     : "
             << outputFile << '\n';

        cout << "Original Size       : "
             << originalSize
             << " bytes\n";

        cout << "Compressed Size     : "
             << compressedSize
             << " bytes\n";

        cout << fixed
             << setprecision(2);

        cout << "Compression Ratio   : "
             << ratio
             << "%\n";

        cout << "Space Saving        : "
             << saving
             << "%\n";

        cout << "====================================================\n";

        return true;
    }

    // ========================================================
    // DECOMPRESS
    // ========================================================

    bool decompress(
        const string& compressedFile,
        const string& outputFile)
    {
        if (!fs::exists(compressedFile))
        {
            cout << "\nERROR: Compressed file does not exist.\n";
            return false;
        }

        if (!fs::is_regular_file(compressedFile))
        {
            cout << "\nERROR: Invalid compressed file.\n";
            return false;
        }

        ifstream input(
            compressedFile,
            ios::binary
        );

        if (!input)
        {
            cout << "\nERROR: Cannot open compressed file.\n";
            return false;
        }

        // ----------------------------------------------------
        // Check magic number
        // ----------------------------------------------------

        char magic[4];

        if (!input.read(magic, 4))
        {
            cout << "\nERROR: Invalid compressed file.\n";
            return false;
        }

        if (
            magic[0] != 'H' ||
            magic[1] != 'U' ||
            magic[2] != 'F' ||
            magic[3] != '1'
        )
        {
            cout << "\nERROR: File is not a valid HUF file.\n";
            return false;
        }

        // ----------------------------------------------------
        // Read original size
        // ----------------------------------------------------

        uint64_t originalSize;

        if (!readUint64(
                input,
                originalSize))
        {
            cout << "\nERROR: Corrupted header.\n";
            return false;
        }

        // ----------------------------------------------------
        // Read frequency table
        // ----------------------------------------------------

        uint16_t uniqueCharacters;

        if (
            !input.read(
                reinterpret_cast<char*>(
                    &uniqueCharacters
                ),
                sizeof(uniqueCharacters)
            )
        )
        {
            cout << "\nERROR: Corrupted frequency table.\n";
            return false;
        }

        if (
            uniqueCharacters == 0 ||
            uniqueCharacters > 256
        )
        {
            cout << "\nERROR: Invalid character table.\n";
            return false;
        }

        frequency.clear();

        for (
            uint16_t i = 0;
            i < uniqueCharacters;
            i++)
        {
            unsigned char character;

            uint64_t freq;

            if (
                !input.read(
                    reinterpret_cast<char*>(
                        &character
                    ),
                    sizeof(character)
                )
            )
            {
                cout << "\nERROR: Corrupted compressed file.\n";
                return false;
            }

            if (
                !readUint64(
                    input,
                    freq
                )
            )
            {
                cout << "\nERROR: Corrupted frequency table.\n";
                return false;
            }

            if (freq == 0)
            {
                cout << "\nERROR: Invalid frequency data.\n";
                return false;
            }

            frequency[character] = freq;
        }

        // ----------------------------------------------------
        // Build tree
        // ----------------------------------------------------

        deleteTree(root);
        root = nullptr;

        buildTree();

        if (root == nullptr)
        {
            cout << "\nERROR: Unable to rebuild Huffman tree.\n";
            return false;
        }

        // ----------------------------------------------------
        // Open output file
        // ----------------------------------------------------

        ofstream output(
            outputFile,
            ios::binary
        );

        if (!output)
        {
            cout << "\nERROR: Cannot create output file.\n";
            return false;
        }

        // ----------------------------------------------------
        // Decode
        // ----------------------------------------------------

        HuffmanNode* current =
            root;

        uint64_t decodedBytes = 0;

        char byte;

        while (
            input.get(byte) &&
            decodedBytes < originalSize)
        {
            unsigned char value =
                static_cast<unsigned char>(
                    byte
                );

            for (int i = 7; i >= 0; i--)
            {
                int bit =
                    (value >> i) & 1;

                if (bit == 0)
                    current = current->left;
                else
                    current = current->right;

                if (current == nullptr)
                {
                    cout << "\nERROR: Corrupted compressed data.\n";

                    output.close();
                    input.close();

                    return false;
                }

                if (current->isLeaf())
                {
                    output.put(
                        static_cast<char>(
                            current->character
                        )
                    );

                    decodedBytes++;

                    current = root;

                    if (
                        decodedBytes ==
                        originalSize
                    )
                    {
                        break;
                    }
                }
            }
        }

        input.close();
        output.close();

        // ----------------------------------------------------
        // Verify decoded size
        // ----------------------------------------------------

        if (decodedBytes != originalSize)
        {
            cout << "\nERROR: Decompression failed.\n";
            cout << "Expected bytes : "
                 << originalSize
                 << '\n';

            cout << "Decoded bytes  : "
                 << decodedBytes
                 << '\n';

            return false;
        }

        cout << "\n";
        cout << "====================================================\n";
        cout << "            DECOMPRESSION SUCCESSFUL\n";
        cout << "====================================================\n";

        cout << "Compressed File : "
             << compressedFile
             << '\n';

        cout << "Output File     : "
             << outputFile
             << '\n';

        cout << "Restored Size   : "
             << fs::file_size(outputFile)
             << " bytes\n";

        cout << "====================================================\n";

        return true;
    }

    // ========================================================
    // VERIFY ORIGINAL DATA
    // ========================================================

    bool verifyFiles(
        const string& originalFile,
        const string& restoredFile)
    {
        if (
            !fs::exists(originalFile) ||
            !fs::exists(restoredFile)
        )
        {
            cout << "\nERROR: Verification files not found.\n";
            return false;
        }

        if (
            fs::file_size(originalFile) !=
            fs::file_size(restoredFile)
        )
        {
            cout << "\nVerification FAILED.\n";
            cout << "File sizes are different.\n";

            return false;
        }

        ifstream original(
            originalFile,
            ios::binary
        );

        ifstream restored(
            restoredFile,
            ios::binary
        );

        char a;
        char b;

        while (
            original.get(a) &&
            restored.get(b)
        )
        {
            if (a != b)
            {
                cout << "\nVerification FAILED.\n";
                cout << "File contents are different.\n";

                return false;
            }
        }

        if (
            original.eof() &&
            restored.eof()
        )
        {
            cout << "\n";
            cout << "====================================================\n";
            cout << "             VERIFICATION SUCCESSFUL\n";
            cout << "====================================================\n";

            cout << "Original and restored files are identical.\n";

            cout << "====================================================\n";

            return true;
        }

        cout << "\nVerification FAILED.\n";

        return false;
    }

    // ========================================================
    // DISPLAY FILE INFORMATION
    // ========================================================

    void displayFileInfo(
        const string& file)
    {
        if (!fs::exists(file))
        {
            cout << "\nFile does not exist.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================\n";
        cout << "                  FILE INFORMATION\n";
        cout << "====================================================\n";

        cout << "File Name : "
             << file
             << '\n';

        cout << "File Size : "
             << fs::file_size(file)
             << " bytes\n";

        cout << "====================================================\n";
    }

    // ========================================================
    // SHOW HUFFMAN CODES
    // ========================================================

    void displayCodes()
    {
        if (huffmanCodes.empty())
        {
            cout << "\nNo Huffman codes available.\n";
            return;
        }

        cout << "\n";
        cout << "====================================================\n";
        cout << "                HUFFMAN CODES\n";
        cout << "====================================================\n";

        for (const auto& pair : huffmanCodes)
        {
            unsigned char ch =
                pair.first;

            if (ch == ' ')
                cout << "[SPACE]";
            else if (ch == '\n')
                cout << "[NEWLINE]";
            else if (ch == '\t')
                cout << "[TAB]";
            else
                cout << "'" << ch << "'";

            cout << " -> "
                 << pair.second
                 << '\n';
        }

        cout << "====================================================\n";
    }
};

// ============================================================
// COMMAND LINE HELP
// ============================================================

void showHelp()
{
    cout << "\n";
    cout << "====================================================\n";
    cout << "           FILE COMPRESSION UTILITY\n";
    cout << "====================================================\n";

    cout << "\nUsage:\n\n";

    cout << "Compress:\n";
    cout << "  day30.exe -c input.txt output.huf\n\n";

    cout << "Decompress:\n";
    cout << "  day30.exe -d output.huf restored.txt\n\n";

    cout << "Verify:\n";
    cout << "  day30.exe -v original.txt restored.txt\n\n";

    cout << "Help:\n";
    cout << "  day30.exe -h\n";

    cout << "\n====================================================\n";
}

// ============================================================
// MAIN
// ============================================================

int main(
    int argc,
    char* argv[])
{
    FileCompressor compressor;

    // --------------------------------------------------------
    // COMMAND LINE MODE
    // --------------------------------------------------------

    if (argc > 1)
    {
        string command = argv[1];

        if (
            command == "-h" ||
            command == "--help"
        )
        {
            showHelp();
            return 0;
        }

        if (command == "-c")
        {
            if (argc != 4)
            {
                cout << "\nInvalid arguments.\n";
                showHelp();
                return 1;
            }

            return compressor.compress(
                argv[2],
                argv[3]
            ) ? 0 : 1;
        }

        if (command == "-d")
        {
            if (argc != 4)
            {
                cout << "\nInvalid arguments.\n";
                showHelp();
                return 1;
            }

            return compressor.decompress(
                argv[2],
                argv[3]
            ) ? 0 : 1;
        }

        if (command == "-v")
        {
            if (argc != 4)
            {
                cout << "\nInvalid arguments.\n";
                showHelp();
                return 1;
            }

            return compressor.verifyFiles(
                argv[2],
                argv[3]
            ) ? 0 : 1;
        }

        cout << "\nUnknown command.\n";
        showHelp();

        return 1;
    }

    // --------------------------------------------------------
    // MENU-DRIVEN MODE
    // --------------------------------------------------------

    int choice;

    string inputFile;
    string compressedFile;
    string restoredFile;

    do
    {
        cout << "\n\n";

        cout << "====================================================\n";
        cout << "          FILE COMPRESSION UTILITY\n";
        cout << "====================================================\n";

        cout << "1. Analyze File\n";
        cout << "2. Compress File\n";
        cout << "3. Decompress File\n";
        cout << "4. Verify Original Data\n";
        cout << "5. Display File Information\n";
        cout << "6. Display Huffman Codes\n";
        cout << "7. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "\nEnter input file: ";
                cin >> inputFile;

                compressor.compress(
                    inputFile,
                    "temp_analysis.huf"
                );

                if (fs::exists(
                        "temp_analysis.huf"))
                {
                    fs::remove(
                        "temp_analysis.huf"
                    );
                }

                break;
            }

            case 2:
            {
                cout << "\nEnter input file: ";
                cin >> inputFile;

                cout << "Enter compressed file name: ";
                cin >> compressedFile;

                compressor.compress(
                    inputFile,
                    compressedFile
                );

                break;
            }

            case 3:
            {
                cout << "\nEnter compressed file: ";
                cin >> compressedFile;

                cout << "Enter output file: ";
                cin >> restoredFile;

                compressor.decompress(
                    compressedFile,
                    restoredFile
                );

                break;
            }

            case 4:
            {
                cout << "\nEnter original file: ";
                cin >> inputFile;

                cout << "Enter restored file: ";
                cin >> restoredFile;

                compressor.verifyFiles(
                    inputFile,
                    restoredFile
                );

                break;
            }

            case 5:
            {
                cout << "\nEnter file name: ";
                cin >> inputFile;

                compressor.displayFileInfo(
                    inputFile
                );

                break;
            }

            case 6:
            {
                compressor.displayCodes();
                break;
            }

            case 7:
            {
                cout << "\nExiting File Compression Utility...\n";
                break;
            }

            default:
            {
                cout << "\nInvalid choice. Try again.\n";
            }
        }

    } while (choice != 7);

    return 0;
}