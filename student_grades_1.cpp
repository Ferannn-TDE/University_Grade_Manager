////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Author : Odedairo Oluwaferanmi Ayodele (800743548)//////////////////////////////////////////////////////////////
// To run in terminal : g++ -std=c++17 -o student_grades_1 student_grades_1.cpp and then ./student_grades_1///////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Discussion of the Data Structure:
// We are using `std::vector` to store the student, course, and grade information. 
// A vector is a dynamic array that allows us to store data contiguously in memory and access it via an index. 
// This choice was made for the following reasons:
//
// 1. **Pros**:
//    - **Dynamic resizing**: Vectors automatically adjust their size as data is added, making them flexible for an unknown number of records.
//    - **Efficient access**: We can access elements by index with constant time complexity (O(1)).
//    - **Simple implementation**: The vector is easy to implement and use, with built-in support for adding and removing elements.
//    - **Memory management**: Vectors manage memory efficiently, growing as necessary when more space is needed, so manual resizing is not required.
//
// 2. **Cons**:
//    - **Costly insertions/removals at the beginning or middle**: While adding/removing elements at the end is efficient, it can be expensive (O(n)) when inserting/removing elements from the middle or start of the vector due to the need to shift elements.
//    - **Extra memory overhead**: Vectors might allocate more memory than needed to accommodate growth, which can lead to memory wastage in some cases.
//
// Based on the requirements of this project (storing lists of students, courses, and grades), the use of `std::vector` was chosen for its flexibility, ease of use, and efficient element access. Although other data structures (e.g., linked lists or arrays) could be used, vectors are a good fit for the problem at hand, as we are primarily adding, modifying, and accessing data sequentially.


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Structure to store student information
struct Student {
    string firstName, lastName, id, phone;
};

// Structure to store course information
struct Course {
    string courseNumber, courseName;
};

// Structure to store grade information
struct Grade {
    string studentID, courseNumber;
    char grade;
};

// Global vectors to store students, courses, and grades
vector<Student> students;
vector<Course> courses;
vector<Grade> grades;

// Function to load student data from a file
void loadStudents() {
    ifstream file("student.dat"); // Open the student data file
    if (!file) {
        cerr << "Error opening student.dat" << endl;
        return;
    }
    string header;
    getline(file, header); // Read and discard the header of the file
    cout << "Reading student.dat:\n"; // Debug output
    Student s;
    // Read the student information and store it in the 'students' vector
    while (file >> s.firstName >> s.lastName >> s.id >> s.phone) {
        cout << "Student: " << s.firstName << " " << s.lastName << " | ID: " << s.id << " | Phone: " << s.phone << endl;
        students.push_back(s);
    }
    file.close(); // Close the file after reading
}

// Function to load course data from a file
void loadCourses() {
    ifstream file("course.dat"); // Open the course data file
    if (!file) {
        cerr << "Error opening course.dat" << endl;
        return;
    }
    string header;
    getline(file, header); // Read and discard the header of the file
    cout << "Reading course.dat:\n"; // Debug output
    Course c;
    // Read the course information and store it in the 'courses' vector
    while (file >> c.courseNumber >> c.courseName) {
        cout << "Course: " << c.courseNumber << " - " << c.courseName << endl;
        courses.push_back(c);
    }
    file.close(); // Close the file after reading
}

// Function to load grade data from a file
void loadGrades() {
    ifstream file("grade.dat"); // Open the grade data file
    if (!file) {
        cerr << "Error opening grade.dat" << endl;
        return;
    }
    string header;
    getline(file, header); // Read and discard the header of the file
    cout << "Reading grade.dat:\n"; // Debug output
    Grade g;
    // Read the grade information and store it in the 'grades' vector
    while (file >> g.studentID >> g.courseNumber >> g.grade) {
        cout << "Grade: Student ID: " << g.studentID << " | Course: " << g.courseNumber << " | Grade: " << g.grade << endl;
        grades.push_back(g);
    }
    file.close(); // Close the file after reading
}

// Function to save data to output files
void saveData() {
    ofstream studentFile("student.out"); // Open student output file
    ofstream courseFile("course.out"); // Open course output file
    ofstream gradeFile("grade.out"); // Open grade output file
    
    // Write student data to the student output file
    studentFile << "Firstname Lastname ID Phone\n";
    for (const auto& s : students) {
        studentFile << s.firstName << " " << s.lastName << " " << s.id << " " << s.phone << "\n";
    }

    // Write course data to the course output file
    courseFile << "CourseNumber CourseName\n";
    for (const auto& c : courses) {
        courseFile << c.courseNumber << " " << c.courseName << "\n";
    }

    // Write grade data to the grade output file
    gradeFile << "StudentID CourseNumber Grade\n";
    for (const auto& g : grades) {
        gradeFile << g.studentID << " " << g.courseNumber << " " << g.grade << "\n";
    }
    
    studentFile.close(); // Close the student output file
    courseFile.close(); // Close the course output file
    gradeFile.close(); // Close the grade output file

    // Print confirmation that data has been saved
    cout << "Data has been successfully saved to the output files.\n";
}

// Function to add or modify a student's grade
void addModifyGrade() {
    string studentID, firstName, lastName, courseNumber;
    char grade;
    bool studentFound = false;

    // Ask for the student's ID
    cout << "Enter Student ID: ";
    cin >> studentID;

    // Search for the student in the students vector
    for (const auto& s : students) {
        if (s.id == studentID) {
            studentFound = true; // Student found
            break;
        }
    }

    // If the student is not found, notify the user and return
    if (!studentFound) {
        cout << "Student not found. Cannot add/modify grade.\n";
        return;
    }

    // Ask for the course number
    cout << "Enter Course Number: ";
    cin >> courseNumber;

    // Ask for the grade with validation
    cout << "Enter Grade (A, B, C, D, F, I or Q to quit): ";
    while (true) {
        cin >> grade; // Read the grade input
        // Check if user wants to quit
        if (grade == 'Q' || grade == 'q') {
            cout << "Quitting grade entry.\n";
            return;
        }

        // Validate grade input
        if (grade == 'A' || grade == 'B' || grade == 'C' || grade == 'D' || grade == 'F' || grade == 'I') {
            break; // Valid grade, exit the loop
        } else {
            cout << "Invalid grade. Please enter one of A, B, C, D, F, I, or Q to quit: ";
        }
    }

    // Check if the grade exists for this student and course, and modify it if found
    bool gradeFound = false;
    for (auto& g : grades) {
        if (g.studentID == studentID && g.courseNumber == courseNumber) {
            g.grade = grade; // Modify the existing grade
            gradeFound = true;
            cout << "Grade modified successfully." << endl;
            break;
        }
    }

    // If no existing grade found, add the new grade for the student and course
    if (!gradeFound) {
        Grade newGrade{studentID, courseNumber, grade};
        grades.push_back(newGrade);
        cout << "Grade added successfully." << endl;
    }
}

// Function to generate a grade report for a specific student
void studentGradeReport() {
    string studentID;
    cout << "Enter Student ID for report: ";
    cin >> studentID;

    bool found = false;
    cout << "Grade Report for Student ID: " << studentID << endl;
    for (const auto& g : grades) {
        if (g.studentID == studentID) {
            cout << "Course: " << g.courseNumber << " | Grade: " << g.grade << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No grades found for this student." << endl;
    }
}

// Function to generate a grade report for a specific course
void courseGradeReport() {
    string courseNumber;
    cout << "Enter Course Number for report: ";
    cin >> courseNumber;

    bool found = false;
    cout << "Grade Report for Course: " << courseNumber << endl;
    for (const auto& g : grades) {
        if (g.courseNumber == courseNumber) {
            cout << "Student ID: " << g.studentID << " | Grade: " << g.grade << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No grades found for this course." << endl;
    }
}

// Function to list all students
void listStudents() {
    cout << "List of Students:\n";
    for (const auto& s : students) {
        cout << s.firstName << " " << s.lastName << " | ID: " << s.id << " | Phone: " << s.phone << endl;
    }
}

// Function to display all courses
void displayCourses() {
    cout << "List of Courses:\n";
    for (const auto& c : courses) {
        cout << c.courseNumber << " - " << c.courseName << endl;
    }
}

// Function to remove a grade for a student in a course
void removeGrade() {
    string studentID, courseNumber;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cout << "Enter Course Number: ";
    cin >> courseNumber;
    
    for (auto it = grades.begin(); it != grades.end(); ++it) {
        if (it->studentID == studentID && it->courseNumber == courseNumber) {
            grades.erase(it); // Remove the grade
            cout << "Grade removed successfully." << endl;
            return;
        }
    }
    cout << "Grade not found." << endl;
}

// Function to display the main menu and handle user choices
void menu() {
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Add/Modify a grade\n";
        cout << "2. Remove a grade\n";
        cout << "3. Student grade report\n";
        cout << "4. Course grade report\n";
        cout << "5. List students\n";
        cout << "6. List courses\n";
        cout << "7. Save Data\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addModifyGrade(); // Call the function to add/modify grades
                break;
            case 2:
                removeGrade(); // Call the function to remove a grade
                break;
            case 3:
                studentGradeReport(); // Call the function to generate a student report
                break;
            case 4:
                courseGradeReport(); // Call the function to generate a course report
                break;
            case 5:
                listStudents(); // List all students
                break;
            case 6:
                displayCourses(); // Display all courses
                break;
            case 7:
                saveData(); // Save data to files
                break;
            case 8:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 8); // Continue until the user selects exit
}

int main() {
    loadStudents(); // Load student data
    loadCourses(); // Load course data
    loadGrades(); // Load grade data
    menu(); // Display the menu and prompt the user for actions
    return 0; // End of the program
}
