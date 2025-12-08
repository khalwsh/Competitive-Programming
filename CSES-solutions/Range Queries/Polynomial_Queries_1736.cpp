/* problem statement text */
/*
CSES - Polynomial Queries

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to maintain an array of nnn values and efficiently process the following types of queries:

Increase the first value in range [a,b][a,b][a,b] by 111, the second value by 222, the third value by 333, and so on.
Calculate the sum of values in range [a,b][a,b][a,b].

Input
The first input line has two integers nnn and qqq: the size of the array and the number of queries.
The next line has nnn values t1,t2,…,tnt_1,t_2,\dots,t_nt1​,t2​,…,tn​: the initial contents of the array.
Finally, there are qqq lines describing the queries. The format of each line is either "1 aaa bbb" or "2 aaa bbb".
Output
Print the answer to each sum query.
Constraints

1≤n,q≤2⋅1051 \le n, q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤ti≤1061 \le t_i \le 10^61≤ti​≤106
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
5 3
4 2 3 1 7
2 1 5
1 1 5
2 1 5

Output:
17
32
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
struct Node {
    ll firstValue, Increment;
    Node(ll f = 0, ll i = 0) {
        firstValue = f;
        Increment = i;
    }
    Node operator+(const Node &a) {
        Node res;
        res.firstValue = firstValue + a.firstValue;
        res.Increment = Increment + a.Increment;
        return res;
    }
};
 
struct SegmentTree {
    vector<ll> tree;
    vector<Node> lazy;
 
    SegmentTree(int n) {
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }
 
    void build(int node, int nl, int nr) {
        if (nl == nr) {
            tree[node] = 0;
            return;
        }
        int mid = nl + (nr - nl) / 2;
        build(2 * node + 1, nl, mid);
        build(2 * node + 2, mid + 1, nr);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
 
    ll sum(ll s, ll inc, ll len) {
        return 1LL * s * len + 1LL * inc * (len - 1) * len / 2;
    }
 
    void prop(int node, int nl, int nr) {
        if (lazy[node].Increment) {
            tree[node] += sum(lazy[node].firstValue, lazy[node].Increment, nr - nl + 1);
            if (nl != nr) {
                lazy[2 * node + 1] = lazy[2 * node + 1] + lazy[node];
                ll mid = nl + (nr - nl) / 2;
                lazy[2 * node + 2] = lazy[2 * node + 2] + Node(
                    lazy[node].firstValue + lazy[node].Increment * (mid - nl + 1),
                    lazy[node].Increment
                );
            }
            lazy[node].Increment = 0;
            lazy[node].firstValue = 0;
        }
    }
 
    void upd(int node, int nl, int nr, int l, int r, ll f, ll inc) {
        prop(node, nl, nr);
        if (nl > r || nr < l) return;
        if (nl >= l && nr <= r) {
            lazy[node].firstValue = (nl - l) * inc + f;
            lazy[node].Increment += inc;
            prop(node, nl, nr);
            return;
        }
        ll mid = nl + (nr - nl) / 2;
        upd(2 * node + 1, nl, mid, l, r, f, inc);
        upd(2 * node + 2, mid + 1, nr, l, r, f, inc);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
 
    ll query(int node, int nl, int nr, int l, int r) {
        prop(node, nl, nr);
        if (nl >= l && nr <= r) return tree[node];
        if (nl > r || nr < l) return 0;
        int mid = nl + (nr - nl) / 2;
        return query(2 * node + 1, nl, mid, l, r) + query(2 * node + 2, mid + 1, nr, l, r);
    }
};
 
int main() {
    PRE();
    int n , q;cin>>n>>q;
    vector<int> t(n);
    for(int i = 0;i < n;i++)cin>>t[i];
    SegmentTree seg(n);
    seg.build(0 , 0 , n - 1);
    for (int i = 0;i < n;i++) seg.upd(0 , 0 , n - 1 , i , i , t[i] , 1);
    while(q--) {
        int type;cin>>type;
        int a , b;cin>>a>>b;
        if(type == 1) {
            seg.upd(0 , 0 , n - 1 , a - 1 , b - 1 , 1 , 1);
        }else {
            cout<<seg.query(0 , 0 , n - 1 , a - 1 , b - 1)<<'\n';
        }
 
    }
 
}