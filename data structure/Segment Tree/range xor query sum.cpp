struct segmentTree {
    static const int BITS = 30;
    vector<int>tree[BITS] , lazy[BITS];
    segmentTree (int n) {
        for (int i = 0;i < BITS;i++) {
            tree[i].resize(4 * n);
            lazy[i].resize(4 * n);
        }
    }
    void prop(int node , int nl , int nr) {
        for (int i = 0; i < BITS; i++) {
            if (lazy[i][node] & 1) {
                tree[i][node] = (nr - nl + 1) - tree[i][node];
                if (nl != nr) {
                    lazy[i][2 * node + 1] ^= 1;
                    lazy[i][2 * node + 2] ^= 1;
                }
                lazy[i][node] = 0;
            }
        }
    }

    void upd(int node , int nl , int nr , int l , int r , int val) {
        prop(node , nl , nr);
        if (nl >= l && nr <= r) {
            for (int i = 0; i < BITS; i++) {
                if (val >> i & 1) {
                    tree[i][node] = (nr - nl + 1) - tree[i][node];
                    if (nl != nr) {
                        lazy[i][2 * node + 1] ^= 1;
                        lazy[i][2 * node + 2] ^= 1;
                    }
                }
            }
            return;
        }

        if (nl > r || nr < l)return;
        int mid = nl + (nr - nl) / 2;
        upd(2 * node + 1 , nl , mid , l , r , val);
        upd(2 * node + 2 , mid + 1 , nr , l , r , val);
        for (int i = 0;i < BITS;i++) {
            tree[i][node] = tree[i][2 * node + 1] + tree[i][2 * node + 2];
        }
    }
    ll query(int node , int nl , int nr , int l , int r) {
        prop(node , nl , nr);
        if (nl > r || nr < l)return 0;
        if (nl >= l && nr <= r) {
            ll res = 0;
            for (int i = 0;i < BITS;i++) {
                res += (1LL<<i) * tree[i][node];
            }
            return res;
        }
        int mid = nl + (nr - nl) / 2;
        return query(2 * node + 1 , nl , mid , l , r) + query(2 * node + 2 , mid + 1 , nr , l , r);
    }
};