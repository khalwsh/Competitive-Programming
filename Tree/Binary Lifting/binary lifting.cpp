const int Log = 21;
int up[N][Log],depth[N],parent[N],root = 0;
vector<int>adj[N];
void MarkDepth(int node,int par,int Dist = 0) {
    depth[node] = Dist;
    for (auto &val: adj[node]) {
        if (val == par)continue;
        MarkDepth(val, node,  Dist+ 1);
    }
}
void build(int n) {
    MarkDepth(root, -1);
    for (auto &val: up)for (auto &i: val)i = -1;
    parent[root] = root;// to handle non-existing edges
    for (int i = 0; i < n; i++)up[i][0] = parent[i];
    for (int i = 1; i < Log; i++) {
        for (int j = 0; j < n; j++) {
            up[j][i] = up[up[j][i - 1]][i - 1];
        }
    }
}
int query(int node,int k) {
    if (depth[node] < k)return -2;
    for (int i = 0; i < Log; i++) {
        if (k & (1 << i))node = up[node][i];
    }
    return node;
}