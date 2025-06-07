const ll INF = 1e18;
int n;
// no need to do multisource BFS just mark as -inf when the other n iterations
vector<array<ll , 3>>edges;
vector<int> solve(int source) {
    vector<ll> dist(n, INF);
    dist[source] = 0;
    for (int pass = 0; pass < n - 1; ++pass) {
        bool changed = false;
        for (auto &e : edges) {
            int u = (int)e[0], v = (int)e[1];
            ll w = e[2];
            if (dist[u] < INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                changed = true;
            }
        }
        if (!changed) break;
    }

    vector<ll> ref = dist;
    for (int pass = 0; pass < n; ++pass) {
        for (auto &e : edges) {
            int u = (int)e[0], v = (int)e[1];
            ll w = e[2];
            if (dist[u] < INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    vector<bool> neg_inf(n, false);
    queue<int> bfs;
    for (int i = 0; i < n; ++i) {
        if (ref[i] != dist[i]) {
            neg_inf[i] = true;
            bfs.push(i);
        }
    }
    vector<vector<int>> adj(n);
    for (auto &e : edges) {
        int u = (int)e[0], v = (int)e[1];
        adj[u].push_back(v);
    }
    while (!bfs.empty()) {
        int u = bfs.front();
        bfs.pop();
        for (int nxt : adj[u]) {
            if (!neg_inf[nxt]) {
                neg_inf[nxt] = true;
                bfs.push(nxt);
            }
        }
    }
    vector<int> nodes;
    for (int i = 0; i < n; ++i) {
        if (neg_inf[i]) {
            nodes.push_back(i);
        }
    }
    return nodes;
}