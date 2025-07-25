template<typename T>
struct sparseTable {
    int sz, lg;
    vector<vector<T> > t;
    function<T(T, T)> combine;
 
    void init(int n, function<T(T, T)> F) {
        sz = n;
        lg = __lg(n);
        combine = F;
        t.resize(lg + 1, vector<T>(n + 1));
    }
 
    void build(vector<T> &v) {
        for (int i = 0; i < sz; i++) {
            // TODO 0-based
            t[0][i] = v[i];
        }
        for (int p = 1; p <= lg; p++) {
            for (int i = 0; i + (1 << p) <= sz; i++) {
                t[p][i] = combine(t[p - 1][i], t[p - 1][i + (1 << (p - 1))]);
            }
        }
    }
 
    // TODO 0-based
    T query(int l, int r) {
        assert(l <= r);
        int k = 31 - __builtin_clz(r - l + 1);
        return combine(t[k][l], t[k][r - (1 << k) + 1]);
    }
 
    T queryLog(int l, int r, T neutral) {
        assert(l <= r);
        T ret = neutral;
        while (l <= r) {
            int k = 31 - __builtin_clz(r - l + 1);
            ret = combine(ret, t[k][l]);
            l += (1 << k);
        }
        return ret;
    }
};