// DSAL Lab Assignment 3
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Node structure for the tree
struct Node {
    string name;             // Name of the node (e.g., chapter name, section name)
    vector<Node*> children;  // List of child nodes

    Node(string n) : name(n) {}
};

// Function to add a child node
void addChild(Node* parent, string childName) {
    Node* child = new Node(childName);
    parent->children.push_back(child);
}

// Function to print the tree (DFS traversal)
void printTree(Node* root, int level = 0) {
    if (root == nullptr) return;

    // Print current node
    for (int i = 0; i < level; i++) cout << "  "; // Indentation for hierarchy
    cout << root->name << endl;

    // Recursively print children
    for (Node* child : root->children) {
        printTree(child, level + 1);
    }
}

// Function to display the menu
void displayMenu() {
    cout << "\nMenu:\n";
    cout << "1. Add Chapter\n";
    cout << "2. Add Section\n";
    cout << "3. Add Subsection\n";
    cout << "4. Print Book Structure\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    // Create the root node (Book)
    Node* book = new Node("Book");

    int choice;
    string name;
    int chapterIndex, sectionIndex;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: // Add Chapter
                cout << "Enter Chapter Name: ";
                cin.ignore(); // Clear input buffer
                getline(cin, name);
                addChild(book, name);
                break;

            case 2: // Add Section
                if (book->children.empty()) {
                    cout << "No chapters available. Please add a chapter first.\n";
                    break;
                }
                cout << "Available Chapters:\n";
                for (size_t i = 0; i < book->children.size(); i++) {
                    cout << i + 1 << ". " << book->children[i]->name << endl;
                }
                cout << "Select Chapter (1-" << book->children.size() << "): ";
                cin >> chapterIndex;
                if (chapterIndex < 1 || chapterIndex > book->children.size()) {
                    cout << "Invalid choice!\n";
                    break;
                }
                cout << "Enter Section Name: ";
                cin.ignore();
                getline(cin, name);
                addChild(book->children[chapterIndex - 1], name);
                break;

            case 3: // Add Subsection
                if (book->children.empty()) {
                    cout << "No chapters available. Please add a chapter first.\n";
                    break;
                }
                cout << "Available Chapters:\n";
                for (size_t i = 0; i < book->children.size(); i++) {
                    cout << i + 1 << ". " << book->children[i]->name << endl;
                }
                cout << "Select Chapter (1-" << book->children.size() << "): ";
                cin >> chapterIndex;
                if (chapterIndex < 1 || chapterIndex > book->children.size()) {
                    cout << "Invalid choice!\n";
                    break;
                }
                if (book->children[chapterIndex - 1]->children.empty()) {
                    cout << "No sections available. Please add a section first.\n";
                    break;
                }
                cout << "Available Sections:\n";
                for (size_t i = 0; i < book->children[chapterIndex - 1]->children.size(); i++) {
                    cout << i + 1 << ". " << book->children[chapterIndex - 1]->children[i]->name << endl;
                }
                cout << "Select Section (1-" << book->children[chapterIndex - 1]->children.size() << "): ";
                cin >> sectionIndex;
                if (sectionIndex < 1 || sectionIndex > book->children[chapterIndex - 1]->children.size()) {
                    cout << "Invalid choice!\n";
                    break;
                }
                cout << "Enter Subsection Name: ";
                cin.ignore();
                getline(cin, name);
                addChild(book->children[chapterIndex - 1]->children[sectionIndex - 1], name);
                break;

            case 4: // Print Book Structure
                cout << "\nBook Structure:\n";
                printTree(book);
                break;

            case 5: // Exit
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

