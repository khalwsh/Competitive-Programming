const int MOD = 1e9 + 7;
ll power(ll base, ll exp) {
    ll result = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return result;
}
class SegmentTree {
private:
    int n;
    vector<ll> tree, lazy_a, lazy_r;  // lazy_a: coefficient, lazy_r: first power of K
    ll K;

    // Get geometric sum: a*r^0 + a*r^1 + ... + a*r^(n-1)
    ll geometric_sum(ll a, ll r, ll n) {
        if (n == 0) return 0;
        if (n == 1) return a % MOD;
        // Using formula: a*(1-r^n)/(1-r) for r != 1
        ll rn = power(r, n);
        ll denominator = power(MOD + 1 - r, MOD - 2); // Modular multiplicative inverse of (1-r)
        return (a * ((1 - rn + MOD) % MOD) % MOD * denominator) % MOD;
    }

    void push_down(int node, int left, int right) {
        if (lazy_a[node] == 0) return;

        if (left != right) {
            int mid = (left + right) >> 1;
            int left_child = node << 1;
            int right_child = left_child | 1;

            // Left child
            lazy_a[left_child] = (lazy_a[left_child] + lazy_a[node]) % MOD;
            lazy_r[left_child] = lazy_r[node];

            // Right child - adjust power of K by length of left subtree
            lazy_a[right_child] = (lazy_a[right_child] +
                                 (lazy_a[node] * power(K, mid - left + 1)) % MOD) % MOD;
            lazy_r[right_child] = (lazy_r[node] + (mid - left + 1)) % (MOD - 1);
        }

        // Update current node
        tree[node] = (tree[node] + geometric_sum(lazy_a[node], K, right - left + 1)) % MOD;
        lazy_a[node] = 0;
        lazy_r[node] = 0;
    }

    void update_range(int node, int tree_left, int tree_right, int query_left, int query_right, ll val) {
        push_down(node, tree_left, tree_right);

        if (tree_left > query_right || tree_right < query_left) return;

        if (tree_left >= query_left && tree_right <= query_right) {
            ll offset = tree_left - query_left;
            lazy_a[node] = (val * power(K, offset)) % MOD;
            lazy_r[node] = offset;
            push_down(node, tree_left, tree_right);
            return;
        }

        int mid = (tree_left + tree_right) >> 1;
        update_range(node << 1, tree_left, mid, query_left, query_right, val);
        update_range((node << 1) | 1, mid + 1, tree_right, query_left, query_right, val);

        tree[node] = (tree[node << 1] + tree[(node << 1) | 1]) % MOD;
    }

    ll query_range(int node, int tree_left, int tree_right, int query_left, int query_right) {
        if (tree_left > query_right || tree_right < query_left) return 0;

        push_down(node, tree_left, tree_right);

        if (tree_left >= query_left && tree_right <= query_right) {
            return tree[node];
        }

        int mid = (tree_left + tree_right) >> 1;
        return (query_range(node << 1, tree_left, mid, query_left, query_right) +
                query_range((node << 1) | 1, mid + 1, tree_right, query_left, query_right)) % MOD;
    }

public:
    SegmentTree(int size, ll k) : n(size), K(k) {
        tree.resize(4 * n);
        lazy_a.resize(4 * n);
        lazy_r.resize(4 * n);
    }

    void update(int left, int right, ll val) {
        update_range(1, 0, n - 1, left, right, val);
    }

    ll query(int left, int right) {
        return query_range(1, 0, n - 1, left, right);
    }

    vector<ll> get_final_array() {
        vector<ll> result(n);
        for (int i = 0; i < n; i++) {
            result[i] = query(i, i);
        }
        return result;
    }
};