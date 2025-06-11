const int N = 1e5 + 10;
vector<int>adj[N];
int depth[N] , root[N] , pos[N] , heavy[N] , sz[N] , timer = 0 , parent[N] , n , q , values[N];
// remember edge orientation
void dfs_sz(int u , int p) {
    depth[u] = depth[p] + 1;
    sz[u] = 1;
    parent[u] = p;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        dfs_sz(v , u);
        sz[u] += sz[v];
    }
    heavy[u] = -1;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) {
            heavy[u] = v;
        }
    }
}
void decompose(int u , int p) {
    pos[u] = timer++;
    if (heavy[u] != -1) {
        root[heavy[u]] = root[u];
        decompose(heavy[u] , u);
    }
    for (auto &v : adj[u]) {
        if (v == p || heavy[u] == v)continue;
        root[v] = v;
        decompose(v , u);
    }
}
// to update sub tree , from pos[u] to pos[u] + sz[u] - 1
void upd_path(int u, int v, ll nw_val) {
    while (root[u] != root[v]) {
        if (depth[root[u]] < depth[root[v]]) swap(u, v);
        seg.upd(0, 0, n - 1, pos[root[u]], pos[u], nw_val);
        u = parent[root[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    if (u != v) seg.upd(0, 0, n - 1, pos[u] + 1, pos[v], nw_val);
}

ll query_path(int u, int v) {
    ll res = 0;
    while (root[u] != root[v]) {
        if (depth[root[u]] < depth[root[v]]) swap(u, v);
        res = max(res, seg.query(0, 0, n - 1, pos[root[u]], pos[u]));
        u = parent[root[u]];
    }
    if (depth[u] > depth[v]) swap(u, v);
    if (u != v) res = max(res, seg.query(0, 0, n - 1, pos[u] + 1, pos[v]));
    return res;
}