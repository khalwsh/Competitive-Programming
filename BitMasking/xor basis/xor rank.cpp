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
    int k_th(int k){
        /*
            Finding the k-th smallest xor_sum of all different subsequence xor_sum
        */
        int low = 1 << comp_sz;
        int x = 0;
        for(int i = BITs - 1; i >= 0; --i){
            if(!basis[i]) continue;
            low /= 2;
            if( (!(x >> i & 1) && low < k) || ((x >> i & 1) && low >= k) ){
                x ^= basis[i];
            }
            if(low < k) k -= low;
        }
        return x;
    }
    /*
    Return the number of distinct subsequence xor_sums that are < x.
    */
    ll rank_xor(int x){
        if(x < 0) return 0;
        ll ans = 0, cnt = 1LL << comp_sz, m = 0;
        for(int i = BITs-1; i >= 0; --i){
            if(basis[i]){
                if((x>>i)&1){
                    ans += cnt>>1;
                    if(!((m>>i)&1)) m ^= basis[i];
                } else if((m>>i)&1) m ^= basis[i];
                cnt >>= 1;
            } else {
                if(((x>>i)&1) != ((m>>i)&1))
                    return ((x>>i)&1 ? ans + cnt : ans);
            }
        }
        return ans;
    }
};