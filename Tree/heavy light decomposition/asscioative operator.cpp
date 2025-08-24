const int N = 1e5 + 10;
// you do in your node , the forward merge and backward merge
// and handle in your update , query on path the merging in answer
vector<int> adj[N];
int parent[N], depth[N], heavy[N], root[N], pos[N], sz[N], timer , values[N];
int n , q;
void dfs_sz(int u, int p) {
    parent[u] = p;
    depth[u]  = (u==p ? 0 : depth[p]+1);
    sz[u]     = 1;
    heavy[u]  = -1;
    int maxSub = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs_sz(v, u);
        if (sz[v] > maxSub) {
            maxSub = sz[v];
            heavy[u] = v;
        }
        sz[u] += sz[v];
    }
}

void decompose(int u, int p) {
    root[u] = p;
    pos[u]  = timer++;
    if (heavy[u] != -1)
        decompose(heavy[u], p);
    for (int v : adj[u]) {
        if (v == parent[u] || v == heavy[u]) continue;
        decompose(v, v);
    }
}

void upd_path(int u, int v, ll nw) {
    while (root[u] != root[v]) {
        if (depth[root[u]] > depth[root[v]]) {
            seg.update(0, 0, n-1, pos[root[u]], pos[u], nw);
            u = parent[root[u]];
        } else {
            seg.update(0, 0, n-1, pos[root[v]], pos[v], nw);
            v = parent[root[v]];
        }
    }
    if (depth[u] > depth[v]) swap(u, v);
    seg.update(0, 0, n-1, pos[u], pos[v], nw);
}

Node query_path(int u, int v) {
    // Identity Node
    Node res_u(0, -inf, -inf, -inf), res_v(0, -inf, -inf, -inf);
    
    while (root[u] != root[v]) {
        if (depth[root[u]] > depth[root[v]]) {
            Node cur = seg.query(0,0,n-1, pos[root[u]], pos[u]);
            // make rev from cur
            Node rev_cur(cur.sum, cur.right, cur.left, cur.max);
            res_u = res_u + rev_cur;
            u = parent[root[u]];
        } else {
            Node cur = seg.query(0,0,n-1, pos[root[v]], pos[v]);
            res_v = cur + res_v;
            v = parent[root[v]];
        }
    }
    if (depth[u] > depth[v]) {
        Node cur = seg.query(0,0,n-1, pos[v], pos[u]);
        // make rev from cur
        Node rev_cur(cur.sum, cur.right, cur.left, cur.max);
        res_u = res_u + rev_cur;
    } else {
        Node cur = seg.query(0,0,n-1, pos[u], pos[v]);
        res_u = res_u + cur;
    }
    return res_u + res_v;
}