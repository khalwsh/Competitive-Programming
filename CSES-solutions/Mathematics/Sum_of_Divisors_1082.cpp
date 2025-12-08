/* problem statement text */
/*
CSES - Sum of Divisors

Time limit: 1.00 s
Memory limit: 512 MB

Let σ(n)\sigma(n)σ(n) denote the sum of divisors of an integer nnn. For example, σ(12)=1+2+3+4+6+12=28\sigma(12)=1+2+3+4+6+12=28σ(12)=1+2+3+4+6+12=28.
Your task is to calculate the sum ∑i=1nσ(i)\sum_{i=1}^n \sigma(i)∑i=1n​σ(i) modulo 109+710^9+7109+7.
Input
The only input line has an integer nnn.
Output
Print ∑i=1nσ(i)\sum_{i=1}^n \sigma(i)∑i=1n​σ(i) modulo 109+710^9+7109+7.
Constraints

1≤n≤10121 \le n \le 10^{12}1≤n≤1012

Example
Input:
5

Output:
21
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
const int N = 4005;
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
__int128 sum(__int128 n){
   return n * ( n + 1 ) / 2;
}
__int128 S(__int128 n){
    __int128 res = 0;
    for(__int128 i=1;i*i<=n;i++){
        __int128 l = i, r = n/i;
        res = res + i*(r-l+1) + sum(r) - sum(l);
        res %= mod;
    }
    return res;
}
__int128 RangeSum(__int128 l,__int128 r){
    return add(S(r)  , - S(l-1) , mod);
}
signed main() {
    khaled
    ll n;cin>>n;
    cout<<(ll)RangeSum(1 , n);
}