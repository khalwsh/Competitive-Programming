/* problem statement text */
/*
CSES - New Flight Routes

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm flight connections between them. Your task is to add new flights so that it will be possible to travel from any city to any other city. What is the minimum number of new flights required?
Input
The first input line has two integers nnn and mmm: the number of cities and flights. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines describing the flights. Each line has two integers aaa and bbb: there is a flight from city aaa to city bbb. All flights are one-way flights.
Output
First print an integer kkk: the required number of new flights. After this, print kkk lines describing the new flights. You can print any valid solution.
Constraints

1≤n≤1051 \le n \le 10^51≤n≤105
1≤m≤2⋅1051 \le m \le 2 \cdot 10^51≤m≤2⋅105
1≤a,b≤n1 \le a,b \le n1≤a,b≤n

Example
Input:
4 5
1 2
2 3
3 1
1 4
3 4

Output:
1
4 2
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
const int N = 2e5 + 10;
vector<vector<int>> adj , dag , comps;
int comp[N] , inStack[N] , lowLink[N] , dfn[N] , in[N] , out[N];
stack<int> st;
int ndfn;
void tarjan(int u){
    dfn[u] = lowLink[u] = ndfn++;
    inStack[u] = true;
    st.push(u);
    for(auto &v : adj[u]){
        if(dfn[v] == -1){
            tarjan(v);
            lowLink[u] = min(lowLink[u] , lowLink[v]);
        }else if(inStack[v]){
            lowLink[u] = min(lowLink[u] , dfn[v]);
        }
    }
    if(dfn[u] == lowLink[u]){
        // head of component
        int x = -1;
        comps.emplace_back(vector<int>());
        while(x != u){
            x = st.top(); st.pop(); inStack[x] = 0;
            comps.back().emplace_back(x);
            comp[x] = (int)comps.size() - 1;
        }
    }
}
void genDag(){
    dag.resize(comps.size());
    for(int u = 0 ; u < adj.size() ; u++){
        for(auto &v :adj[u]){
            if(comp[u] != comp[v]){
                dag[comp[u]].emplace_back(comp[v]);
                in[comp[v]]++;
                out[comp[u]]++;
            }
        }
    }
}
 
void SCC(int n){
    ndfn = 0;
    comps.clear();
    for(int i=0;i<n;i++){
        dfn[i] = -1;
        lowLink[i] = inStack[i] = in[i] = 0;
    }
    for(int i = 0 ; i < n ; i++)
        if(dfn[i] == -1) tarjan(i);
    genDag();
}
struct HopcroftKarp {
    int n;
    vector<set<int>> adj;
    vector<int> mu, mv, dist;
 
    HopcroftKarp(int n , int m) : n(n), adj(n), mu(n, -1), mv(m, -1), dist(n) {}
 
    void add_edge(int u, int v) {
        adj[u].insert(v);
    }
 
    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; ++u) {
            if (mu[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (mv[v] == -1) {
                    found = true;
                }
                if (mv[v] != -1 && dist[mv[v]] == -1) {
                    dist[mv[v]] = dist[u] + 1;
                    q.push(mv[v]);
                }
            }
        }
        return found;
    }
 
    bool dfs(int u) {
        for (int v : adj[u]) {
            if (mv[v] == -1 || (dist[mv[v]] == dist[u] + 1 && dfs(mv[v]))) {
                mu[u] = v;
                mv[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }
 
    int max_matching() {
        int res = 0;
        while (bfs()) {
            for (int u = 0; u < n; ++u) {
                if (mu[u] == -1 && dfs(u)) {
                    res++;
                }
            }
        }
        return res;
    }
};
 
int main() {
    PRE();
    int n , m; cin >> n >> m;
    adj.resize(n);
    for (int i = 0;i < m;i++) {
        int u , v;cin >> u >> v;
        u-- ,v--;
        adj[u].emplace_back(v);
    }
    SCC(n);
    vector<int> srcs , sinks;
    for (int i = 0;i < comps.size();i++) {
        if (!in[i]) srcs.emplace_back(i);
        if (!out[i]) sinks.emplace_back(i);
    }
    vector<int> vis(n , 0);
    HopcroftKarp karp(comps.size() , comps.size() );
    function<void(int , int)> dfs = [&](int u , int src) {
        vis[u] = 1;
        if (!out[u]) {
            karp.add_edge(u , src);
            return;
        }
        for (auto &v : dag[u]) {
            if (vis[v] == 1) dfs(v , src);
        }
        vis[u] = 2;
    };
    for (auto &val : srcs) {
        dfs(val , val);
    }
    karp.max_matching();
    vector<pair<int , int>> e;
    for (auto &v : sinks) {
        if (karp.mu[v] == -1) {
            e.emplace_back(v , srcs[0]);
        }else {
            e.emplace_back(v , karp.mu[v]);
        }
    }
    for (auto &v : srcs) {
        if (karp.mv[v] == -1) {
            e.emplace_back(sinks[0] , v);
        }
    }
    sort(e.begin() , e.end());
    e.erase(unique(e.begin() , e.end()) , e.end());
    cout << e.size() << '\n';
    for (auto &[u , v] : e) {
        cout << comps[u].front() + 1 << " " << comps[v].front() + 1 << '\n';
    }
}