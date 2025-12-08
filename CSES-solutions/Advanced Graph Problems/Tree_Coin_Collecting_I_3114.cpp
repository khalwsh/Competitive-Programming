/* problem statement text */
/*
CSES - Tree Coin Collecting I

Time limit: 1.00 s
Memory limit: 512 MB

You are given a tree with nnn nodes. Some nodes contain a coin.
Your task is to answer qqq queries of the form: what is the shortest length of a path from node aaa to node bbb that visits a node with a coin?
Input
The first line contains two integers nnn and qqq: the number of nodes and queries. The nodes are numbered 1,2,…,n1, 2, \dots, n1,2,…,n.
The second line contains nnn integers c1,c2,…,cnc_1, c_2,\dots, c_nc1​,c2​,…,cn​. If ci=1c_i = 1ci​=1, node iii has a coin. If ci=0c_i = 0ci​=0, node iii doesn't have a coin. You can assume at least one node has a coin.
Then there are n−1n-1n−1 lines describing the edges. Each line contains two integers aaa and bbb: there is an edge between nodes aaa and bbb.
Finally, there are qqq lines describing the queries. Each line contains two integers aaa and bbb: the start and end nodes.
Output
Print qqq integers: the answers to the queries.
Constraints

1≤n,q≤2⋅1051 \le n, q \le 2 \cdot 10^51≤n,q≤2⋅105
1≤a,b≤n1 \le a, b \le n1≤a,b≤n

Example
Input:
5 4
1 0 0 1 0
2 4
2 3
1 3
3 5
1 5
3 2
4 4
5 5

Output:
2
3
0
4
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
const int N = 2e5 + 10 , K = 20;
int up[K][N] , mn[K][N] , d[N];
vector<int> adj[N];
int a[N] , dist[N];
void dfs(int u , int p) {
    up[0][u] = p;
    d[u] = d[p] + 1;
    for (int j = 1; j < K;j++) {
        up[j][u] = up[j - 1][up[j - 1][u]];
    }
    for (auto &v : adj[u]) {
        if (v == p) continue;
        dfs(v , u);
    }
}
void dfs2(int u , int p) {
    mn[0][u] = dist[u];
    for (int j = 1; j < K;j++) {
        mn[j][u] = min(mn[j - 1][u] , mn[j - 1][up[j - 1][u]]);
    }
    for (auto &v : adj[u]) {
        if (v == p) continue;
        dfs2(v , u);
    }
}
int walk(int u , int kth) {
    for (int j = 0;j < K;j++) {
        if (kth >> j & 1) u = up[j][u];
    }
    return u;
}
int Lca(int u , int v) {
    if (d[u] > d[v]) swap(u , v);
    v = walk(v , d[v] - d[u]);
    if (u == v) return u;
    for (int i = K - 1;i >= 0;i--) {
        if (up[i][v] != up[i][u]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    assert(up[0][u] == up[0][v]);
    return up[0][u];
}
int solve(int u , int kth) {
    int res = dist[u];
    for (int j = 0;j < K;j++) {
        if (kth >> j & 1) res = min(res , mn[j][u]) , u = up[j][u];
    }
    return res;
}
int get_mn(int u , int v  , int L) {
    return min({dist[L] , solve(u , d[u] - d[L]) , solve(v , d[v] - d[L])});
}
int get_dist(int u , int v  , int L) {
    return d[u] + d[v] - 2 * d[L];
}
int main() {
    PRE();
    int n , m; cin >> n >> m;
    for (int i = 0;i < n;i++) cin >> a[i];
    for (int i = 0;i < n - 1;i++){
        int u , v; cin >> u >> v;
        u-- , v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0 , 0);
    queue<int> q;
    memset(dist , -1 , sizeof dist);
    for (int i = 0;i < n;i++) {
        if (a[i]) {
            dist[i] = 0;
            q.push(i);
        }
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (auto &v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = 1 + dist[u];
                q.push(v);
            }
        }
    }
    dfs2(0 , 0);
    while (m--) {
        int u , v;cin >> u >> v;
        u-- , v--;
        int L = Lca(u , v);
        cout << get_dist(u , v , L) + 2 * get_mn(u , v , L) << '\n';
    }
}