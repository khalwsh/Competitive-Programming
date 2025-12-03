struct Node {
    int left = -1, right = -1;
    int len = 0;
    int pref[2]{0, 0}, suf[2]{0, 0}, mx[2]{0, 0};
 
    Node() = default;
 
    Node(int v) {
        left = right = v;
        len = 1;
        pref[v] = suf[v] = mx[v] = 1;
        pref[v ^ 1] = suf[v ^ 1] = mx[v ^ 1] = 0;
    }
};
 
struct SegmentTree {
    int n = 0;
    vector<Node> tree;
 
    void init(int n_) {
        n = n_;
        tree.assign(4 * n, Node());
    }
 
    static Node mergeNode(const Node &A, const Node &B) {
        if (A.len == 0) return B;
        if (B.len == 0) return A;
 
        Node res;
        res.left = A.left;
        res.right = B.right;
        res.len = A.len + B.len;
 
        for (int val = 0; val <= 1; ++val) {
            res.pref[val] = A.pref[val];
            if (A.pref[val] == A.len) res.pref[val] = A.len + B.pref[val];
 
            res.suf[val] = B.suf[val];
            if (B.suf[val] == B.len) res.suf[val] = B.len + A.suf[val];
 
            res.mx[val] = max(A.mx[val], B.mx[val]);
 
            if (A.right == val && B.left == val) {
                res.mx[val] = max(res.mx[val], A.suf[val] + B.pref[val]);
            }
        }
 
        return res;
    }
 
    void upd(int node, int nl, int nr, int idx, int nw) {
        if (nl == nr) {
            tree[node] = Node(nw);
            return;
        }
        int mid = nl + (nr - nl) / 2;
        if (idx <= mid) upd(2 * node + 1, nl, mid, idx, nw);
        else upd(2 * node + 2, mid + 1, nr, idx, nw);
        tree[node] = mergeNode(tree[2 * node + 1], tree[2 * node + 2]);
    }
 
    Node query(int node, int nl, int nr, int l, int r) {
        if (r < nl || nr < l) return Node();
        if (l <= nl && nr <= r) return tree[node];
        int mid = nl + (nr - nl) / 2;
        Node leftNode = query(2 * node + 1, nl, mid, l, r);
        Node rightNode = query(2 * node + 2, mid + 1, nr, l, r);
        return mergeNode(leftNode, rightNode);
    }
};