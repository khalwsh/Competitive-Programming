/* problem statement text */
/*
CSES - Reachable Nodes

Time limit: 1.00 s
Memory limit: 512 MB

A directed acyclic graph consists of nnn nodes and mmm edges. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
Calculate for each node the number of nodes you can reach from that node (including the node itself).
Input
The first input line has two integers nnn and mmm: the number of nodes and edges.
Then there are mmm lines describing the edges. Each line has two distinct integers aaa and bbb: there is an edge from node aaa to node bbb.
Output
Print nnn integers: for each node the number of reachable nodes.
Constraints

1≤n≤5⋅1041 \le n \le 5 \cdot 10^41≤n≤5⋅104
1≤m≤1051 \le m \le 10^51≤m≤105

Example
Input:
5 6
1 2
1 3
1 4
2 3
3 5
4 5

Output:
5 3 2 2 1
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e4 + 1;
bitset<N>adj[N];
vector<int>graph[N];
int in[N];
int n , m;
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i = 0;i < m;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        graph[u].emplace_back(v);
        in[v]++;
    }
    queue<int>nodes;
    for(int i = 0;i < n;i++) {
        if(!in[i])nodes.push(i);
    }
    vector<int>topo;
    topo.reserve(n);
    while(!nodes.empty()) {
        int node = nodes.front();
        nodes.pop();
        topo.emplace_back(node);
        for(auto &val:graph[node]) {
            if(!--in[val])nodes.push(val);
        }
    }
    // reverse(topo.begin() , topo.end())
    for(int i = n - 1;i >= 0;i--) {
        adj[topo[i]][topo[i]] = true;
        for(auto &val:graph[topo[i]]) {
            adj[topo[i]] |= adj[val];
        }
    }
    for(int i = 0;i < n;i++)cout<<adj[i].count()<<" ";
}