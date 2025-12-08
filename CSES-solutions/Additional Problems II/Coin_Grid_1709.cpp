/* problem statement text */
/*
CSES - Coin Grid

Time limit: 1.00 s
Memory limit: 512 MB

There is an n×nn \times nn×n grid whose each square is empty or has a coin. On each move, you can remove all coins in a row or column.
What is the minimum number of moves after which the grid is empty?
Input
The first input line has an integer nnn: the size of the grid. The rows and columns are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are nnn lines describing the grid. Each line has nnn characters: each character is either . (empty) or o (coin).
Output
First print an integer kkk: the minimum number of moves. After this, print kkk lines describing the moves.
On each line, first print 111 (row) or 222 (column), and then the number of a row or column. You can print any valid solution.
Constraints

1≤n≤1001 \le n \le 1001≤n≤100

Example
Input:
3
..o
o.o
...

Output:
2
1 2
2 3
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
}
 
struct HopcroftKarp {
    int n, m;
    vector<vector<int>> adj;
    vector<int> mu, mv, dist;
 
    HopcroftKarp(int n, int m)
      : n(n), m(m), adj(n),
        mu(n, -1), mv(m, -1), dist(n) {}
 
    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }
 
    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; u++) {
            if (mu[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        bool found_augment = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                int u2 = mv[v];
                if (u2 == -1) {
                    found_augment = true;
                } else if (dist[u2] < 0) {
                    dist[u2] = dist[u] + 1;
                    q.push(u2);
                }
            }
        }
        return found_augment;
    }
 
    bool dfs(int u) {
        for (int v : adj[u]) {
            int u2 = mv[v];
            if (u2 == -1 || (dist[u2] == dist[u] + 1 && dfs(u2))) {
                mu[u] = v;
                mv[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }
 
    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < n; u++) {
                if (mu[u] == -1 && dfs(u))
                    matching++;
            }
        }
        return matching;
    }
};
 
int main(){
    PRE();
    int n;
    cin >> n;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    HopcroftKarp hk(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'o') {
                hk.add_edge(i, j);
            }
        }
    }
 
    int M = hk.max_matching();
    vector<char> visL(n, 0), visR(n, 0);
    queue<int> q;
    for (int u = 0; u < n; u++) {
        if (hk.mu[u] == -1) {
            visL[u] = 1;
            q.push(u);
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : hk.adj[u]) {
            if (!visR[v] && hk.mv[v] != u) {
                visR[v] = 1;
                int u2 = hk.mv[v];
                if (u2 != -1 && !visL[u2]) {
                    visL[u2] = 1;
                    q.push(u2);
                }
            }
        }
    }
    vector<pair<int,int>> ops;
    for (int i = 0; i < n; i++) {
        if (!visL[i]) {
            ops.emplace_back(1, i+1);
        }
    }
    for (int j = 0; j < n; j++) {
        if (visR[j]) {
            ops.emplace_back(2, j+1);
        }
    }
 
    cout << ops.size() << "\n";
    for (auto [t, idx] : ops) {
        cout << t << " " << idx << "\n";
    }
}