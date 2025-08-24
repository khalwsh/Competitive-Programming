// Li Chao tree on a fixed set of x-coordinates (discrete points).
// Supports inserting lines (either tracked or untracked) and rolling back the last tracked insertion.
// Query returns the minimum value at a known x in the set.
//

const ll INFLL = (1LL << 62);
struct Line {
    ll m = 0, b = INFLL;
    Line() = default;
    Line(ll _m, ll _b) : m(_m), b(_b) {}
    ll eval(ll x) const {
        __int128 v = ( (__int128)m * x + (__int128)b );
        if (v > INFLL) return INFLL;
        if (v < -INFLL) return -INFLL;
        return (ll)v;
    }
};

struct LiChaoRollback {
private:
    void record_change(int node) {
        changes.push_back({node, seg[node]});
    }
    void insert_impl(int node, int l, int r, Line newline, bool track) {
        int mid = (l + r) >> 1;
        ll xl = xs[l], xm = xs[mid];

        Line cur = seg[node];

        bool leftBetter = newline.eval(xl) < cur.eval(xl);
        bool midBetter  = newline.eval(xm) < cur.eval(xm);

        if (midBetter) {
            if (track) record_change(node);
            swap(seg[node], newline);
            cur = seg[node];
        }

        if (l == r) return;

        if (leftBetter != midBetter) {
            insert_impl(node << 1, l, mid, newline, track);
        } else {
            insert_impl(node << 1 | 1, mid + 1, r, newline, track);
        }
    }

    ll query_impl(int node, int l, int r, int idx, ll x) const {
        ll res = seg[node].eval(x);
        if (l == r) return res;
        int mid = (l + r) >> 1;
        if (idx <= mid) return min(res, query_impl(node << 1, l, mid, idx, x));
        else return min(res, query_impl(node << 1 | 1, mid + 1, r, idx, x));
    }
public:
    int n = 0;
    vector<ll> xs;
    vector<Line> seg;
    struct Change { int node; Line old; };
    vector<Change> changes;
    vector<int> checkpoints;
    LiChaoRollback() = default;

    void init(const vector<ll>& coords) {
        xs = coords;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        n = (int)xs.size();
        seg.assign(4 * max(1, n), Line());
        changes.clear();
        checkpoints.clear();
    }

    void insert_tracked(const Line& ln) {
        checkpoints.push_back((int)changes.size());
        if (n) insert_impl(1, 0, n - 1, ln, true);
    }

    void insert_untracked(const Line& ln) {
        if (n) insert_impl(1, 0, n - 1, ln, false);
    }

    void rollback() {
        if (checkpoints.empty()) return;
        int target = checkpoints.back();
        checkpoints.pop_back();
        while ((int)changes.size() > target) {
            Change ch = changes.back();
            changes.pop_back();
            seg[ch.node] = ch.old;
        }
    }

    ll query(ll x) const {
        if (n == 0) return INFLL;
        int idx = int(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
        return query_impl(1, 0, n - 1, idx, x);
    }
};