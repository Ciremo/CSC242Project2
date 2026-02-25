#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
 // STEP 1: Open the dictionary file
 // Authored by: Jhoana Mayle
 ifstream dict_file("words.txt"); 
 if (dict_file.fail()) {
 cout << "Could not open dictionary file." << endl;
 return 1;
 }
 // STEP 2: Define a vector of strings called words
 // Authored by: Jhoana Mayle
 vector<string> words;
