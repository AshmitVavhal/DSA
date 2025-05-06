#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

const int MAX = 100; // Maximum number of cities

unordered_map<string, vector<string>> graph;
unordered_map<string, bool> visited;

void dfs(string city) {
    visited[city] = true;
    for (string neighbor : graph[city]) {
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
}

int main() {
    int edges;
    cout << "Enter number of flight connections: ";
    cin >> edges;

    cout << "Enter each connection (city1 city2):\n";
    for (int i = 0; i < edges; i++) {
        string a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a); // Undirected
    }

    // Start DFS from the first city
    string start = graph.begin()->first;
    dfs(start);

    // Check if all cities are visited
    bool connected = true;
    for (auto& city : graph) {
        if (!visited[city.first]) {
            connected = false;
            break;
        }
    }

    cout << "\nThe graph is " << (connected ? "connected." : "not connected.") << endl;

    return 0;
}

