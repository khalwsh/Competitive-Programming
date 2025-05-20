struct TwoSat {
    int N;
    vector<vector<int>> gr;
    vector<int> values;

    TwoSat(int n = 0) : N(n), gr(2 * n) {}

    int varIndex(int x) {
        return (x > 0 ? 2 * (x - 1) : 2 * (-x - 1) + 1);
    }

    void either(int x, int y) {
        int a = varIndex(x);
        int b = varIndex(y);
        gr[a ^ 1].push_back(b); // ¬a ⇒ b
        gr[b ^ 1].push_back(a); // ¬b ⇒ a
    }

    void setTrue(int x) {
        either(x, x); // x ∨ x
    }

    void setFalse(int x) {
        either(-x, -x); // ¬x ∨ ¬x
    }

    void or_(int x, int y) {
        either(x, y); // x ∨ y
    }

    void and_(int x, int y) {
        // x ∧ y  ≡  (x) AND (y)
        // To enforce x and y to be true, we set both to true
        setTrue(x);
        setTrue(y);
    }

    void xor_(int x, int y) {
        // x != y
        either(x, y);
        either(-x, -y);
    }

    void xnor(int x, int y) {
        // x == y
        either(x, -y);
        either(-x, y);
    }

    vector<int> val, comp, z;
    int time = 0;

    int dfs(int u) {
        int low = val[u] = ++time;
        z.push_back(u);
        for (int v : gr[u]) {
            if (!val[v]) low = min(low, dfs(v));
            else if (!comp[v]) low = min(low, val[v]);
        }
        if (low == val[u]) {
            while (true) {
                int v = z.back(); z.pop_back();
                comp[v] = low;
                int var = v >> 1;
                if (values[var] == -1)
                    values[var] = v & 1;
                if (v == u) break;
            }
        }
        return low;
    }

    bool solve() {
        values.assign(N, -1);
        val.assign(2 * N, 0);
        comp.assign(2 * N, 0);
        time = 0;
        for (int i = 0; i < 2 * N; ++i) {
            if (!val[i]) dfs(i);
        }
        for (int i = 0; i < N; ++i) {
            if (comp[2 * i] == comp[2 * i + 1])
                return false;
        }
        return true;
    }
};