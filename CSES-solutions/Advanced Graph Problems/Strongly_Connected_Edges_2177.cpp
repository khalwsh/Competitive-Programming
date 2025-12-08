/* problem statement text */
/*
CSES - Strongly Connected Edges

Time limit: 1.00 s
Memory limit: 512 MB

Given an undirected graph, your task is to choose a direction for each edge so that the resulting directed graph is strongly connected.
Input
The first input line has two integers nnn and mmm: the number of nodes and edges. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines describing the edges. Each line has two integers aaa and bbb: there is an edge between nodes aaa and bbb.
You may assume that the graph is simple, i.e., there are at most one edge between two nodes and every edge connects two distinct nodes.
Output
Print mmm lines describing the directions of the edges. Each line has two integers aaa and bbb: there is an edge from node aaa to node bbb. You can print any valid solution.
If there are no solutions, only print IMPOSSIBLE.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
3 3
1 2
1 3
2 3

Output:
1 2
2 3
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
 
int tin_b[N], low_b[N];
bool vis_b[N];
int timer_b = 0;
int bridges = 0;
 
void dfs_bridges(int u, int p = -1) {
    vis_b[u] = true;
    tin_b[u] = low_b[u] = ++timer_b;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (vis_b[v]) {
            low_b[u] = min(low_b[u], tin_b[v]);
        } else {
            dfs_bridges(v, u);
            low_b[u] = min(low_b[u], low_b[v]);
            if (low_b[v] > tin_b[u]) {
                // u - v is a bridge
                bridges++;
            }
        }
    }
}
 
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
            // tree edge
            if (!seen.count({u , v})) {
                e.emplace_back(u , v);
                seen.insert({u , v}) , seen.insert({v , u});
            }
            dfs(v , u);
        } else if (v != p) {
            // backword edge
            if (!seen.count({u , v})) {
                e.emplace_back(u , v);
                seen.insert({u , v}) , seen.insert({v , u});
            }
        }
    }
}
 
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    int comps = 0;
    for (int i = 1; i <= n; ++i) {
        if (!vis_b[i]) {
            comps++;
            dfs_bridges(i);
        }
    }
 
    if (comps > 1 || bridges > 0) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }
 
    for (int i = 1; i <= n; ++i) vis[i] = false;
    timer = 0;
    seen.clear();
    e.clear();
 
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) dfs(i);
    }
 
    for (auto &ed : e) {
        int a = ed.first, b = ed.second;
        cout << a << " " << b << '\n';
    }
 
    return 0;
}