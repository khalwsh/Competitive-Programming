const int N = 1e5+9 , LOG = 20;
vector<int> adj[N];
int up[N][LOG] , dep[N];
 
void dfs(int u, int p){
    dep[u] = dep[p] + 1;
 
    up[u][0] = p;
    for(int x = 1; x < LOG; ++x){
        up[u][x] = up[ up[u][x-1] ][x-1];
    }
    for(auto &v : adj[u]) if(v != p){
        dfs(v,u);
    }
}
 
int go_up(int u, ll k) {
    for (int x = 0; x < LOG; ++x) if (k>>x&1) {
        u =  up[u][x];
    }
    return u;
}
 
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u,v);
    // Lift the deeper node 'u' up by the difference in depths.
    u = go_up(u, dep[u] - dep[v]);
    if (u == v) return u;
    for (int x = LOG-1; x >= 0; --x) if (up[u][x] != up[v][x]) {
        u = up[u][x];
        v = up[v][x];
    }
    return  up[u][0];
}
 
int dis(int u ,int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u,v)];
}
 
int kth(int u, int v, int k) {
    int L = lca(u,v);
    int d_u_L = dep[u] - dep[L];
    --k;
 
    if (d_u_L >= k) {
        return go_up(u , k);
    }
 
    k -= d_u_L;
    int d_v_L = dep[v] - dep[L];
    return go_up(v, d_v_L - k);
}