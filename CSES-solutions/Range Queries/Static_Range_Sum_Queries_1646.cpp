/* problem statement text */
/*
CSES - Static Range Sum Queries

Time limit: 1.00 s
Memory limit: 512 MB

Given an array of nnn integers, your task is to process qqq queries of the form: what is the sum of values in range [a,b][a,b][a,b]?
Input
The first input line has two integers nnn and qqq: the number of values and queries.
The second line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array values.
Finally, there are qqq lines describing the queries. Each line has two integers aaa and bbb: what is the sum of values in range [a,b][a,b][a,b]?
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
11
2
24
4
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int dx[]{1,-1,0,0,1,1,-1,-1};//0->4 normal,4->8 diagonal
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846;
const long double eps=1e-10;
#define int long long
template<typename T>
using ordered_set=tree<T,null_type,greater_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
long long derangement(int n){if(n == 0)return 1;if(n == 1)return 0;if(n == 2)return 1;return (n - 1)*(derangement(n - 1) + derangement(n - 2));}
bool line_checking(long long a1,long long b1,long long a2,long long b2,long long a3,long long b3){return (a3-a1)*(b2-b1)==(a2-a1)*(b3-b1);}
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long safe_mul_mod(long long a,long long b,const long long &mod){long long res=0,y=a%mod;while(b>0){if(b&1){res=((res%mod)+(y%mod))%mod;}y=((y%mod)*(2ll%mod))%mod;b>>=1;}return (res%mod);}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
long long mod_inverse_fermat(long long B,const long long&mod=1e9+7){ return fast_power(B,mod-2,mod);}//mod is prime
vector<int>mod_inverse_for_range(int p){vector<int>inv(p,1);for(int i=2;i<p;i++) {inv[i] = ( p - (p / i) * inv[p % i] % p ) % p;}return inv;}//mod is prime
vector<long long>factorial(long long n,const long long& mod){vector<long long>v(n+1,1);for(int i=2;i<=n;i++)v[i]=mul(i,v[i-1],mod);return v;}
long long phi(long long n) {long long result = n;for (int i = 2; i * i <= n; i++) {if (n % i == 0) {while (n % i == 0)n /= i;result -= result / i;}}if (n > 1)result -= result / n;return result;}
bool power_of_two(int n) { n=abs(n); return n && !(n & (n - 1));}
const int N=5e5+1;
const int mod=998244353;
const long long inf=3e18;
//__builtin_popcountll
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
class max_segment_tree{
public:
    vector<int>tree;
    max_segment_tree(int n){
        tree.resize(4*n);
    }
    void build(vector<int>&v,int node,int l,int r){
        if(l==r){
            tree[node]=v[l];
            return;
        }
        int mid=(l+r)/2;
        build(v,2*node+1,l,mid);
        build(v,2*node+2,mid+1,r);
        tree[node]=max(tree[2*node+1],tree[2*node+2]);
    }
    int query(int node,int nl,int nr,int l,int r){
        if(nr<l||nl>r)return -inf;
        if(nr<=r&&nl>=l){
            return tree[node];
        }
        int mid=(nr+nl)/2;
        return max(query(2*node+1,nl,mid,l,r), query(2*node+2,mid+1,nr,l,r));
    }
};
class sum_segment_tree{
public:
    vector<int>tree;
    int _n;
    sum_segment_tree(int n){
        tree.resize(4*n);
        _n=n;
    }
    void build(int node,int l,int r,vector<int>&v){
        if(l==r){
            tree[node]=v[l];
            return;
        }
        build(2*node+1,l,(r+l)/2,v);
        build(2*node+2,(r+l)/2+1,r,v);
        tree[node]=tree[2*node+1]+tree[2*node+2];
    }
    int query(int node,int nl,int nr,int l,int r){
        if(nr<l||nl>r)return 0;
        if(nl>=l&&nr<=r)return tree[node];
        return query(2*node+1,nl,(nr+nl)/2,l,r)+query(2*node+2,(nr+nl)/2+1,nr,l,r);
    }
    void override(int node,int nl,int nr,int index,int value,int&x){
        if(index<nl||index>nr)return;
        if(index==nl&&nl==nr){
            tree[node]=value;
            x=node;
            return;
        }
        override(2*node+1,nl,(nr+nl/2),index,value,x);
        override(2*node+2,(nr+nl)/2+1,nr,index,value,x);
    }
    void update(int index,int value){
        int node=0;
        override(0,0,_n-1,index,value,node);
        while(true){
            tree[node]=tree[2*node+1]+tree[2*node+2];
            if(node==0)break;
            node/=2;
        }
    }
};
signed main() {
    khaled
    int n;
    int q;
    cin>>n>>q;
    vector<int>v(n);
    for(auto &val:v)cin>>val;
    sum_segment_tree seg(n);
    seg.build(0,0,n-1,v);
    while(q--){
        int a,b;
        cin>>a>>b;
        a--,b--;
        cout<<seg.query(0,0,n-1,a,b)<<line;
    }
}