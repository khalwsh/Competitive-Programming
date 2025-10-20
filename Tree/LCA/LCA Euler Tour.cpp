// remember to pass LCA to the dsu , build LCA before passing it
template <class T>
struct sparsetable {
    int n, LOG;
    vector<vector<T>> st;
 
    sparsetable() {}
 
    sparsetable(vector<T> a) {
        n = a.size();
        LOG = bit_width(a.size()) + 1;
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
    vector<vector<int>> g;
    vector<int> tin, tout, dep;
    vector<pair<int, int>> flat;
    sparsetable<pair<int, int>> st;
 
    LCA() {}
    LCA(int n) : timer(0), g(n), tin(n), tout(n), dep(n), flat(2 * n) {}
 
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
 
    void dfs(int v, int p) {
        flat[timer] = {dep[v], v};
        tin[v] = timer++;
        for (int u : g[v]) {
            if (u == p) continue;
            dep[u] = dep[v] + 1;
            dfs(u, v);
            flat[timer++] = {dep[v], v};
        }
        tout[v] = timer;
    }
 
    void build(int root) {
        dfs(root, -1);
        st = sparsetable(flat);
    }
 
    int get_lca(int u, int v) {
        auto [l, r] = minmax(tin[u], tin[v]);
        return st.query(l, r).second;
    }
 
    int get_dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[get_lca(u, v)];
    }
};
 
LCA lca;
