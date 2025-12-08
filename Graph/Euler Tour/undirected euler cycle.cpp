const int N = 2e5 + 10;
int n, m;                
set<int> adj[N];        
int degree[N];         
vector<int> tour;      

void dfs(int node) {
    while (!adj[node].empty()) {
        auto it = prev(adj[node].end());
        int x = *it;
        adj[node].erase(it);
        if (adj[x].erase(node)) {
            dfs(x);
        }
    }
    tour.emplace_back(node);
}

bool check() {
    for (int i = 0; i < n; ++i) {
        if (degree[i] & 1) return false;
    }
    return true;
}

bool isConnected() {
    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (degree[i] > 0) { start = i; break; }
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
        if (degree[i] > 0 && !vis[i]) return false;
    }
    return true;
}

bool get() {
    if (!check()) return false;
    if (!isConnected()) return false;

    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (degree[i] > 0) { start = i; break; }
    }
    if (start == -1) {
        return (m == 0);
    }

    tour.clear();
    dfs(start);
    reverse(tour.begin(), tour.end());
    return (int)tour.size() == m + 1;
}