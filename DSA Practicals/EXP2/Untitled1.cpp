#include <iostream>
#include <list>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

class HashNode {
public:
    string key;
    string value;

    HashNode(string k, string v) : key(k), value(v) {}
};

class HashMap {
private:
    list<HashNode> table[TABLE_SIZE];

    int hashFunction(string key) {
        int hash = 0;
        for (int i = 0; i < key.length(); ++i) {
            hash = (hash + int(key[i])) % TABLE_SIZE;
        }
        return hash;
    }

public:
    // Insert a key-value pair
    void insert(string key, string value) {
        int index = hashFunction(key);

        list<HashNode>::iterator it;
        for (it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                cout << "Key already exists. Updating value.\n";
                it->value = value;
                return;
            }
        }

        table[index].push_back(HashNode(key, value));
        cout << "Inserted (" << key << ", " << value << ")\n";
    }

    // Find a value by key
    void find(string key) {
        int index = hashFunction(key);

        list<HashNode>::iterator it;
        for (it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                cout << "Found: " << it->value << endl;
                return;
            }
        }

        cout << "Key not found.\n";
    }

    // Delete a key-value pair
    void remove(string key) {
        int index = hashFunction(key);

        list<HashNode>::iterator it;
        for (it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);
                cout << "Key deleted.\n";
                return;
            }
        }

        cout << "Key not found.\n";
    }

    // Display all elements
    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "Bucket " << i << ": ";
            list<HashNode>::iterator it;
            for (it = table[i].begin(); it != table[i].end(); ++it) {
                cout << "[" << it->key << ":" << it->value << "] -> ";
            }
            cout << "NULL\n";
        }
    }
};

// Main function
int main() {
    HashMap dict;
    int choice;
    string key, value;

    do {
        cout << "\n--- Dictionary using Hashing ---\n";
        cout << "1. Insert\n2. Find\n3. Delete\n4. Display\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                dict.insert(key, value);
                break;
            case 2:
                cout << "Enter key to find: ";
                cin >> key;
                dict.find(key);
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                dict.remove(key);
                break;
            case 4:
                dict.display();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

