/* problem statement text */
/*
CSES - Distinct Values Queries

Time limit: 1.00 s
Memory limit: 512 MB

You are given an array of nnn integers and qqq queries of the form: how many distinct values are there in a range [a,b][a,b][a,b]?
Input
The first input line has two integers nnn and qqq: the array size and number of queries.
The next line has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​: the array values.
Finally, there are qqq lines describing the queries. Each line has two integers aaa and bbb.
Output
For each query, print the number of distinct values in the range.
Constraints

1≤n,q≤2⋅1051 \le n,q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤xi≤1091 \le x_i \le 10^91≤xi​≤109
1≤a≤b≤n1 \le a \le b \le n1≤a≤b≤n

Example
Input:
5 3
3 2 3 1 2
1 3
2 4
1 5

Output:
2
3
3
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#define int long long
#define double long double
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
int SafeMul(int a,int b,int m){if(b==0)return 0;int res = SafeMul(a,b/2,m);res = add(res,res,m);if(b&1)return add(res,a,m);else return res;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(int a1,int b1,int a2,int b2,int a3,int b3) { return (b2-b1)*(a2-a3)==(b2-b3)*(a2-a1); }
pair<int,int> rotate(int i,int j,int n){ return make_pair(j,n-1-i); }
const int N = 2e5+5;
//const int mod=1e9+7;
const int mod = 998244353;
const long long inf=2e18;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
int n,q;
int v[N];
vector<pair<int,int>>queries[N];
int ans[N];
struct Fenwick{
    int n;
    vector<int>tree;
    void init(int _n){
        n=_n;
        tree.resize(this->n);
    }
    void add(int pos,int value){
        for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]+=value;
    }
    int get(int pos) {
        int sum = 0;
        for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
        return sum;
    }
    int query(int l,int r){
        return get(r)-get(l-1);//send zero base
    }
};
 
signed main() {
    khaled
    cin>>n>>q;
    for(int i=0;i<n;i++){
        cin>>v[i];
    }
    Fenwick fen;
    fen.init(n);
    map<int,int>last_index;
    for(int i=0;i<q;i++){
        int l,r;
        cin>>l>>r;
        l--,r--;
        queries[l].emplace_back(r,i);
    }
    for(int i=n-1;i>=0;i--){
        int val = v[i];
        if(last_index.count(val)){
            fen.add(last_index[val],-1);
        }
        last_index[val] = i;
        fen.add(i,1);
        for(auto &j:queries[i]){
            ans[j.second] = fen.get(j.first);
        }
    }
    for(int i=0;i<q;i++){
        cout<<ans[i]<<line;
    }
}