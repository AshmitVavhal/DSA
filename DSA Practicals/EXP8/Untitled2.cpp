#include <iostream>
#include <vector>
using namespace std;

// Function to calculate the sum of probabilities from i to j
int sumProbabilities(const vector<int>& p, int i, int j) {
    int sum = 0;
    for (int k = i; k <= j; ++k) {
        sum += p[k];
    }
    return sum;
}

// Function to find the minimum search cost of the optimal binary search tree
int optimalBST(const vector<int>& p, int n) {
    // Table to store the minimum cost for subtrees
    vector<vector<int>> cost(n, vector<int>(n, 0));

    // Base case: the cost for a single key is its own probability
    for (int i = 0; i < n; ++i) {
        cost[i][i] = p[i];
    }

    // Fill the table for increasing subtree sizes
    for (int len = 2; len <= n; ++len) {  // len is the length of the subtree
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;  // j is the end index of the current subtree
            cost[i][j] = 99999999;  // Use a large number instead of INT_MAX

            // Try each key as the root for the current subtree
            for (int r = i; r <= j; ++r) {
                int leftCost = (r > i) ? cost[i][r - 1] : 0;
                int rightCost = (r < j) ? cost[r + 1][j] : 0;

                // Total cost with root r and add the sum of probabilities
                int totalCost = leftCost + rightCost + sumProbabilities(p, i, j);
                cost[i][j] = min(cost[i][j], totalCost);
            }
        }
    }

    return cost[0][n - 1];  // The minimum cost for the whole tree
}

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    vector<int> p(n);
    cout << "Enter the probabilities for each key: ";
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    int minCost = optimalBST(p, n);
    cout << "The minimum search cost for the optimal BST is: " << minCost << endl;

    return 0;
}
