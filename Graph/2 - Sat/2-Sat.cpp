struct SCC {
    int n;
    vector<vector<int>> g;

    SCC(int n) : n(n), g(n) {}

    void add(int u, int v) {
        g[u].push_back(v);
    }

    pair<int, vector<int>> ids() {
        vector<int> in(n, -1), low(n), id(n), st;
        int timer = 0, cnt = 0;

        function<void(int)> dfs = [&](int v) {
            low[v] = in[v] = timer++;
            st.push_back(v);

            for (int u : g[v]) {
                if (in[u] == -1) {
                    dfs(u);
                    low[v] = min(low[v], low[u]);
                } else if (in[u] < n) {
                    low[v] = min(low[v], in[u]);
                }
            }

            if (low[v] == in[v]) {
                while (true) {
                    int u = st.back();
                    st.pop_back();
                    in[u] = n;
                    id[u] = cnt;
                    if (u == v) break;
                }
                cnt++;
            }
        };

        for (int i = 0; i < n; i++)
            if (in[i] == -1)
                dfs(i);

        for (int &x : id)
            x = cnt - 1 - x;

        return {cnt, id};
    }
};

struct TwoSAT {
    int n, tot;
    vector<bool> ans;
    SCC s;
    vector<int> tr, fl;

    TwoSAT(int n)
        : n(n),
          tot(n),
          ans(n),
          s(2 * (9 * n + 5)),
          tr(4 * n + 5, -1),
          fl(4 * n + 5, -1) {
        build(tr, 1, 0, n - 1, 1);
        build(fl, 1, 0, n - 1, 0);
    }

    int new_var() {
        return tot++;
    }

    void add_or(int i, bool f, int j, bool g) {
        s.add(2 * i + !f, 2 * j + g);
        s.add(2 * j + !g, 2 * i + f);
    }

    void Imply(int i, bool f, int j, bool g) {
        add_or(i, !f, j, g);
    }

    void Xor(int i, bool f, int j, bool g) {
        add_or(i, f, j, g);
        add_or(i, !f, j, !g);
    }

    void XNOR(int i, bool f, int j, bool g) {
        Imply(i, f, j, g);
        Imply(j, g, i, f);
    }

    void XNAND(int i, bool f, int j, bool g) {
        add_or(i, !f, j, !g);
    }

    void AND(int i, bool f, int j, bool g) {
        force(i, f);
        force(j, g);
    }

    void force(int i, bool f) {
        add_or(i, f, i, f);
    }

    void build(vector<int> &t, int p, int l, int r, bool val) {
        t[p] = new_var();

        if (l == r) {
            Imply(t[p], 1, l, val);
            return;
        }

        int m = (l + r) >> 1;

        build(t, p << 1, l, m, val);
        build(t, p << 1 | 1, m + 1, r, val);

        Imply(t[p], 1, t[p << 1], 1);
        Imply(t[p], 1, t[p << 1 | 1], 1);
    }

    void update(vector<int> &t, int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return;

        if (ql <= l && r <= qr) {
            force(t[p], 1);
            return;
        }

        int m = (l + r) >> 1;

        update(t, p << 1, l, m, ql, qr);
        update(t, p << 1 | 1, m + 1, r, ql, qr);
    }

    void set_range_true(int l, int r) {
        update(tr, 1, 0, n - 1, l, r);
    }

    void set_range_false(int l, int r) {
        update(fl, 1, 0, n - 1, l, r);
    }

    bool solve() {
        auto [cnt, id] = s.ids();

        for (int i = 0; i < n; i++) {
            if (id[2 * i] == id[2 * i + 1])
                return false;

            ans[i] = id[2 * i] < id[2 * i + 1];
        }

        return true;
    }
};
