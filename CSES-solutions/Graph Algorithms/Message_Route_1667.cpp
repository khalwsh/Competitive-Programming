/* problem statement text */
/*
CSES - Message Route

Time limit: 1.00 s
Memory limit: 512 MB

Syrjälä's network has nnn computers and mmm connections. Your task is to find out if Uolevi can send a message to Maija, and if it is possible, what is the minimum number of computers on such a route.
Input
The first input line has two integers nnn and mmm: the number of computers and connections. The computers are numbered 1,2,…,n1,2,\dots,n1,2,…,n. Uolevi's computer is 111 and Maija's computer is nnn.
Then, there are mmm lines describing the connections. Each line has two integers aaa and bbb: there is a connection between those computers.
Every connection is between two different computers, and there is at most one connection between any two computers.
Output
If it is possible to send a message, first print kkk: the minimum number of computers on a valid route. After this, print an example of such a route. You can print any valid solution.
If there are no routes, print "IMPOSSIBLE".
Constraints

2≤n≤1052 \le n \le 10^52≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 5
1 2
1 3
1 4
2 3
5 4

Output:
3
1 4 5
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
signed main() {
    khaled
    int n;
    int m;
    cin>>n>>m;
    vector<int>adj[n];
    for(int i=0;i<m;i++)
    {
        int a,b;
        cin>>a>>b;
        a--,b--;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    vector<int>dist(n,INT_MAX);
    dist[0]=0;
    vector<int>parent(n,0);
    for(int i=0;i<n;i++)parent[i]=i;
    queue<pair<int,int>>pq;
    pq.push({0,0});
    while(!pq.empty())
    {
        int node=pq.front().second;
        int cost=pq.front().first;
        pq.pop();
        if(cost!=dist[node])continue;
        for(auto &val:adj[node])
        {
            if(dist[val]>cost+1)
            {
                dist[val]=cost+1;
                parent[val]=node;
                pq.push({dist[val],val});
            }
        }
    }
    if(dist[n-1]==INT_MAX)
        cout<<"IMPOSSIBLE";
    else
    {
        vector<int>path;
        int temp=n-1;
        while(parent[temp]!=temp)
        {
            path.emplace_back(temp);
            temp=parent[temp];
        }
        path.emplace_back(0);
        reverse(path.begin(),path.end());
        cout<<path.size()<<line;
        for(auto &val:path)cout<<val+1<<" ";
    }
}