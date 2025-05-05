//============================================================================
// Name        : CS300ProjectTwo(Nii_Tagoe).cpp
// Author      : Nii Amatey Tagoe
// Version     : 1.0
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "CS300ProjectTwo(Nii_Tagoe).h"

using namespace std;

// Cousre class representing the course and storing course objects
class Course {
public:
    std::string courseNumber;
    std::string courseTitle;
    std::vector<std::string> prereqs;

    //default contructor
    Course() : courseNumber(""), courseTitle(""), prereqs({}) {}

    Course(std::string courseCode, std::string title, std::vector<std::string> prerequisites = {})
        : courseNumber(courseCode), courseTitle(title), prereqs(prerequisites) {}
};

//Course hash table class
class CourseHashTable {
private:
    //an unordered_map for the storage of the courses used by the hash table 
    std::unordered_map<std::string, Course> courses;

public:
    //add new course to the hash table
    void addCourse(const Course& course) {
        courses[course.courseNumber] = course;
    }
    // get pointer to a course by it's number
    Course* getCourse(const std::string& courseCode) {
        //if the course does not exist 
        if (courses.find(courseCode) != courses.end()) {
            return &courses[courseCode];
        }
        else {
            //return null pointer
            return nullptr;
        }
    }
    // constant reference to the entire has table
    const std::unordered_map<std::string, Course>& getAllCourses() const {
        //return course
        return courses;
    }
};

//this function loads the course data from the CS300ProjectTwo text file
void loadData(CourseHashTable& courses, const std::string& fileName) {
    std::ifstream file(fileName);
    std::string line;
    //while getting each line 
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string part;
        std::vector<std::string> parts;
        //seperate by comma ','
        while (getline(iss, part, ',')) {
            parts.push_back(part);
        }

        std::string courseCode = parts[0];
        std::string title = parts[1];
        std::vector<std::string> prerequisites(parts.begin() + 2, parts.end());

        Course course(courseCode, title, prerequisites);
        courses.addCourse(course);
    }
}

//Displays the menu and all possible options
void printMenu() {
    std::cout << "1. Load Data Structure.\n"
        << "2. Print Course List.\n"
        << "3. Print Course.\n"
        << "9. Exit\n \n"
        << "What would you like to do: ";
}

//this function prints a sorted sample of the course list 
void printCourseList(const std::unordered_map<std::string, Course>& courses) {

    //vector to store sorted Course Number
    std::vector<std::string> courseCodes;
    //iterate through each key-value pair in the unordered_map
    for (const auto& pair : courses) {
        courseCodes.push_back(pair.first);
    }
    //sort the course numbers in courseCodes
    sort(courseCodes.begin(), courseCodes.end());
    //iterate over the sorted vector course codes
    for (const auto& number : courseCodes) {
        std::cout << number << ": " << courses.at(number).courseTitle << std::endl;
    }
}
//this function will print the course title and prerequistie 
void printCourse(const CourseHashTable& coursesTable) {
    auto courses = coursesTable.getAllCourses(); // This gets the unordered_map
    std::string code;
    std::cout << "What course do you want to know about? ";
    std::cin >> code;
    //used the find method of the unordered_map to find the needed course number
    auto it = courses.find(code);
    // if the iterator it does not equal the end of the map and if the course is found, dereferences the iterator to access the pair representing the course
    if (it != courses.end()) {
        const auto& course = it->second;
        //Print the title of the course accessed by course.courseTitle
        std::cout << "Course: " << course.courseTitle << "\nPrerequisites: ";
        //iterate over the prereqs seperated by space
        for (const auto& pre : course.prereqs) {
            std::cout << pre << " ";
        }
        std::cout << std::endl;
    }
    //else print Enter valid course number
    else {
        std::cout << "Enter a valid Course Number." << std::endl;
    }
}


//main
int main() {
    CourseHashTable courses;
    int choice;
    std::string fileName;

    cout << "Welcome to the Course Planner" << endl;
    do {
        cout << "\n";

        printMenu();
        std::cin >> choice;
        switch (choice) {

        case 1:
            std::cout << "Enter file name: ";
            std::cin >> fileName; //allows user to input the file name that has to be read and loaded
            loadData(courses, fileName);//File name to input is "CS300ProjectTwo.txt"
            break;
        case 2:
            std::cout << "Here is a sample schedule: \n"; 
            printCourseList(courses.getAllCourses());//gets the all courses and prints them out alphanumerically
            break;

        case 3:
            printCourse(courses);//user inputs course number and the console prints out the course title and prereqs if any 
            break;

        case 9:
            std::cout << "Thank you for using the course planner.\n";
            break;
        default:
            std::cout << choice << " is not a valid option. Please enter a number between 1 and 3.\n";
        }
    } while (choice != 9);

    return 0;
}
