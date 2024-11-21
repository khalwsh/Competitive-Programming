struct SegmentTree {
    int N;
    vector<int> lo, hi;
    vector<ll> del, ass, sum;

    SegmentTree(int n) {
        N = n;
        lo.resize(4 * n);
        hi.resize(4 * n);
        del.resize(4 * n, 0);
        ass.resize(4 * n, -1); // -1 means no assignment
        sum.resize(4 * n, 0);
    }

    int len(int i) {
        return hi[i] - lo[i] + 1;
    }

    void increment(int i, ll v) {
        del[i] += v;
        sum[i] += len(i) * v;
    }

    void assign(int i, ll v) {
        ass[i] = v;
        del[i] = 0;
        sum[i] = len(i) * v;
    }

    void push(int i) {
        if (ass[i] != -1) {  // There's an assignment to propagate
            assign(2 * i, ass[i]);
            assign(2 * i + 1, ass[i]);
            ass[i] = -1;  // Clear the assignment
        }
        if (del[i] != 0) {  // There's an addition to propagate
            increment(2 * i, del[i]);
            increment(2 * i + 1, del[i]);
            del[i] = 0;  // Clear the addition
        }
    }

    void pull(int i) {
        sum[i] = sum[2 * i] + sum[2 * i + 1];
    }

    void build(int i, int l, int r) {
        lo[i] = l;
        hi[i] = r;
        if (l == r) {
            sum[i] = 0;  // Initially all elements are 0
            return;
        }
        int m = (l + r) / 2;
        build(2 * i, l, m);
        build(2 * i + 1, m + 1, r);
        pull(i);
    }

    void increment(int i, int l, int r, ll v) {
        if (l > hi[i] || r < lo[i]) return;
        if (l <= lo[i] && hi[i] <= r) {
            increment(i, v);
            return;
        }

        push(i);
        increment(2 * i, l, r, v);
        increment(2 * i + 1, l, r, v);
        pull(i);
    }

    void assign(int i, int l, int r, ll v) {
        if (l > hi[i] || r < lo[i]) return;
        if (l <= lo[i] && hi[i] <= r) {
            assign(i, v);
            return;
        }

        push(i);
        assign(2 * i, l, r, v);
        assign(2 * i + 1, l, r, v);
        pull(i);
    }

    ll query(int i, int l, int r) {
        if (l > hi[i] || r < lo[i]) return 0;
        if (l <= lo[i] && hi[i] <= r) {
            return sum[i];
        }

        push(i);
        ll lsum = query(2 * i, l, r);
        ll rsum = query(2 * i + 1, l, r);
        pull(i);

        return lsum + rsum;
    }
};