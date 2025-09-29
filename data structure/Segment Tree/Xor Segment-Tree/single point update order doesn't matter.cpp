/*
 * This segment tree is like normal segment tree but in query you query on position x ^ i for all l <= i <= r
 * you only need to handle apply and merge
 * when you send the node starting the segment tree send 1 not 0
 * work only with operation when repeat didn't affect answer
*/
template<typename T>
struct Seg {
    T apply(T old, T nw) {
        // apply update to certain leaf node
        return nw ^ old;
    }
 
    T merge(T l, T r) {
        // merge answer
        return l ^ r;
    }
 
    int n;
    int N;
    int LOG;
    vector<T> t;
 
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
 
 
    void build(int node, int b, int e, const vector<T> &a) {
        if (b == e) {
            if (b < a.size())
                t[node] = a[b];
            return;
        }
        int mid = (b + e) >> 1;
        int L = node << 1, R = L | 1;
        build(L, b, mid, a);
        build(R, mid + 1, e, a);
        t[node] = merge(t[L], t[R]);
    }
 
    // point update: A[idx] ^= val
    void update_xor(int node, int b, int e, int idx, ll val) {
        if (idx < b || idx > e) return;
        if (b == e) {
            t[node] = apply(t[node], val);
            return;
        }
        int mid = (b + e) >> 1;
        int L = node << 1, R = L | 1;
        update_xor(L, b, mid, idx, val);
        update_xor(R, mid + 1, e, idx, val);
        t[node] = merge(t[L], t[R]);
    }
 
    // query: XOR of A[p ^ x] for p in [i..j]
    T query(int node, int b, int e, int i, int j, int x, int layer = -2) {
        if (i > j || b > j || e < i) return T();
        if (layer == -2) layer = LOG - 1;
 
        if (i <= b && e <= j) {
            return t[node];
        }
        int mid = (b + e) >> 1;
        int L = node << 1, R = L | 1;
        // check bit 'layer' of x: if 0 -> normal mapping, else swapped mapping
        if (((~x) >> layer) & 1) {
            return merge(query(L, b, mid, i, j, x, layer - 1), query(R, mid + 1, e, i, j, x, layer - 1));
        } else {
            // swapped: left part queries map into right subtree and vice versa
            int len = 1 << layer;
            T res_l = query(L, b, mid, i - len, j - len, x, layer - 1);
            T res_r = query(R, mid + 1, e,i+ len, j + len, x, layer - 1);
            return merge(res_l, res_r);
        }
    }
};