/* problem statement text */
/*
CSES - Flight Routes Check

Time limit: 1.00 s
Memory limit: 512 MB

There are nnn cities and mmm flight connections. Your task is to check if you can travel from any city to any other city using the available flights.
Input
The first input line has two integers nnn and mmm: the number of cities and flights. The cities are numbered 1,2,…,n1,2,\dots,n1,2,…,n.
After this, there are mmm lines describing the flights. Each line has two integers aaa and bbb: there is a flight from city aaa to city bbb. All flights are one-way flights.
Output
Print "YES" if all routes are possible, and "NO" otherwise. In the latter case also print two cities aaa and bbb such that you cannot travel from city aaa to city bbb. If there are several possible solutions, you can print any of them.
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
NO
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
 
void sol(int n , vector<int> adj[] , int m) {
    vector<vector<int>> dag , comps;
    const int N = n;
    int comp[N] , inStack[N] , lowLink[N] , dfn[N] , deg[N];
    stack<int> st;
    int ndfn;
    function<void(int)> tarjan = [&](int u){
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
    };
    auto genDag = [&](){
        dag.resize(comps.size());
        for(int u = 0 ; u < n ; u++){
            for(auto &v :adj[u]){
                if(comp[u] != comp[v]){
                    dag[comp[u]].emplace_back(comp[v]);
                    deg[comp[v]]++;
                }
            }
        }
    };
    auto SCC = [&](int n){
        ndfn = 0;
        comps.clear();
        for(int i=0;i<n;i++){
            dfn[i] = -1;
            lowLink[i] = inStack[i] = deg[i] = 0;
        }
        for(int i = 0 ; i < n ; i++)
            if(dfn[i] == -1) tarjan(i);
        genDag();
    };
    SCC(n);
    if(comps.size() != 1){
        cout<<comps[0].front() + 1<<" "<<comps[1].front() + 1<<'\n';
    }
}
 
const int N = 200000 + 10;
int n, m;
vector<int> adj[N], radj[N];
int in[N], out[N];
vector<int> tour;
 
void dfs1(int s, const vector<int> g[], vector<char> &vis) {
    stack<int> st;
    st.push(s);
    vis[s] = 1;
    while (!st.empty()) {
        int v = st.top(); st.pop();
        for (int u : g[v]) {
            if (!vis[u]) {
                vis[u] = 1;
                st.push(u);
            }
        }
    }
}
 
void dfs2(int v) {
    while (!adj[v].empty()) {
        int u = adj[v].back();
        adj[v].pop_back();
        dfs2(u);
    }
    tour.push_back(v);
}
 
bool get() {
    for (int i = 0; i < n; ++i) {
        if (in[i] != out[i]) return false;
    }
 
    int start = -1;
    for (int i = 0; i < n; ++i) {
        if (out[i] > 0) { start = i; break; }
    }
    if (start == -1) {
        tour = {0};
        return (m == 0);
    }
    vector<char> vis(n, 0);
    dfs1(start, adj, vis);
    for (int i = 0; i < n; ++i)
        if ((in[i] + out[i]) > 0 && !vis[i]) return false;
 
    fill(vis.begin(), vis.end(), 0);
    dfs1(start, radj, vis);
    for (int i = 0; i < n; ++i)
        if ((in[i] + out[i]) > 0 && !vis[i]) return false;
 
    tour.clear();
    dfs2(start);
    reverse(tour.begin(), tour.end());
    if ((int)tour.size() != m + 1) return false;
    return true;
}
 
int main() {
    PRE();
    cin >> n >> m;
    for (int i = 0;i < m;i++) {
        int u , v;cin >> u >> v;
        u-- , v--;
        adj[u].emplace_back(v);
        radj[v].emplace_back(u);
        in[v]++ , out[u]++;
    }
    if (!get()) {
        cout << "NO\n";
        sol(n , adj , m);
    }else {
        cout << "YES\n";
    }
}