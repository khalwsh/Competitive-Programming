struct Basis {
    static const int BITs = 30;
    int basis[BITs + 1]{};
    int comp_sz = 0;
    void insert(int msk) {
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
    ll min_xor(ll x){
        for(int i = BITs - 1; i >= 0; --i){
            if( (x ^ basis[i]) < x) x ^= basis[i];
        }
        return x;
    }
};