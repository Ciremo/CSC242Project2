/* ---------------------------------------------------------------------------
** I attest that this following code represents my own work and is subject to
** the plagiarism policy found in the course syllabus.
** 
** Class: 		CSC 242
** Assignment: 	Final Project part 1
** File: 		source.cpp
** Description: Spell Checker for the English language. It uses a dictionary
** of words to check if a given word is speeled correctly or not. 
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
	// STEP 1: Open the dictionary file
	// Authored by: Jhoana Mayle
	ifstream dict_file("words.txt");
	if (dict_file.fail()) 
	{
		cout << "Could not open dictionary file: words.txt" << endl;
		return 1;
	}
	
	// STEP 2: Define a vector of strings called words
	// Authored by: Jhoana Mayle
	vector<string> words;
	
	// STEP 3: Read each word from the dictionary file and store it in the vector
	// Authored by: Eric Mounivong
	string word;
	while (dict_file >> word) 
	{
		words.push_back(word);
	}

	// STEP 4: Close the dictionary file
	// Authored by: Eric Mounivong
	dict_file.close();
	
	// STEP 5: Open the File to be checked
	// Authored by: Ever Hernandez
	ifstream check_file("words.txt");
	if (check_file.fail()) {
		cout << "Could not open file to be checked: words.txt" << endl;
		return 1;
	}

	// STEP 6: Check each input word against the dictionary
	// Authored by: Eric Mounivong
	string input_word;
	while (check_file >> input_word)
	{
		if (find(words.begin(), words.end(), input_word) != words.end()) 
		{
			cout << input_word << " : Word found." << endl;
		} 
		else
		{
			cout << input_word << " : Word not found." << endl;
		}
		string current_word;
		cout << "Enter a word to check (or type 'exit' to quit): ";
		while (cin >> current_word) 
		{
			if (current_word == "exit") 
			{
				break;
			}
			if (find(words.begin(), words.end(), current_word) != words.end()) 
			{
				cout << current_word << " : Word found." << endl;
			} 
			else 
			{
				cout << current_word << " : Word not found." << endl;
			}
			cout << "Enter a word to check (or type 'exit' to quit): ";
			check_file.close();
		}
		
		
	}

	check_file.close();
	return 0;
} // End of the program
