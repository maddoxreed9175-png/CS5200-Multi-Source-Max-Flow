#include "maxmultiflow.h"

int randInt(int lo, int hi) {
    return lo + rand() % (hi - lo + 1);
}

int main() {
    const int NUM_GRAPHS = 100;
    srand(12345); // fixed seed for reproducible output

    cout << "Graph |  V |   E | sources | sinks | max flow\n";
    cout << "------+----+-----+---------+-------+---------\n";

    for (int g = 1; g <= NUM_GRAPHS; ++g) {
        int V = randInt(8, 30);
        int m = randInt(1, 4);
        int n = randInt(1, 4);

        // Pick disjoint sources and sinks (no vertex is both)
        vector<int> perm(V);
        for (int i = 0; i < V; ++i) perm[i] = i;
        for (int i = V - 1; i > 0; --i)        // Fisher-Yates shuffle
            swap(perm[i], perm[randInt(0, i)]);
        vector<int> sources(perm.begin(), perm.begin() + m);
        vector<int> sinks(perm.begin() + m, perm.begin() + m + n);

        // Random directed edges, no self-loops, capacities in [1, 20]
        int pct = randInt(10, 30); // edge probability in percent
        vector<InputEdge> edges;
        for (int u = 0; u < V; ++u)
            for (int v = 0; v < V; ++v)
                if (u != v && randInt(1, 100) <= pct)
                    edges.push_back({u, v, (long long)randInt(1, 20)});

        long long flow = EfficientMaxMultiFlow(V, edges, sources, sinks);

        cout << g << " | V=" << V << " | E=" << edges.size()
             << " | sources=" << m << " | sinks=" << n
             << " | max flow=" << flow << "\n";
    }
    return 0;
}
