/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 		CSC 242
** Assignment: 	Final Project part 2
** File: 		source.cpp
** Description: 
**
** Authors: 	Jhoana Mayle, Ever Hernandez, Eric Mounivong
** Date: 		February 25, 2026
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

/**
 * Author: [Team Member 1 Name]
 * Creates the cipher alphabet by removing duplicate letters from the keyword
 * and appending the remaining alphabet letters in reverse order.
 */
string create_cipher_alphabet(string key) {
    string cipher = "";
    string upperKey = "";

    // Convert key to uppercase and remove duplicates
    for (char c : key) {
        char up = toupper(c);
        if (isalpha(up) && cipher.find(up) == string::npos) {
            cipher += up;
        }
    }

    // Append remaining letters of the alphabet in reverse order (Z to A)
    for (char c = 'Z'; c >= 'A'; c--) {
        if (cipher.find(c) == string::npos) {
            cipher += c;
        }
    }
    return cipher;
}

/**
 * Author: [Team Member 2 Name]
 * Processes the input file and writes the encrypted/decrypted result to the output file.
 * Uses pass-by-reference for strings to avoid unnecessary copying.
 */
void transform_file(const string& in_name, const string& out_name, const string& cipher, bool decrypt) {
    ifstream in_file(in_name);
    ofstream out_file(out_name);

    if (!in_file || !out_file) {
        cerr << "Error opening files." << endl;
        return;
    }

    char ch;
    string plain = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    while (in_file.get(ch)) {
        if (isalpha(ch)) {
            bool isLower = islower(ch);
            char upper = toupper(ch);
            char transformed;

            if (decrypt) {
                size_t pos = cipher.find(upper);
                transformed = plain[pos];
            }
            else {
                size_t pos = plain.find(upper);
                transformed = cipher[pos];
            }

            // Preserve original casing
            out_file << (char)(isLower ? tolower(transformed) : transformed);
        }
        else {
            out_file << ch; // Keep spaces, numbers, and punctuation
        }
    }

    in_file.close();
    out_file.close();
}

/**
 * Author: [Team Member 3 Name]
 * Main execution block to handle user input and coordinate the transformation.
 */
int main() {
    string mode, key, inputFileName, outputFileName;

    cout << "Enter mode (-e to encrypt, -d to decrypt): ";
    cin >> mode;

    cout << "Enter keyword: ";
    cin >> key;

    if (key.empty()) {
        cout << "Error: It is an error not to supply a keyword." << endl;
        return 1;
    }

    // Based on assignment example: crypt -d -kFEATHER encrypt.txt output.txt
    inputFileName = "encrypt.txt";
    outputFileName = "output.txt";

    string cipherAlphabet = create_cipher_alphabet(key);
    bool isDecrypt = (mode == "-d");

    transform_file(inputFileName, outputFileName, cipherAlphabet, isDecrypt);

    cout << "Success! Check " << outputFileName << " for results." << endl;

    return 0;
}
