/*
 Name: Hamza Adnan
 Email: hadnan@crimson.ua.edu
 Course Section: Fall 2023 CS 201
 Homework #: 0
 Instructions to Compile: "g++ -o hw0 hw0.cpp"
 Instructions to Execute: "./hw0 inputfile fileByName fileByYear"
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Create a Movie class with parameters name, year, and actors
class Movie {
public:
    string name;
    int year;
    vector<string> actors;

    Movie(const string& n, int y, const vector<string>& a)
        : name(n), year(y), actors(a) {}

    //Operator for sorting by name and year
    bool operator<(const Movie& other) const {
        if (name != other.name) {
            return name < other.name;
        } else {
            return year < other.year;
        }
    }

    // Operator for sorting by year and name and breaking tie if year is the same
    static bool sortByYear(const Movie& a, const Movie& b) {
        return (a.year != b.year) ? (a.year < b.year) : (a.name < b.name);
    }
};

// split function splits the string at a certain "splitter" index and adds segments to parts
vector<string> split(const string& str, char splitter) {
    vector<string> parts;
    size_t start = 0;
    size_t end = str.find(splitter);
    
    while (end != string::npos) {
        parts.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(splitter, start);
    }
    
    parts.push_back(str.substr(start));
    return parts;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Incorrect number of arguments" << endl;
        return 1;
    }

    string inputFiledb = argv[1];
    ifstream inputFile(inputFiledb);

    if (!inputFile) {
        cerr << "Error: Cannot open input file: " << inputFiledb << endl;
        return 1;
    }

    
    //Create a vector with class Movie properties
    vector<Movie> movies;

    // Read input file and add its components to vector
    string line;
    	
    std::chrono::duration<double> timetaken[3];

	auto starttime = std::chrono::steady_clock::now();
    while (getline(inputFile, line)) {
        size_t yearStart = line.find_last_of('(');
        size_t yearEnd = line.find_last_of(')');
        
        if (yearStart != string::npos && yearEnd != string::npos && yearEnd > yearStart + 1) {
            string Name = line.substr(0, yearStart - 1);

            //Get rid of parenthesis
            string yearStr = line.substr(yearStart + 1, yearEnd - yearStart - 1);

            // Use stoi to convert year to int
            int year = stoi(yearStr);

            vector<string> actorList = split(line.substr(yearEnd + 2), '/');
            
            movies.emplace_back(Name, year, actorList);
        }
    }

    starttime = std::chrono::steady_clock::now();
    auto endtime = std::chrono::steady_clock::now();
	timetaken[0] = endtime - starttime;
     cout << "Time taken by function to create movies list: ";
        cout << timetaken[0].count() * 1000000 << " microseconds" << endl;


    inputFile.close();

	auto starttime = std::chrono::steady_clock::now();
    // -----------------------------------------
    sort(movies.begin(), movies.end());
    // -----------------------------------------
    auto endtime = std::chrono::steady_clock::now();
	timetaken[1] = endtime - starttime;
     cout << "Time taken by function to sort Movies by Name: "
         << timetaken[1].count() * 1000000 << " microseconds" << endl;



    string outputFileName = argv[2];
    ofstream outputByName(outputFileName);
    for (const Movie& movie : movies) {
        outputByName << movie.name << " (" << movie.year << ")";
        for (const string& actor : movie.actors) {
            outputByName << "/" << actor;
        }
        outputByName << "\n";
    }
    outputByName.close();

    // Sort and write to name output file
	auto starttime = std::chrono::steady_clock::now();
    // -----------------------------------------
    sort(movies.begin(), movies.end(), Movie::sortByYear);
    auto endtime = std::chrono::steady_clock::now();
	timetaken[2] = endtime - starttime;
     cout << "Time taken by function to sort Movies by Year: "
         << timetaken[2].count() * 1000000 << " microseconds" << endl;
    //------------------------------------------------
 
    //---------------------------------------------------

    string outputFileYear = argv[3];
    ofstream outputByYear(outputFileYear);
    for (const Movie& movie : movies) {
        outputByYear << movie.name << " (" << movie.year << ")";
        for (const string& actor : movie.actors) {
            outputByYear << "/" << actor;
        }
        outputByYear << "\n";
    }
    outputByYear.close();

    return 0;
}

/*References:
https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
https://www.geeksforgeeks.org/size_t-data-type-c-language/
https://www.geeksforgeeks.org/sort-c-stl/
https://cplusplus.com/reference/string/string/substr/
https://www.geeksforgeeks.org/creating-a-vector-of-class-objects-in-cpp/
https://stackoverflow.com/questions/7880/how-do-you-open-a-file-in-c

*/