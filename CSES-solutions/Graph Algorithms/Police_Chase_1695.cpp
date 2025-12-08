/* problem statement text */
/*
CSES - Police Chase

Time limit: 1.00 s
Memory limit: 512 MB

Kaaleppi has just robbed a bank and is now heading to the harbor. However, the police wants to stop him by closing some streets of the city.
What is the minimum number of streets that should be closed so that there is no route between the bank and the harbor?
Input
The first input line has two integers nnn and mmm: the number of crossings and streets. The crossings are numbered 1,2,…,n1,2,\dots,n1,2,…,n. The bank is located at crossing 111, and the harbor is located at crossing nnn.
After this, there are mmm lines that describing the streets. Each line has two integers aaa and bbb: there is a street between crossings aaa and bbb. All streets are two-way streets, and there is at most one street between two crossings.
Output
First print an integer kkk: the minimum number of streets that should be closed. After this, print kkk lines describing the streets. You can print any valid solution.
Constraints

2≤n≤5002 \le n \le 5002≤n≤500
1≤m≤10001 \le m \le 10001≤m≤1000
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
4 5
1 2
1 3
2 3
3 4
1 4

Output:
2
3 4
1 4
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
// O(V^2 E) and in unit graph works in O(E sqrt(v))
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};
struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;
 
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }
 
    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }
 
    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap == edges[id].flow)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }
 
    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u])
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }
 
    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
    // After max-flow, find min-cut edges: edges from reachable to non-reachable
    vector<pair<int,int>> min_cut_edges() {
        vector<char> visited(n, false);
        queue<int> qu;
        qu.push(s);
        visited[s] = true;
        // BFS on residual graph
        while (!qu.empty()) {
            int v = qu.front(); qu.pop();
            for (int id : adj[v]) {
                if (edges[id].flow == edges[id].cap) continue; // no residual capacity
                int u = edges[id].u;
                if (!visited[u]) {
                    visited[u] = true;
                    qu.push(u);
                }
            }
        }
        vector<pair<int,int>> cut;
        // original edges are at even indices
        for (int id = 0; id < m; id += 2) {
            const auto &e = edges[id];
            if (visited[e.v] && !visited[e.u] && e.cap > 0) {
                cut.emplace_back(e.v, e.u);
            }
        }
        return cut;
    }
};
 
int main() {
    PRE();
    int n , m;cin>>n>>m;
    Dinic flow(n , 0 , n - 1);
    for (int i = 0;i < m;i++) {
        int u , v;cin>>u>>v;
        u-- , v--;
        flow.add_edge(u , v , 1);
        flow.add_edge(v , u , 1);
    }
    cout<<flow.flow()<<'\n';
    auto res = flow.min_cut_edges();
    for (auto &val : res) {
        cout<<val.first + 1<<" "<<val.second + 1<<'\n';
    }
 
}