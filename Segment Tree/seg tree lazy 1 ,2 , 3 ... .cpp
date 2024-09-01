class SegmentTree {
    int n;
    vector<long long> segtree;
    vector<pair<long long, int> > lazy;

public:
    void init(int sz) {
        n = sz;
        segtree.resize(1 + 4 * sz);
        lazy.resize(1 + 4 * sz);
    }

    long long gauss(int start, int len, int step) {
        return 1LL * start * len + 1LL * step * (len - 1) * len / 2;
    }

    void lz(int node, int L, int R) {
        segtree[node] += gauss(lazy[node].first, R - L + 1, lazy[node].second);
        int mid = (L + R) / 2;
        if (L != R) {
            lazy[node << 1].first += lazy[node].first;
            lazy[node << 1].second += lazy[node].second;
            lazy[node << 1 | 1].first += lazy[node].first + 1LL * lazy[node].second * (mid - L + 1);
            lazy[node << 1 | 1].second += lazy[node].second;
        }
        lazy[node] = {0, 0};
    }

    void build(int node, int L, int R, vector<int> &v) {
        if (L == R) {
            segtree[node] = v[L];
            return;
        }
        int mid = (L + R) / 2;
        build(node << 1, L, mid, v);
        build(node << 1 | 1, mid + 1, R, v);
        segtree[node] = segtree[node << 1] + segtree[node << 1 | 1];
    }

    void update(int node, int L, int R, int Lq, int Rq, int val) {
        if (lazy[node].first)
            lz(node, L, R);
        if (R < Lq || L > Rq)
            return;
        if (Lq <= L && R <= Rq) {
            lazy[node].first = val + (L - Lq);
            lazy[node].second++;
            lz(node, L, R);
            return;
        }
        int mid = (L + R) / 2;
        update(node << 1, L, mid, Lq, Rq, val);
        update(node << 1 | 1, mid + 1, R, Lq, Rq, val);
        segtree[node] = segtree[node << 1] + segtree[node << 1 | 1];
    }

    long long query(int node, int L, int R, int Lq, int Rq) {
        if (lazy[node].first)
            lz(node, L, R);
        if (R < Lq || L > Rq)
            return 0;
        if (Lq <= L && R <= Rq)
            return segtree[node];
        int mid = (L + R) / 2;
        return query(node << 1, L, mid, Lq, Rq) + query(node << 1 | 1, mid + 1, R, Lq, Rq);
    }
};
