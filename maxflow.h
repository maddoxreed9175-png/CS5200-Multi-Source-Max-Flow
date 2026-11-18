#ifndef MAX_FLOW_H
#define MAX_FLOW_H

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

struct Edge {
    int to;
    int rev; // Index of the reverse edge in adj[to]
    long long cap;
};

class MaxFlow {
    int n;
    vector<vector<Edge>> adj;

public:
    MaxFlow(int nodes) : n(nodes), adj(nodes) {}

    // Adds a directed edge from u to v with given capacity
    void add_edge(int u, int v, long long cap) {
        Edge forward = {v, (int)adj[v].size(), cap};
        Edge backward = {u, (int)adj[u].size(), 0}; // Residual reverse edge
        adj[u].push_back(forward);
        adj[v].push_back(backward);
    }

    // Finds the maximum flow from source s to sink t
    long long edmonds_karp(int s, int t) {
        long long total_flow = 0;
        vector<int> parent_node(n);
        vector<int> parent_edge(n);

        while (true) {
            fill(parent_node.begin(), parent_node.end(), -1);
            queue<pair<int, long long>> q;
            q.push({s, INF});
            parent_node[s] = s;

            long long path_flow = 0;

            // BFS to find the shortest augmenting path
            while (!q.empty()) {
                int u = q.front().first;
                long long flow = q.front().second;
                q.pop();

                for (int i = 0; i < adj[u].size(); ++i) {
                    Edge &e = adj[u][i];
                    if (parent_node[e.to] == -1 && e.cap > 0) {
                        parent_node[e.to] = u;
                        parent_edge[e.to] = i;
                        long long new_flow = min(flow, e.cap);
                        if (e.to == t) {
                            path_flow = new_flow;
                            break;
                        }
                        q.push({e.to, new_flow});
                    }
                }
                if (path_flow > 0) break;
            }

            // No augmenting path left
            if (path_flow == 0) break;

            total_flow += path_flow;

            // Update residual capacities along the path
            int curr = t;
            while (curr != s) {
                int prev = parent_node[curr];
                int idx = parent_edge[curr];
                adj[prev][idx].cap -= path_flow;
                int rev_idx = adj[prev][idx].rev;
                adj[curr][rev_idx].cap += path_flow;
                curr = prev;
            }
        }

        return total_flow;
    }
};

/*int main() {
    // Example graph with 6 nodes (0 to 5)
    MaxFlow mf(6);
    mf.add_edge(0, 1, 16);
    mf.add_edge(0, 2, 13);
    mf.add_edge(1, 2, 10);
    mf.add_edge(1, 3, 12);
    mf.add_edge(2, 1, 4);
    mf.add_edge(2, 4, 14);
    mf.add_edge(3, 2, 9);
    mf.add_edge(3, 5, 20);
    mf.add_edge(4, 3, 7);
    mf.add_edge(4, 5, 4);

    cout << "Maximum Flow: " << mf.edmonds_karp(0, 5) << endl; // Output: 23
    return 0;
}*/

#endif // MAX_FLOW_H
