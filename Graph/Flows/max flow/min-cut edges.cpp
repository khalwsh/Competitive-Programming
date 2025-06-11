// O(V^2 E) and in unit graph works in O(E sqrt(v))
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
    // After max-flow, find min-cut edges: edges from reachable to non-reachable
    vector<pair<int,int>> min_cut_edges() {
        vector<char> visited(n, false);
        queue<int> qu;
        qu.push(s);
        visited[s] = true;
        // BFS on residual graph
        while (!qu.empty()) {
            int v = qu.front(); qu.pop();
            for (int id : adj[v]) {
                if (edges[id].flow == edges[id].cap) continue; // no residual capacity
                int u = edges[id].u;
                if (!visited[u]) {
                    visited[u] = true;
                    qu.push(u);
                }
            }
        }
        vector<pair<int,int>> cut;
        // original edges are at even indices
        for (int id = 0; id < m; id += 2) {
            const auto &e = edges[id];
            if (visited[e.v] && !visited[e.u] && e.cap > 0) {
                cut.emplace_back(e.v, e.u);
            }
        }
        return cut;
    }
};