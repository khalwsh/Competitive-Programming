/* problem statement text */
/*
CSES - Acyclic Graph Edges

Time limit: 1.00 s
Memory limit: 512 MB

Given an undirected graph, your task is to choose a direction for each edge so that the resulting directed graph is acyclic.
Input
The first input line has two integers nnn and mmm: the number of nodes and edges. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines describing the edges. Each line has two distinct integers aaa and bbb: there is an edge between nodes aaa and bbb.
Output
Print mmm lines describing the directions of the edges. Each line has two integers aaa and bbb: there is an edge from node aaa to node bbb. You can print any valid solution.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
3 3
1 2
2 3
3 1

Output:
1 2
3 2
3 1
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
 
// if you want to extract edges do it after you run dfs
// because you traverse edge more than 1 time so it can be duplicated
// so run then check if (tin[u] < tin[b]) tree edge otherwise backward edge
const int N = 3e5 + 5;
vector<int> adj[N];
vector<pair<int,int>> e;
int tin[N];
bool vis[N];
int timer = 0;
set<pair<int , int>> seen;
void dfs(int u , int p = -1) {
    vis[u] = true;
    tin[u] = ++timer;
    for (int v : adj[u]) {
        if (vis[v] && tin[u] < tin[v]) {
            // forward edge
            if (!seen.count({u , v}))
                e.emplace_back(v , u) , seen.insert({u , v}) , seen.insert({v , u});
            continue;
        }
        if (!vis[v]) {
            if (!seen.count({u , v})) {
                e.emplace_back(u , v);
                seen.insert({u , v}) , seen.insert({v , u});
            }
            dfs(v , u);
        }else if (v != p) {
            // backword edge
            if (!seen.count({u , v})) {
                e.emplace_back(u , v);
                seen.insert({u , v}) , seen.insert({v , u});
            }
        }
    }
}
// if (!vis[v]) {
//     // v is not visited → TREE EDGE (u -> v)
// }
// else if (v != parent) {
//     // visited and not parent → BACK EDGE (u -> v)
// }
 
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) dfs(i) , cnt++;
    }
    if (cnt != 1) {
        cout << "IMPOSSIBLE";
        exit(0);
    }
    for (auto &ed : e) {
        int a = ed.first, b = ed.second;
        cout << a << " " << b << '\n';
    }
 
}