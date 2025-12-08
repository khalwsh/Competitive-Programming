/* problem statement text */
/*
CSES - Fixed Length Walk Queries

Time limit: 1.00 s
Memory limit: 512 MB

You are given an undirected graph with nnn nodes and mmm edges. The graph is simple and connected.
You start at a specific node, and on each turn
you must move through an edge to another node.
Your task is to answer qqq queries of the form: "is it possible to start at node aaa and end up on node bbb after exactly xxx turns?"
Input
The first line contains three integers nnn, mmm and qqq:
the number of nodes, edges and queries. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines which describe the edges. Each line contains two integers aaa and bbb: there is an edge between nodes aaa and bbb.
Finally, there are qqq lines, each describing a query.
Each line contains three integers aaa, bbb and xxx.
Output
For each query, print the answer (YES or NO) on its own line.
Constraints

2≤n≤25002 \le n \le 25002≤n≤2500
1≤m≤50001 \le m \le 50001≤m≤5000
1≤q≤1051 \le q \le 10^51≤q≤105
0≤x≤1090 \le x \le 10^90≤x≤109

Example
Input:
4 5 6
1 2
2 3
1 3
2 4
3 4
1 2 2
1 4 1
1 4 5
2 2 1
2 2 2
3 4 8

Output:
YES
NO
YES
NO
YES
YES

Explanation:

In query 1, a possible route is 1→3→21 \rightarrow 3 \rightarrow 21→3→2.
In query 3, a possible route is 1→3→2→1→3→41 \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow 3 \rightarrow 41→3→2→1→3→4.
In query 6, a possible route is 3→4→2→3→4→2→1→3→43 \rightarrow 4 \rightarrow 2 \rightarrow 3 \rightarrow 4 \rightarrow 2 \rightarrow 1 \rightarrow 3 \rightarrow 43→4→2→3→4→2→1→3→4.
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
 
const int N = 2500 + 5;
vector<int> adj[N];
int dist[N][N][2];
int main() {
    PRE();
    int n, m , q;
    cin >> n >> m >> q;
    memset(dist , -1 , sizeof dist);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1;i <= n;i++) {
        queue<pair<int ,int>> qu;
        dist[i][i][0] = 0;
        qu.push({i , 0});
        while (!qu.empty()) {
            auto [u , parity] = qu.front();
            qu.pop();
            for (auto &v : adj[u]) {
                if (dist[i][v][!parity] == -1) {
                    dist[i][v][!parity] = 1 + dist[i][u][parity];
                    qu.push({v , !parity});
                }
            }
        }
    }
    for (int i = 0;i < q;i++) {
        int u , v , x; cin >> u >> v >> x;
        bool ok = false;
        if (dist[u][v][0] != -1 && x >= dist[u][v][0] && (x & 1) == 0) ok = true;
        if (dist[u][v][1] != -1 && x >= dist[u][v][1] && (x & 1) == 1) ok = true;
        cout << (ok ? "YES" : "NO") << '\n';
    }
}