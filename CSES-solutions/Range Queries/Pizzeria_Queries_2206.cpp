/* problem statement text */
/*
CSES - Pizzeria Queries

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn buildings on a street, numbered 1,2,…,n1,2,\dots,n1,2,…,n. Each building has a pizzeria and an apartment.
The pizza price in building kkk is pkp_kpk​. If you order a pizza from building aaa to building bbb, its price (with delivery) is pa+∣a−b∣p_a+|a-b|pa​+∣a−b∣.
Your task is to process two types of queries:

The pizza price pkp_kpk​ in building kkk becomes xxx.
You are in building kkk and want to order a pizza. What is the minimum price?

Input
The first input line has two integers nnn and qqq: the number of buildings and queries.
The second line has nnn integers p1,p2,…,pnp_1,p_2,\dots,p_np1​,p2​,…,pn​: the initial pizza price in each building.
Finally, there are qqq lines that describe the queries. Each line is either "1 kkk xxx" or "2 kkk".
Output
Print the answer for each query of type 2.
Constraints

1≤n,q≤2⋅1051 \le n,q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤pi,x≤1091 \le p_i, x \le 10^91≤pi​,x≤109
1≤k≤n1 \le k \le n1≤k≤n

Example
Input:
6 3
8 6 4 5 7 5
2 2
1 5 1
2 2

Output:
5
4
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
const int N = 2e5 + 5;
const int mod = 1e9 + 7;
// const int mod = 998244353;
const ll inf=1e18;
const double pi=3.14159265350979323846,eps=1e-12;
const int dx[]{0, 0 , 1 ,-1},dy[]{1 , -1 , 0 , 0};// right left down up
string dir ="RLDU";
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*==============================================  KHALWSH  ==============================================*/
class SegmentTree {
    //you need to initialize the No-Operation variable before work
    //if it's assign make it -inf if it's add make it 0
    //1- make object , 2- initialize no-op 3- call init
public:
    vector<int> tree, lazy;
    int n;
    int No_Operation = -2e9;
 
    void init(int _n) {
        n = _n;
        tree.resize(4 * n);
        lazy.resize(4 * n, No_Operation);
    }
    SegmentTree(int _n = 1){
        init(_n);
    }
private:
    void build(int node, int nl, int nr, vector<int> &v) {
        if (nl == nr) {
            tree[node] = v[nl];
            return;
        }
        int mid = nl + (nr - nl) / 2;
        build(2 * node + 1, nl, mid, v);
        build(2 * node + 2, mid + 1, nr, v);
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }
 
    void SingleUpdateAssign(int node, int nl, int nr, int ind, int newVal) {
        //set the value;
        if (nl == nr && nl == ind) {
            tree[node] = newVal;
            return;
        }
        if (nl > ind || nr < ind)return;
        int mid = nl + (nr - nl) / 2;
        SingleUpdateAssign(2 * node + 1, nl, mid, ind, newVal);
        SingleUpdateAssign(2 * node + 2, mid + 1, nr, ind, newVal);
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }
 
    void PropAssign(int node, int nl, int nr) {
        if (lazy[node] != No_Operation) {
            tree[node] = lazy[node];
            if (nl != nr) {
                lazy[2 * node + 1] = lazy[node];
                lazy[2 * node + 2] = lazy[node];
            }
            lazy[node] = No_Operation;
        }
    }
 
    void RangeUpdateAssign(int node, int nl, int nr, int l, int r, int newVal) {
        PropAssign(node, nl, nr);
        if (nl >= l && nr <= r) {
            tree[node] = newVal;
            if (nl != nr) {
                lazy[2 * node + 1] = newVal;
                lazy[2 * node + 2] = newVal;
            }
            return;
        }
        if (nl > r || nr < l)return;
        int mid = nl + (nr - nl) / 2;
        RangeUpdateAssign(2 * node + 1, nl, mid, l, r, newVal);
        RangeUpdateAssign(2 * node + 2, mid + 1, nr, l, r, newVal);
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }
 
    void SingleUpdateAdd(int node, int nl, int nr, int ind, int Delta) {
        //set the value;
        if (nl == nr && nl == ind) {
            tree[node] += Delta;
            return;
        }
        if (nl > ind || nr < ind)return;
        int mid = nl + (nr - nl) / 2;
        SingleUpdateAdd(2 * node + 1, nl, mid, ind, Delta);
        SingleUpdateAdd(2 * node + 2, mid + 1, nr, ind, Delta);
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }
 
    void PropAdd(int node, int nl, int nr) {
        if (lazy[node] != No_Operation) {
            tree[node] += lazy[node];
            if (nl != nr) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = No_Operation;
        }
    }
 
    void RangeUpdateAdd(int node, int nl, int nr, int l, int r, int Delta) {
        PropAdd(node, nl, nr);
        if (nl >= l && nr <= r) {
            tree[node] += Delta;
            if (nl != nr) {
                lazy[2 * node + 1] += Delta;
                lazy[2 * node + 2] += Delta;
            }
            return;
        }
        if (nl > r || nr < l)return;
        int mid = nl + (nr - nl) / 2;
        RangeUpdateAdd(2 * node + 1, nl, mid, l, r, Delta);
        RangeUpdateAdd(2 * node + 2, mid + 1, nr, l, r, Delta);
        tree[node] = min(tree[2 * node + 1], tree[2 * node + 2]);
    }
 
    int QueryAdd(int node, int nl, int nr, int l, int r) {
        PropAdd(node, nl, nr);
        if (nl >= l && nr <= r)return tree[node];
        if (nl > r || nr < l)return inf;
        int mid = nl + (nr - nl) / 2;
        return min(QueryAdd(2 * node + 1, nl, mid, l, r), QueryAdd(2 * node + 2, mid + 1, nr, l, r));
    }
 
    int QueryAssign(int node, int nl, int nr, int l, int r) {
        PropAssign(node, nl, nr);
        if (nl >= l && nr <= r)return tree[node];
        if (nl > r || nr < l)return 2e9;
        int mid = nl + (nr - nl) / 2;
        return min(QueryAssign(2 * node + 1, nl, mid, l, r), QueryAssign(2 * node + 2, mid + 1, nr, l, r));
    }
 
public:
    void build(vector<int> &v) {
        build(0, 0, n - 1, v);
    }
 
    void SingleUpdateAssign(int ind, int newVal) {
        SingleUpdateAssign(0, 0, n - 1, ind, newVal);
    }
 
    void SingleUpdateAdd(int ind, int delta) {
        SingleUpdateAdd(0, 0, n - 1, ind, delta);
    }
 
    void RangeUpdateAdd(int l, int r, int delta) {
        RangeUpdateAdd(0, 0, n - 1, l, r, delta);
    }
 
    void RangeUpdateAssign(int l, int r, int newVal) {
        RangeUpdateAssign(0, 0, n - 1, l, r, newVal);
    }
 
    int QueryAdd(int l, int r) {
        return QueryAdd(0, 0, n - 1, l, r);
    }
 
    int QueryAssign(int l, int r) {
        return QueryAssign(0, 0, n - 1, l, r);
    }
};
int main() {
    khaled
    int n , q;cin>>n>>q;
    SegmentTree seg1 , seg2;
    seg1.init(4 * n) , seg2.init(4 * n);
    for(int i = 0;i < n;i++) {
        int x;cin>>x;
        seg1.RangeUpdateAssign(i ,i, x - i);
        seg2.RangeUpdateAssign(i ,i, x + i);
    }
    while(q--) {
        int type;cin>>type;
        if(type == 1) {
            int idx , x;
            cin>>idx>>x;
            idx--;
            seg1.RangeUpdateAssign(idx , idx , x - idx);
            seg2.RangeUpdateAssign(idx ,idx , x + idx);
        }else {
            int idx;cin>>idx;
            idx--;
            int res = seg1.QueryAssign(idx , idx) + idx;
            if(idx - 1 >= 0)res = min(res , seg1.QueryAssign(0 , idx - 1) + idx);
            if(idx + 1 < n)res = min(res , seg2.QueryAssign(idx + 1 , n - 1) - idx);
            cout<<res<<line;
        }
    }
}