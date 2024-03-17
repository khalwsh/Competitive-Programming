vector<int> adj[N], adj_rev[N];
//build the adj and adj_rev in main
bool used[N];
vector<int> order, component;
vector<vector<int>>comps;
void dfs1(int v) {
    used[v] = true;
    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);
    order.push_back(v);
}
void dfs2(int v) {
    used[v] = true;
    component.push_back(v);
    for (auto u : adj_rev[v])
        if (!used[u])   dfs2(u);
}
void Kosaraju(int n){
    for (int i = 0; i < n; ++i) used[i] = false;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs1(i);
        }
    }
    for (int i = 0; i < n; ++i) used[i] = false;
    reverse(order.begin(), order.end());
    for (auto v: order) {
        if (!used[v]) {
            dfs2(v);
            comps.emplace_back(component);
            component.clear();
        }
    }
}