/* problem statement text */
/*
CSES - Distance Queries

Time limit: 1.00 s
Memory limit: 512 MB

You are given a tree consisting of nnn nodes.
Your task is to process qqq queries of the form: what is the distance between nodes aaa and bbb?
Input
The first input line contains two integers nnn and qqq: the number of nodes and queries. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n.
Then there are n−1n-1n−1 lines describing the edges. Each line contains two integers aaa and bbb: there is an edge between nodes aaa and bbb.
Finally, there are qqq lines describing the queries. Each line contains two integer aaa and bbb: what is the distance between nodes aaa and bbb?
Output
Print qqq integers: the answer to each query.
Constraints

1≤n,q≤2⋅1051 \le n, q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 3
1 2
1 3
3 4
3 5
1 3
2 5
1 4

Output:
1
3
2
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
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(long long a1,long long b1,long long a2,long long b2,long long a3,long long b3) {return (a3 - a1) * (b2 - b1) == (a2 - a1) * (b3 - b1);}
const int N=2e5+1;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=2e17+1;
/*=======================================================================================================*/
/*==============================================  KHALWSH  ==============================================*/
/*=======================================================================================================*/
const int k=20;
int BinaryLifting[k][N],depth[N],parent[N];
vector<int>adj[N];
void MarkDepth(int node=0,int par=-1,int dep=0){
    depth[node]=dep;
    for(auto &val:adj[node]){
        if(val!=par)MarkDepth(val,node,dep+1);
    }
}
void build(int n){
    for(int i=0;i<n;i++){
        BinaryLifting[0][i]=parent[i];
    }
    for(int i=1;i<k;i++){
        for(int j=0;j<n;j++){
            BinaryLifting[i][j]=BinaryLifting[i-1][BinaryLifting[i-1][j]];
        }
    }
}
int Walk(int node,int kth){
    if(depth[node]<kth)return -2;
    for(int i=0;i<k;i++){
        if(kth&(1<<i))node=BinaryLifting[i][node];
    }
    return node;
}
int LCA(int a,int b){
    if(depth[a]<depth[b])swap(a,b);
    a=Walk(a,depth[a]-depth[b]);
    if(a==b)return a;
    for(int i=k-1;i>=0;i--){
        if(BinaryLifting[i][a]!=BinaryLifting[i][b]){
            a=BinaryLifting[i][a];
            b=BinaryLifting[i][b];
        }
    }
    return parent[a];
}
void rooting(){
    queue<pair<int,int>>q;
    q.push({0,-1});
    while(!q.empty()){
        int node=q.front().first;
        int par=q.front().second;
        q.pop();
        for(auto &val:adj[node]){
            if(val==par)continue;
            parent[val]=node;
            q.push({val,node});
        }
    }
}
signed main() {
    khaled
    int n,q;
    cin>>n>>q;
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        a--,b--;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    rooting();
    MarkDepth();
    build(n);
    while(q--){
        int a,b;
        cin>>a>>b;
        a--,b--;
        cout<<depth[a]+depth[b]-2*depth[LCA(a,b)]<<line;
    }
}