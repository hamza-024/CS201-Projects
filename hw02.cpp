/*
 Name: Hamza Adnan
 Email: hadnan@crimson.ua.edu
 Course Section: Fall 2023 CS 201
 Homework #: 2
 Instructions to Compile: "g++ hw2.cpp"
 Instructions to Execute: "./a.exe inputfile.txt"
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

void countWordsInLine(const string& line, map<string, int>& wordCount) {
    istringstream wordStream(line);
    string word;

    while (wordStream >> word) {      

        // Convert the word to lowercase to ensure case-insensitive counting
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Increment word count in the map
        wordCount[word]++;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Incorrect number of arguments" << endl;
        return 1;
    }

    string inputWords = argv[1];
    ifstream file(inputWords);

    if (!file) {
        cerr << "Error: Cannot open input file: " << inputWords << endl;
        return 1;
    }

    map<string, int> wordCount;

    string inputLine;
    while (getline(file, inputLine)) {
        countWordsInLine(inputLine, wordCount);
    }

    // Convert map to vector for custom sorting
    vector<pair<string, int>> vec(wordCount.begin(), wordCount.end());

    // Sort the vector by frequency (in descending order) and then by word (in ascending order)
    sort(vec.begin(), vec.end(),
        [](const pair<string, int>& word1, const pair<string, int>& word2) {
            if (word1.second != word2.second) {
                return word1.second > word2.second;
            }
            return word1.first < word2.first;
        });

    for (const auto& pair : vec) {
        cout << pair.first << ": " << pair.second << endl;
    }

    cout << "Total Countable Words in file: " << wordCount.size() << endl;

    file.close();
    return 0;
}

/*References:
https://www.geeksforgeeks.org/processing-strings-using-stdistringstream/
https://en.cppreference.com/w/cpp/algorithm/find
https://www.geeksforgeeks.org/sort-vector-of-pairs-in-descending-order-in-c/
https://www.geeksforgeeks.org/vector-of-maps-in-c-with-examples/
*/
