class SegmentTree {
public:
    int n;
    int NoOperation;
    vector<int> tree, lazy;

    void init(int _n) {
        n = _n;
        NoOperation = 0;
        tree.resize(4 * n);
        lazy.resize(4 * n, NoOperation);
    }

    SegmentTree(int _n) {
        init(_n);
    }

private:
    void build(int node, int nl, int nr, vector<int> &v) {
        if (nl == nr) {
            tree[node] = v[nl];
            return;
        }
        int mid = nl + (nr - nl) / 2;
        build(2 * node + 1, nl, mid, v);
        build(2 * node + 2, mid + 1, nr, v);
        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void PropAdd(int node, int nl, int nr) {
        if (lazy[node] == NoOperation)return;
        tree[node] += lazy[node];
        if (nl != nr) {
            lazy[2 * node + 1] += lazy[node];
            lazy[2 * node + 2] += lazy[node];
        }
        lazy[node] = NoOperation;
    }

    void RangeAdd(int node, int nl, int nr, int l, int r, int delta) {
        PropAdd(node, nl, nr);
        if (nl >= l && nr <= r) {
            tree[node] += delta;
            if (nl != nr) {
                lazy[2 * node + 1] += delta;
                lazy[2 * node + 2] += delta;
            }
            return;
        }
        if (nl > r || nr < l)return;
        int mid = nl + (nr - nl) / 2;
        RangeAdd(2 * node + 1, nl, mid, l, r, delta);
        RangeAdd(2 * node + 2, mid + 1, nr, l, r, delta);
        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void PropAssign(int node, int nl, int nr) {
        if (lazy[node] == NoOperation)return;
        tree[node] = lazy[node];
        if (nl != nr) {
            lazy[2 * node + 1] = lazy[node];
            lazy[2 * node + 2] = lazy[node];
        }
        lazy[node] = NoOperation;
    }

    void RangeAssign(int node, int nl, int nr, int l, int r, int newVal) {
        PropAssign(node, nl, nr);
        if (nl >= l && nr <= r) {
            tree[node] = newVal;
            if (nl != nr) {
                lazy[2 * node + 1] = newVal;
                lazy[2 * node + 2] = newVal;
            }
            return;
        }
        if (nl > r || nr < l)return;
        int mid = nl + (nr - nl) / 2;
        RangeAssign(2 * node + 1, nl, mid, l, r, newVal);
        RangeAssign(2 * node + 2, mid + 1, nr, l, r, newVal);
        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    int QueryAdd(int node, int nl, int nr, int l, int r) {
        PropAdd(node, nl, nr);
        if (nl >= l && nr <= r) {
            return tree[node];
        }
        if (nl > r || nr < l)return -inf;
        int mid = nl + (nr - nl) / 2;
        return max(QueryAdd(2 * node + 1, nl, mid, l, r), QueryAdd(2 * node + 2, mid + 1, nr, l, r));
    }

    int QueryAssign(int node, int nl, int nr, int l, int r) {
        PropAssign(node, nl, nr);
        if (nl >= l && nr <= r) {
            return tree[node];
        }
        if (nl > r || nr < l)return -inf;
        int mid = nl + (nr - nl) / 2;
        return max(QueryAssign(2 * node + 1, nl, mid, l, r), QueryAssign(2 * node + 2, mid + 1, nr, l, r));
    }

public:
    void build(vector<int> &v) {
        build(0, 0, n - 1, v);
    }

    void RangeAdd(int l, int r, int delta) {
        RangeAdd(0, 0, n - 1, l, r, delta);
    }

    void RangeAssign(int l, int r, int newVal) {
        RangeAssign(0, 0, n - 1, l, r, newVal);
    }

    int QueryAdd(int l, int r) {
        return QueryAdd(0, 0, n - 1, l, r);
    }

    int QueryAssign(int l, int r) {
        return QueryAssign(0, 0, n - 1, l, r);
    }
};