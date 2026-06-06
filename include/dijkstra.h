#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "heap.h"
#include <limits>
#include <utility>
#include <vector>

using namespace std;

const long long DIJKSTRA_INF = numeric_limits<long long>::max() / 2;

template <typename W = long long>
vector<W> dijkstra(const vector<vector<pair<int, W>>>& adj, int src, int arnost = 2) {
    int n = static_cast<int>(adj.size());
    vector<W> dist(n, static_cast<W>(DIJKSTRA_INF));
    dist[src] = 0;

    dheap<pair<W, int>> pq(vector<pair<W, int>>{{0, src}}, arnost);

    while (!pq.empty()) {
        auto cur = pq.pop();
        W d = cur.first;
        int u = cur.second;

        if (d != dist[u]) {
            continue;
        }

        for (auto& e : adj[u]) {
            int v = e.first;
            W w = e.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

#endif
