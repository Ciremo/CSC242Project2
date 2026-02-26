/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 		CSC 242
** Assignment: 	Final Project part 1
** File: 		source.cpp
** Description: Spell Checker for the English language. It uses a dictionary
** of words to check if a given word is in the dictionary or not.
**
** Authors: 	Jhoana Mayle, Ever Hernandez, Eric Mounivong
** Date: 		February 25, 2026
** -------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // STEP 1: Open the dictionary file.
    // Authored by: Jhoana Mayle
    ifstream dict_file("words.txt");
    if (dict_file.fail())
    {
        cout << "Could not open dictionary file: words.txt" << endl;
        return 1;
    }

    // STEP 2: Define a vector of strings called words.
    // Authored by: Jhoana Mayle
    vector<string> words;

    // STEP 3: For each word in the dictionary file, append the word to the words vector.
    // Authored by: Eric Mounivong
    string word;
    while (dict_file >> word)
    {
        words.push_back(word);
    }

    // Sort so we can use binary_search (faster than find)
    // Authored by: Eric Mounivong
    sort(words.begin(), words.end());

    // STEP 4: Open the file to be checked.
    // Authored by: Ever Hernandez
    ifstream check_file("input.txt"); // <-- change this to the file you want to spellcheck
    if (check_file.fail())
    {
        cout << "Could not open file to be checked: input.txt" << endl;
        return 1;
    }

    // STEP 5: For each word in that file, if the word is not contained in the words vector, print the word.
    // Authored by: Eric Mounivong
    string input_word;
    while (check_file >> input_word)
    {
        // Using binary_search since we sorted the vector
        if (!binary_search(words.begin(), words.end(), input_word))
        {
            cout << input_word << endl;
        }
    }

    return 0;
} // End of the program

