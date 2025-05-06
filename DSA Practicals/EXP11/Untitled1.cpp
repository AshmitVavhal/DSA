#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    int rollNumber;
    string name;
    string division;
    string address;
};

class StudentInfo {
private:
    string filename;

public:
    StudentInfo(string file) {
        filename = file;
    }

    // Function to add student data
    void addStudent() {
        ofstream outFile(filename, ios::app); // open in append mode
        if (!outFile) {
            cout << "Error opening file!" << endl;
            return;
        }

        Student student;
        cout << "Enter roll number: ";
        cin >> student.rollNumber;
        cin.ignore(); // to ignore the newline character left by cin

        cout << "Enter name: ";
        getline(cin, student.name);

        cout << "Enter division: ";
        getline(cin, student.division);

        cout << "Enter address: ";
        getline(cin, student.address);

        outFile << student.rollNumber << "\n";
        outFile << student.name << "\n";
        outFile << student.division << "\n";
        outFile << student.address << "\n";
        outFile << "----\n"; // Separator for easy reading
        outFile.close();

        cout << "Student record added successfully!" << endl;
    }

    // Function to display student information by roll number
    void displayStudent(int rollNumber) {
        ifstream inFile(filename); // open in read mode
        if (!inFile) {
            cout << "Error opening file!" << endl;
            return;
        }

        Student student;
        bool found = false;

        // Read student records until the end of the file
        while (inFile >> student.rollNumber) {
            inFile.ignore(); // Ignore the newline after reading roll number
            getline(inFile, student.name);
            getline(inFile, student.division);
            getline(inFile, student.address);
            inFile.ignore();  // Ignore the separator line

            if (student.rollNumber == rollNumber) {
                found = true;
                cout << "Student Details: " << endl;
                cout << "Roll Number: " << student.rollNumber << endl;
                cout << "Name: " << student.name << endl;
                cout << "Division: " << student.division << endl;
                cout << "Address: " << student.address << endl;
                break;
            }
        }

        if (!found) {
            cout << "Student with roll number " << rollNumber << " not found!" << endl;
        }

        inFile.close();
    }

    // Function to delete a student record by roll number
    void deleteStudent(int rollNumber) {
        ifstream inFile(filename); // open in read mode
        if (!inFile) {
            cout << "Error opening file!" << endl;
            return;
        }

        ofstream outFile("temp.txt"); // temporary file to write data
        if (!outFile) {
            cout << "Error creating temporary file!" << endl;
            return;
        }

        Student student;
        bool found = false;

        // Read each student and write to the temp file, skipping the record to be deleted
        while (inFile >> student.rollNumber) {
            inFile.ignore();  // Ignore the newline after reading roll number
            getline(inFile, student.name);
            getline(inFile, student.division);
            getline(inFile, student.address);
            inFile.ignore();  // Ignore the separator line

            if (student.rollNumber == rollNumber) {
                found = true;
                cout << "Student with roll number " << rollNumber << " deleted successfully!" << endl;
            } else {
                outFile << student.rollNumber << "\n";
                outFile << student.name << "\n";
                outFile << student.division << "\n";
                outFile << student.address << "\n";
                outFile << "----\n"; // Separator
            }
        }

        if (!found) {
            cout << "Student with roll number " << rollNumber << " not found!" << endl;
        }

        inFile.close();
        outFile.close();

        // Remove the original file and rename the temporary file
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
    }
};

int main() {
    StudentInfo studentInfo("students.txt");
    int choice, rollNumber;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                studentInfo.addStudent();
                break;
            case 2:
                cout << "Enter roll number to display: ";
                cin >> rollNumber;
                studentInfo.displayStudent(rollNumber);
                break;
            case 3:
                cout << "Enter roll number to delete: ";
                cin >> rollNumber;
                studentInfo.deleteStudent(rollNumber);
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

