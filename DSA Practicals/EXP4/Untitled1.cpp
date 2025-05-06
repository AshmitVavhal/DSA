#include <iostream>
using namespace std;

// Node definition
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(NULL), right(NULL) {}
};

// 1. Insert a node into the BST
Node* insert(Node* root, int val) {
    if (root == NULL) return new Node(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    return root;
}

// 2. Find height of the tree
int height(Node* root) {
    if (root == NULL) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// 3. Find minimum value (leftmost node in BST)
int findMin(Node* root) {
    if (root == NULL) return -1;
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

// 4. Mirror the binary tree (swap left and right subtrees)
void mirror(Node* root) {
    if (root == NULL) return;
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
}

// 5. Search in a BST
bool bstSearch(Node* root, int val) {
    if (root == NULL) return false;
    if (val == root->data) return true;
    if (val < root->data) return bstSearch(root->left, val);
    return bstSearch(root->right, val);
}

// In-order traversal
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = NULL;
    int n, val;

    cout << "Enter number of values to insert: ";
    cin >> n;

    cout << "Enter values:\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        root = insert(root, val);
    }

    cout << "\nIn-order Traversal: ";
    inorder(root);

    cout << "\nHeight (Longest Path): " << height(root);
    cout << "\nMinimum Value: " << findMin(root);

    // Search for the value in the BST
    cout << "\n\nEnter value to search in BST: ";
    cin >> val;
    if (bstSearch(root, val))
        cout << "Value found in BST.\n";
    else
        cout << "Value not found in BST.\n";

    // Mirror the tree and show the result
    cout << "\nMirroring Tree...\n";
    mirror(root);
    cout << "In-order after mirroring: ";
    inorder(root);

    return 0;
}


