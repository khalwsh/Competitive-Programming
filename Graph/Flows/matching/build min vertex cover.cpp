struct HopcroftKarp {
    int n;
    vector<vector<int>> adj;
    vector<int> mu, mv, dist;

    HopcroftKarp(int n , int m) : n(n), adj(n), mu(n, -1), mv(m, -1), dist(n) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; ++u) {
            if (mu[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (mv[v] == -1) {
                    found = true;
                }
                if (mv[v] != -1 && dist[mv[v]] == -1) {
                    dist[mv[v]] = dist[u] + 1;
                    q.push(mv[v]);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            if (mv[v] == -1 || (dist[mv[v]] == dist[u] + 1 && dfs(mv[v]))) {
                mu[u] = v;
                mv[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int res = 0;
        while (bfs()) {
            for (int u = 0; u < n; ++u) {
                if (mu[u] == -1 && dfs(u)) {
                    res++;
                }
            }
        }
        return res;
    }

    // --- new function: returns labels of a minimum vertex cover ---
    // Left vertices are labeled 0..n-1, right vertices are labeled n..n+m-1.
    vector<int> min_vertex_cover() {
        // ensure maximum matching exists
        max_matching();

        int m = (int)mv.size();
        vector<char> visL(n, false), visR(m, false);
        queue<int> q;

        // start from all free (unmatched) left vertices
        for (int u = 0; u < n; ++u) {
            if (mu[u] == -1) {
                visL[u] = true;
                q.push(u);
            }
        }

        // BFS along alternating paths: non-matching edges left->right,
        // matching edges right->left.
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                // traverse unmatched edge u->v (i.e. edge not used in current matching)
                if (!visR[v] && mu[u] != v) {
                    visR[v] = true;
                    int u2 = mv[v];
                    if (u2 != -1 && !visL[u2]) {
                        visL[u2] = true;
                        q.push(u2);
                    }
                }
            }
        }

        // By Konig: min vertex cover = (L \ visitedL) U (visitedR)
        vector<int> cover;
        for (int u = 0; u < n; ++u) {
            if (!visL[u]) cover.push_back(u); // left node
        }
        for (int v = 0; v < m; ++v) {
            if (visR[v]) cover.push_back(n + v); // encode right node as n+v
        }
        return cover;
    }
};