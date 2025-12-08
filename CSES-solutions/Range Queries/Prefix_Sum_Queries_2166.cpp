/* problem statement text */
/*
CSES - Prefix Sum Queries

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to process qqq queries of the following types:

update the value at position kkk to uuu
what is the maximum prefix sum in range [a,b][a,b][a,b]?

Empty prefixes (with sum 0) are allowed.
Input
The first input line has two integers nnn and qqq: the number of values and queries.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array values.
Finally, there are qqq lines describing the queries. Each line has three integers: either "111 kkk uuu" or "222 aaa bbb".
Output
Print the result of each query of type 2.
Constraints

1≤n,q≤2⋅1051 \le n,q \le 2 \cdot 10^51≤n,q≤2⋅105
−109≤xi,u≤109-10^9 \le x_i, u \le 10^9−109≤xi​,u≤109
1≤k≤n1 \le k \le n1≤k≤n
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
8 4
1 2 -1 3 1 -5 1 4
2 2 6
1 4 -2
2 2 6
2 3 4

Output:
5
2
0
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <tr2/dynamic_bitset>
using namespace __gnu_pbds; // for ordered set
using namespace std; // global name space
using namespace tr2; // for dynamic_bitset<>
// #define int long long
#define line '\n'
typedef long long ll;
typedef long double ld;
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
ll SafeMul(ll a,ll b,ll m){if(b==0)return 0;ll res = SafeMul(a,b/2,m);res = add(res,res,m);if(b&1)return add(res,a,m);else return res;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(int a1,int b1,int a2,int b2,int a3,int b3) { return (b2-b1)*(a2-a3)==(b2-b3)*(a2-a1); }
pair<int,int> rotate(int i,int j,int n){ return make_pair(j,n-1-i); }
const int N = 3e5;
const int mod=1e9+7;
// const int mod = 998244353;
const ll inf=1e18;
const double pi=3.14159265350979323846,eps=1e-12;
const int dx[]{0, 0 , 1 ,-1},dy[]{1 , -1 , 0 , 0};// right left down up
string dir ="RLDU";
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*==============================================  KHALWSH  ==============================================*/
struct Node {
    // note: you don't consider empty subarray so if you want max(answer , 0)
    ll left, right, max, sum;
 
    Node(ll a = 0, ll b = 0, ll c = 0, ll d = 0) {
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
    khaled
    int n , q;cin>>n>>q;
    SegmentTree seg(n);
    for(int i = 0;i<n;i++) {
        int x;cin>>x;
        seg.update(0 , 0 , n - 1 , i , i , x);
    }
    while(q--) {
        int type;cin>>type;
        int l , r;cin>>l>>r;
        if(type == 1) {
            l --;
            seg.update(0 , 0 , n - 1 , l , l , r);
        }else {
            l-- , r--;
            cout<<max(0ll ,seg.query(0 , 0 , n - 1 , l , r).left)<<line;
        }
    }
}