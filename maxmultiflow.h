#ifndef MAX_MULTI_FLOW_H
#define MAX_MULTI_FLOW_H

#include "maxflow.h"

struct InputEdge {
    int u, v;
    long long cap;
};

// V       : number of vertices in G, labeled 0 .. V-1
// edges   : directed edges (u, v, capacity) of G
// sources : s[1..m]
// sinks   : t[1..n]
// Returns the value of a maximum multi-source, multi-sink flow.
long long EfficientMaxMultiFlow(int V,
                                const vector<InputEdge>& edges,
                                const vector<int>& sources,
                                const vector<int>& sinks) {
    int s_star = V;       // add node s*
    int t_star = V + 1;   // add node t*

    MaxFlow mf(V + 2);

    // Copy the original graph G
    for (const InputEdge& e : edges)
        mf.add_edge(e.u, e.v, e.cap);

    // s* -> s[i] with infinite capacity
    for (int s : sources)
        mf.add_edge(s_star, s, INF);

    // t[j] -> t* with infinite capacity
    for (int t : sinks)
        mf.add_edge(t, t_star, INF);

    // One max-flow call from s* to t*
    return mf.edmonds_karp(s_star, t_star);
}

#endif // MAX_MULTI_FLOW_H
