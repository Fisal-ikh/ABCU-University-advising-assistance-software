//Author: Fisal Ikhmayes 
//School: SNHU
//Class: CS300 Project 2


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

// Course class to hold course information
class Course {
public:
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;

    Course() {}
    Course(string number, string title) : courseNumber(number), courseTitle(title) {}
};

// Function 
void loadCourseData(string filename, unordered_map<string, Course>& courses);
void printCourseList(const unordered_map<string, Course>& courses);
void printCourse(const unordered_map<string, Course>& courses, const string& courseNumber);

int main() {
    unordered_map<string, Course> courses;
    string filename;

    
    filename = ("ABCU_Advising_Program_Input.txt");

    // Load course data into hash table
    loadCourseData(filename, courses);

    // Menu loop
    int choice = 0;
    while (choice != 4) {
        cout << "\nMenu:\n";
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                loadCourseData(filename, courses);
                cout << "Data loaded successfully.\n";
                break;
            case 2:
                printCourseList(courses);
                break;
            case 3:
                {
                    string courseNumber;
                    cout << "Enter the course number:";
                    cin >> courseNumber;
                    printCourse(courses, courseNumber);
                }
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}

// Function to load course data from file into hash table
void loadCourseData(string filename, unordered_map<string, Course>& courses) {
    ifstream file(filename);
    if (file.is_open()) {
        courses.clear(); // Clear existing data

        string line;
        while (getline(file, line)) {
            string courseNumber, courseTitle, prerequisite;
            stringstream ss(line);
            getline(ss, courseNumber, ',');
            getline(ss, courseTitle, ',');

            Course course(courseNumber, courseTitle);
            while (getline(ss, prerequisite, ',')) {
                course.prerequisites.push_back(prerequisite);
            }

            courses[courseNumber] = course;
        }

        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}

// Function to print course list in alphanumeric order
void printCourseList(const unordered_map<string, Course>& courses) {
    vector<string> courseNumbers;
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }

    sort(courseNumbers.begin(), courseNumbers.end());

    cout << "Course List:\n";
    for (const auto& number : courseNumbers) {
        cout << number << ": " << courses.at(number).courseTitle << "\n";
    }
}

// Function to print course information
void printCourse(const unordered_map<string, Course>& courses, const string& courseNumber) {
    if (courses.find(courseNumber) != courses.end()) {
        cout << "Course Number: " << courseNumber << "\n";
        cout << "Course Title: " << courses.at(courseNumber).courseTitle << "\n";
        cout << "Prerequisites:\n";
        for (const auto& prerequisite : courses.at(courseNumber).prerequisites) {
            cout << prerequisite << "\n";
        }
    } else {
        cout << "Course not found.\n";
    }
}
