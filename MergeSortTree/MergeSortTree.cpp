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
        // how many values less than value
        if (r < nl || l > nr) return 0;
        if (l <= nl && nr <= r) {
            return lower_bound(tree[node].begin(), tree[node].end(), value) - tree[node].begin();
        }

        int mid = nl + (nr - nl) / 2;
        return countLessThan(2 * node + 1, nl, mid, l, r, value) +
               countLessThan(2 * node + 2, mid + 1, nr, l, r, value);
    }

    int countGreaterThan(int node, int nl, int nr, int l, int r, int value) {
        // how many values greater than value
        if (r < nl || l > nr) return 0;
        if (l <= nl && nr <= r) {
            return tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), value);
        }

        int mid = nl + (nr - nl) / 2;
        return countGreaterThan(2 * node + 1, nl, mid, l, r, value) +
               countGreaterThan(2 * node + 2, mid + 1, nr, l, r, value);
    }

    void processBatch(int node, int nl, int nr,
                      const vector<int>& L, const vector<int>& R, int v,
                      vector<int>& ans, const vector<int>& qids) {
        if(qids.empty()) return;

        vector<int> pending;
        for (int qi : qids) {
            if (L[qi] <= nl && nr <= R[qi]) {
                int cnt = tree[node].size() - (lower_bound(tree[node].begin(), tree[node].end(), v) - tree[node].begin());
                ans[qi] += cnt;
            } else {
                if (R[qi] < nl || L[qi] > nr) {
                } else {
                    pending.push_back(qi);
                }
            }
        }

        if(nl == nr) return;

        int mid = nl + (nr - nl) / 2;
        vector<int> leftPending, rightPending;
        for (int qi : pending) {
            if (!(R[qi] < nl || L[qi] > mid)) {
                leftPending.push_back(qi);
            }
            if (!(R[qi] < mid+1 || L[qi] > nr)) {
                rightPending.push_back(qi);
            }
        }
        if (!leftPending.empty())
            processBatch(2 * node + 1, nl, mid, L, R, v, ans, leftPending);
        if (!rightPending.empty())
            processBatch(2 * node + 2, mid + 1, nr, L, R, v, ans, rightPending);
    }
    vector<int> batchQueryGreaterThanOrEqual(const vector<int>& L, const vector<int>& R, int v) {
        int q = L.size();
        vector<int> ans(q, 0);

        vector<int> allQueries(q);
        for (int i = 0; i < q; i++) {
            allQueries[i] = i;
        }
        processBatch(0, 0, n - 1, L, R, v, ans, allQueries);
        return ans;
    }
    vector<int> batchQueryLessThanOrEqual(const vector<int>& L, const vector<int>& R, int v) {
        int q = L.size();
        vector<int> ans(q, 0);
        vector<int> allQueries(q);
        for (int i = 0; i < q; i++) {
            allQueries[i] = i;
        }
        processBatchLess(0, 0, n - 1, L, R, v, ans, allQueries);
        return ans;
    }

    void processBatchLess(int node, int nl, int nr,
                          const vector<int>& L, const vector<int>& R, int v,
                          vector<int>& ans, const vector<int>& qids) {
        if(qids.empty()) return;
        vector<int> pending;
        for (int qi : qids) {
            if (L[qi] <= nl && nr <= R[qi]) {
                int cnt = upper_bound(tree[node].begin(), tree[node].end(), v) - tree[node].begin();
                ans[qi] += cnt;
            } else {
                if (!(R[qi] < nl || L[qi] > nr))
                    pending.push_back(qi);
            }
        }
        if(nl == nr) return;
        int mid = nl + (nr - nl) / 2;
        vector<int> leftPending, rightPending;
        for (int qi : pending) {
            if (!(R[qi] < nl || L[qi] > mid))
                leftPending.push_back(qi);
            if (!(R[qi] < mid + 1 || L[qi] > nr))
                rightPending.push_back(qi);
        }
        if (!leftPending.empty())
            processBatchLess(2 * node + 1, nl, mid, L, R, v, ans, leftPending);
        if (!rightPending.empty())
            processBatchLess(2 * node + 2, mid + 1, nr, L, R, v, ans, rightPending);
    }
};