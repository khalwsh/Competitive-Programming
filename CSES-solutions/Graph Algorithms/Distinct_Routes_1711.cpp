/* problem statement text */
/*
CSES - Distinct Routes

Time limit: 1.00 s
Memory limit: 512 MB

A game consists of nnn rooms and mmm teleporters. At the beginning of each day, you start in room 111 and you have to reach room nnn.
You can use each teleporter at most once during the game. How many days can you play if you choose your routes optimally?
Input
The first input line has two integers nnn and mmm: the number of rooms and teleporters. The rooms are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines describing the teleporters. Each line has two integers aaa and bbb: there is a teleporter from room aaa to room bbb.
There are no two teleporters whose starting and ending room are the same.
Output
First print an integer kkk: the maximum number of days you can play the game. Then, print kkk route descriptions according to the example. You can print any valid solution.
Constraints

2≤n≤5002 \le n \le 5002≤n≤500
1≤m≤10001 \le m \le 10001≤m≤1000
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
6 7
1 2
1 3
2 6
3 4
3 5
4 6
5 6

Output:
2
3
1 2 6
4
1 3 4 6
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
    vector<pair<vector<int>, ll>> extract_paths() {
        vector<pair<vector<int>, ll>> paths;
        vector<int> parent_edge(n);
 
        function<ll(int, vector<vector<pair<int,int>>>&)> dfs2 =
        [&](int v, vector<vector<pair<int,int>>>& g) -> ll {
            if (v == t) return LLONG_MAX;
            for (auto &pr : g[v]) {
                int u = pr.first, id = pr.second;
                if (edges[id].flow <= 0) continue;
                if (parent_edge[u] == -1) {
                    parent_edge[u] = id;
                    ll pushed = dfs2(u, g);
                    if (pushed > 0) {
                        return min(pushed, edges[id].flow);
                    }
                }
            }
            return 0LL;
        };
 
        while (true) {
            vector<vector<pair<int,int>>> g(n);
            for (int id = 0; id < m; id += 2) {
                if (edges[id].flow > 0) {
                    g[edges[id].v].emplace_back(edges[id].u, id);
                }
            }
 
            fill(parent_edge.begin(), parent_edge.end(), -1);
            parent_edge[s] = -2;
            ll pushed = dfs2(s, g);
            if (pushed == 0) break;
 
            vector<int> path;
            int v = t;
            while (v != s) {
                int id = parent_edge[v];
                path.push_back(v);
                edges[id].flow -= pushed;
                edges[id ^ 1].flow += pushed;
                v = edges[id].v;
            }
            path.push_back(s);
            reverse(path.begin(), path.end());
            paths.emplace_back(path, pushed);
        }
        return paths;
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
    }
    cout<<flow.flow()<<'\n';
    auto res = flow.extract_paths();
    for (auto &val : res) {
        cout<<val.first.size()<<"\n";
        for (auto &x : val.first)
            cout<< x + 1 <<" ";
        cout<<"\n";
    }
}