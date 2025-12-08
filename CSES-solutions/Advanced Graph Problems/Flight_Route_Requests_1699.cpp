/* problem statement text */
/*
CSES - Flight Route Requests

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities with airports but no flight connections. You are given mmm requests which routes should be possible to travel.
Your task is to determine the minimum number of one-way flight connections which makes it possible to fulfil all requests.
Input
The first input line has two integers nnn and mmm: the number of cities and requests. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines describing the requests. Each line has two integers aaa and bbb: there has to be a route from city aaa to city bbb. Each request is unique.
Output
Print one integer: the minimum number of flight connections.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a, b \le n1≤a,b≤n

Example
Input:
4 5
1 2
2 3
2 4
3 1
3 4

Output:
4

Explanation: You can create the connections 1→21 \rightarrow 21→2, 2→32 \rightarrow 32→3, 2→42 \rightarrow 42→4 and 3→13 \rightarrow 13→1. Then you can also fly from city 333 to city 444 using the route 3→1→2→43 \rightarrow 1 \rightarrow 2 \rightarrow 43→1→2→4.
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
const int N = 1e5 + 10;
vector<int> adj[N] , dir[N];
int res = 0;
bool vis[N];
int vis2[N];
vector<int> all;
void dfs(int u , int p = -1) {
    vis[u] = true;
    all.emplace_back(u);
    for (auto &v : adj[u]) {
        if (v == p) continue;
        if (vis[v]) continue;
        else dfs(v , u);
    }
}
bool cyc = false;
void dfs2(int u) {
    vis2[u] = 1;
    for (auto &v : dir[u]) {
        if (vis2[v] == 1) {
            cyc = true;continue;
        }
        dfs2(v);
    }
    vis2[u] = 2;
}
bool cycle() {
    cyc = false;
    for (auto &u : all) {
        if (!vis2[u]) dfs2(u);
    }
    return cyc;
}
int main() {
    PRE();
    int n , m; cin >> n >> m;
    for (int i = 0;i < m;i++) {
        int u , v; cin >> u >> v;
        u-- , v--;
        adj[u].emplace_back(v);
        dir[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for (int i = 0;i < n;i++) {
        if (!vis[i]) {
            all.clear();
            dfs(i);
            int cnt = all.size();
            if (!cycle()) cnt--;
            res += cnt;
        }
    }
    cout << res;
}