static const int oo = 2e15;
 
struct Edge {
    int u, v, flow = 0, cap = 0, cost; // keep the order
    Edge(int u, int v, int c, int cost): u(u), v(v), cap(c), cost(cost) {}
    int rem() { return cap - flow; }
};
 
 
struct MCMF {
    int n, s, t, cost = 0, flow = 0;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> from;
 
    MCMF(int n, int s, int t): n(n), s(s), t(t) {
        adj.assign(n + 1, {});
    }
 
    void addEdge(int u, int v, int w = oo, int cost = 0, int undir = 0) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(u, v, w, cost));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(v, u, w * undir, -cost));
    }
 
    void move() {
        while (bfs()) {
            int u = t, addflow = oo;
            while (u != s) {
                Edge& e = edges[from[u]];
                addflow = min(addflow, e.rem());
                u = e.u;
            }
 
            u = t;
            while (u != s) {
                int i = from[u];
                edges[i].flow += addflow;
                edges[i ^ 1].flow -= addflow;
                cost += edges[i].cost * addflow;
                u = edges[i].u;
            }
 
            flow += addflow;
        }
    }
 
    bool bfs() {
        from.assign(n + 1, -1);
        vector<int> d(n + 1, oo), state(n + 1, 2);
        deque<int> q;
 
        state[s] = 1, d[s] = 0;
        q.clear();
        q.push_back(s);
 
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            state[u] = 0;
            for (auto& i : adj[u]) {
                auto& [_, v, f, c, cost] = edges[i];
 
                if (f >= c || d[v] <= d[u] + cost) continue;
 
                d[v] = d[u] + cost;
 
                from[v] = i;
                if (state[v] == 1) continue;
                if (!state[v] || (!q.empty() && d[q.front()] > d[v]))
                    q.push_front(v);
                else q.push_back(v);
                state[v] = 1;
            }
        }
 
        return ~from[t];
    }
};