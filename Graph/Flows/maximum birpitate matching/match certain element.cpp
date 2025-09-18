struct HopcroftKarp {
    int n;
    vector<vector<int>> adj;
    vector<int> mu, mv, dist;
 
    HopcroftKarp(int n, int m) : n(n), adj(n), mu(n, -1), mv(m, -1), dist(n) {}
 
    void add_edge(int u, int v) {
        if (u >= 0 && u < n) adj[u].push_back(v);
    }
 
    bool bfs(int mex) {
        queue<int> q;
        for (int u = 0; u <= mex; ++u) {
            if (mu[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else dist[u] = -1;
        }
        for (int u = mex + 1; u < n; ++u) dist[u] = -1;
 
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (mv[v] == -1) {
                    found = true;
                } else {
                    int to = mv[v];
                    if (to <= mex && dist[to] == -1) {
                        dist[to] = dist[u] + 1;
                        q.push(to);
                    }
                }
            }
        }
        return found;
    }
 
    bool dfs(int u, int mex) {
        for (int v : adj[u]) {
            if (mv[v] == -1 || (mv[v] <= mex && dist[mv[v]] == dist[u] + 1 && dfs(mv[v], mex))) {
                mu[u] = v;
                mv[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }
 
    int max_matching(int mex) {
        if (mex < 0) return 0;
        mex = min(mex, n - 1);
        int res = 0;
        while (bfs(mex)) {
            int added = 0;
            for (int u = 0; u <= mex; ++u) {
                if (mu[u] == -1 && dfs(u, mex)) {
                    ++added;
                    ++res;
                }
            }
            if (added == 0) break;
        }
        return res;
    }
};