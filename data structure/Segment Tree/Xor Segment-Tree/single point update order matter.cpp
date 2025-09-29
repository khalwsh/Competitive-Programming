/*
 * This segment tree is like normal segment tree but in query you query on position x ^ i for all l <= i <= r
 * you only need to handle apply and merge
 * you must pass n to be power of 2 and when build pad the vector with zeros until it's length be power of 2
 * when you send the node starting the segment tree send 1 not 0
*/
template<typename T>
struct Seg {
    T apply(T old, T nw) {
        // apply update to certain leaf node
        return nw;
    }

    T merge(T l, T r) {
        // merge answer
        return l + r;
    }

    int n;
    int N;
    int LOG;
    vector<vector<T> > t;

    Seg(int n = 0) {
        if (n > 0) init(n);
    }

    void init(int _n) {
        n = _n;
        LOG = 0;
        while ((1 << LOG) < n) ++LOG;
        N = 1 << LOG;
        t.assign(4 * N + 5, {});
    }

    vector<T> mergeNode(const vector<T> &L, const vector<T> &R) {
        // merge 2
        int half = (int) L.size();
        vector<T> res(half * 2);
        for (int i = 0; i < half; ++i) res[i] = merge(L[i], R[i]);
        for (int i = 0; i < half; ++i) res[i + half] = merge(R[i], L[i]);
        return res;
    }

    void build(int node, int b, int e, const vector<T> &a) {
        if (b == e) {
            t[node].assign(1, (b < (int) a.size() ? a[b] : T()));
            return;
        }
        int mid = (b + e) >> 1;
        int L = node << 1, R = L | 1;
        build(L, b, mid, a);
        build(R, mid + 1, e, a);
        t[node] = mergeNode(t[L], t[R]);
    }

    // point update: A[idx] ^= val
    void update_xor(int node, int b, int e, int idx, ll val) {
        if (idx < b || idx > e) return;
        if (b == e) {
            t[node][0] = apply(t[node][0], val);
            return;
        }
        int mid = (b + e) >> 1;
        int L = node << 1, R = L | 1;
        update_xor(L, b, mid, idx, val);
        update_xor(R, mid + 1, e, idx, val);
        t[node] = mergeNode(t[L], t[R]);
    }

    // query: XOR of A[p ^ x] for p in [i..j]
    T query(int node, int b, int e, int i, int j, int x, int layer = -2) {
        if (i > j || b > j || e < i) return T();
        if (layer == -2) layer = LOG - 1;

        if (i <= b && e <= j) {
            if (layer == -1) return t[node][0];
            int mask = (1 << (layer + 1)) - 1;
            int idx = x & mask;
            if (idx >= (int) t[node].size()) idx %= (int) t[node].size();
            return t[node][idx];
        }
        int mid = (b + e) >> 1;
        int L = node << 1, R = L | 1;

        // check bit 'layer' of x: if 0 -> normal mapping, else swapped mapping
        if (((~x) >> layer) & 1) {
            return merge(query(L, b, mid, i, j, x, layer - 1), query(R, mid + 1, e, i, j, x, layer - 1));
        } else {
            // swapped: left part queries map into right subtree and vice versa
            T res = T();
            int i1 = i, j1 = min(mid, j);
            int i2 = max(i, mid + 1), j2 = j;

            if (i1 <= j1) {
                int ni = mid + 1 + (i1 - b);
                int nj = mid + 1 + (j1 - b);
                res = merge(res, query(R, mid + 1, e, ni, nj, x, layer - 1));
            }
            if (i2 <= j2) {
                int ni = b + (i2 - (mid + 1));
                int nj = b + (j2 - (mid + 1));
                res = merge(res, query(L, b, mid, ni, nj, x, layer - 1));
            }
            return res;
        }
    }
};