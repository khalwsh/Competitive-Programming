struct Node {
    int lv, rv;
    int len1;
    int len2;
    int res;
    int size;
    Node() : lv(-1), rv(-1), len1(0), len2(0), res(0), size(0) {}
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
        res.lv = left.lv;
        res.rv = right.rv;
        res.size = left.size + right.size;
        res.res = max(left.res, right.res);
        if (left.rv == right.lv) {
            res.res = max(res.res, left.len2 + right.len1);
        }
        res.len1 = left.len1;
        if (left.len1 == left.size && left.rv == right.lv) {
            res.len1 += right.len1;
        }
        res.len2 = right.len2;
        if (right.len2 == right.size && right.lv == left.rv) {
            res.len2 += left.len2;
        }
        return res;
    }

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            tree[v].lv = tree[v].rv = arr[tl];
            tree[v].len1 = tree[v].len2 = tree[v].res = 1;
            tree[v].size = 1;
        } else {
            int tm = (tl + tr) / 2;
            build(v * 2 + 1, tl, tm);
            build(v * 2 + 2, tm + 1, tr);
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }

    void update(int v, int tl, int tr, int pos , int val) {
        if (tl == tr) {
            arr[pos] = val;

            tree[v].lv = tree[v].rv = val;
            tree[v].len1 = tree[v].len2 = tree[v].res = 1;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update(v * 2 + 1, tl, tm, pos , val);
            } else {
                update(v * 2 + 2, tm + 1, tr, pos , val);
            }
            tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
        }
    }
    Node query(int v, int tl, int tr, int l, int r) {
        if (l == tl && r == tr)
            return tree[v];

        int tm = (tl + tr) / 2;

        Node left = query(v * 2 + 1, tl, tm, l, min(r, tm));
        Node right = query(v * 2 + 2, tm + 1, tr, max(l, tm + 1), r);

        if (left.res == 0)
            return right;
        if (right.res == 0)
            return left;

        return merge(left, right);
    }
    void update(int pos , int nval) {
        update(0, 0, n - 1, pos , nval);
    }
    int query(int l , int r) {
        return query(0 , 0 , n - 1 , l , r).res;
    }
};
