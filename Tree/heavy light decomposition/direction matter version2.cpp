
const ll inf = 1e18;
const int N = 1e5 + 10;

struct Node {
    // note: you don't consider empty subarray so if you want max(answer , 0)
    ll left, right, max, sum;

    Node(ll a = 0, ll b = -inf, ll c = -inf, ll d = -inf) {
        sum = a, left = b, right = c, max = d;
    }

    Node operator+(const Node &a) const {
        Node res;
        res.sum = a.sum + sum;
        res.left = std::max(left, sum + a.left);
        res.right = std::max(a.right, a.sum + right);
        res.max = std::max({max, a.max, right + a.left});
        return res;
    }
};

struct SegmentTree {
    vector<Node> tree;
    vector<ll> lazy;
    int n;

    SegmentTree(int _n = 0) {
        n = _n;
        tree.resize(4 * n);
        lazy.resize(4 * n, -inf);
    }

    void init(int _n) {
        n = _n;
        tree.assign(4 * n, Node());
        lazy.assign(4 * n, -inf);
    }

    void build(int node, int nl, int nr, vector<ll> &v) {
        if (nl == nr) {
            tree[node] = Node(v[nl], v[nl], v[nl], v[nl]);
            return;
        }
        int mid = nl + (nr - nl) / 2;
        build(2 * node + 1, nl, mid, v);
        build(2 * node + 2, mid + 1, nr, v);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    void prop(int node, int nl, int nr) {
        if (lazy[node] != -inf) {
            ll val = 1LL * (nr - nl + 1) * lazy[node];
            tree[node] = Node(val, val, val, val);
            if (nl != nr) {
                lazy[node * 2 + 1] = lazy[node];
                lazy[node * 2 + 2] = lazy[node];
            }
            lazy[node] = -inf;
        }
    }

    void update(int node, int nl, int nr, int l, int r, ll newValue) {
        prop(node, nl, nr);
        if (nl >= l && nr <= r) {
            ll val = 1LL * (nr - nl + 1) * newValue;
            tree[node] = Node(val, val, val, val);
            if (nl != nr) {
                lazy[node * 2 + 1] = newValue;
                lazy[node * 2 + 2] = newValue;
            }
            return;
        }
        if (nl > r || nr < l) return;
        int mid = nl + (nr - nl) / 2;
        update(2 * node + 1, nl, mid, l, r, newValue);
        update(2 * node + 2, mid + 1, nr, l, r, newValue);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    Node query(int node, int nl, int nr, int l, int r) {
        prop(node, nl, nr);
        if (nl >= l && nr <= r) return tree[node];
        if (nl > r || nr < l) return Node(); // empty
        int mid = nl + (nr - nl) / 2;
        return query(2 * node + 1, nl, mid, l, r) + query(2 * node + 2, mid + 1, nr, l, r);
    }
} seg(N);

/*
 * you call size
 * then call decompose
 * path update work normally
 * you need to implement revNode which will will make the node like it was right to left calculated not left to right
 */
vector<int> adj[N];
int parent[N], depth[N], heavy[N], root[N], pos[N], sz[N], timer, values[N];
int n, q;

void dfs_sz(int u, int p) {
    parent[u] = p;
    depth[u] = (u == p ? 0 : depth[p] + 1);
    sz[u] = 1;
    heavy[u] = -1;
    int maxSub = 0;
    for (int v: adj[u]) {
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
    pos[u] = timer++;
    if (heavy[u] != -1)
        decompose(heavy[u], p);
    for (int v: adj[u]) {
        if (v == parent[u] || v == heavy[u]) continue;
        decompose(v, v);
    }
}

void upd_path(int u, int v, ll nw) {
    while (root[u] != root[v]) {
        if (depth[root[u]] > depth[root[v]]) {
            seg.update(0, 0, n - 1, pos[root[u]], pos[u], nw);
            u = parent[root[u]];
        } else {
            seg.update(0, 0, n - 1, pos[root[v]], pos[v], nw);
            v = parent[root[v]];
        }
    }
    if (depth[u] > depth[v]) swap(u, v);
    seg.update(0, 0, n - 1, pos[u], pos[v], nw);
}

static Node revNode(const Node &x) {
    Node r = x;
    swap(r.left, r.right);
    return r;
}

Node query_path(int u, int v) {
    Node leftRes = Node();
    Node rightRes = Node();
    while (root[u] != root[v]) {
        if (depth[root[u]] > depth[root[v]]) {
            Node cur = seg.query(0, 0, n - 1, pos[root[u]], pos[u]);
            cur = revNode(cur);
            leftRes = leftRes + cur;
            u = parent[root[u]];
        } else {
            Node cur = seg.query(0, 0, n - 1, pos[root[v]], pos[v]);
            rightRes = cur + rightRes;
            v = parent[root[v]];
        }
    }
    Node mid;
    if (pos[u] <= pos[v]) {
        mid = seg.query(0, 0, n - 1, pos[u], pos[v]);
    } else {
        mid = seg.query(0, 0, n - 1, pos[v], pos[u]);
        mid = revNode(mid);
    }
    Node res = leftRes + mid + rightRes;
    return res;
}
