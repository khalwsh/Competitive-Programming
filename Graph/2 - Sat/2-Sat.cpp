struct SCC_Solver {
    int n;
    vector<vector<int> > g;
    SCC_Solver(int n) : n(n), g(n) {
    }
    void add_edge(int u, int v) { g[u].push_back(v); }
    pair<int, vector<int> > scc_ids() {
        vector<int> tin(n, -1), low(n), id(n), stk;
        int timer = 0, scc_cnt = 0;
        stk.reserve(n);
        function<void(int)> dfs = [&](int v) {
            low[v] = tin[v] = timer++;
            stk.push_back(v);
            for (int to: g[v]) {
                if (tin[to] == -1) {
                    dfs(to);
                    low[v] = min(low[v], low[to]);
                } else if (tin[to] < n) {
                    // Node is on stack
                    low[v] = min(low[v], tin[to]);
                }
            }
            if (low[v] == tin[v]) {
                while (true) {
                    int u = stk.back();
                    stk.pop_back();
                    tin[u] = n; // Mark as processed
                    id[u] = scc_cnt;
                    if (u == v) break;
                }
                scc_cnt++;
            }
        };
        for (int i = 0; i < n; i++) if (tin[i] == -1) dfs(i);
        for (auto &x: id) x = scc_cnt - 1 - x;
        return {scc_cnt, id};
    }
    vector<vector<int> > sccs() {
        auto p = scc_ids();
        int scc_cnt = p.first;
        vector<int> id = p.second;
        vector<vector<int> > res(scc_cnt);
        for (int i = 0; i < n; i++) res[id[i]].push_back(i);
        return res;
    }
};
struct TwoSAT {
    int n;
    vector<bool> ans;
    SCC_Solver s;
    TwoSAT(int n) : n(n), ans(n), s(2 * n) {}
    void add_or(int i, bool f, int j, bool g) {
        s.add_edge(2 * i + !f, 2 * j + g);
        s.add_edge(2 * j + !g, 2 * i + f);
    }
    void Xor(int i, bool f, int j, bool g) {
        add_or(i, f, j, g);
        add_or(i, !f, j, !g);
    }
    void Imply(int i, bool f, int j, bool g) { add_or(i, !f, j, g); }
    void BiImply(int i, bool f, int j, bool g) {
        // XNOR
        Imply(i, f, j, g);
        Imply(j, f, i, g);
    }
    void force_true(int i) { add_or(i, true, i, true); }
    void force_false(int i) { add_or(i, false, i, false); }
    bool solve() {
        auto p = s.scc_ids();
        vector<int> id = p.second;
        for (int i = 0; i < n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] < id[2 * i + 1];
        }
        return true;
    }
    vector<bool> get_ans() { return ans; }
};