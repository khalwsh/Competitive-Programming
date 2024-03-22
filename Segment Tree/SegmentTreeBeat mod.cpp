struct SegmentTreeBeats{
    vector<int>tsum,tmax;
    //one based seg
    //build by update index with it's value
    //update set index val to x
    //update take index val % x
    SegmentTreeBeats(int n){
        tsum.resize(4*n);
        tmax.resize(4*n);
    }
    void update_mod(int l, int r, long long v, int t = 1, int tl = 1, int tr = N) {
        if (r < tl || tr < l || tmax[t] < v) {
            return;
        } else if (tl == tr) {
            int val = tmax[t] % v;
            tsum[t] = tmax[t] = val;
            return;
        }

        int tm = (tl + tr) / 2;
        update_mod(l, r, v, t * 2, tl, tm);
        update_mod(l, r, v, t * 2 + 1, tm + 1, tr);
        tsum[t] = tsum[t * 2] + tsum[t * 2 + 1];
        tmax[t] = max(tmax[t * 2], tmax[t * 2 + 1]);
    }

    void update_set(int i, long long v, int t = 1, int tl = 1, int tr = N) {
        if (tl == tr) {
            tsum[t] = tmax[t] = v;
            return;
        }

        int tm = (tl + tr) / 2;
        if (i <= tm) {
            update_set(i, v, t * 2, tl, tm);
        } else {
            update_set(i, v, t * 2 + 1, tm + 1, tr);
        }
        tsum[t] = tsum[t * 2] + tsum[t * 2 + 1];
        tmax[t] = max(tmax[t * 2], tmax[t * 2 + 1]);
    }

    long long query(int l, int r, int t = 1, int tl = 1, int tr = N) {
        if (r < tl || tr < l) {
            return 0;
        } else if (l <= tl && tr <= r) {
            return tsum[t];
        }

        int tm = (tl + tr) / 2;
        return query(l, r, t * 2, tl, tm) + query(l, r, t * 2 + 1, tm + 1, tr);
    }
};
