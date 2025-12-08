/* problem statement text */
/*
CSES - Shortest Routes I

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm flight connections between them. Your task is to determine the length of the shortest route from Syrjälä to every city.
Input
The first input line has two integers nnn and mmm: the number of cities and flight connections. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n, and city 111 is Syrjälä.
After that, there are mmm lines describing the flight connections. Each line has three integers aaa, bbb and ccc: a flight begins at city aaa, ends at city bbb, and its length is ccc. Each flight is a one-way flight.
You can assume that it is possible to travel from Syrjälä to all other cities.
Output
Print nnn integers: the shortest route lengths from Syrjälä to cities 1,2,…,n1,2,\dots,n1,2,…,n.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤c≤1091 \le c \le 10^91≤c≤109

Example
Input:
3 4
1 2 6
1 3 2
3 2 3
1 3 4

Output:
0 5 2
*/
#include<bits/stdc++.h>
using namespace std;
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
bool valid(int i,int j,int n,int m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))+mod)%mod;}
long long fast_power(long long base,long long power,const long long &mod=INT64_MAX){
    if(power==0)return 1ll;long long d= fast_power(base,power/2)%mod;d=mul(d,d,mod);if(power&1)return mul(d,base,mod);else return d;}
long long mod_inverse_fermat(long long B,const long long&mod=1e9+7){ return fast_power(B,mod-2);}//mod is prime
int dx[]{1,-1,0,0,1,1,-1,-1};//0->4 normal,4->8 diagonal
int dy[]{0,0,1,-1,1,-1,1,-1};
#define int long long
/*--------------------------------------------------------------------------------------------------------------------*/
vector<int>dikstra(int n,vector<pair<int,int>>adj[])
{
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    vector<int>dist(n,INT64_MAX);
    dist[0]=0;
    pq.push({0,0});
    while(!pq.empty())
    {
        int node=pq.top().second;
        int cost=pq.top().first;
        pq.pop();
        if(dist[node]!=cost)continue;
        for(auto &val:adj[node])
        {
            if(dist[val.first]>cost+val.second)
            {
                dist[val.first]=val.second+cost;
                pq.push({dist[val.first],val.first});
            }
        }
    }
    return dist;
}
signed main() {
    khaled
    int n;
    int m;
    cin>>n>>m;
    vector<pair<int,int>>adj[n];
    for(int i=0;i<m;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        a--,b--;
        adj[a].emplace_back(b,c);
    }
    vector<int>dist=dikstra(n,adj);
    for(auto&val:dist)cout<<val<<" ";
    cout<<line;
}
 