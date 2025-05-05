template<typename T = ll>
struct SRQ {
    static const int LG = 20;
    int n;
    vector<vector<T>> prec;
    vector<int> msk;
    vector<T> a;

    SRQ(const vector<T>& arr) : a(arr) {
        n = a.size();
        prec.assign(LG, vector<T>(n));
        msk.assign(n, 0);
        build(0, n-1, 0);
    }

    // our associative operator
    T comb(T x, T y) const {
        return x * y % p;
    }

    void build(int l, int r, int lvl) {
        if (l == r) return;
        int m = (l + r) >> 1;
        prec[lvl][m]     = a[m];
        prec[lvl][m + 1] = a[m + 1];

        for (int i = m - 1; i >= l; --i)
            prec[lvl][i] = comb(a[i], prec[lvl][i + 1]);

        for (int i = m + 2; i <= r; ++i)
            prec[lvl][i] = comb(a[i], prec[lvl][i - 1]);

        for (int i = m + 1; i <= r; ++i)
            msk[i] |= (1 << lvl);

        build(l,     m,    lvl + 1);
        build(m + 1, r,    lvl + 1);
    }

    T query(int l, int r) const {
        if (l == r)
            return a[l];
        int mask_xor = msk[l] ^ msk[r];
        if (mask_xor == 0) {
            int m = (0 + (n - 1)) >> 1;
            if (r <= m)      return prec[0][r];
            else if (l > m)  return prec[0][l];
            return comb(prec[0][l], prec[0][r]);
        }
        int k = __builtin_ctz(mask_xor);
        return comb(prec[k][l], prec[k][r]);
    }
};