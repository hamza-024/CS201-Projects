#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Function to split a string based on a delimiter into a vector
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main(int argc, char *argv[]) {
    int i = 0;
    // Check for correct command-line arguments
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <db file> <query file>" << endl;
        return -1;
    }

    string line;
    unordered_map<string, vector<string>> movieToActorsMap;
    ifstream dbfile(argv[1]);
    if (!dbfile.is_open()) {
        cout << "Unable to open file: " << argv[1] << endl;
        return -1;
    }

    cout << "***Reading db file " << argv[1] << "***" << endl;
    while (getline(dbfile, line)) {
        vector<string> tokens = split(line, '/');
        if (!tokens.empty()) {
            string movieName = tokens[0];
            tokens.erase(tokens.begin()); // Remove the movie name from the list
            movieToActorsMap[movieName] = tokens;
        }
    }
    dbfile.close();

    // Now let's print the content of the map
    for (const auto &pair : movieToActorsMap) {
        cout << "***Line " << ++i << " ***" << endl;
        cout << "***Movie: " << pair.first << "***" << endl;
        cout << "Actors: " << endl;
        for (const auto &actor : pair.second) {
            cout << "\t" << actor << endl;
        }
    }
    cout << "***Done reading db file " << argv[1] << "***" << endl;

    // The query file part can be similar to what was done before, or it can be adapted to perform lookups in the map.

    return 0;
}
