struct MCMF {
    ll n, s, t, cost = 0, flow = 0;
    vector<Edge> edges;
    vector<vector<int>> adj;
    vector<int> from;

    MCMF(int n, int s, int t): n(n), s(s), t(t) {
        adj.assign(n + 1, {});
    }

    void addEdge(int u, int v, ll w = oo, ll cost = 0, int undir = 0) {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(u, v, w, cost));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(v, u, w * undir, -cost));
    }
    // to move step by step correctly you need ultimate source that every step you add edge from us to s
    /* example
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) & 1) {
                f.addEdge(us, s, 1, 0);
                f.move();
                res = max(res, sum - f.cost);
            }
        }
    }
    */
    void move() {
        while (bfs()) {
            ll addflow = oo;
            for (int u = t; u != s; u = edges[from[u]].u)
                addflow = min(addflow, edges[from[u]].rem());

            for (int u = t; u != s; u = edges[from[u]].u) {
                int i = from[u];
                edges[i].flow    += addflow;
                edges[i^1].flow  -= addflow;
                cost             += edges[i].cost * addflow;
            }
            flow += addflow;
        }
    }

    bool bfs() {
        from.assign(n + 1, -1);
        vector<ll> d(n + 1, oo);
        vector<int> state(n + 1, 2);
        deque<int> q;

        d[s] = 0;
        state[s] = 1;
        q.push_back(s);

        while (!q.empty()) {
            int u = q.front(); q.pop_front();
            state[u] = 0;
            for (auto &ei : adj[u]) {
                auto &e = edges[ei];
                int v = e.v;
                if (e.rem() <= 0 || d[v] <= d[u] + e.cost) continue;
                d[v] = d[u] + e.cost;
                from[v] = ei;
                if (state[v] == 1) continue;
                if (state[v] == 0 || (!q.empty() && d[q.front()] > d[v]))
                    q.push_front(v);
                else
                    q.push_back(v);
                state[v] = 1;
            }
        }
        return from[t] != -1;
    }
};
