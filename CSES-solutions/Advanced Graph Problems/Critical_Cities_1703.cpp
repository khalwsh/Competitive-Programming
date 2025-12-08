/* problem statement text */
/*
CSES - Critical Cities

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm flight connections between them. A city is called a critical city if it appears on every route from a city to another city.
Your task is to find all critical cities from Syrjälä to Lehmälä.
Input
The first input line has two integers nnn and mmm: the number of cities and flights. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n. City 111 is Syrjälä, and city nnn is Lehmälä.
Then, there are mmm lines describing the connections. Each line has two integers aaa and bbb: there is a flight from city aaa to city bbb. All flights are one-way.
You may assume that there is a route from Syrjälä to Lehmälä.
Output
First print an integer kkk: the number of critical cities. After this, print kkk integers: the critical cities in increasing order.
Constraints

2≤n≤1052 \le n \le 10^52≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 5
1 2
2 3
2 4
3 5
4 5

Output:
3
1 2 5
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
// -----------------------
// Defenition : there is an edge from u to v if every path from source to v pass through u
// idom[i] = immediate dominator of node with DFS index i (i.e., dominator-tree parent in DFS-index space).
// domTree[u] adjacency list of u in the dominator tree.
// id[u] : will be 0 if the source is not connected to node u
// Usage example of Dominator Tree:
// init(n);
// add directed edges to g[u] with u in [1..n];
// build(root);
// now domTree[u] holds neighbors of u in the dominator tree (for reachable nodes).
// -----------------------
const int N = 200000 + 5;
vector<int> g[N];
vector<int> rg[N], bucket[N];
vector<int> domTree[N];
int sdom[N], par[N], idom[N], dsu[N], label[N], pdom[N];
int id[N], rev_[N], T;
 
void init(int n) {
    T = 0;
    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        rg[i].clear();
        bucket[i].clear();
        domTree[i].clear();
        id[i] = 0;
        rev_[i] = 0;
        sdom[i] = par[i] = idom[i] = dsu[i] = label[i] = pdom[i] = 0;
    }
}
 
int find_(int u, int x = 0) {
    if (u == dsu[u]) return x ? -1 : u;
    int v = find_(dsu[u], x + 1);
    if (v < 0) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
}
 
void dfs(int u) {
    id[u] = ++T;
    rev_[T] = u;
    label[T] = sdom[T] = dsu[T] = T;
    for (int v: g[u]) {
        if (!id[v]) {
            dfs(v);
            par[id[v]] = id[u];
        }
        if (id[v]) rg[id[v]].push_back(id[u]);
    }
}
 
void build(int root) {
    dfs(root);
    int n = T;
 
    for (int i = n; i >= 1; --i) {
        for (int v: rg[i]) {
            int u = find_(v);
            sdom[i] = min(sdom[i], sdom[u]);
        }
        if (i > 1) bucket[sdom[i]].push_back(i);
 
        for (int w: bucket[i]) {
            int v = find_(w);
            if (sdom[v] == sdom[w]) idom[w] = sdom[w];
            else idom[w] = v;
        }
 
        if (i > 1) dsu[i] = par[i];
    }
    pdom[root] = root;
    for (int i = 2; i <= n; ++i) {
        if (idom[i] != sdom[i]) idom[i] = idom[idom[i]];
        int u = rev_[idom[i]];
        int v = rev_[i];
        pdom[v] = u;
        domTree[u].push_back(v);
        domTree[v].push_back(u);
    }
}
int n;
vector<ll> dijkstra(int source , vector<pair<int , int>> adj[]) {
    priority_queue<pair<ll , int> , vector< pair<ll , int>> , greater<>> pq;
    vector<ll>dist(n + 1 , 1e18);
    dist[source] = 0;
    pq.push({0 , source});
    while (!pq.empty()) {
        auto [cost , u] = pq.top();
        pq.pop();
        if (cost != dist[u]) continue;
        for (auto &[v , w] : adj[u]) {
            if (dist[v] > w + cost) {
                dist[v] = w + cost;
                pq.push({dist[v] , v});
            }
        }
    }
    return dist;
}
int main() {
    PRE();
    int m;
    cin >> n >> m;
    init(n);
    for (int i = 0;i < m;i++) {
        int u , v; cin >> u >> v;
        g[u].emplace_back(v);
    }
    build(1);
    vector<int> res;
    int x = n;
    while (pdom[x] != x) {
        res.emplace_back(x);
        x = pdom[x];
    }
    res.emplace_back(x);
    cout << res.size() << "\n";
    sort(res.begin(), res.end());
    for (auto &val : res) cout << val << " ";
}