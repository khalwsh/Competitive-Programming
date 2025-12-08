/* problem statement text */
/*
CSES - Subtree Queries

Time limit: 1.00 s
Memory limit: 512 MB

You are given a rooted tree consisting of nnn nodes. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n, and node 111 is the root. Each node has a value.
Your task is to process following types of queries:

change the value of node sss to xxx
calculate the sum of values in the subtree of node sss

Input
The first input line contains two integers nnn and qqq: the number of nodes and queries. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n.
The next line has nnn integers v1,v2,…,vnv_1,v_2,\ldots,v_nv1​,v2​,…,vn​: the value of each node.
Then there are n−1n-1n−1 lines describing the edges. Each line contans two integers aaa and bbb: there is an edge between nodes aaa and bbb.
Finally, there are qqq lines describing the queries. Each query is either of the form "1 sss xxx" or "2 sss".
Output
Print the answer to each query of type 2.
Constraints

1≤n,q≤2⋅1051 \le n, q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤a,b,s≤n1 \le a,b, s \le n1≤a,b,s≤n
1≤vi,x≤1091 \le v_i, x \le 10^91≤vi​,x≤109

Example
Input:
5 3
4 2 5 2 1
1 2
1 3
3 4
3 5
2 3
1 5 3
2 3

Output:
8
10
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
int n , q;
vector<int>adj[N];
int values[N];
int Timer = 0 ,  St[N] , En[N];
vector<int>Tree;
void dfs(int node , int par) {
   St[node] = Timer;
   Tree[Timer] = node;
   Timer++;
   for(auto &val:adj[node]) {
      if(par == val)continue;
      dfs(val , node);
   }
   En[node] = Timer - 1;
}
template<class T>
struct Fenwick{
   int n;
   vector<T>tree;
   int N = 1;
   void init(int _n){
      n=_n;
      tree.resize(this->n);
      N = log2_floor(n) + 1;
   }
   void add(int pos,T value){
      for(int i=pos+1;i<=n;i+=i&-i)tree[i-1]+=value;
   }
   T get(int pos) {
      T sum = 0;
      for (int i = pos + 1; i; i -= i & -i)sum += tree[i - 1];
      return sum;
   }
   T query(int l,int r){
      return get(r)-get(l-1);//send zero base
   }
   int lower_bound(T t){
      T sum = 0;
      int pos = 0;
      for(int i = N; i >= 0; i--){
         int next_pos = pos + (1 << i);
         if(next_pos <= n && sum + tree[next_pos - 1] < t){
            sum += tree[next_pos - 1];
            pos = next_pos;
         }
      }
      return pos; // zero-based index
   }
};
int main(){
   khaled
   cin>>n>>q;
   Tree.resize(n);
   for(int i = 0;i < n ;i ++) {
      cin>>values[i];
   }
   for(int i = 0;i < n - 1;i++) {
      int a , b;cin>>a>>b;
      a-- , b--;
      adj[a].emplace_back(b);
      adj[b].emplace_back(a);
   }
   dfs(0 , -1);
   for(int i = 0;i < n;i++) {
      Tree[i] = values[Tree[i]];
   }
   Fenwick<ll>fen;
   fen.init(n + 1);
   for(int i = 0;i < n;i++)fen.add(i , Tree[i]);
   while(q--) {
      int type;cin>>type;
      if(type == 1) {
         ll node , x;cin>>node>>x;
         fen.add(St[node - 1] , x - values[node - 1]);
         values[node - 1] = x;
      }else {
         int node;
         cin>>node;
         cout<<fen.query(St[node - 1] , En[node - 1])<<line;
      }
   }
}