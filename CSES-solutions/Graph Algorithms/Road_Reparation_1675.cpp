/* problem statement text */
/*
CSES - Road Reparation

Time limit: 1.00 s
Memory limit: 128 MB

There are nnn cities and mmm roads between them. Unfortunately, the condition of the roads is so poor that they cannot be used. Your task is to repair some of the roads so that there will be a decent route between any two cities.
For each road, you know its reparation cost, and you should find a solution where the total cost is as small as possible.
Input
The first input line has two integers nnn and mmm: the number of cities and roads. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Then, there are mmm lines describing the roads. Each line has three integers aaa, bbb and ccc: there is a road between cities aaa and bbb, and its reparation cost is ccc. All roads are two-way roads.
Every road is between two different cities, and there is at most one road between two cities.
Output
Print one integer: the minimum total reparation cost. However, if there are no solutions, print "IMPOSSIBLE".
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤c≤1091 \le c \le 10^91≤c≤109

Example
Input:
5 6
1 2 3
2 3 5
2 4 2
3 4 8
5 1 7
5 4 4

Output:
14
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
vector<vector<long long>>dp_nCr(100,vector<long long>(100,-1));
long long nCr(long long n,long long r){if(r == 0 || r == n)return 1;if(r == 1 || r == n - 1)return n;if(dp_nCr[n][r]!=-1)return dp_nCr[n][r]; return dp_nCr[n][r]= nCr(n - 1, r) + nCr(n - 1, r - 1);}
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
long long NCR_MOD(long long n, long long r,vector<long long>&fact,const long long&mod){return mul(mul(fact[n], mod_inverse_fermat(fact[n - r], mod), mod), mod_inverse_fermat(fact[r], mod), mod);}
int dx[]{1,-1,0,0,1,1,-1,-1};//0->4 normal,4->8 diagonal
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846;
const long double Eps=1e-10;
#define int long long
template<typename T>
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
const int N=1e7+1;
const int mod=1e9+7;
const long long inf=1e17;
/*--------------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------------------------*/
class dsu{
public:
    vector<int>parent,siz;
    dsu(int n){
        parent.resize(n);
        siz.resize(n,1);
        for(int i=0;i<n;i++)
            parent[i]=i;
    }
    int find_parent(int child){
        return (child==parent[child]?child:parent[child]=find_parent(parent[child]));
    }
    void merge(int a,int b){
        a= find_parent(a);
        b= find_parent(b);
        if(a==b)return ;
        if(siz[a]<siz[b])swap(a,b);
        parent[b]=a;
        siz[a]+=siz[b];
    }
};
signed main() {
    khaled
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>>adj[n];
    for(int i=0;i<m;i++){
        int a,b,cost;
        cin>>a>>b>>cost;
        a--,b--;
        adj[a].emplace_back(b,cost);
        adj[b].emplace_back(a,cost);
    }
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<>>pq;
    pq.push({0,{0,-1}});
    vector<pair<int,int>>mst;
    int res=0;
    vector<bool>vis(n,false);
    while(!pq.empty()){
        int node=pq.top().second.first;
        int parent=pq.top().second.second;
        int cost=pq.top().first;
        pq.pop();
        if(vis[node])continue;
        vis[node]=true;
        res+=cost;
        if(parent!=-1){
            mst.emplace_back(parent,node);
        }
        for(auto &val:adj[node]){
            if(!vis[val.first]){
                pq.push({val.second,{val.first,node}});
            }
        }
    }
    if(mst.size()!=n-1)cout<<"IMPOSSIBLE";
    else cout<<res<<line;
}