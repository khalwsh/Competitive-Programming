const int N = 2e5 + 10;
vector<int>adj[N];
int n , sz[N];
ll res = 0;
bool removed[N];

int dfs_sz(int u, int p) {
    sz[u] = 1;
    for (auto &v : adj[u]) {
        if (v == p || removed[v])continue;
        sz[u] += dfs_sz(v , u);
    }
    return sz[u];
}

int dfs_centroid(int u, int p, int s) {
    for (auto &v : adj[u]) {
        if (v == p || removed[v]) continue;
        if (sz[v] * 2 > s) return dfs_centroid(v , u , s);
    }
    return u;
}

void dfs_add(int u , int p  , int delta , int depth = 1) {
    // add the contribution of this node u to the data structure
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        dfs_add(v , u ,   delta , depth + 1);
    }
}

void dfs_ans(int u , int p , int depth = 1) {
    // merge the answer of node u with the answers in data structure
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        dfs_ans(v , u , depth + 1);
    }
}

void decompose(int u) {
    int comp_sz   = dfs_sz(u, -1);
    int centroid  = dfs_centroid(u, -1, comp_sz);

    // 1) answer for paths pass through centroid , note : be careful with paths start or end at centroid itself
    for (auto &v : adj[centroid]) {
        if (removed[v]) continue;
        dfs_ans(v, centroid);
        dfs_add(v, centroid , +1);
    }
    
    // 2) roll back your updates
    for (auto &v : adj[centroid]) {
        if (removed[v]) continue;
        dfs_add(v, centroid , -1);
    }

    removed[centroid] = true;
    for (auto &v : adj[centroid]) {
        if (!removed[v]) {
            decompose(v);
        }
    }
}