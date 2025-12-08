/* problem statement text */
/*
CSES - Subordinates

Time limit: 1.00 s
Memory limit: 512 MB

Given the structure of a company, your task is to calculate for each employee the number of their subordinates.
Input
The first input line has an integer nnn: the number of employees. The employees are numbered 1,2,…,n1,2,\dots,n1,2,…,n, and employee 111 is the general director of the company.
After this, there are n−1n-1n−1 integers: for each employee 2,3,…,n2,3,\dots,n2,3,…,n their direct boss in the company.
Output
Print nnn integers: for each employee 1,2,…,n1,2,\dots,n1,2,…,n the number of their subordinates.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105

Example
Input:
5
1 1 2 3

Output:
4 1 1 0 0
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
const int N = 3e5 + 5;
const int mod=2000003;
// const int mod = 998244353;
const ll inf=1e18;
const double pi=3.14159265350979323846,eps=1e-12;
const int dx[]{0, 0 , 1 ,-1},dy[]{1 , -1 , 0 , 0};// right left down up
string dir ="RLDU";
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using ordered_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
/*==============================================  KHALWSH  ==============================================*/
int n;
vector<int>adj[N];
int siz[N];
int in[N];
void dfs(int i ) {
   siz[i] = 1;
   for(auto &val:adj[i]) {
      dfs(val);
      siz[i] += siz[val];
   }
}
int main(){
   khaled
   cin>>n;
   for(int i = 1;i < n;i++) {
      int x;cin>>x;
      adj[x - 1].emplace_back(i);
      in[i]++;
   }
   for(int i = 0;i < n;i++) {
      if(in[i] == 0)dfs(i);
   }
   for(int i = 0;i < n;i++)cout<<siz[i] - 1<<" ";
}