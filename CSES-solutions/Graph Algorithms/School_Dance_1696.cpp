/* problem statement text */
/*
CSES - School Dance

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn boys and mmm girls in a school. Next week a school dance will be organized. A dance pair consists of a boy and a girl, and there are kkk potential pairs.
Your task is to find out the maximum number of dance pairs and show how this number can be achieved.
Input
The first input line has three integers nnn, mmm and kkk: the number of boys, girls, and potential pairs. The boys are numbered 1,2,…,n1,2,\dots,n1,2,…,n, and the girls are numbered 1,2,…,m1,2,\dots,m1,2,…,m.
After this, there are kkk lines describing the potential pairs. Each line has two integers aaa and bbb: boy aaa and girl bbb are willing to dance together.
Output
First print one integer rrr: the maximum number of dance pairs. After this, print rrr lines describing the pairs. You can print any valid solution.
Constraints

1≤n,m≤5001 \le n,m \le 5001≤n,m≤500
1≤k≤10001 \le k \le 10001≤k≤1000
1≤a≤n1 \le a \le n1≤a≤n
1≤b≤m1 \le b \le m1≤b≤m

Example
Input:
3 2 4
1 1
1 2
2 1
3 1

Output:
2
1 2
3 1
*/
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
 
const int INF = 1e9; // Infinity value for unmatched nodes
 
// BFS Phase to build layers
bool bfs(int n, int m, vector<vector<int>>& adj, vector<int>& pairU, vector<int>& pairV, vector<int>& dist) {
    queue<int> q;
 
    // Initialize distances
    for (int u = 1; u <= n; ++u) {
        if (pairU[u] == 0) { // If the boy is unmatched
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[0] = INF; // Sentinel for unmatched nodes
 
    // Perform BFS
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dist[u] < dist[0]) { // Check all neighbors
            for (int v : adj[u]) {
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
 
    return dist[0] != INF; // Returns true if there's an augmenting path
}
 
// DFS Phase to find augmenting paths
bool dfs(int u, vector<vector<int>>& adj, vector<int>& pairU, vector<int>& pairV, vector<int>& dist) {
    if (u != 0) { // Sentinel check
        for (int v : adj[u]) {
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v], adj, pairU, pairV, dist)) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}
 
// Hopcroft-Karp Algorithm
vector<pair<int , int>> hopcroftKarp(int n, int m, vector<vector<int>>& adj) {
    // graph should be 1 based
    vector<int> pairU(n + 1, 0); // Pairings for boys
    vector<int> pairV(m + 1, 0); // Pairings for girls
    vector<int> dist(n + 1);     // Distance array for BFS
 
    int matching = 0;
 
    // Repeat until no augmenting path exists
    while (bfs(n, m, adj, pairU, pairV, dist)) {
        for (int u = 1; u <= n; ++u) {
            if (pairU[u] == 0 && dfs(u, adj, pairU, pairV, dist)) {
                ++matching;
            }
        }
    }
 
    // Output the matches
    vector<pair<int , int>>matches;
    for (int v = 1; v <= m; ++v) {
        if (pairV[v] != 0) {
            matches.emplace_back(pairV[v] , v);
        }
    }
 
    return matches;
}
 
int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
 
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }
 
    // Call the Hopcroft-Karp algorithm
    auto res = hopcroftKarp(n, m, adj);
    cout<<res.size()<<"\n";
    for(auto &val:res)cout<<val.first<<" "<<val.second<<'\n';
    return 0;
}