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
    ll get(ll k, int n) {
        // k: 1-based index among ALL subsets (duplicates allowed)
        // n: original number of vectors (so total subsets = 1<<n)
        ll mult = 1LL << (n - comp_sz);
        ll k_unique = (k + mult - 1) / mult;

        vector<pair<int, ll>> vec;
        for (int i = BITs; i >= 0; --i) {
            if (basis[i]) vec.emplace_back(i, basis[i]);
        }
        int m = (int)vec.size();
        ll rem = k_unique;
        ll x = 0;
        for (int j = 0; j < m; ++j) {
            int lead = vec[j].first;
            ll b = vec[j].second;
            ll half = 1LL << (m - j - 1);
            if (((x >> lead) & 1LL) == 0) {
                if (rem > half) {
                    rem -= half;
                    x ^= b;
                }
            } else {
                if (rem <= half) {
                    x ^= b;
                } else {
                    rem -= half;
                }
            }
        }
        return x;
    }

};