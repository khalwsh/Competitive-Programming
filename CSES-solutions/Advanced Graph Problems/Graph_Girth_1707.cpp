/* problem statement text */
/*
CSES - Graph Girth

Time limit: 1.00 s
Memory limit: 512 MB

Given an undirected graph, your task is to determine its girth, i.e., the length of its shortest cycle.
Input
The first input line has two integers nnn and mmm: the number of nodes and edges. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines describing the edges. Each line has two integers aaa and bbb: there is an edge between nodes aaa and bbb.
You may assume that there is at most one edge between each two nodes.
Output
Print one integer: the girth of the graph. If there are no cycles, print −1-1−1.
Constraints

1≤n≤25001 \le n \le 25001≤n≤2500
1≤m≤50001 \le m \le 50001≤m≤5000

Example
Input:
5 6
1 2
1 3
2 4
2 5
3 4
4 5

Output:
3
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
 
const int N = 3e5 + 5;
vector<int> adj[N];
 
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int res = n + 10;
    for (int i = 1;i <= n;i++) {
        queue<pair<int ,int>> q;
        q.push({i , -1});
        vector<int>dist(n + 1 , -1);
        dist[i] = 0;
        while (!q.empty()) {
            auto [u , p] = q.front();
            q.pop();
            for (auto &v : adj[u]) {
                if (v == p) continue;
                if (~dist[v]) {
                    res = min(res , dist[u] + dist[v] + 1);
                }else {
                    dist[v] = dist[u] + 1;
                    q.push({v , u});
                }
            }
        }
    }
    if (res == n + 10) {
        cout << "-1";
    }else
        cout << res;
}