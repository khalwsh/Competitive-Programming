const int N = 2e5 + 10 , K = 19;
int depth[N];
vector<int>adj[N] , centroid_tree[N];
int centroid_parent[N];
int n , m , sz[N] , centroid_tree_root = -1;
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
map<int , int> dist[N];
void dfs_dist(int u, int p, int c, int d) {
    dist[c][u] = d;
    for (int v : adj[u]) {
        if (v == p || removed[v]) continue;
        dfs_dist(v, u, c, d + 1);
    }
}

int decompose(int u) {
    int comp_sz   = dfs_sz(u, -1);
    int centroid  = dfs_centroid(u, -1, comp_sz);
    if (centroid_tree_root == -1) centroid_tree_root = centroid;
    removed[centroid] = true;

    dist[centroid][centroid] = 0;

    for (int v : adj[centroid]) {
        if (!removed[v]) {
            dfs_dist(v, centroid, centroid, 1);
        }
    }
    for (auto &v : adj[centroid]) {
        if (!removed[v]) {
            int x = decompose(v);
            centroid_tree[centroid].emplace_back(x);
            centroid_tree[x].emplace_back(centroid);
            centroid_parent[x] = centroid;
        }
    }
    return centroid;
}