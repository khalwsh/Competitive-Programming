/* problem statement text */
/*
CSES - Counting Towers

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to build a tower whose width is 222 and height is nnn. You have an unlimited supply of blocks whose width and height are integers.
For example, here are some possible solutions for n=6n=6n=6:

Given nnn, how many different towers can you build? Mirrored and rotated towers are counted separately if they look different.
Input
The first input line contains an integer ttt: the number of tests.
After this, there are ttt lines, and each line contains an integer nnn: the height of the tower.
Output
For each test, print the number of towers modulo 109+710^9+7109+7.
Constraints

1≤t≤1001 \le t \le 1001≤t≤100
1≤n≤1061 \le n \le 10^61≤n≤106

Example
Input:
3
2
6
1337

Output:
8
2864
640403945
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
//const int N = 1e6+5;
const int mod=1e9+7;
//const int mod = 998244353;
const ll inf=1e18;
const double pi=3.14159265350979323846,eps=1e-12;
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*==============================================  KHALWSH  ==============================================*/
const int maxN = 1e6;
const ll MOD = 1e9+7;
 
int T, N;
ll dp[maxN+1];
 
int main(){
    dp[1] = 2;
    dp[2] = 8;
    for(int i = 3; i <= maxN; i++)
        dp[i] = ((6*dp[i-1] - 7*dp[i-2]) % MOD + MOD) % MOD;
 
    scanf("%d", &T);
    for(int t = 0; t < T; t++){
        scanf("%d", &N);
        printf("%lld\n", dp[N]);
    }
}