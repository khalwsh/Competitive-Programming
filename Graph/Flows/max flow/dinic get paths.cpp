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
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
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
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
    vector<pair<vector<int>, ll>> extract_paths() {
        vector<pair<vector<int>, ll>> paths;
        vector<int> parent_edge(n);

        function<ll(int, vector<vector<pair<int,int>>>&)> dfs2 =
        [&](int v, vector<vector<pair<int,int>>>& g) -> ll {
            if (v == t) return LLONG_MAX;
            for (auto &pr : g[v]) {
                int u = pr.first, id = pr.second;
                if (edges[id].flow <= 0) continue;
                if (parent_edge[u] == -1) {
                    parent_edge[u] = id;
                    ll pushed = dfs2(u, g);
                    if (pushed > 0) {
                        return min(pushed, edges[id].flow);
                    }
                }
            }
            return 0LL;
        };

        while (true) {
            vector<vector<pair<int,int>>> g(n);
            for (int id = 0; id < m; id += 2) {
                if (edges[id].flow > 0) {
                    g[edges[id].v].emplace_back(edges[id].u, id);
                }
            }

            fill(parent_edge.begin(), parent_edge.end(), -1);
            parent_edge[s] = -2;
            ll pushed = dfs2(s, g);
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