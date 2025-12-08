/* problem statement text */
/*
CSES - Subarray Sum Queries II

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers and qqq queries. In each query, your task is to calculate the maximum subarray sum in the range [a,b][a,b][a,b].
Empty subarrays (with sum 000) are allowed.
Input
The first line contains two integers nnn and qqq: the number of elements and the number of queries.
Then there are nnn integers x1,x2,…,xnx_1,x_2,\ldots,x_nx1​,x2​,…,xn​: the contents of the array.
Finally there are qqq lines that describe the queries. Each line has two integers aaa and bbb.
Output
Print the answer for each query.
Constraints

1≤n,q≤2⋅1051 \le n, q\le 2 \cdot 10^51≤n,q≤2⋅105
−109≤xi≤109-10^9 \le x_i \le 10^9−109≤xi​≤109
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
8 4
2 5 1 -2 3 -1 -7 1
2 4
2 5
6 7
4 8

Output:
6
7
0
3
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf = 1e16;
struct Node {
    // note: you don't consider empty subarray so if you want max(answer , 0)
    ll left, right, max, sum;
 
    Node(ll a = -inf, ll b = -inf, ll c = -inf, ll d = -inf) {
        sum = a, left = b, right = c, max = d;
    }
 
    Node operator+(const Node &a) {
        Node res;
        res.sum = a.sum + sum;
        res.left = std::max(left, sum + a.left);
        res.right = std::max(a.right, a.sum + right);
        res.max = std::max({max, a.max, right + a.left});
        return res;
    }
 
};
struct SegmentTree {
    vector<Node> tree;
    vector<ll> lazy;
    int n;
 
    SegmentTree(int _n) {
        n = _n;
        tree.resize(4 * n);
        lazy.resize(4 * n, -inf);
    }
 
    void build(int node, int nl, int nr, vector<ll> &v) {
 
        if (nl == nr) {
            tree[node] = Node(v[nl], v[nl], v[nl], v[nl]);
            return;
        }
        int mid = nl + (nr - nl) / 2;
        build(2 * node + 1, nl, mid, v);
        build(2 * node + 2, mid + 1, nr, v);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
 
    void prop(int node, int nl, int nr) {
        if (lazy[node] != -inf) {
            ll val = 1LL * (nr - nl + 1) * lazy[node];
            tree[node] = Node(val, val, val, val);
            if (nl != nr) {
                lazy[node * 2 + 1] = lazy[node];
                lazy[node * 2 + 2] = lazy[node];
            }
            lazy[node] = -inf;
        }
    }
 
    void update(int node, int nl, int nr, int l, int r, ll newValue) {
        prop(node, nl, nr);
        if (nl >= l && nr <= r) {
            ll val = 1LL * (nr - nl + 1) * newValue;
            tree[node] = Node(val, val, val, val);
            if (nl != nr) {
                lazy[node * 2 + 1] = newValue;
                lazy[node * 2 + 2] = newValue;
            }
            return;
        }
        if (nl > r || nr < l)return;
        int mid = nl + (nr - nl) / 2;
        update(2 * node + 1, nl, mid, l, r, newValue);
        update(2 * node + 2, mid + 1, nr, l, r, newValue);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
 
    Node query(int node, int nl, int nr, int l, int r) {
        prop(node, nl, nr);
        if (nl >= l && nr <= r)return tree[node];
        if (nl > r || nr < l)return Node();
        int mid = nl + (nr - nl) / 2;
        return query(2 * node + 1, nl, mid, l, r) + query(2 * node + 2, mid + 1, nr, l, r);
    }
};
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n , m;cin>>n>>m;
    SegmentTree seg(n);
    for(int i = 0;i < n;i++) {
        int x;cin>>x;
        seg.update(0 , 0 ,n - 1 , i , i, x);
    }
    for(int i = 0;i < m;i++) {
        int j , x;cin>>j>>x;
        j-- , x--;
        cout<<max(0ll , seg.query(0 , 0 , n - 1,  j , x).max)<<'\n';
    }
}