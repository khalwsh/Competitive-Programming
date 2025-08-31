struct Node {
    ll firstValue, Increment;
    Node(ll f = 0, ll i = 0) {
        firstValue = f;
        Increment = i;
    }
    Node operator+(const Node &a) {
        Node res;
        res.firstValue = firstValue + a.firstValue;
        res.Increment = Increment + a.Increment;
        return res;
    }
};

struct SegmentTree {
    vector<ll> tree;
    vector<Node> lazy;

    SegmentTree(int n) {
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }

    void build(int node, int nl, int nr) {
        if (nl == nr) {
            tree[node] = 0;
            return;
        }
        int mid = nl + (nr - nl) / 2;
        build(2 * node + 1, nl, mid);
        build(2 * node + 2, mid + 1, nr);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    ll sum(ll s, ll inc, ll len) {
        return 1LL * s * len + 1LL * inc * (len - 1) * len / 2;
    }

    void prop(int node, int nl, int nr) {
        if (lazy[node].Increment) {
            tree[node] += sum(lazy[node].firstValue, lazy[node].Increment, nr - nl + 1);
            if (nl != nr) {
                lazy[2 * node + 1] = lazy[2 * node + 1] + lazy[node];
                ll mid = nl + (nr - nl) / 2;
                lazy[2 * node + 2] = lazy[2 * node + 2] + Node(
                    lazy[node].firstValue + lazy[node].Increment * (mid - nl + 1),
                    lazy[node].Increment
                );
            }
            lazy[node].Increment = 0;
            lazy[node].firstValue = 0;
        }
    }

    void upd(int node, int nl, int nr, int l, int r, ll f, ll inc) {
        prop(node, nl, nr);
        if (nl > r || nr < l) return;
        if (nl >= l && nr <= r) {
            lazy[node].firstValue = (nl - l) * inc + f;
            lazy[node].Increment += inc;
            prop(node, nl, nr);
            return;
        }
        ll mid = nl + (nr - nl) / 2;
        upd(2 * node + 1, nl, mid, l, r, f, inc);
        upd(2 * node + 2, mid + 1, nr, l, r, f, inc);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    ll query(int node, int nl, int nr, int l, int r) {
        prop(node, nl, nr);
        if (nl >= l && nr <= r) return tree[node];
        if (nl > r || nr < l) return 0;
        int mid = nl + (nr - nl) / 2;
        return query(2 * node + 1, nl, mid, l, r) + query(2 * node + 2, mid + 1, nr, l, r);
    }
};