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
 
const int N = 3e5 + 5;
vector<int> adj[N];
vector<pair<int,int>> e;
int tin[N];
bool vis[N];
int timer = 0;
 
void dfs(int u) {
    vis[u] = true;
    tin[u] = ++timer;
    for (int v : adj[u]) {
        if (!vis[v]) dfs(v);
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
        e.emplace_back(u, v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) dfs(i);
    }
 
    for (auto &ed : e) {
        int a = ed.first, b = ed.second;
        if (tin[a] < tin[b]) cout << a << " " << b << '\n';
        else cout << b << " " << a << '\n';
    }
}
