struct Node {
    int left_val, right_val;
    int left_len, right_len;
    int max_len;

    Node() : left_val(0), right_val(0), left_len(0), right_len(0), max_len(0) {}
};

class SegmentTree {
public:
    int n;
    vector<Node> tree;
    vector<int> arr;
    
    SegmentTree(const vector<int>& a) {
        arr = a;
        n = arr.size();
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    Node merge(const Node& left, const Node& right) {
        Node res;
        res.left_val = left.left_val;
        res.right_val = right.right_val;

        res.left_len = left.left_len;
        if (left.left_len == left.max_len && left.right_val == right.left_val)
            res.left_len += right.left_len;
        
        res.right_len = right.right_len;
        if (right.right_len == right.max_len && right.left_val == left.right_val)
            res.right_len += left.right_len;

        res.max_len = max(left.max_len, right.max_len);
        if (left.right_val == right.left_val)
            res.max_len = max(res.max_len, left.right_len + right.left_len);

        return res;
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].left_val = tree[v].right_val = arr[tl];
            tree[v].left_len = tree[v].right_len = tree[v].max_len = 1;
        } else {
            int tm = (tl + tr) / 2;
            build(v * 2 + 1, tl, tm);
            build(v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    void update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            arr[pos] = val;
            tree[v].left_val = tree[v].right_val = val;
            tree[v].left_len = tree[v].right_len = tree[v].max_len = 1;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(v * 2 + 1, tl, tm, pos, val);
            else update(v * 2 + 2, tm + 1, tr, pos, val);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    Node query(int v, int tl, int tr, int l, int r) {
        if (l > r) return Node(); // empty
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        Node left = query(v * 2 + 1, tl, tm, l, min(r, tm));
        Node right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);
        if (left.max_len == 0) return right;
        if (right.max_len == 0) return left;
        return merge(left, right);
    }
    void update(int pos, int val) { update(0, 0, n - 1, pos, val); }
    int query(int l, int r) { return query(0, 0, n - 1, l, r).max_len; }
};