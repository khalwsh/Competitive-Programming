const int N = 200000 + 10;
int n, m;
vector<int> adj[N], radj[N];
int in[N], out[N];
vector<int> tour;

void dfs1(int s, const vector<int> g[], vector<char> &vis) {
    stack<int> st;
    st.push(s);
    vis[s] = 1;
    while (!st.empty()) {
        int v = st.top(); st.pop();
        for (int u : g[v]) {
            if (!vis[u]) {
                vis[u] = 1;
                st.push(u);
            }
        }
    }
}

void dfs2(int v) {
    while (!adj[v].empty()) {
        int u = adj[v].back();
        adj[v].pop_back();
        dfs2(u);
    }
    tour.push_back(v);
}

bool get() {
    for (int i = 0; i < n; ++i) {
        if (in[i] != out[i]) return false;
    }

    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (out[i] > 0) { start = i; break; }
    }
    if (start == -1) {
        tour = {0};
        return (m == 0);
    }
    vector<char> vis(n, 0);
    dfs1(start, adj, vis);
    for (int i = 0; i < n; ++i)
        if ((in[i] + out[i]) > 0 && !vis[i]) return false;

    fill(vis.begin(), vis.end(), 0);
    dfs1(start, radj, vis);
    for (int i = 0; i < n; ++i)
        if ((in[i] + out[i]) > 0 && !vis[i]) return false;

    tour.clear();
    dfs2(start);
    reverse(tour.begin(), tour.end());
    if ((int)tour.size() != m + 1) return false;
    return true;
}