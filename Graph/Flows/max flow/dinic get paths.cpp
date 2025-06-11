// O(V^2 E) and in unit graph works in O(E sqrt(v))
#include <bits/stdc++.h>
using namespace std;

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        while (!q.empty()) q.pop();
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap == edges[id].flow)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int &cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u])
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }

    // Decompose the computed flow into s->t paths
    vector<pair<vector<int>, long long>> get_paths() {
        // Build adjacency of edges with positive flow
        vector<vector<pair<int,int>>> g(n);
        for (int id = 0; id < m; id += 2) {
            if (edges[id].flow > 0) {
                g[edges[id].v].emplace_back(edges[id].u, id);
            }
        }
        vector<pair<vector<int>, long long>> paths;
        vector<int> parent_edge(n);

        function<long long(int)> dfs2 = [&](int v) {
            if (v == t) return LLONG_MAX;
            for (auto &pr : g[v]) {
                int u = pr.first, id = pr.second;
                if (parent_edge[u] == -1) {
                    parent_edge[u] = id;
                    long long pushed = dfs2(u);
                    if (pushed > 0) {
                        return min(pushed, edges[id].flow);
                    }
                }
            }
            return 0LL;
        };

        while (true) {
            fill(parent_edge.begin(), parent_edge.end(), -1);
            parent_edge[s] = -2; // mark source
            long long pushed = dfs2(s);
            if (pushed == 0) break;
            vector<int> path;
            int v = t;
            while (v != s) {
                int id = parent_edge[v];
                path.push_back(v);
                edges[id].flow -= pushed;
                edges[id ^ 1].flow += pushed;
                v = edges[id].v;
            }
            path.push_back(s);
            reverse(path.begin(), path.end());
            paths.emplace_back(path, pushed);
        }
        return paths;
    }
};