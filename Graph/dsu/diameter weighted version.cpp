
template <class T>
struct sparsetable {
    int n, LOG;
    vector<vector<T>> st;

    sparsetable() {}

    sparsetable(vector<T> a) {
        n = (int)a.size();
        LOG = std::bit_width(n) + 1; // requires C++20; replace if needed
        st = vector<vector<T>>(LOG, vector<T>(n));
        st[0] = a;
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int l, int r) {
        int k = __lg(r - l + 1);
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

struct LCA {
    int timer;
    vector<vector<pair<int, ll>>> g; // (neighbor, weight)
    vector<int> tin, tout;
    vector<ll> dep; // store weighted depth
    vector<pair<ll, int>> flat; // (depth, node)
    sparsetable<pair<ll, int>> st;

    LCA() {}
    LCA(int n) : timer(0), g(n), tin(n), tout(n), dep(n), flat(2 * n) {}

    void add_edge(int u, int v, ll w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    void dfs(int v, int p) {
        flat[timer] = {dep[v], v};
        tin[v] = timer++;
        for (auto [u, w] : g[v]) {
            if (u == p) continue;
            dep[u] = dep[v] + w;
            dfs(u, v);
            flat[timer++] = {dep[v], v};
        }
        tout[v] = timer;
    }

    void build(int root) {
        timer = 0;
        // flat should be sized to exactly 2*n (or 2*n-1), ensure capacity
        if ((int)flat.size() != 2 * (int)g.size()) flat.assign(2 * g.size(), {0, 0});
        dep.assign(g.size(), 0);
        dfs(root, -1);
        // resize flat to actual used size (timer) before building sparse table
        vector<pair<ll,int>> used_flat(flat.begin(), flat.begin() + timer);
        st = sparsetable<pair<ll,int>>(used_flat);
    }

    int get_lca(int u, int v) {
        auto [l, r] = minmax(tin[u], tin[v]);
        return st.query(l, r).second;
    }

    ll get_dist(int u, int v) {
        int w = get_lca(u, v);
        return dep[u] + dep[v] - 2LL * dep[w];
    }
};

LCA lca;

struct DSU {
    int cnt;
    ll diam{}; // total diameter across unions (long long)
    vector<int> p, sz;
    vector<pair<int, int>> far; // far endpoint nodes for each component

    struct RB {
        int b;          // child that was attached
        int a;          // parent at the time of union
        int old_x;      // old far[a].first (before union)
        int old_y;      // old far[a].second
        ll old_diam;    // old diam before union
        int old_sz_a;   // old size of a (optional but safe)
    };

    vector<RB> st; // rollback stack

    DSU() {}
    DSU(int n) : cnt(n), p(n), sz(n, 1), far(n) {
        iota(begin(p), end(p), 0);
        for (int i = 0; i < n; i++) far[i] = {i, i};
        diam = 0;
    }

    int find(int v) {
        while (v != p[v]) v = p[v];
        return v;
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        // save rollback info
        RB rb;
        rb.b = b;
        rb.a = a;
        rb.old_x = far[a].first;
        rb.old_y = far[a].second;
        rb.old_diam = diam;
        rb.old_sz_a = sz[a];

        // perform union
        cnt--;
        sz[a] += sz[b];
        p[b] = a;

        // compute candidate diameters using far endpoints
        auto [x1, y1] = far[a];
        ll d1 = lca.get_dist(x1, y1);
        auto [x2, y2] = far[b];
        ll d2 = lca.get_dist(x2, y2);

        ll mx = d1;
        int mx1 = x1, mx2 = y1;
        if (d2 > mx) { mx = d2; mx1 = x2; mx2 = y2; }

        // check cross distances
        for (int u : {x1, y1}) {
            for (int v : {x2, y2}) {
                ll dist = lca.get_dist(u, v);
                if (dist > mx) { mx = dist; mx1 = u; mx2 = v; }
            }
        }

        // update global diameter and far endpoints for new root a
        diam = max(diam, mx);
        far[a] = {mx1, mx2};

        st.push_back(rb);
        return true;
    }

    void rollback() {
        if (st.empty()) return;
        RB rb = st.back(); st.pop_back();
        int b = rb.b;
        int a = rb.a;
        // restore parent and sizes
        p[b] = b;
        sz[a] = rb.old_sz_a;
        // restore far endpoints and diameter
        far[a] = {rb.old_x, rb.old_y};
        diam = rb.old_diam;
        cnt++;
    }
};