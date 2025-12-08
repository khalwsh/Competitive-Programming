/* problem statement text */
/*
CSES - MST Edge Cost

Time limit: 1.00 s
Memory limit: 512 MB

Given an undirected weighted graph, determine for each edge the minimum spanning tree cost if the edge must be included in the spanning tree.
Input
The first line has two integers nnn and mmm: the number of nodes and edges. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
The following mmm lines describe the edges. Each line has three integers aaa, bbb, www: there is an edge between nodes aaa and bbb with weight www.
You can assume that the graph is connected and simple and each edge appears at most once in the graph.
Output
For each edge in the input order, print the minimum spanning tree cost when the edge is included.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤w≤1091 \le w \le 10^91≤w≤109

Example
Input:
5 6
1 2 4
1 3 2
2 4 2
3 4 1
3 5 4
4 5 3

Output:
10
8
8
8
9
8
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
 
struct DSU {
    int n;
    vector<int> p, r;
    DSU(int n = 0) : n(n), p(n + 1), r(n + 1, 0) {
        for (int i = 1; i <= n; ++i) p[i] = i;
    }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};
 
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
    struct Edge {
        int u, v;
        ll w;
        int idx;
    };
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].idx = i;
    }
 
    vector<int> order(m);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(),
         [&](int a, int b) { return edges[a].w < edges[b].w; });
    DSU dsu(n);
    vector<char> inMST(m, false);
    ll MST_cost = 0;
    vector<vector<pair<int, ll>>> adj(n + 1);
    for (int id : order) {
        auto &e = edges[id];
        if (dsu.unite(e.u, e.v)) {
            inMST[id] = true;
            MST_cost += e.w;
            adj[e.u].push_back({e.v, e.w});
            adj[e.v].push_back({e.u, e.w});
        }
    }
 
    int LOG = 20;
    vector<vector<int>> up(LOG, vector<int>(n + 1, 0));
    vector<vector<ll>> mx(LOG, vector<ll>(n + 1, 0));
    vector<int> depth(n + 1, -1);
 
    int root = 1;
    depth[root] = 0;
    deque<int> dq;
    dq.push_back(root);
    up[0][root] = 0;
    mx[0][root] = 0;
    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        for (auto [v, w] : adj[u]) {
            if (depth[v] == -1) {
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                mx[0][v] = w;
                dq.push_back(v);
            }
        }
    }
 
    for (int k = 1; k < LOG; ++k) {
        for (int v = 1; v <= n; ++v) {
            int mid = up[k - 1][v];
            up[k][v] = up[k - 1][mid];
            mx[k][v] = max(mx[k - 1][v], mx[k - 1][mid]);
        }
    }
 
    auto max_on_path = [&](int a, int b) -> ll {
        if (a == b) return 0;
        ll ans = 0;
        if (depth[a] < depth[b]) swap(a, b);
        int diff = depth[a] - depth[b];
        for (int k = 0; k < LOG; ++k) {
            if (diff & (1 << k)) {
                ans = max(ans, mx[k][a]);
                a = up[k][a];
            }
        }
        if (a == b) return ans;
        for (int k = LOG - 1; k >= 0; --k) {
            if (up[k][a] != up[k][b]) {
                ans = max(ans, mx[k][a]);
                ans = max(ans, mx[k][b]);
                a = up[k][a];
                b = up[k][b];
            }
        }
        ans = max(ans, mx[0][a]);
        ans = max(ans, mx[0][b]);
        return ans;
    };
 
    vector<ll> output(m);
    for (int i = 0; i < m; ++i) {
        if (inMST[i]) {
            output[i] = MST_cost;
        } else {
            ll mx_edge = max_on_path(edges[i].u, edges[i].v);
            output[i] = MST_cost - mx_edge + edges[i].w;
        }
    }
 
    for (int i = 0; i < m; ++i) cout << output[i] << "\n";
}