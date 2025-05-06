#include <iostream>
using namespace std;

const int TABLE_SIZE = 10;
const int MAX_CHAIN = 5;  // Max entries in a chain (for simplicity)

class LinearProbingHashTable {
    long long table[TABLE_SIZE];
    int comparisons;

public:
    LinearProbingHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = -1;
    }

    int hashFunction(long long key) {
        return key % TABLE_SIZE;
    }

    void insert(long long phone) {
        int index = hashFunction(phone);
        int startIndex = index;

        while (table[index] != -1) {
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                cout << "Linear probing table full!\n";
                return;
            }
        }
        table[index] = phone;
    }

    bool search(long long phone) {
        int index = hashFunction(phone);
        int startIndex = index;
        comparisons = 0;

        while (table[index] != -1) {
            comparisons++;
            if (table[index] == phone)
                return true;
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex)
                break;
        }
        return false;
    }

    int getComparisons() {
        return comparisons;
    }

    void display() {
        cout << "\nLinear Probing Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != -1)
                cout << "[" << i << "] " << table[i] << "\n";
            else
                cout << "[" << i << "] Empty\n";
        }
    }
};

class ChainingHashTable {
    long long table[TABLE_SIZE][MAX_CHAIN];  // array of chains
    int chainSize[TABLE_SIZE]; // number of elements in each chain
    int comparisons;

public:
    ChainingHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            chainSize[i] = 0;
            for (int j = 0; j < MAX_CHAIN; j++)
                table[i][j] = -1;
        }
    }

    int hashFunction(long long key) {
        return key % TABLE_SIZE;
    }

    void insert(long long phone) {
        int index = hashFunction(phone);
        if (chainSize[index] < MAX_CHAIN) {
            table[index][chainSize[index]++] = phone;
        } else {
            cout << "Chaining limit exceeded at index " << index << endl;
        }
    }

    bool search(long long phone) {
        int index = hashFunction(phone);
        comparisons = 0;

        for (int i = 0; i < chainSize[index]; i++) {
            comparisons++;
            if (table[index][i] == phone)
                return true;
        }
        return false;
    }

    int getComparisons() {
        return comparisons;
    }

    void display() {
        cout << "\nChaining Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "] ";
            for (int j = 0; j < chainSize[i]; j++) {
                cout << table[i][j] << " -> ";
            }
            cout << "NULL\n";
        }
    }
};

int main() {
    LinearProbingHashTable linearTable;
    ChainingHashTable chainTable;

    int n;
    cout << "Enter number of clients: ";
    cin >> n;

    cout << "Enter " << n << " telephone numbers:\n";
    for (int i = 0; i < n; i++) {
        long long num;
        cin >> num;
        linearTable.insert(num);
        chainTable.insert(num);
    }

    linearTable.display();
    chainTable.display();

    int searchCount;
    cout << "\nHow many numbers do you want to search? ";
    cin >> searchCount;

    for (int i = 0; i < searchCount; i++) {
        long long query;
        cout << "Enter number to search: ";
        cin >> query;

        bool foundLinear = linearTable.search(query);
        bool foundChain = chainTable.search(query);

        cout << "Linear Probing: " << (foundLinear ? "Found" : "Not Found")
             << ", Comparisons: " << linearTable.getComparisons() << endl;

        cout << "Chaining: " << (foundChain ? "Found" : "Not Found")
             << ", Comparisons: " << chainTable.getComparisons() << endl;
    }

    return 0;
}
