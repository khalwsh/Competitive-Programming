struct Node {
    ll mx[2]  = { -1, -1 };
    ll idx[2] = { -1, -1 };
    Node operator+(const Node &other) const noexcept {
        Node res;
        ll best = -1, i1 = -1;
        ll sec = -1, i2 = -1;
 
        ll vals[4] = { mx[0], mx[1], other.mx[0], other.mx[1] };
        ll ids[4]  = { idx[0], idx[1], other.idx[0], other.idx[1] };
 
        for (int k = 0; k < 4; ++k) {
            ll v = vals[k];
            if (v == -1) continue;
            ll id = ids[k];
            if (v > best) {
                sec = best; i2 = i1;
                best = v; i1 = id;
            } else if (v > sec) {
                sec = v; i2 = id;
            }
        }
 
        res.mx[0]  = best;   res.idx[0]  = i1;
        res.mx[1]  = sec; res.idx[1]  = i2;
        return res;
    }
};
 
 
struct SegmentTree {
    vector<Node> tree;
    SegmentTree (int _n) {
        tree.resize(4 * _n);
    }
    void upd(int node , int nl , int nr , int pos , int idx , ll nw) {
        if (nl == nr) {
            Node x;
            x.mx[0] = nw , x.idx[0] = idx;
            tree[node] = tree[node] + x;
            return;
        }
        int mid = nl + (nr - nl) / 2;
        if (pos <= mid) upd(2 * node + 1 , nl , mid  , pos , idx , nw);
        else upd(2 * node + 2 , mid + 1 ,nr , pos , idx , nw);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
    Node query(int node , int nl , int nr , int l , int r) {
        if (nl >= l && nr <= r) return tree[node];
        if (nl > r || nr < l) return Node();
        int mid = nl + (nr - nl) / 2;
        return query(2 * node + 1 , nl , mid , l , r) + query(2 * node + 2 , mid + 1 ,nr , l , r);
    }
};