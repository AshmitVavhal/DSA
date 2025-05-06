#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
    int empID;
    string name;
    string designation;
    double salary;
};

// Function to add employee information
void addEmployee() {
    Employee emp;
    ofstream file("employees.txt", ios::app);  // Open file in append mode for text file
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    cout << "Enter Employee ID: ";
    cin >> emp.empID;
    cin.ignore();  // To clear input buffer
    cout << "Enter Name: ";
    getline(cin, emp.name);
    cout << "Enter Designation: ";
    getline(cin, emp.designation);
    cout << "Enter Salary: ";
    cin >> emp.salary;

    // Writing employee information in text format
    file << emp.empID << "\n";
    file << emp.name << "\n";
    file << emp.designation << "\n";
    file << emp.salary << "\n";
    file << "----\n";  // Add separator for easy identification of records
    file.close();

    cout << "Employee added successfully!" << endl;
}

// Function to delete employee information by empID
void deleteEmployee() {
    int empID;
    cout << "Enter Employee ID to delete: ";
    cin >> empID;

    ifstream inFile("employees.txt");  // Open file for reading
    ofstream outFile("temp.txt");      // Open temporary file for writing

    Employee emp;
    bool found = false;

    // Reading the file line by line and copying data to the temp file except the record to be deleted
    while (inFile >> emp.empID) {
        inFile.ignore(); // Ignore newline after empID
        getline(inFile, emp.name);
        getline(inFile, emp.designation);
        inFile >> emp.salary;
        inFile.ignore(); // Ignore newline after salary
        inFile.ignore(); // Ignore the separator line

        if (emp.empID != empID) {
            // Copy this employee to the temporary file if empID does not match
            outFile << emp.empID << "\n";
            outFile << emp.name << "\n";
            outFile << emp.designation << "\n";
            outFile << emp.salary << "\n";
            outFile << "----\n";
        } else {
            found = true; // Record to delete found
        }
    }

    inFile.close();
    outFile.close();

    // If the record is found, replace the original file with the temp file
    if (found) {
        remove("employees.txt");   // Remove the original file
        rename("temp.txt", "employees.txt");  // Rename the temp file
        cout << "Employee record deleted!" << endl;
    } else {
        cout << "Employee not found!" << endl;
        remove("temp.txt");  // Delete the temp file if no record was deleted
    }
}

// Function to display employee information by empID
void displayEmployee() {
    int empID;
    cout << "Enter Employee ID to display: ";
    cin >> empID;

    ifstream file("employees.txt");  // Open file for reading
    Employee emp;
    bool found = false;

    // Reading the file line by line and checking for matching empID
    while (file >> emp.empID) {
        file.ignore(); // Ignore newline after empID
        getline(file, emp.name);
        getline(file, emp.designation);
        file >> emp.salary;
        file.ignore(); // Ignore newline after salary
        file.ignore(); // Ignore the separator line

        if (emp.empID == empID) {
            // If employee found, display details
            cout << "Employee ID: " << emp.empID << endl;
            cout << "Name: " << emp.name << endl;
            cout << "Designation: " << emp.designation << endl;
            cout << "Salary: " << emp.salary << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee not found!" << endl;
    }

    file.close();
}

int main() {
    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Employee\n";
        cout << "2. Delete Employee\n";
        cout << "3. Display Employee\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                displayEmployee();
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

