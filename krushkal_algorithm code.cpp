
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

int findParent(vector<int>& parent, int x) {
    if (parent[x] == x)
        return x;

    return parent[x] = findParent(parent, parent[x]);
}

void unionSets(vector<int>& parent,
               vector<int>& rank,
               int u, int v) {
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}

int main() {
    int n, m;

    cout << "Enter number of vertices: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> m;

    vector<Edge> edges(m);

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < m; i++) {
        cin >> edges[i].u
            >> edges[i].v
            >> edges[i].weight;
    }

    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(n);
    vector<int> rank(n, 0);

    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    int totalWeight = 0;
    int selected = 0;

    cout << "\nMinimum Spanning Tree:\n";

    for (Edge e : edges) {
        int u = findParent(parent, e.u);
        int v = findParent(parent, e.v);

        if (u != v) {
            cout << e.u << " - " << e.v
                 << " : " << e.weight << "\n";

            totalWeight += e.weight;
            unionSets(parent, rank, u, v);
            selected++;

            if (selected == n - 1)
                break;
        }
    }

    if (selected != n - 1) {
        cout << "Graph is disconnected; MST does not exist.\n";
    }
    else {
        cout << "Total weight of MST: "
             << totalWeight << "\n";
    }

    return 0;
}
```
