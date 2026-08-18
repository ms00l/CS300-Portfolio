#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// whitespace trim method
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// loading courses into hash table
void LoadCourses(string filePath, unordered_map<string, Course>& courseTable) {
    ifstream courseFile(filePath);
    
    if (!courseFile.is_open()) {
        cout << "Error: Could not open file " << filePath << endl;
        return;
    }

    string line;
    while (getline(courseFile, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // trim commas
        while (getline(ss, token, ',')) {
            tokens.push_back(trim(token));
        }

        // formatting error check
        if (tokens.size() < 2) {
            cout << "Error: Line missing course number or name. Skipping." << endl;
            continue;
        }

        Course newCourse;
        newCourse.courseNumber = tokens[0];
        newCourse.name = tokens[1];

        // check for blanks
        if (newCourse.courseNumber == "" || newCourse.name == "") {
            cout << "Error: Blank course number or name found. Skipping." << endl;
            continue;
        }

        // prerequisite add
        if (tokens.size() > 2) {
            for (size_t i = 2; i < tokens.size(); ++i) {
                newCourse.prerequisites.push_back(tokens[i]);
            }
        }

        // final insert
        courseTable[newCourse.courseNumber] = newCourse;
    }

    courseFile.close();
    cout << "Course data loaded successfully." << endl;
}

// print the alphanumeric list
void PrintAllCourses(const unordered_map<string, Course>& courseTable) {
    vector<string> keyList;

    // extract course nums from hash table
    for (auto const& pair : courseTable) {
        keyList.push_back(pair.first);
    }

    // sorting alphanumerically
    sort(keyList.begin(), keyList.end());

    // loop sorted keys and print
    cout << "\nHere is a sample schedule:" << endl;
    for (const string& key : keyList) {
        Course course = courseTable.at(key);
        cout << course.courseNumber << ", " << course.name << endl;
    }
}

// print specific course
void PrintCourseInformation(string searchCourseNumber, const unordered_map<string, Course>& courseTable) {
    transform(searchCourseNumber.begin(), searchCourseNumber.end(), searchCourseNumber.begin(), ::toupper);

    if (courseTable.find(searchCourseNumber) != courseTable.end()) {
        Course course = courseTable.at(searchCourseNumber);
        cout << "\n" << course.courseNumber << ", " << course.name << endl;
        cout << "Prerequisites: ";
        
        if (course.prerequisites.empty()) {
            cout << "None" << endl;
        } else {
            for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                string prereqID = course.prerequisites[i];
                
                // grabbing prereq if it exists
                if (courseTable.find(prereqID) != courseTable.end()) {
                    cout << prereqID << ": " << courseTable.at(prereqID).name;
                } else {
                    cout << prereqID << ": Unknown";
                }

                if (i < course.prerequisites.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "Error: Course " << searchCourseNumber << " not found." << endl;
    }
}

int main() {
    unordered_map<string, Course> courseTable;
    int userChoice = 0;
    bool dataLoaded = false;
    string fileName;

    cout << "Welcome to the course planner." << endl;

    while (userChoice != 9) {
        cout << "\n  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << "What would you like to do? ";
        
        // input validation
        if (!(cin >> userChoice)) {
            cout << "Error: Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (userChoice) {
            case 1:
                cout << "Enter the file name to load: ";
                cin >> fileName;
                LoadCourses(fileName, courseTable);
                dataLoaded = true;
                break;

            case 2:
                if (!dataLoaded) {
                    cout << "Error: You must load the file data first (Option 1)." << endl;
                } else {
                    PrintAllCourses(courseTable);
                }
                break;

            case 3:
                if (!dataLoaded) {
                    cout << "Error: You must load the file data first (Option 1)." << endl;
                } else {
                    cout << "What course do you want to know about? ";
                    string searchCourse;
                    cin >> searchCourse;
                    PrintCourseInformation(searchCourse, courseTable);
                }
                break;

            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;

            default:
                cout << "Error: Invalid option. Please enter 1, 2, 3, or 9." << endl;
                break;
        }
    }

    return 0;
}