/* problem statement text */
/*
CSES - Flight Routes

Time limit: 1.00 s
Memory limit: 512 MB

Your task is to find the kkk shortest flight routes from Syrjälä to Metsälä. A route can visit the same city several times.
Note that there can be several routes with the same price and each of them should be considered (see the example).
Input
The first input line has three integers nnn, mmm, and kkk: the number of cities, the number of flights, and the parameter kkk. The cities are numbered 1,2,…,n1,2,\ldots,n1,2,…,n. City 1 is Syrjälä, and city nnn is Metsälä.
After this, the input has mmm lines describing the flights. Each line has three integers aaa, bbb, and ccc: a flight begins at city aaa, ends at city bbb, and its price is ccc. All flights are one-way flights.
You may assume that there are at least kkk distinct routes from Syrjälä to Metsälä.
Output
Print kkk integers: the prices of the kkk cheapest routes sorted according to their prices.
Constraints

2≤n≤1052 \le n \le 10^52≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤c≤1091 \le c \le 10^91≤c≤109
1≤k≤101 \le k \le 101≤k≤10

Example
Input:
4 6 3
1 2 1
1 3 3
2 3 2
2 4 6
3 2 8
3 4 1

Output:
4 4 7

Explanation: The cheapest routes are 1→3→41 \rightarrow 3 \rightarrow 41→3→4 (price 444), 1→2→3→41 \rightarrow 2 \rightarrow 3 \rightarrow 41→2→3→4 (price 444) and 1→2→41 \rightarrow 2 \rightarrow 41→2→4 (price 777).
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
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
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
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=1e2;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
vector<pair<int,int>> adj[N];
int n , m, k;
signed main() {
    khaled
    cin >> n >> m >> k;
    for(int i = 0; i < m; ++i){
        int u , v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(v , w);
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> q;
    vector<int> cnt(n) , ans;
    int start = 0 , end = n - 1;
    q.push({0 , start});
    while(q.size() && cnt[end] < k){
        auto [d , u] = q.top(); q.pop();
        cnt[u]++;
        if(u == end) ans.emplace_back(d);
        if(cnt[u] <= k){
            for(auto &[v,  w] : adj[u]) {
                if (cnt[v] < k)
                    q.push({(w + d), v});
            }
        }
    }
    sort(ans.begin() , ans.end());
    for(auto &w : ans) cout << w << " ";
}