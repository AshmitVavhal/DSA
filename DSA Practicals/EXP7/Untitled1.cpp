#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure for edges
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Disjoint Set Union (Union-Find) to handle cycle detection
class DisjointSet {
    vector<int> parent, rank;
    
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u) 
            parent[u] = find(parent[u]);  // Path compression
        return parent[u];
    }

    void unionSet(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) 
                parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV]) 
                parent[rootU] = rootV;
            else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Kruskal's Algorithm to find MST
int kruskal(int n, vector<Edge>& edges) {
    DisjointSet ds(n);
    sort(edges.begin(), edges.end(), [](Edge& e1, Edge& e2) {
        return e1.weight < e2.weight;
    });
    
    int mstCost = 0;
    for (Edge& edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int weight = edge.weight;
        
        if (ds.find(u) != ds.find(v)) {
            ds.unionSet(u, v);
            mstCost += weight;
        }
    }
    return mstCost;
}

int main() {
    int n, m;
    cout << "Enter the number of offices (cities): ";
    cin >> n;
    cout << "Enter the number of possible phone lines (edges): ";
    cin >> m;

    vector<Edge> edges;
    
    cout << "Enter the connections (city1 city2 cost):\n";
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        edges.push_back(Edge(u, v, cost));
    }
    
    // Find MST using Kruskal's algorithm
    int mstCost = kruskal(n, edges);
    
    cout << "The minimum cost to connect all offices is: " << mstCost << endl;

    return 0;
}
