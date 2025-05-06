#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Define a structure for nodes in the AVL Tree
struct Node {
    string key, meaning;
    int height;
    Node* left;
    Node* right;

    Node(string k, string m) : key(k), meaning(m), height(1), left(nullptr), right(nullptr) {}
};

// AVL Tree class to manage the dictionary
class AVLTree {
private:
    Node* root;

    // Get the height of a node
    int height(Node* node) {
        return node ? node->height : 0;
    }

    // Update the height of a node
    void updateHeight(Node* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    // Rotate right
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    // Rotate left
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // Balance the node to maintain AVL property
    Node* balance(Node* node) {
        updateHeight(node);
        int balanceFactor = height(node->left) - height(node->right);
        if (balanceFactor > 1) {
            if (height(node->left->left) < height(node->left->right)) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (balanceFactor < -1) {
            if (height(node->right->right) < height(node->right->left)) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    // Insert a new node in the tree
    Node* insert(Node* node, const string& key, const string& meaning) {
        if (!node) return new Node(key, meaning);
        if (key < node->key) {
            node->left = insert(node->left, key, meaning);
        } else if (key > node->key) {
            node->right = insert(node->right, key, meaning);
        } else {
            node->meaning = meaning; // Update meaning if key already exists
        }
        return balance(node);
    }

    // Find the minimum node in the tree
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    // Delete a node from the tree
    Node* deleteNode(Node* root, const string& key) {
        if (!root) return root;
        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        return balance(root);
    }

    // In-order traversal (ascending order)
    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->key << ": " << root->meaning << endl;
            inorder(root->right);
        }
    }

    // Reverse in-order traversal (descending order)
    void reverseInorder(Node* root) {
        if (root) {
            reverseInorder(root->right);
            cout << root->key << ": " << root->meaning << endl;
            reverseInorder(root->left);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    // Insert a new keyword and meaning
    void insert(const string& key, const string& meaning) {
        root = insert(root, key, meaning);
    }

    // Delete a keyword
    void deleteKey(const string& key) {
        root = deleteNode(root, key);
    }

    // Display the dictionary in ascending or descending order
    void display(bool ascending = true) {
        if (ascending) {
            inorder(root);
        } else {
            reverseInorder(root);
        }
    }

    // Get maximum comparisons = height of tree
    int getMaxComparisons() {
        return height(root);
    }
};

// Main function to interact with the dictionary
int main() {
    AVLTree dictionary;
    int choice;
    string key, meaning;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Display Dictionary (Ascending)\n";
        cout << "4. Display Dictionary (Descending)\n";
        cout << "5. Maximum Comparisons to Search Keyword\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Add Keyword
                cout << "Enter Keyword: ";
                cin >> key;
                cout << "Enter Meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dictionary.insert(key, meaning);
                break;
            case 2: // Delete Keyword
                cout << "Enter Keyword to Delete: ";
                cin >> key;
                dictionary.deleteKey(key);
                break;
            case 3: // Display Dictionary Ascending Order
                cout << "Dictionary in Ascending Order:\n";
                dictionary.display(true);
                break;
            case 4: // Display Dictionary Descending Order
                cout << "Dictionary in Descending Order:\n";
                dictionary.display(false);
                break;
            case 5: // Max Comparisons
                cout << "Maximum comparisons required to find a keyword: ";
                cout << dictionary.getMaxComparisons() << endl;
                break;
            case 6: // Exit
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

