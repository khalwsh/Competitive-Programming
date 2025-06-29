const int N = 2e5 + 10;
ll ans[N];
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

void dfs_add(int u , int p  , int delta , int depth = 1 , int msk = 0) {
    // add the contribution of this node u to the data structure
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        dfs_add(v , u ,   delta , depth + 1 , msk);
    }
}

void dfs_ans(int u , int p , int centroid , int depth = 1 , int msk = 0) {
    // merge the answer of node u with the answers in data structure
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        dfs_ans(v , u , centroid, depth + 1 , msk);
    }
}

ll dfs_contrubition(int u , int p , int centroid , int depth = 1 , int msk = 0) {
    // you see the paths in other subtrees or start in the centroid and end in your subtree contribution to u
    ll res = 0;
    for (auto &v : adj[u]) {
        if (removed[v] || v == p) continue;
        res += dfs_contrubition(v , u , centroid, depth + 1 , msk);
    }
    ans[u] += res;
    return res;
}

void decompose(int u) {
    int comp_sz   = dfs_sz(u, -1);
    int centroid  = dfs_centroid(u, -1, comp_sz);

    // 1) answer all paths passing through 'centroid'
    for (auto &v : adj[centroid]) {
        if (removed[v]) continue;
        dfs_ans(v, centroid , centroid);
        dfs_add(v, centroid , +1);
    }
    // 2) add paths that end in centroid itself
    
    // 3) exclude each subtree , see the paths in this subtree contribution then reinsert it
    for (auto &v : adj[centroid]) {
        if (removed[v]) continue;
        dfs_add(v , centroid , -1);
        dfs_contrubition(v , centroid , centroid);
        dfs_add(v , centroid , +1);
    }
    
    // clear data from the data structure , and reset res
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
 