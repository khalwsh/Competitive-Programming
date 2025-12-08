/* problem statement text */
/*
CSES - Investigation

Time limit: 1.00 s
Memory limit: 512 MB

You are going to travel from Syrjälä to Lehmälä by plane. You would like to find answers to the following questions:

what is the minimum price of such a route?
how many minimum-price routes are there? (modulo 109+7)10^9+7)109+7)
what is the minimum number of flights in a minimum-price route?
what is the maximum number of flights in a minimum-price route?

Input
The first input line contains two integers nnn and mmm: the number of cities and the number of flights. The cities are numbered 1,2,…,n1,2,\ldots,n1,2,…,n. City 1 is Syrjälä, and city nnn is Lehmälä.
After this, there are mmm lines describing the flights. Each line has three integers aaa, bbb, and ccc: there is a flight from city aaa to city bbb with price ccc. All flights are one-way flights.
You may assume that there is a route from Syrjälä to Lehmälä.
Output
Print four integers according to the problem statement.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤c≤1091 \le c \le 10^91≤c≤109

Example
Input:
4 5
1 4 5
1 2 4
2 4 5
1 3 2
3 4 3

Output:
5 2 1 2
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
const long long inf=1e18+1;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
int n,m;
vector<pair<int,int>>adj[N];
int MinPriceRoot(){
    vector<int>dist(n,inf);
    dist[0]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    pq.push({0,0});
    while(!pq.empty()){
        int node = pq.top().second;
        int cost = pq.top().first;
        pq.pop();
        if(cost!=dist[node])continue;
        for(auto &val:adj[node]){
            if(dist[val.first]>dist[node]+val.second){
                dist[val.first]=dist[node]+val.second;
                pq.push({dist[val.first],val.first});
            }
        }
    }
    return dist[n-1];
}
int CountMinPrice(){
    vector<pair<int,int>>dist(n);
    for(auto &val:dist)val = make_pair(inf,0);
    dist[0]= make_pair(0,1);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    pq.push({0,0});
    while(!pq.empty()){
        int node = pq.top().second;
        int cost = pq.top().first;
        pq.pop();
        if(cost!=dist[node].first)continue;
        for(auto &val:adj[node]){
            if(dist[val.first].first>dist[node].first+val.second){
                dist[val.first].first=dist[node].first+val.second;
                pq.push({dist[val.first].first,val.first});
                dist[val.first].second = dist[node].second;
            }else if(dist[val.first].first == dist[node].first+val.second){
                dist[val.first].second = add(dist[val.first].second,dist[node].second,mod);
            }
        }
    }
    return dist[n-1].second%mod;
}
int MinNumber(){
    vector<pair<int,int>>dist(n);
    for(auto &val:dist)val = make_pair(inf,0);
    dist[0]= make_pair(0,1);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    pq.push({0,0});
    while(!pq.empty()){
        int node = pq.top().second;
        int cost = pq.top().first;
        pq.pop();
        if(cost!=dist[node].first)continue;
        for(auto &val:adj[node]){
            if(dist[val.first].first>dist[node].first+val.second||dist[val.first].first == dist[node].first+val.second&&dist[node].second+1<dist[val.first].second){
                dist[val.first].first=dist[node].first+val.second;
                pq.push({dist[val.first].first,val.first});
                dist[val.first].second = dist[node].second + 1;
            }
        }
    }
    return dist[n-1].second;
}
int MaxNumber(){
    vector<pair<int,int>>dist(n);
    for(auto &val:dist)val = make_pair(inf,0);
    dist[0]= make_pair(0,1);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    pq.push({0,0});
    while(!pq.empty()){
        int node = pq.top().second;
        int cost = pq.top().first;
        pq.pop();
        if(cost!=dist[node].first)continue;
        for(auto &val:adj[node]){
            if(dist[val.first].first>dist[node].first+val.second||dist[val.first].first == dist[node].first+val.second&&dist[node].second+1>dist[val.first].second){
                dist[val.first].first=dist[node].first+val.second;
                pq.push({dist[val.first].first,val.first});
                dist[val.first].second = dist[node].second + 1;
            }
        }
    }
    return dist[n-1].second;
}
signed main() {
    khaled
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        a--,b--;
        adj[a].emplace_back(b,c);
    }
    cout<<MinPriceRoot()<<" "<<CountMinPrice()<<" "<<MinNumber()-1<<" "<<MaxNumber()-1;
    cout<<line;
}