/* problem statement text */
/*
CSES - Lines and Queries I

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to efficiently process the following types of queries:

Add a line ax+bax+bax+b
Find the maximum point in any line at position xxx

Input
The first line has an integer nnn: the number of queries.
The following nnn lines describe the queries. The format of each line is either "1 aaa bbb" or "2 xxx".
You may assume that the first query is of type 1.
Output
Print the answer for each query of type 2.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
−109≤a,b≤109-10^9 \le a,b \le 10^9−109≤a,b≤109
0≤x≤1050 \le x \le 10^50≤x≤105

Example
Input:
6
1 1 2
2 1
2 3
1 0 4
2 1
2 3

Output:
3
5
4
5
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
 
const ll INFLL = -(1LL << 62);
struct Line {
    ll m = 0, b = INFLL;
    Line() = default;
    Line(ll _m, ll _b) : m(_m), b(_b) {}
    ll eval(ll x) const {
        auto v = m * x + b;
        return v;
    }
};
 
struct LiChaoRollback {
private:
    void record_change(int node) {
        changes.push_back({node, seg[node]});
    }
    void insert_impl(int node, int l, int r, Line newline, bool track) {
        int mid = (l + r) >> 1;
        ll xl = xs[l], xm = xs[mid];
 
        Line cur = seg[node];
 
        // (<) -> min f(x) , (>) -> max f(x)
        bool leftBetter = newline.eval(xl) > cur.eval(xl);
        bool midBetter  = newline.eval(xm) > cur.eval(xm);
 
        if (midBetter) {
            if (track) record_change(node);
            swap(seg[node], newline);
            cur = seg[node];
        }
 
        if (l == r) return;
 
        if (leftBetter != midBetter) {
            insert_impl(node << 1, l, mid, newline, track);
        } else {
            insert_impl(node << 1 | 1, mid + 1, r, newline, track);
        }
    }
 
    ll query_impl(int node, int l, int r, int idx, ll x) const {
        ll res = seg[node].eval(x);
        if (l == r) return res;
        int mid = (l + r) >> 1;
        if (idx <= mid) return max(res, query_impl(node << 1, l, mid, idx, x));
        else return max(res, query_impl(node << 1 | 1, mid + 1, r, idx, x));
    }
public:
    int n = 0;
    vector<ll> xs;
    vector<Line> seg;
    struct Change { int node; Line old; };
    vector<Change> changes;
    vector<int> checkpoints;
    LiChaoRollback() = default;
 
    void init(const vector<ll>& coords) {
        xs = coords;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        n = (int)xs.size();
        seg.assign(4 * max(1, n), Line());
        changes.clear();
        checkpoints.clear();
    }
 
    void insert_tracked(const Line& ln) {
        checkpoints.push_back((int)changes.size());
        if (n) insert_impl(1, 0, n - 1, ln, true);
    }
 
    void insert_untracked(const Line& ln) {
        if (n) insert_impl(1, 0, n - 1, ln, false);
    }
 
    void rollback() {
        if (checkpoints.empty()) return;
        int target = checkpoints.back();
        checkpoints.pop_back();
        while ((int)changes.size() > target) {
            Change ch = changes.back();
            changes.pop_back();
            seg[ch.node] = ch.old;
        }
    }
 
    ll query(ll x) const {
        if (n == 0) return INFLL;
        int idx = int(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
        return query_impl(1, 0, n - 1, idx, x);
    }
};
 
int main() {
    PRE();
    int n;cin >> n;
    LiChaoRollback root;
    vector<ll>coords;
    vector<pair<int , int>>queries;
    for (int i = 0;i < n;i++) {
        int t;cin >> t;
        if (t == 1) {
            int a , b; cin >> a >> b;
            queries.emplace_back(a , b);
        }else {
            int x;cin >> x;
            queries.emplace_back(x , (int)1e9 + 10);
            coords.emplace_back(x);
        }
    }
    root.init(coords);
    for (auto &val : queries) {
        if (val.second == 1e9 + 10) {
            cout << root.query(val.first) << '\n';
        }else{
            root.insert_tracked({val.first , val.second});
            root.rollback();
            root.insert_tracked({val.first , val.second});
        }
    }
}