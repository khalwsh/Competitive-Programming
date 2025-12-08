/* problem statement text */
/*
CSES - Round Trip

Time limit: 1.00 s
Memory limit: 512 MB

Byteland has nnn cities and mmm roads between them. Your task is to design a round trip that begins in a city, goes through two or more other cities, and finally returns to the starting city. Every intermediate city on the route has to be distinct.
Input
The first input line has two integers nnn and mmm: the number of cities and roads. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Then, there are mmm lines describing the roads. Each line has two integers aaa and bbb: there is a road between those cities.
Every road is between two different cities, and there is at most one road between any two cities.
Output
First print an integer kkk: the number of cities on the route. Then print kkk cities in the order they will be visited. You can print any valid solution.
If there are no solutions, print "IMPOSSIBLE".
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 6
1 3
1 2
5 3
1 5
2 4
4 5

Output:
4
3 5 1 3
*/
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#define int long long
#define line '\n'
#define khaled ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace __gnu_pbds;
using namespace std;
template<typename T>
using ordered_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;
bool valid(long long i,long long j,long long n,long long m){return i>=0&&i<n&&j>=0&&j<m;}
long long mul(long long x,long long y,const long long&mod){return ((x%mod)*(y%mod))%mod;}
long long add(long long x,long long y,const long long&mod){return (((x%mod)+(y%mod))%mod+mod)%mod;}
long long fast_power(long long base,long long power,const long long &m=INT64_MAX){if (power == 1 || power == 0)return base * power + (!power);long long res = (fast_power(base, power / 2, m) % m) % m;if (power & 1)return mul(base,mul(res,res,m),m);else return mul(res,res,m);}
int log2_floor(long long i) {return i ? __builtin_clzll(1) - __builtin_clzll(i) : 0;}
int power_of_2(int n){ return __builtin_popcountll(n)==1;}
bool line_checking(int a1,int b1,int a2,int b2,int a3,int b3) { return (b2-b1)*(a2-a3)==(b2-b3)*(a2-a1); }
pair<int,int> rotate(int i,int j,int n){ return make_pair(j,n-1-i); }
const int N=2e5+5;
const int mod=1e9+7;
//const int mod = 998244353;
const long long inf=1e18+1;
int dx[]{1,-1,0,0,1,1,-1,-1};
int dy[]{0,0,1,-1,1,-1,1,-1};
const long double pi=3.14159265350979323846,eps=1e-8;
/*==============================================  KHALWSH  ==============================================*/
//g++ main.cpp -o main
//main.exe
vector<int>adj[N];
bool vis[N];
bool cycle = false;
int parent[N];
void dfs(int node,int par){
	vis[node]=true;
	//mark in stack
	for(auto &val:adj[node]){
		if(par==val)continue;
		if(vis[val])cycle = true;
		else dfs(val,node);
	}
	//unmark
}
bool finish = false;
int CycleStart = -1;
int CycleEnd = -1;
void dfs2(int node,int par){
	vis[node]=true;
    for(auto &val:adj[node]){
		if(par==val)continue;
		if(finish)return;
		else if(vis[val]==1){
			//cycle is found
			CycleStart = val;
			CycleEnd = node;
			finish = true;
			return;
		}else{
			parent[val]=node;
			dfs2(val,node);
		}
		if(finish)return;
	}		
}
signed main() {
    khaled
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		
		int a,b;
		cin>>a>>b;
		a--,b--;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}
	for(int i=0;i<n;i++){
		if(!vis[i])dfs(i,-1);
	}
	if(cycle == false){
		cout<<"IMPOSSIBLE";
		exit(0);
	}
	vector<int>path;
	memset(vis,0,sizeof vis);
	for(int i=0;i<n;i++){
		if(!vis[i])dfs2(i,-1);
		if(finish)break;
	}
	path.emplace_back(CycleStart);
	for(int x = CycleEnd;x!=CycleStart;x = parent[x]){
		path.emplace_back(x);
	}
	path.emplace_back(CycleStart);
	reverse(path.begin(),path.end());
	cout<<path.size()<<line;
	for(auto &val:path)cout<<val+1<<" ";
}