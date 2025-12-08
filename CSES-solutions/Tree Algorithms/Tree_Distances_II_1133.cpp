/* problem statement text */
/*
CSES - Tree Distances II

Time limit: 1.00 s
Memory limit: 512 MB

You are given a tree consisting of nnn nodes.
Your task is to determine for each node the sum of the distances from the node to all other nodes.
Input
The first input line contains an integer nnn: the number of nodes. The nodes are numbered 1,2,…,n1,2,\ldots,n1,2,…,n.
Then there are n−1n-1n−1 lines describing the edges. Each line contains two integers aaa and bbb: there is an edge between nodes aaa and bbb.
Output
Print nnn integers: for each node 1,2,…,n1,2,\ldots,n1,2,…,n, the sum of the distances.
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
6 9 5 8 8
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
const int N = 3e5 + 10;
int n;
int s[N];
vector<int>adj[N];
ll sum = 0;
ll ans[N];
void dfs1(int u , int p , int cur = 0) {
    s[u] = 1;
    sum += cur;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        dfs1(v , u , cur + 1);
        s[u] += s[v];
    }
}
void dfs2(int u , int p) {
    ans[u] = sum;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        int subtree = s[v];
        int out = n - s[v];
        sum += out - subtree;
        dfs2(v , u);
        sum -= out - subtree;
    }
}
int main() {
    PRE();
    cin>>n;
    for (int i = 0;i < n - 1;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs1(0 , -1);
    dfs2(0 , -1);
    for (int i = 0;i < n;i++)
        cout<<ans[i]<<" ";
}