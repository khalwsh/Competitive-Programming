/* problem statement text */
/*
CSES - Static Range Minimum Queries

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to process qqq queries of the form: what is the minimum value in range [a,b][a,b][a,b]?
Input
The first input line has two integers nnn and qqq: the number of values and queries.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array values.
Finally, there are qqq lines describing the queries. Each line has two integers aaa and bbb: what is the minimum value in range [a,b][a,b][a,b]?
Output
Print the result of each query.
Constraints

1≤n,q≤2⋅1051 \le n,q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
8 4
3 2 4 5 1 1 5 3
2 4
5 6
1 8
3 3

Output:
2
1
1
4
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
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
int main(){
    PRE();
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
 
    SRQ<ll>srq(a , [&](ll c , ll d)->ll {
        return min(c , d);
    });
    vector<pair<int , int>>queries;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        queries.emplace_back(l , r);
    }
    for (auto &val : srq.solve(queries)) {
        cout<<val<<'\n';
    }
}