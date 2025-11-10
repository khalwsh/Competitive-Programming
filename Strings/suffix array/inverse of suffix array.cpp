class SegmentTree {
private:
    int n;
    std::vector<char> tree;
    char default_val;

    void update(int node, int start, int end, int idx, char val) {
        if (start == end) {
            tree[node] = std::max(tree[node], val);
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) {
            update(2 * node + 1, start, mid, idx, val);
        } else {
            update(2 * node + 2, mid + 1, end, idx, val);
        }
        tree[node] = std::max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    char query(int node, int start, int end, int left, int right) {
        if (right < start || end < left) return default_val;
        if (left <= start && end <= right) return tree[node];
        int mid = (start + end) / 2;
        char l = query(2 * node + 1, start, mid, left, right);
        char r = query(2 * node + 2, mid + 1, end, left, right);
        return std::max(l, r);
    }

public:
    SegmentTree(int _n, char def) : n(_n), default_val(def), tree(4 * _n, def) {}

    void update(int idx, char val) {
        update(0, 0, n - 1, idx, val);
    }

    char query(int left, int right) {
        if (left > right) return default_val;
        return query(0, 0, n - 1, left, right);
    }
};
// pass p in zero base
string build(vector<int>p) {
    int n = p.size();
    if (n == 0) return "";
    std::vector<int> inv(n);
    for (int i = 0; i < n; ++i) {
        inv[p[i]] = i;
    }
    char default_char = 'a' - 1;
    SegmentTree tree(n, default_char);
    vector<char> s(n);
    char curr_char = 'a';
    for (int i = 0; i < n; ++i) {
        if (i > 0 && p[i] == n - 1) {
            ++curr_char;
        }
        if (p[i] < n - 1) {
            int rank_tail = inv[p[i] + 1];
            char max_conf = tree.query(rank_tail + 1, n - 1);
            if (max_conf == curr_char) {
                ++curr_char;
            }
        }
        if (curr_char > 'z') {
            return "-1";
        }
        s[p[i]] = curr_char;
        if (p[i] < n - 1) {
            tree.update(inv[p[i] + 1], curr_char);
        }
    }
    return string(s.begin(), s.end());
}