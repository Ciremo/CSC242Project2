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
** Date: 		February 28, 2026
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Authhored by: Ever Hernandez
// Alphabet Generator
string create_cipher_alphabet(string key) {
    string cipher = "";
    for (char c : key) {
        char up = toupper(static_cast<unsigned char>(c));
        if (isalpha(static_cast<unsigned char>(up)) && cipher.find(up) == string::npos) {
            cipher += up;
        }
    }
    // Append remaining letters in reverse order as per Assignment 5 diagram
    for (char c = 'Z'; c >= 'A'; c--) {
        if (cipher.find(c) == string::npos) {
            cipher += c;
        }
    }
    return cipher;
}

// Authored by: Johana Mayle 
// File Processing
void transform_file(const string& in_name, const string& out_name, const string& cipher, bool decrypt) {
    ifstream in_file(in_name);
    ofstream out_file(out_name);

    if (!in_file || !out_file) {
        cerr << "Error opening files." << endl;
        return;
    }

    const string plain = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char ch;

    while (in_file.get(ch)) {
        if (isalpha(static_cast<unsigned char>(ch))) {
            bool isLower = islower(static_cast<unsigned char>(ch));
            char upper = toupper(static_cast<unsigned char>(ch));
            char transformed;

            if (decrypt) {
                // Find position in the scrambled alphabet (cipher) to get standard letter
                size_t pos = cipher.find(upper);
                transformed = plain[pos];
            }
            else {
                // Find position in standard alphabet (plain) to get scrambled letter
                size_t pos = plain.find(upper);
                transformed = cipher[pos];
            }
            out_file << (char)(isLower ? tolower(static_cast<unsigned char>(transformed)) : transformed);
        }
        else {
            out_file << ch;
        }
    }
}

// Authored by: Eric Mounnivong
// Main Logic
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

    // Logic to ensure decryption always goes to decrypted.txt
    // and encryption always goes to encrypted.txt per your requirement.
    if (mode == "-d") {
        inputFileName = "encrypted.txt"; // Assuming you are decrypting what you just encrypted
        outputFileName = "decrypted.txt";
    }
    else {
        inputFileName = "input.txt";
        outputFileName = "encrypted.txt";
    }

    string cipherAlphabet = create_cipher_alphabet(key);
    bool isDecrypt = (mode == "-d");

    transform_file(inputFileName, outputFileName, cipherAlphabet, isDecrypt);

    cout << "Success! Results saved in " << outputFileName << endl;

    return 0;
}
