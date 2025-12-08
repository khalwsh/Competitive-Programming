/* problem statement text */
/*
CSES - Necessary Roads

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm roads between them. There is a route between any two cities.
A road is called necessary if there is no route between some two cities after removing that road. Your task is to find all necessary roads.
Input
The first input line has two integers nnn and mmm: the number of cities and roads. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines that describe the roads. Each line has two integers aaa and bbb: there is a road between cities aaa and bbb. There is at most one road between two cities, and every road connects two distinct cities.
Output
First print an integer kkk: the number of necessary roads. After that, print kkk lines that describe the roads. You may print the roads in any order.
Constraints

2≤n≤1052 \le n \le 10^52≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 5
1 2
1 4
2 4
3 5
4 5

Output:
2
3 5
4 5
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
 
void PRE() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const int N = 2e5 + 10;
vector<int>adj[N];
vector<pair<int,int>>bridges;
int dfn[N], LowLink[N],ndfn = 0;
void Tarjan(int node,int parent){
    dfn[node] = LowLink[node] = ndfn++;
    for(auto &val:adj[node]){
        if(dfn[val]==-1){
            Tarjan(val,node);
            LowLink[node] = min(LowLink[node],LowLink[val]);
        }else if(parent!=val){
            LowLink[node] = min(LowLink[node],dfn[val]);
        }
    }
    if(LowLink[node]==dfn[node] && ~parent){
        bridges.emplace_back(parent,node);
    }
}
void Bridges(int n){
    memset(dfn,-1,sizeof dfn);
    for(int i=0;i<n;i++){
        if(dfn[i]==-1){
            Tarjan(i,-1);
        }
    }
}
int main() {
    PRE();
    int n , m; cin >> n >> m;
    for (int i = 0;i < m;i++) {
        int u , v;cin >> u >> v;
        u-- , v--;
        adj[u].emplace_back(v);
        swap(u , v);
        adj[u].emplace_back(v);
    }
    Bridges(n);
    cout << bridges.size() << '\n';
    for (auto &[u , v] : bridges){
        if (u > v) swap(u , v);
        cout << u + 1 << " " << v + 1 << "\n";
    }
}