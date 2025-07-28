// you build the Li-chao on the points x-coordinates you will query on them and then add segments and query
struct LiChao {
    struct Line { ll m, b; };
private:
    void insert(int p, int l, int r, Line ln) {
        int m = (l + r) >> 1;
        ll xl = xs[l], xm = xs[m], xr = xs[r-1];
        Line& cur = st[p];
        if (eval(ln, xm) > eval(cur, xm)) swap(cur, ln);
        if (r - l == 1) return;
        if (eval(ln, xl) > eval(cur, xl))
            insert(p<<1, l, m, ln);
        else if (eval(ln, xr) > eval(cur, xr))
            insert(p<<1|1, m, r, ln);
    }

    void insert_seg(int p, int l, int r, Line ln, int ql, int qr) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) {
            insert(p, l, r, ln);
            return;
        }
        int m = (l + r) >> 1;
        insert_seg(p<<1, l, m, ln, ql, qr);
        insert_seg(p<<1|1, m, r, ln, ql, qr);
    }

    ll query_point(int p, int l, int r, ll xq, int idx) const {
        ll res = eval(st[p], xq);
        if (r - l == 1) return res;
        int m = (l + r) >> 1;
        if (idx < m)
            res = max(res, query_point(p<<1, l, m, xq, idx));
        else
            res = max(res, query_point(p<<1|1, m, r, xq, idx));
        return res;
    }
public:
    int n;
    vector<ll> xs;
    vector<Line> st;

    LiChao(const vector<ll>& coords) {
        xs = coords;
        n = xs.size();
        st.assign(4 * n, {0, -INF_LL});
    }

    ll eval(const Line& ln, ll x) const {
        return ln.m * x + ln.b;
    }

    void add_line(ll m, ll b) {
        insert(1, 0, n, {m, b});
    }

    void add_segment(ll m, ll b, ll xl, ll xr) {
        int L = lower_bound(xs.begin(), xs.end(), xl) - xs.begin();
        int R = lower_bound(xs.begin(), xs.end(), xr) - xs.begin();
        if (L < R) insert_seg(1, 0, n, {m, b}, L, R);
    }

    ll query(ll xq) const {
        int idx = lower_bound(xs.begin(), xs.end(), xq) - xs.begin();
        return query_point(1, 0, n, xq, idx);
    }
};
