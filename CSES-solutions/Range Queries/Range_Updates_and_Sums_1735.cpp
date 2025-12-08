/* problem statement text */
/*
CSES - Range Updates and Sums

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to maintain an array of nnn values and efficiently process the following types of queries:

Increase each value in range [a,b][a,b][a,b] by xxx.
Set each value in range [a,b][a,b][a,b] to xxx.
Calculate the sum of values in range [a,b][a,b][a,b].

Input
The first input line has two integers nnn and qqq: the array size and the number of queries.
The next line has nnn values t1,t2,…,tnt_1,t_2,\dots,t_nt1​,t2​,…,tn​: the initial contents of the array.
Finally, there are qqq lines describing the queries. The format of each line is one of the following: "1 aaa bbb xxx",  "2 aaa bbb xxx", or "3 aaa bbb".
Output
Print the answer to each sum query.
Constraints

1≤n,q≤2⋅1051 \le n, q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤ti,x≤1061 \le t_i, x \le 10^61≤ti​,x≤106
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
6 5
2 3 1 1 5 3
3 3 5
1 2 4 2
3 3 5
2 2 4 5
3 3 5

Output:
7
11
15
*/
#include <bits/stdc++.h>
 
#include <random>
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
const int N = 1e6 + 1;
int v[N];
struct SegmentTree {
    int N;
    vector<int> lo, hi;
    vector<ll> del, ass, sum;
 
    SegmentTree(int n) {
        N = n;
        lo.resize(4 * n);
        hi.resize(4 * n);
        del.resize(4 * n, 0);
        ass.resize(4 * n, -1); // -1 means no assignment
        sum.resize(4 * n, 0);
    }
 
    int len(int i) {
        return hi[i] - lo[i] + 1;
    }
 
    void increment(int i, ll v) {
        del[i] += v;
        sum[i] += len(i) * v;
    }
 
    void assign(int i, ll v) {
        ass[i] = v;
        del[i] = 0;
        sum[i] = len(i) * v;
    }
 
    void push(int i) {
        if (ass[i] != -1) {  // There's an assignment to propagate
            assign(2 * i, ass[i]);
            assign(2 * i + 1, ass[i]);
            ass[i] = -1;  // Clear the assignment
        }
        if (del[i] != 0) {  // There's an addition to propagate
            increment(2 * i, del[i]);
            increment(2 * i + 1, del[i]);
            del[i] = 0;  // Clear the addition
        }
    }
 
    void pull(int i) {
        sum[i] = sum[2 * i] + sum[2 * i + 1];
    }
 
    void build(int i, int l, int r) {
        lo[i] = l;
        hi[i] = r;
        if (l == r) {
            sum[i] = v[l];  // Initially all elements are 0
            return;
        }
        int m = (l + r) / 2;
        build(2 * i, l, m);
        build(2 * i + 1, m + 1, r);
        pull(i);
    }
 
    void increment(int i, int l, int r, ll v) {
        if (l > hi[i] || r < lo[i]) return;
        if (l <= lo[i] && hi[i] <= r) {
            increment(i, v);
            return;
        }
 
        push(i);
        increment(2 * i, l, r, v);
        increment(2 * i + 1, l, r, v);
        pull(i);
    }
 
    void assign(int i, int l, int r, ll v) {
        if (l > hi[i] || r < lo[i]) return;
        if (l <= lo[i] && hi[i] <= r) {
            assign(i, v);
            return;
        }
 
        push(i);
        assign(2 * i, l, r, v);
        assign(2 * i + 1, l, r, v);
        pull(i);
    }
 
    ll query(int i, int l, int r) {
        if (l > hi[i] || r < lo[i]) return 0;
        if (l <= lo[i] && hi[i] <= r) {
            return sum[i];
        }
 
        push(i);
        ll lsum = query(2 * i, l, r);
        ll rsum = query(2 * i + 1, l, r);
        pull(i);
 
        return lsum + rsum;
    }
};
 
int main() {
    PRE();
    int N, Q;
    cin >> N >> Q;
    for (int i = 1;i <= N;i++) {
        cin >> v[i];
    }
    SegmentTree seg(N);
    seg.build(1, 1, N);
 
    for (int q = 0; q < Q; q++) {
        int t, a, b;
        ll x;
        cin >> t >> a >> b;
        if (t == 1) {
            cin >> x;
            seg.increment(1, a, b, x);
        } else if (t == 2) {
            cin >> x;
            seg.assign(1, a, b, x);
        } else if (t == 3) {
            cout << seg.query(1, a, b) << "\n";
        }
    }
 
}