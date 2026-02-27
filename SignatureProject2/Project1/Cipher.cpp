/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
**
** Class: 		CSC 242
** Assignment: 	Final Project part 2
** File: 		Cipher.cpp
** Description: A program that encrypts or decrypts a file using the Caesar Cipher
**
** Authors: 	Jhoana Mayle, Ever Hernandez, Eric Mounivong
** Date: 		February 28, 2026
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Authored by: Ever Hernandez
// Alphabet Generator
string create_cipher_alphabet(string key) // This function creates a cipher alphabet based on the provided key, ensuring that it includes unique letters from the key followed by the remaining letters of the alphabet in reverse order.
{
    string cipher = "";
    for (char c : key) 
    {
        char up = toupper(static_cast<unsigned char>(c));
        if (isalpha(static_cast<unsigned char>(up)) && cipher.find(up) == string::npos) 
        {
            cipher += up;
        }
    }
    // Append remaining letters in reverse order as per Assignment 5 diagram
    for (char c = 'Z'; c >= 'A'; c--)
    {
        if (cipher.find(c) == string::npos)
        {
            cipher += c;
        }
    }
    return cipher;
}

// Authored by: Jhoana Mayle 
// File Processing
void transform_file(const string& in_name, const string& out_name, const string& cipher, bool decrypt) // This function reads from the input file, transforms each character based on the cipher alphabet (either encrypting or decrypting), and writes the result to the output file. 
// It handles both uppercase and lowercase letters while preserving non-alphabetic characters.
{
	ifstream in_file(in_name); // Open the input file for reading
	ofstream out_file(out_name); // Open the output file for writing

	if (!in_file || !out_file) // Check if files opened successfully
    {
        cerr << "Error opening files." << endl;
        return;
    }

    const string plain = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    char ch;

	while (in_file.get(ch)) // Read each character from the input file
    {
		if (isalpha(static_cast<unsigned char>(ch))) // Check if the character is an alphabet letter
        {
            bool isLower = islower(static_cast<unsigned char>(ch));
            char upper = toupper(static_cast<unsigned char>(ch));
            char transformed;

            if (decrypt)
            {
                // Find position in the scrambled alphabet (cipher) to get standard letter
                size_t pos = cipher.find(upper);
                transformed = plain[pos];
            }
            else
            {
                // Find position in standard alphabet (plain) to get scrambled letter
                size_t pos = plain.find(upper);
                transformed = cipher[pos];
            }
            out_file << (char)(isLower ? tolower(static_cast<unsigned char>(transformed)) : transformed);
        }
        else
        {
            out_file << ch;
        }
    }
}

// Authored by: Eric Mounivong
// Main Logic
int main() // The main function prompts the user for the mode (encryption or decryption) and the keyword, validates the input, and then calls the appropriate functions to perform the transformation on the specified files. 
           //It ensures that decryption always reads from "encrypted.txt" and writes to "decrypted.txt", while encryption reads from "input.txt" and writes to "encrypted.txt".
{
    string mode, key, inputFileName, outputFileName;

    cout << "Enter mode (-e to encrypt, -d to decrypt): ";
    cin >> mode;
    cout << "Enter keyword: ";
    cin >> key;

	if (key.empty()) // Validate that a keyword is provided
    {
        cout << "Error: It is an error not to supply a keyword." << endl;
        return 1;
    }

    // Logic to ensure decryption always goes to decrypted.txt
    // and encryption always goes to encrypted.txt per your requirement.
    if (mode == "-d")
    {
        inputFileName = "encrypted.txt"; // Assuming you are decrypting what you just encrypted
        outputFileName = "decrypted.txt";
    }
    else  
    {
        inputFileName = "input.txt";
        outputFileName = "encrypted.txt";
    }

	string cipherAlphabet = create_cipher_alphabet(key); // Generate the cipher alphabet based on the provided keyword
    bool isDecrypt = (mode == "-d"); 

	transform_file(inputFileName, outputFileName, cipherAlphabet, isDecrypt); // Perform the file transformation based on the mode (encryption or decryption)

	cout << "Success! Results saved in " << outputFileName << endl; // Inform the user that the process was successful and indicate where the results are saved

    return 0;
} // End of the main function and the program.
