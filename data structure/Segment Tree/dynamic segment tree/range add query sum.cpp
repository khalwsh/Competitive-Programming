const ll sz = 2e9;
struct dynamicSeg {
    ll sum = 0;
    dynamicSeg *left = nullptr, *right = nullptr;
    bool has_lazy = false;
    ll lazy_val = 0;
    void prop(ll nl , ll nr , ll mid) {
        if (has_lazy) {
            if (!left) left = new dynamicSeg();
            if (!right) right = new dynamicSeg();

            left->sum += (mid - nl + 1) * lazy_val;
            left->has_lazy = true;
            left->lazy_val += lazy_val;

            right->sum += (nr - mid) * lazy_val;
            right->has_lazy = true;
            right->lazy_val += lazy_val;

            lazy_val = 0;
            has_lazy = false;
        }
    }
    void upd(ll nl, ll nr, ll l, ll r, ll v) {
        ll mid = nl + (nr - nl) / 2;
        prop(nl , nr , mid);
        if (l > nr || r < nl) return;
        if (l <= nl && nr <= r) {
            sum += (nr - nl + 1) * v;
            has_lazy = true;
            lazy_val += v;
            return;
        }
        if (l <= mid) {
            if (!left) left = new dynamicSeg();
            left->upd(nl, mid, l, r, v);
        }
        if (r > mid) {
            if (!right) right = new dynamicSeg();
            right->upd(mid + 1, nr, l, r, v);
        }

        sum = (left ? left->sum : 0) + (right ? right->sum : 0);
    }
    ll query(ll nl , ll nr , ll l , ll r) {
        ll mid = nl + (nr - nl) / 2;
        prop(nl , nr , mid);
        if (nl >= l && nr <= r)return sum;
        if (nl > r || nr < l)return 0;
        auto res1 = left == nullptr ? 0 : left->query(nl , mid , l , r);
        auto res2 = right == nullptr ? 0 : right -> query(mid + 1 , nr , l , r);
        return  res1 + res2;
    }
};