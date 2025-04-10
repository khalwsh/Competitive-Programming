struct SparseTable {
    vector<vector<int>> sp;
    vector<int> LOG;
    vector<int> arr;
    int n, LG;
    function<int(int, int)> f;

    SparseTable(vector<int>& _arr, function<int(int, int)> lamda) : arr(_arr), f(lamda) {
        n = (int)_arr.size();
        LOG = vector<int>(n + 1);
        LOG[0] = LOG[1] = 0;

        for (int i = 2; i <= n; ++i) {
            LOG[i] = LOG[i - 1] + !(i & (i - 1));
        }

        LG = LOG[n];
        sp = vector<vector<int>>(LG + 1, vector<int>(n));

        build();
    }

    void build() { // O(n log(n))
        sp[0] = arr;

        for (int lvl = 1; lvl <= LG; ++lvl) {
            for (int j = 0; j + (1 << lvl) <= n; ++j) {
                sp[lvl][j] = f(sp[lvl - 1][j], sp[lvl - 1][j + (1 << (lvl - 1))]);
            }
        }
    }

    int Query1(int l, int r) { // O(1)
        int lg = LOG[r - l + 1];
        return f(sp[lg][l], sp[lg][r - (1 << lg) + 1]);
    }

    int Query2(int l, int r) { // O(LogN)
        int lg = LOG[n];
        int ans = 0;

        for (int j = lg; ~j; --j) {
            if ((1 << j) <= (r - l + 1)) {
                ans = f(ans, sp[j][l]);
                l += (1 << j);
            }
        }
        return ans;
    }
};