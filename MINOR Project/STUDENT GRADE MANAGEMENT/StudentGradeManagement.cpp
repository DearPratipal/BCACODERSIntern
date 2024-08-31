#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure to store student information
struct Student {
    string name;
    vector<double> grades;
};

// Function to add a new student
void addStudent(vector<Student> &students) {
    Student student;
    cout << "Enter student name: ";
    cin.ignore(); // Ignore the newline left in the buffer
    getline(cin, student.name);

    int numGrades;
    cout << "Enter the number of grades for " << student.name << ": ";
    cin >> numGrades;

    double grade;
    for (int i = 0; i < numGrades; ++i) {
        cout << "Enter grade " << i + 1 << ": ";
        cin >> grade;
        student.grades.push_back(grade);
    }

    students.push_back(student);
    cout << "Student added successfully." << endl;
}

// Function to calculate the average grade of a student
double calculateAverage(const vector<double> &grades) {
    if (grades.empty()) return 0.0;

    double sum = 0;
    for (double grade : grades) {
        sum += grade;
    }
    return sum / grades.size();
}

// Function to display all students and their grades
void displayStudents(const vector<Student> &students) {
    if (students.empty()) {
        cout << "No students available." << endl;
        return;
    }

    cout << "\n--- Student Grades ---" << endl;
    for (const auto &student : students) {
        cout << "Name: " << student.name << endl;
        cout << "Grades: ";
        for (double grade : student.grades) {
            cout << grade << " ";
        }
        cout << "\nAverage: " << calculateAverage(student.grades) << endl;
        cout << "-----------------------" << endl;
    }
}

// Function to display the menu
void displayMenu() {
    cout << "\nStudent Grade Management System" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Display All Students" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    vector<Student> students;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                displayStudents(students);
                break;
            case 3:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
