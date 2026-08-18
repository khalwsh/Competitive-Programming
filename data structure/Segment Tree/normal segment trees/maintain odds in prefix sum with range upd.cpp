struct Node {
    int len= 0;
    int tot= 0;
    int odd0= 0;
    int odd1= 0;
    int even0= 0;
    int even1= 0;
    Node operator+(const Node& r) const {
        Node res;
        res.len = len + r.len;
        res.tot = tot ^ r.tot;
        int rodd0 = r.odd0;
        int rodd1 = r.odd1;
        int reven0 = r.even0;
        int reven1 = r.even1;
        if (tot == 1) {
            swap(rodd0, rodd1);
            swap(reven0, reven1);
        }
        int mapped_odd0, mapped_odd1, mapped_even0, mapped_even1;
        if (len & 1) {
            mapped_odd0  = reven0;
            mapped_odd1  = reven1;
            mapped_even0 = rodd0;
            mapped_even1 = rodd1;
        } else {
            mapped_odd0  = rodd0;
            mapped_odd1  = rodd1;
            mapped_even0 = reven0;
            mapped_even1 = reven1;
        }
        res.odd0  = odd0  + mapped_odd0;
        res.odd1  = odd1  + mapped_odd1;
        res.even0 = even0 + mapped_even0;
        res.even1 = even1 + mapped_even1;
        return res;
    }
};

struct Seg {
    int n;
    vector<ll> a;
    vector<Node> seg;
    vector<bool> lz;
    Seg(const vector<ll>& arr) {
        n = (int)arr.size();
        a.resize(n);
        for (int i = 0; i < n; ++i) a[i] = arr[i] & 1;
        seg.assign(4 * max(1, n), Node());
        lz.assign(4 * max(1, n), 0);
        if (n) build(0, 0, n - 1);
    }
    void build(int idx, int l, int r) {
        seg[idx].len = r - l + 1;
        if (l == r) {
            int v = a[l];
            seg[idx].tot = v;
            seg[idx].odd0 = (v == 0);
            seg[idx].odd1 = (v == 1);
            seg[idx].even0 = 0;
            seg[idx].even1 = 0;
            return;
        }
        int m = (l + r) >> 1;
        int L = idx * 2 + 1, R = idx * 2 + 2;
        build(L, l, m);
        build(R, m + 1, r);
        seg[idx] = seg[L] + seg[R];
    }
    void apply_flip(int idx) {
        swap(seg[idx].odd0, seg[idx].odd1);
        if (seg[idx].len & 1) seg[idx].tot ^= 1;
        lz[idx] = !lz[idx];
    }
    void push(int idx) {
        if (lz[idx]) {
            int L = idx * 2 + 1, R = idx * 2 + 2;
            apply_flip(L);
            apply_flip(R);
            lz[idx] = false;
        }
    }
    void update(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            apply_flip(idx);
            return;
        }
        push(idx);
        int m = (l + r) >> 1;
        int L = idx * 2 + 1, R = idx * 2 + 2;
        if (ql <= m) update(L, l, m, ql, qr);
        if (qr > m) update(R, m + 1, r, ql, qr);
        seg[idx] = seg[L] + seg[R];
    }
    void add(int L, int R) {
        update(0, 0, n - 1, L, R);
    }
    pair<int,int> get() {
        int even = seg[0].even0 + seg[0].odd0;
        int odd  = seg[0].even1 + seg[0].odd1;
        return {even, odd};
    }
};