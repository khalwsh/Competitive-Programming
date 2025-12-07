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
    // Count distinct XORs < x
    ll count_le(ll x){
        if(x < 0) return 0;
        ll ret = 0, cnt = 1 << comp_sz, m = 0;
        for(int i = BITs - 1;i >= 0;--i){
            if(basis[i]){
                ll half = cnt >> 1;
                if(x>>i&1){ ret += half; if(!(m>>i&1)) m ^= basis[i]; }
                else      { if( m>>i&1) m ^= basis[i]; }
                cnt = half;
            } else {
                if(((x^m)>>i)&1) return (x>>i&1 ? ret+cnt : ret);
            }
        }
        return ret;
    }

    ll count_leq(int X){ return count_le(X+1); }
};