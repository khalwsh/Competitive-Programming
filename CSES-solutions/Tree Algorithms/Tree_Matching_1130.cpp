/* problem statement text */
/*
CSES - Tree Matching

Time limit: 1.00 s
Memory limit: 512 MB

You are given a tree consisting of nnn nodes.
A matching is a set of edges where each node is an endpoint of at most one edge. What is the maximum number of edges in a matching?
Input
The first input line contains an integer nnn: the number of nodes. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n.
Then there are n−1n-1n−1 lines describing the edges. Each line contains two integers aaa and bbb: there is an edge between nodes aaa and bbb.
Output
Print one integer: the maximum number of pairs.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5
1 2
1 3
3 4
3 5

Output:
2

Explanation: One possible matching is (1,2)(1,2)(1,2) and (3,4)(3,4)(3,4).
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
 
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
const int N = 3e5 + 1;
vector<int>adj[N];
int f[N] , g[N]; // f[i] : maximum number of nodes in the sub tree of i including i
                 // g[i] : maximum number of nodes in the sub tree of i not including i
void dfs(int u , int p) {
    // cout<<u<<endl;
    for (auto &v : adj[u]) {
        if (v != p) dfs(v , u);
    }
    for (auto &v : adj[u]) {
        if (v != p) {
            g[u] += max(f[v] , g[v]);
        }
    }
    for (auto &v : adj[u]) {
        if (v != p) {
            f[u] = max(f[u] , g[v] + 1 + g[u] - max(f[v] , g[v]));
        }
    }
}
int main() {
    PRE();
    int n;cin>>n;
    for (int i = 1;i < n;i++) {
        int u , v;cin>>u>>v;u-- , v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(0 , -1);
    cout<<max(f[0] , g[0]);
}