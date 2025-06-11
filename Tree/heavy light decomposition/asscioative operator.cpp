// you do in your node , the forward merge and backward merge
// and handle in your update , query on path the merging in answer
// so you merge this + a you look at it ---> or <----
vector<int> adj[N];
int parent[N], depth[N], heavy[N], root[N], pos[N], sz[N], timer;

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

void upd_path(int u, int v, const Node &nw) {
    while (root[u] != root[v]) {
        if (depth[root[u]] > depth[root[v]]) {
            seg.upd(0, 0, n-1, pos[root[u]], pos[u], nw);
            u = parent[root[u]];
        } else {
            seg.upd(0, 0, n-1, pos[root[v]], pos[v], nw);
            v = parent[root[v]];
        }
    }
    if (depth[u] > depth[v]) swap(u, v);
    seg.upd(0, 0, n-1, pos[u], pos[v], nw);
}

Node query_path(int u, int v) {
    Node res_u(1,0), res_v(1,0);
    while (root[u] != root[v]) {
        if (depth[root[u]] > depth[root[v]]) {
            Node cur = seg.query(0,0,n-1, pos[root[u]], pos[u]);
// reverse merging
            // res_u = res_u + Node(cur.c_rev, cur.d_rev);
            u = parent[root[u]];
        } else {
            Node cur = seg.query(0,0,n-1, pos[root[v]], pos[v]);
// forward merging
            // res_v = Node(cur.c_for, cur.d_for) + res_v;
            v = parent[root[v]];
        }
    }
// if you want weight on edges add one on the range if nodes are not equal , if equal ignore update
    if (depth[u] > depth[v]) {
        Node cur = seg.query(0,0,n-1, pos[v], pos[u]);
// reverse merging
        // res_u = res_u + Node(cur.c_rev, cur.d_rev);
    } else {
        Node cur = seg.query(0,0,n-1, pos[u], pos[v]);
// forward merging
        // res_u = res_u + Node(cur.c_for, cur.d_for);
    }
    return res_u + res_v;
}