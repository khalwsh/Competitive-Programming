struct MergeSortTree {
    vector<vector<int>> tree;
    int n;
 
    MergeSortTree(int _n) : n(_n) {
        tree.resize(4 * n);
    }
 
    void build(int node, int nl, int nr, vector<int>& arr) {
        if (nl == nr) {
            tree[node] = {arr[nl]};
            return;
        }
 
        int mid = nl + (nr - nl) / 2;
        build(2 * node + 1, nl, mid, arr);
        build(2 * node + 2, mid + 1, nr, arr);
 
        tree[node].resize(nr - nl + 1);
        merge(tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
              tree[2 * node + 2].begin(), tree[2 * node + 2].end(),
              tree[node].begin());
    }
 
    int countLessThan(int node, int nl, int nr, int l, int r, int value) {
        // how many value less than me
        if (r < nl || l > nr) return 0;
        if (l <= nl && nr <= r) {
            return lower_bound(tree[node].begin(), tree[node].end(), value) - tree[node].begin();
        }
 
        int mid = nl + (nr - nl) / 2;
        return countLessThan(2 * node + 1, nl, mid, l, r, value) +
               countLessThan(2 * node + 2, mid + 1, nr, l, r, value);
    }
 
    int countGreaterThan(int node, int nl, int nr, int l, int r, int value) {
        // how many value greater than me
        if (r < nl || l > nr) return 0;
        if (l <= nl && nr <= r) {
            return tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), value);
        }
 
        int mid = nl + (nr - nl) / 2;
        return countGreaterThan(2 * node + 1, nl, mid, l, r, value) +
               countGreaterThan(2 * node + 2, mid + 1, nr, l, r, value);
    }
};