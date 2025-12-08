/* problem statement text */
/*
CSES - Finding a Centroid

Time limit: 1.00 s
Memory limit: 512 MB

Given a tree of nnn nodes, your task is to find a centroid, i.e., a node such that when it is appointed the root of the tree, each subtree has at most ⌊n/2⌋\lfloor n/2 \rfloor⌊n/2⌋ nodes.
Input
The first input line contains an integer nnn: the number of nodes. The nodes are numbered 1,2,…,n1,2,…,n1,2,…,n.
Then there are n−1n-1n−1 lines describing the edges. Each line contains two integers aaa and bbb: there is an edge between nodes aaa and bbb.
Output
Print one integer: a centroid node. If there are several possibilities, you can choose any of them.
Constraints

1≤n≤2⋅1051 \le n \le 2 \cdot 10^51≤n≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
5
1 2
2 3
3 4
3 5

Output:
3
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
const int N = 2e5 + 10;
vector<int>adj[N];
int centriod = 0;
int siz[N];
void dfs1(int node , int par) {
    siz[node] = 1;
    for(auto &val:adj[node]) {
        if(val == par)continue;
        dfs1(val , node);
        siz[node] += siz[val];
    }
}
int dfs2(int node , int par) {
    for(auto &val:adj[node]) {
        if(val == par)continue;
        if(siz[val] > n / 2) {
            return dfs2(val , node);
        }
    }
    return node;
}
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i = 1;i < n;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs1(0 , -1);
    centriod = dfs2(0 , -1);
    cout<<centriod + 1<<'\n';
}