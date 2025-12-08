/* problem statement text */
/*
CSES - Necessary Cities

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm roads between them. There is a route between any two cities.
A city is called necessary if there is no route between some other two cities after removing that city (and adjacent roads). Your task is to find all necessary cities.
Input
The first input line has two integers nnn and mmm: the number of cities and roads. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines that describe the roads. Each line has two integers aaa and bbb: there is a road between cities aaa and bbb. There is at most one road between two cities, and every road connects two distinct cities.
Output
First print an integer kkk: the number of necessary cities. After that, print a list of kkk cities. You may print the cities in any order.
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
int dfn[N],LowLink[N],ndfn = 0;
vector<int>adj[N];
bool IsArtPoints[N];
vector<int>ArtPoints;
void Tarjan(int node,int parent){
    dfn[node] = LowLink[node] = ndfn++;
    int child = 0;
    for(auto &val:adj[node]){
        if(dfn[val]==-1){
            child++;
            Tarjan(val,node);
            LowLink[node] = min(LowLink[node],LowLink[val]);
            if(LowLink[val]>=dfn[node]){
                if(parent==-1&&child<=1)continue;
                IsArtPoints[node] = true;
            }
        }else if(parent!=val){
            LowLink[node] = min(LowLink[node],dfn[val]);
        }
    }
}
void Art(int n){
    ndfn = 0;
    for(int i=0;i<n;i++){
        dfn[i] = -1;
        IsArtPoints[i] = false;
        LowLink[i] = 0;
    }
    for(int i=0;i<n;i++){
        if(dfn[i]==-1)Tarjan(i,-1);
    }
    for(int i=0;i<n;i++){
        if(IsArtPoints[i])ArtPoints.emplace_back(i);
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
    Art(n);
    cout << ArtPoints.size() << '\n';
    sort(ArtPoints.begin(), ArtPoints.end());
    for (auto &val : ArtPoints) cout << ++val << " ";
}