/* problem statement text */
/*
CSES - Reading Books

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn books, and Kotivalo and Justiina are going to read them all. For each book, you know the time it takes to read it.
They both read each book from beginning to end, and they cannot read a book at the same time. What is the minimum total time required?
Input
The first input line has an integer nnn: the number of books.
The second line has nnn integers t1,t2,…,tnt_1,t_2,\dots,t_nt1​,t2​,…,tn​: the time required to read each book.
Output
Print one integer: the minimum total time.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤ti≤1091 \le t_i \le 10^91≤ti​≤109

Example
Input:
3
2 8 3

Output:
16
*/
//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
//#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <tr2/dynamic_bitset>
using namespace __gnu_pbds; // for ordered set
using namespace std; // global name space
using namespace tr2; // for dynamic_bitset<>
//#define int long long
//#define double long double
#define line '\n'
typedef long long ll;
typedef double ld;
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
const int N = 1e6+5;
const int mod=1e9+7;
//const int mod = 998244353;
const ll inf=1e18;
const double pi=3.14159265350979323846,eps=1e-12;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*==============================================  KHALWSH  ==============================================*/
 
signed main() {
    khaled
    int n;
    cin>>n;
    ll sum = 0 ;
    int mx = 0;
    for(int i=0;i<n;i++){
        int x;cin>>x;
        sum += 1LL * x;
        mx = max(mx , x);
    }
    if(sum - mx < mx){
        cout<<2 * mx;
    }else
        cout<<sum<<line;
}