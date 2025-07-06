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
    ll distinct_subsets() {
        return (1LL << comp_sz);
    }
    ll get(ll k){
        if (distinct_subsets() < k) return -1;
        // Finding the k-th (one base) smallest xor_sum of all different subsequence xor_sum
        ll low = 1 << comp_sz;
        ll x = 0;
        for(int i = BITs; i >= 0; --i){
            if(!basis[i]) continue;
            low /= 2;
            if( (!(x >> i & 1) && low < k) || ((x >> i & 1) && low >= k) ){
                x ^= basis[i];
            }
            if(low < k) k -= low;
        }
        return x;
    }
};