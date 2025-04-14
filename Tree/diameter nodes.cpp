pair<int, int> diameter_nodes(int n, vector<int> adj[]) {
    vector<int> dist(n, -1);
    int start = 0;
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int far = start;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dist[u] > dist[far]) far = u;
        for (auto v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    int u1 = far;
    fill(dist.begin(), dist.end(), -1);
    q.push(u1);
    dist[u1] = 0;
    far = u1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dist[u] > dist[far]) far = u;
        for (auto v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    int u2 = far;
    return {u1, u2};
}
