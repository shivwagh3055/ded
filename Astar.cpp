#include <iostream>
#include <queue>
#include <climits>
using namespace std;

int main() {

    // Graph adjacency matrix (costs)
    int cost[5][5] = {
        {0, 4, 2, 0, 0}, // A
        {0, 0, 0, 5, 0}, // B
        {0, 0, 0, 8,10}, // C
        {0, 0, 0, 0, 2}, // D
        {0, 0, 0, 0, 0}  // E
    };

    // Heuristic values to goal (E)
    int h[5] = {10, 7, 9, 3, 0};

    // Distance from start
    int g[5];
    for(int i=0;i<5;i++) g[i] = INT_MAX;

    int start = 0; // A
    int goal  = 4; // E
    g[start] = 0;

    struct Node {
        int f, city;
        bool operator>(const Node &o) const { return f > o.f; }
    };

    priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    pq.push({h[start], start});

    while(!pq.empty()){
        Node cur = pq.top(); pq.pop();
        int u = cur.city;

        if(u == goal){
            cout << "Shortest cost from A to E = " << g[u] << endl;
            return 0;
        }

        for(int v = 0; v < 5; v++){
            if(cost[u][v] != 0){ // if path exists
                int newCost = g[u] + cost[u][v];
                if(newCost < g[v]){
                    g[v] = newCost;
                    pq.push({g[v] + h[v], v});
                }
            }
        }
    }

    cout << "No route found.\n";
    return 0;
}
