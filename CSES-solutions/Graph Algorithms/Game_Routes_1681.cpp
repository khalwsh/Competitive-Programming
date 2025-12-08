/* problem statement text */
/*
CSES - Game Routes

Time limit: 1.00 s
Memory limit: 512 MB

A game has nnn levels, connected by mmm teleporters, and your task is to get from level 111 to level nnn. The game has been designed so that there are no directed cycles in the underlying graph. In how many ways can you complete the game?
Input
The first input line has two integers nnn and mmm: the number of levels and teleporters. The levels are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines describing the teleporters. Each line has two integers aaa and bbb: there is a teleporter from level aaa to level bbb.
Output
Print one integer: the number of ways you can complete the game. Since the result may be large, print it modulo 109+710^9+7109+7.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
4 5
1 2
2 4
1 3
3 4
1 4

Output:
3
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
void PRE() {
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
}
const int N = 3e5 + 1;
vector<int>adj[N];
int in[N] , dp[N];
const int mod = 1e9 + 7;
int main() {
    PRE();
    int m;
    int n;cin>>n>>m;
    for (int i = 0;i < m;i++) {
        int u , v;cin>>u>>v;u-- , v--;
        adj[u].emplace_back(v);
        in[v]++;
    }
    vector<int>topo;
    queue<int>q;
    for (int i = 0;i < n;i++) {
        if (!in[i]) {
            q.push(i);
        }
    }
    while (q.size()) {
        int node = q.front();q.pop();
        topo.push_back(node);
        for (auto &val:adj[node]) {
            if (--in[val] == 0) {
                q.push(val);
            }
        }
    }
    dp[n - 1] = 1;
    for (int i = topo.size() - 1;i >= 0;i--) {
        for (auto &v : adj[topo[i]]) {
            dp[topo[i]] += dp[v];
            dp[topo[i]] %= mod;
        }
    }
    cout<<dp[0]<<'\n';
}