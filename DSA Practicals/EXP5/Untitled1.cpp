#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// Tree node
struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char val) : data(val), left(NULL), right(NULL) {}
};

// Utility: Check if character is an operator
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// 1. Construct Expression Tree from prefix expression
Node* constructTreeFromPrefix(string prefix) {
    stack<Node*> stk;

    // Scan prefix expression from right to left
    for (int i = prefix.size() - 1; i >= 0; i--) {
        char ch = prefix[i];

        Node* node = new Node(ch);

        if (isOperator(ch)) {
            // Pop two nodes for operator
            if (!stk.empty()) node->left = stk.top(), stk.pop();
            if (!stk.empty()) node->right = stk.top(), stk.pop();
        }

        stk.push(node);
    }

    return stk.top();  // Root of the expression tree
}

// 2. Non-Recursive Post-order Traversal using two stacks
void postOrderNonRecursive(Node* root) {
    if (!root) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* curr = s1.top(); s1.pop();
        s2.push(curr);

        if (curr->left) s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }

    cout << "Post-order traversal: ";
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
    cout << endl;
}

// 3. Delete the entire tree (recursive cleanup)
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string prefix;
    cout << "Enter prefix expression: ";
    cin >> prefix;

    Node* root = constructTreeFromPrefix(prefix);

    postOrderNonRecursive(root);

    deleteTree(root);
    cout << "Expression tree deleted successfully.\n";

    return 0;
}

