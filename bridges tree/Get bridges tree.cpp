int n,m;
vector<pair<int,int>> adj[N] , edges;
vector<int> BridgeTree[N];
int lowLink[N] , dfn[N] , comp[N] , ndfn , comp_num;
bool isBridge[N];//max M
bool  vis[N];
void tarjan(int u , int par) {
    dfn[u] = lowLink[u] = ndfn++;
    for (auto &[v, id]: adj[u]) {
        if (dfn[v] == -1) {
            tarjan(v, u);
            lowLink[u] = min(lowLink[u], lowLink[v]);
            if (lowLink[v] == dfn[v]) {
                int uu = u, vv = v;
                if (uu > vv) swap(uu, vv);
                isBridge[id] = true;
            }
        } else if (v != par) {
            lowLink[u] = min(lowLink[u], dfn[v]);
        }
    }
}
void Find_component(int u , int par) {
    vis[u] = true;
    comp[u] = comp_num;
    for (auto &[v, id]: adj[u])
        if (vis[v] == 0 && isBridge[id] == 0)
            Find_component(v, u);
}
void GetBridgesTree() {
    for (int i = 0; i < n; i++) {
        dfn[i] = -1;
        lowLink[i] = 0;
    }
    ndfn = 0;
    tarjan(0, 0);
    for (int i = 0; i < n; i++)
        if (vis[i] == 0) {
            Find_component(i, i);
            comp_num++;
        }
    for (int i = 0; i < m; i++) {
        if (isBridge[i]) {
            BridgeTree[comp[edges[i].first]].emplace_back(comp[edges[i].second]);
            BridgeTree[comp[edges[i].second]].emplace_back(comp[edges[i].first]);
        }
    }
}
