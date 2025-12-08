/* problem statement text */
/*
CSES - Range Update Queries

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to process qqq queries of the following types:

increase each value in range [a,b][a,b][a,b] by uuu
what is the value at position kkk?

Input
The first input line has two integers nnn and qqq: the number of values and queries.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array values.
Finally, there are qqq lines describing the queries. Each line has three integers: either "111 aaa bbb uuu" or "222 kkk".
Output
Print the result of each query of type 2.
Constraints

1≤n,q≤2⋅1051 \le n,q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤xi,u≤1091 \le x_i, u \le 10^91≤xi​,u≤109
1≤k≤n1 \le k \le n1≤k≤n
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
8 3
3 2 4 5 1 1 5 3
2 4
1 2 5 1
2 4

Output:
5
6
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;
#define int long long
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846;
const long double eps=1e-9;
template<typename T>
using ordered_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
const int N=1e6;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e17;
int power_of_2(int n){
    return __builtin_popcountll(n)==1;
}
//__builtin_clzll(x): the number of zeros at the beginning of the number
//__builtin_ctzll(x): the number of zeros at the end of the number
//__builtin_popcountll(x): the number of ones in the number
//__builtin_parityll(x): the parity (even or odd) of the number of ones
/*=======================================================================================================*/
/*==============================================  KHALWSH  ==============================================*/
/*=======================================================================================================*/
class segment_tree{
public:
    int n;
    vector<int>tree,lazy;
    int no_operation=0;
    segment_tree(int n){
       this->n=n;
       this->tree.resize(this->n*4);
       this->lazy.resize(this->n*4);
    }
    void build(int node,int nl,int nr,vector<int>&v){
        if(nl==nr){
            tree[node]=v[nl];
            return ;
        }
        int mid=nl+(nr-nl)/2;
        build(2*node+1,nl,mid,v),build(2*node+2,mid+1,nr,v);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    void lazy_update(int node,int nl,int nr,int l,int r,int delta){
        if(nl>=l&&nr<=r){
            //totally overlap
            //add to the tree and make lazy zero and push to children
            lazy[node]+=delta;
            tree[node]+=lazy[node];
            if(nl!=nr){
                lazy[2*node+1]+=lazy[node];
                lazy[2*node+2]+=lazy[node];
            }
            lazy[node]=no_operation;
            return;
        }else if(nr<l||nl>r){
            return;
        }
        int mid=nl+(nr-nl)/2;
        lazy_update(2*node+1,nl,mid,l,r,delta);
        lazy_update(2*node+2,mid+1,nr,l,r,delta);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    int query(int node,int nl,int nr,int l,int r){
        if(lazy[node]!=0){
            tree[node]+=lazy[node];
            if(nl!=nr){
                lazy[2*node+1]+=lazy[node];
                lazy[2*node+2]+=lazy[node];
            }
            lazy[node]=no_operation;
        }
        if(nr<l||nl>r)return no_operation;
        if(nl>=l&&nr<=r){
            return tree[node];
        }
        int mid=nl+(nr-nl)/2;
        return query(2*node+1,nl,mid,l,r)+query(2*node+2,mid+1,nr,l,r);
    }
    int query(int l,int r){
        return query(0,0,n-1,l,r);
    }
    void lazy_update(int l,int r,int cost){
        return lazy_update(0,0,n-1,l,r,cost);
    }
    void build(vector<int>&v){
        build(0,0,n-1,v);
    }
};
signed main() {
    khaled
    int n,q;
    cin>>n>>q;
    vector<int>v(n);
    for(auto &val:v)cin>>val;
    segment_tree seg(n);
    seg.build(v);
    while(q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int a, b;
            cin >> a >> b;
            int cost;
            cin >> cost;
            a--, b--;
            seg.lazy_update(a, b, cost);
        } else {
            int a;
            cin >> a;
            int b = a;
            a--, b--;
            cout << seg.query(a, b) << line;
        }
    }
 
}