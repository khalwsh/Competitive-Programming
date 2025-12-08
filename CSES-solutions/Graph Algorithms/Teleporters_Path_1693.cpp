/* problem statement text */
/*
CSES - Teleporters Path

Time limit: 1.00 s
Memory limit: 512 MB

A game has nnn levels and mmm teleportes between them. You win the game if you move from level 111 to level nnn using every teleporter exactly once.
Can you win the game, and what is a possible way to do it?
Input
The first input line has two integers nnn and mmm: the number of levels and teleporters. The levels are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Then, there are mmm lines describing the teleporters. Each line has two integers aaa and bbb: there is a teleporter from level aaa to level bbb.
You can assume that each pair (a,b)(a,b)(a,b) in the input is distinct.
Output
Print m+1m+1m+1 integers: the sequence in which you visit the levels during the game. You can print any valid solution.
If there are no solutions, print "IMPOSSIBLE".
Constraints

2≤n≤1052 \le n \le 10^52≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5 6
1 2
1 3
2 4
2 5
3 1
4 2

Output:
1 3 1 2 4 2 5
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
const int N = 2e5 + 10;
 
int n, m;
vector<int> adj[N];
vector<int> tour;
int in[N], out[N];
int Start = -1, End = -1;
 
bool euler() {
    for (int i = 0; i < n; i++) {
        if (abs(in[i] - out[i]) > 1)
            return false;
 
        if (in[i] == out[i] + 1) {
            if (End != -1) return false;
            End = i;
        }
 
        if (out[i] == in[i] + 1) {
            if (Start != -1) return false;
            Start = i;
        }
    }
    return true;
}
 
void dfs(int node) {
    while (out[node]) {
        dfs(adj[node][--out[node]]);
    }
    tour.emplace_back(node);
}
 
bool get() {
    if (!euler())
        return false;
 
    dfs(Start);
 
    if ((int)tour.size() != m + 1)
        return false;
 
    reverse(tour.begin(), tour.end());
    return true;
}
 
int main() {
    PRE();
    cin >> n >> m;
    for (int i = 0;i < m;i++) {
        int u , v;cin >> u >> v;
        u-- , v--;
        adj[u].emplace_back(v);
        in[v]++ , out[u]++;
    }
    if (!get() || Start != 0 || End != n - 1) {
        cout << "IMPOSSIBLE";
    }else {
        for (auto &val : tour) cout << ++val << " ";
    }
}