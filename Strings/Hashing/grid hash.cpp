template <typename T>
struct Hashing {
    vector<vector<long long>> hs;
    vector<long long> PWX, PWY;
    int n, m;
    static constexpr int PX = 3731, PY = 2999, mod = 998244353;

    Hashing() {}

    // Constructor for vector<vector<T>> (e.g., vector<vector<int>>, vector<vector<char>>)
    Hashing(const vector<vector<T>>& grid) {
        n = grid.size();
        m = grid[0].size();
        if constexpr (std::is_same_v<T, char>) {
            initialize(grid, [](char c) { return c - 'a' + 1; }); // Convert chars correctly
        } else {
            initialize(grid, [](T val) { return static_cast<int>(val); });
        }
    }

    // Constructor for vector<string>
    Hashing(const vector<string>& s) {
        n = s.size();
        m = s[0].size();
        initialize_string(s);
    }

    // Generic initializer for vector<vector<T>>
    template <typename U, typename F>
    void initialize(const vector<vector<U>>& grid, F transform) {
        hs.assign(n + 1, vector<long long>(m + 1, 0));
        PWX.assign(n + 1, 1);
        PWY.assign(m + 1, 1);

        for (int i = 0; i < n; i++) PWX[i + 1] = 1LL * PWX[i] * PX % mod;
        for (int i = 0; i < m; i++) PWY[i + 1] = 1LL * PWY[i] * PY % mod;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                hs[i + 1][j + 1] = transform(grid[i][j]);
            }
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                hs[i][j + 1] = (hs[i][j + 1] + 1LL * hs[i][j] * PY % mod) % mod;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                hs[i + 1][j] = (hs[i + 1][j] + 1LL * hs[i][j] * PX % mod) % mod;
            }
        }
    }

    // Special case initializer for vector<string>
    void initialize_string(const vector<string>& s) {
        hs.assign(n + 1, vector<long long>(m + 1, 0));
        PWX.assign(n + 1, 1);
        PWY.assign(m + 1, 1);

        for (int i = 0; i < n; i++) PWX[i + 1] = 1LL * PWX[i] * PX % mod;
        for (int i = 0; i < m; i++) PWY[i + 1] = 1LL * PWY[i] * PY % mod;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                hs[i + 1][j + 1] = s[i][j] - 'a' + 1;
            }
        }

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                hs[i][j + 1] = (hs[i][j + 1] + 1LL * hs[i][j] * PY % mod) % mod;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= m; j++) {
                hs[i + 1][j] = (hs[i + 1][j] + 1LL * hs[i][j] * PX % mod) % mod;
            }
        }
    }

    long long get_hash(int x1, int y1, int x2, int y2) {
        x1++, y1++, x2++, y2++;
        assert(1 <= x1 && x1 <= x2 && x2 <= n);
        assert(1 <= y1 && y1 <= y2 && y2 <= m);
        x1--;
        y1--;
        int dx = x2 - x1, dy = y2 - y1;
        return (1LL * (hs[x2][y2] - 1LL * hs[x2][y1] * PWY[dy] % mod + mod) % mod -
                1LL * (hs[x1][y2] - 1LL * hs[x1][y1] * PWY[dy] % mod + mod) % mod * PWX[dx] % mod + mod) % mod;
    }

    long long get_hash() {
        return get_hash(0, 0, n - 1, m - 1);
    }
};