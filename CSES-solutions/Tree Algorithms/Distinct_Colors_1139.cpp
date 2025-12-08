/* problem statement text */
/*
CSES - Distinct Colors

Time limit: 1.00 s
Memory limit: 512 MB

You are given a rooted tree consisting of nnn nodes. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n, and node 111 is the root. Each node has a color.
Your task is to determine for each node the number of distinct colors in the subtree of the node.
Input
The first input line contains an integer nnn: the number of nodes. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n.
The next line consists of nnn integers c1,c2,…,cnc_1,c_2,\ldots,c_nc1​,c2​,…,cn​: the color of each node.
Then there are n−1n-1n−1 lines describing the edges. Each line contains two integers aaa and bbb: there is an edge between nodes aaa and bbb.
Output
Print nnn integers: for each node 1,2,…,n1,2,\ldots,n1,2,…,n, the number of distinct colors.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n
1≤ci≤1091 \le c_i \le 10^91≤ci​≤109

Example
Input:
5
2 3 2 2 1
1 2
1 3
3 4
3 5

Output:
3 1 2 1 1
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
const int N = 2e5 + 10;
int v[N] , ans[N] , sz[N];
vector<int>adj[N];
set<int>colors[N];
 
void dfs(int u , int p) {
    sz[u] = 1;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        dfs(v , u);
        sz[u] += sz[v];
    }
    int bg = -1;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        if (bg == -1 || sz[bg] < sz[v]) bg = v;
    }
    if (bg != -1)
        swap(colors[u] , colors[bg]);
    colors[u].insert(v[u]);
    for (auto &v : adj[u]) {
        if (v == p || v == bg)continue;
        for (auto &val : colors[v]) colors[u].insert(val);
    }
    ans[u] = colors[u].size();
}
int main() {
    PRE();
    int n;cin>>n;
    for (int i = 0;i < n;i++) cin >> v[i];
    for (int i = 0;i < n - 1;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        adj[u].emplace_back(v);
        swap(u , v);
        adj[u].emplace_back(v);
    }
    dfs(0 , -1);
    for (int i = 0;i < n;i++) {
        cout<<ans[i]<<" ";
    }
}