const int N = 2e5 + 10;
int n, m;
multiset<int> adj[N];
int deg[N];
vector<int> tour;

void dfs(int u) {
    while (!adj[u].empty()) {
        auto it = adj[u].begin();
        int v = *it;
        adj[u].erase(it);
        if (u != v) {
            auto it_rev = adj[v].find(u);
            if (it_rev != adj[v].end()) {
                adj[v].erase(it_rev);
            }
        }
        dfs(v);
    }
    tour.emplace_back(u);
}

bool check() {
    for (int i = 0; i < n; ++i) {
        if (deg[i] & 1) return false;
    }
    return true;
}

bool isConnected() {
    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (deg[i] > 0) { start = i; break; }
    }
    if (start == -1) return true;

    vector<char> vis(n, 0);
    stack<int> st;
    st.push(start);
    vis[start] = 1;
    while (!st.empty()) {
        int v = st.top(); st.pop();
        for (int u : adj[v]) {
            if (!vis[u]) {
                vis[u] = 1;
                st.push(u);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (deg[i] > 0 && !vis[i]) return false;
    }
    return true;
}

bool get() {
    if (!check()) return false;
    if (!isConnected()) return false;

    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (deg[i] > 0) { start = i; break; }
    }
    if (start == -1) {
        return (m == 0);
    }

    tour.clear();
    dfs(start);
    reverse(tour.begin(), tour.end());
    return (int)tour.size() == m + 1;
}