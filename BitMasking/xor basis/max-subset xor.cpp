struct Basis {
    const static int BITs = 60;
    ll basis[BITs + 1]{};
    int comp_sz = 0;

    void insert(ll msk) {
        for (int i = BITs; i >= 0; i--) {
            if (!(msk >> i & 1))continue;
            if (!basis[i]) {
                comp_sz++;
                basis[i] = msk;
                return;
            }
            msk ^= basis[i];
        }
    }

    ll get(ll msk) {
        for (int i = BITs; i >= 0; i--) {
            if (msk >> i & 1) continue;
            msk ^= basis[i];
        }
        return msk;
    }
};