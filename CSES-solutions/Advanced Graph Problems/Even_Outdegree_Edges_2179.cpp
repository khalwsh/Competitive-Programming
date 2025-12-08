/* problem statement text */
/*
CSES - Even Outdegree Edges

Time limit: 1.00 s
Memory limit: 512 MB

Given an undirected graph, your task is to choose a direction for each edge so that in the resulting directed graph each node has an even outdegree. The outdegree of a node is the number of edges coming out of that node.
Input
The first input line has two integers nnn and mmm: the number of nodes and edges. The nodes are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines describing the edges. Each line has two integers aaa and bbb: there is an edge between nodes aaa and bbb.
You may assume that the graph is simple, i.e., there is at most one edge between any two nodes and every edge connects two distinct nodes.
Output
Print mmm lines describing the directions of the edges. Each line has two integers aaa and bbb: there is an edge from node aaa to node bbb. You can print any valid solution.
If there are no solutions, only print IMPOSSIBLE.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
4 4
1 2
2 3
3 4
1 4

Output:
1 2
3 2
3 4
1 4
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
vector<int> graph[100001];
int visited[100001], odd[100001], timer = 1;
vector<pair<int, int>> ans;
 
void dfs(int node, int parent = 0) {
    visited[node] = timer++;
    for (int i : graph[node])
        if (i != parent) {
            if (!visited[i]) {
                dfs(i, node);
                if (odd[i]) {
                    ans.push_back({i, node});
                    odd[i] = 0;
                } else {
                    ans.push_back({node, i});
                    odd[node] ^= 1;
                }
            } else if (visited[node] > visited[i]) {
                ans.push_back({node, i});
                odd[node] ^= 1;
            }
        }
}
 
int main() {
    PRE();
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
        if (!visited[i]) dfs(i);
    if (accumulate(odd + 1, odd + n + 1, 0)) printf("IMPOSSIBLE");
    else
        for (pair<int, int> i : ans) cout << i.first << " " << i.second << '\n';
}