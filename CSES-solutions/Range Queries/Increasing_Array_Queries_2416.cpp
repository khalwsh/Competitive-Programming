/* problem statement text */
/*
CSES - Increasing Array Queries

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array that consists of nnn integers. The array elements are indexed 1,2,…,n1,2,\dots,n1,2,…,n.
You can modify the array using the following operation: choose an array element and increase its value by one.
Your task is to process qqq queries of the form: when we consider a subarray from position aaa to position bbb, what is the minimum number of operations after which the subarray is increasing?
An array is increasing if each element is greater than or equal with the previous element.
Input
The first input line has two integers nnn and qqq: the size of the array and the number of queries.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the contents of the array.
Finally, there are qqq lines that describe the queries. Each line has two integers aaa and bbb: the starting and ending position of a subarray.
Output
For each query, print the minimum number of operations.
Constraints

1≤n,q≤2⋅1051 \le n,q \le 2\cdot10^51≤n,q≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
5 3
2 10 4 2 5
3 5
2 2
1 4

Output:
2
0
14
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
vector<int> getNxtMax(vector<int> &arr) {
    stack<int> st;
    vector<int> res(arr.size(), -1);
    for (int i = 0; i < arr.size(); i++) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}
struct SegmentTree {
    int n;
    vector<long long> st;      // segment sums
    vector<long long> lazy;    // lazy value for assignment
    vector<char> has_lazy;     // flag whether lazy is valid
 
    SegmentTree() : n(0) {}
 
    // build from array (0-indexed)
    SegmentTree(int x) {
        n = x;
        st.resize(4 * x);
        lazy.resize(4 * x);
        has_lazy.resize(4 * x);
    }
 
    // push lazy assignment from node to its children
    void push(int node, int l, int r) {
        if (!has_lazy[node] || l == r) return; // nothing to push or leaf
        int mid = (l + r) >> 1;
        int lc = node<<1, rc = node<<1|1;
 
        // apply assignment to left child
        has_lazy[lc] = 1;
        lazy[lc] = lazy[node];
        st[lc] = lazy[node] * (long long)(mid - l + 1);
 
        // apply assignment to right child
        has_lazy[rc] = 1;
        lazy[rc] = lazy[node];
        st[rc] = lazy[node] * (long long)(r - mid);
 
        // clear current node's lazy flag
        has_lazy[node] = 0;
    }
 
    // public: set all elements in [ql, qr] to value
    void set_range(int ql, int qr, long long value) {
        if (n == 0) return;
        update_assign(1, 0, n-1, ql, qr, value);
    }
 
    // recursive update (assignment)
    void update_assign(int node, int l, int r, int ql, int qr, long long value) {
        if (qr < l || r < ql) return; // no overlap
        if (ql <= l && r <= qr) {
            has_lazy[node] = 1;
            lazy[node] = value;
            st[node] = value * (long long)(r - l + 1);
            return;
        }
        push(node, l, r);
        int mid = (l + r) >> 1;
        update_assign(node<<1, l, mid, ql, qr, value);
        update_assign(node<<1|1, mid+1, r, ql, qr, value);
        st[node] = st[node<<1] + st[node<<1|1];
    }
 
    // public: query sum in [ql, qr]
    long long range_sum(int ql, int qr) {
        if (n == 0) return 0;
        return query_sum(1, 0, n-1, ql, qr);
    }
 
    // recursive query
    long long query_sum(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0; // no overlap
        if (ql <= l && r <= qr) return st[node]; // total overlap
        push(node, l, r);
        int mid = (l + r) >> 1;
        return query_sum(node<<1, l, mid, ql, qr) +
               query_sum(node<<1|1, mid+1, r, ql, qr);
    }
};
const int N = 2e5 + 10;
vector<array<int , 2>> queries[N];
int main() {
    PRE();
    int n , q; cin >> n >> q;
    vector<int>v(n);
    for (int i = 0;i < n;i++) cin >> v[i];
    vector<ll>pref(n);
    for (int i = 0;i < n;i++) {
        pref[i] = v[i];
        if (i) pref[i] += pref[i - 1];
    }
    auto query = [&](int l , int r) -> ll {
        return pref[r] - (l == 0 ? 0 : pref[l - 1]);
    };
    for (int i = 0;i < q;i++) {
        int l , r;cin >> l >> r;
        l-- , r--;
        queries[l].emplace_back(array<int , 2>{r , i});
    }
    SegmentTree seg(n);
    auto nxt = getNxtMax(v);
    vector<ll>ans(q);
    for (int i = n - 1;i >= 0;i--) {
        int l = i , r = (nxt[i] == -1 ? n : nxt[i]) - 1;
        seg.set_range(l , r , v[i]);
        // cout << l << " " << r << " " << v[i] << endl;
        for (auto &val : queries[i]) {
            ans[val[1]] = seg.range_sum(i , val[0]) - query(i , val[0]);
        }
    }
    for (int i = 0;i < q;i++) cout << ans[i] << '\n';
}