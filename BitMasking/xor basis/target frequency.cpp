long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
const int mod = 998244353;
struct Basis {
    static const int BITs = 60;
    ll basis[BITs + 1]{};
    int comp_sz = 0;
    void insert(ll msk) {
        for (int i = BITs; i >= 0;i--) {
            if (!(msk >> i & 1))continue;
            if (!basis[i]) {
                comp_sz++;
                basis[i] = msk;
                return;
            }
            msk ^= basis[i];
        }
    }
    ll get(ll mask , int total_elements) {
        for (int i = BITs; i >= 0; --i) {
            if (!(mask >> i & 1)) continue;
            if (!basis[i])
                return 0;
            mask ^= basis[i];
        }
        return binpow(2 , total_elements - comp_sz , mod);
    }
};
