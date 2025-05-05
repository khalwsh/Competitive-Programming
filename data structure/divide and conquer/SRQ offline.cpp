template<typename T = ll>
class SRQ {
public:
    using CombineFn = function<T(const T&, const T&)>;

    // Query: inclusive indices [l, r]
    struct Query { int l, r, idx; };

    SRQ(const vector<T>& arr, CombineFn combine)
        : a(arr), n(arr.size()), comb(combine)
    {}

    // Takes list of queries (pairs of l, r) and returns answers in order
    vector<T> solve(const vector<pair<int,int>>& queries) {
        int m = queries.size();
        vector<Query> qs;
        qs.reserve(m);
        for (int i = 0; i < m; ++i) {
            qs.push_back({queries[i].first, queries[i].second, i});
        }
        ans.assign(m, T());
        rec(0, n-1, qs);
        return ans;
    }

private:
    const vector<T>& a;
    int n;
    CombineFn comb;
    vector<T> ans;

    void rec(int l, int r, const vector<Query>& queries) {
        if (queries.empty()) return;
        if (l == r) {
            for (auto &q : queries) {
                ans[q.idx] = a[l];
            }
            return;
        }
        int mid = (l + r) / 2;
        // Precompute suffix minima on left and prefix minima on right
        int lsz = mid - l + 1;
        int rsz = r - mid;
        vector<T> suf(lsz), pre(rsz);
        for (int i = mid; i >= l; --i) {
            if (i == mid) suf[i-l] = a[i];
            else suf[i-l] = comb(suf[i-l+1], a[i]);
        }
        for (int i = mid+1; i <= r; ++i) {
            if (i == mid+1) pre[i-mid-1] = a[i];
            else pre[i-mid-1] = comb(pre[i-mid-2], a[i]);
        }

        vector<Query> leftQ, rightQ;
        for (auto &q : queries) {
            if (q.l <= mid && q.r > mid) {
                T leftVal = suf[q.l - l];
                T rightVal = pre[q.r - mid - 1];
                ans[q.idx] = comb(leftVal, rightVal);
            } else if (q.r <= mid) {
                leftQ.push_back(q);
            } else { // q.l > mid
                rightQ.push_back(q);
            }
        }
        rec(l, mid, leftQ);
        rec(mid+1, r, rightQ);
    }
};