
/*
- remember to init centroid parent with -1
- this will return centroid_tree which is tree of height log(n)
- you will build lca on original tree , consider making it with Euler tour because already height is log(n)
- usually you need to update the path from node u to root and when query take the best from u to root adding the cost of moving
*/

const int N = 2e5 + 10 , K = 19;
int depth[N];
vector<int>adj[N] , centroid_tree[N];
int centroid_parent[N];
int n , m , sz[N] , centroid_tree_root = -1;
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

int decompose(int u) {
    int comp_sz   = dfs_sz(u, -1);
    int centroid  = dfs_centroid(u, -1, comp_sz);
    if (centroid_tree_root == -1) centroid_tree_root = centroid;
    removed[centroid] = true;
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