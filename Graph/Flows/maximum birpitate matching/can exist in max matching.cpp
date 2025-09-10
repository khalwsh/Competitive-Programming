// max N is > n + m + 10 , you can build matching faster using Hopcroft karp
const int N = 1010;
int scc[N] , dfn[N] , low[N] , snt , dnt;
int st[N] , top;
bool vis[ N];
int ma[N] , lk[N];
vector<int>g[N] , g2[N];
int dfs(int x) {
    for (int i : g[x]) {
        if (!vis[i]) {
            vis[i] = 1;
            if (ma[i] == 0 || dfs(ma[i])) {
                return ma[i] = x , 1;
            }
        }
    }
    return 0;
}
void tarjan(int u) {
    dfn[u] = low[u] = ++dnt;
    st[top++] = u , vis[u] = 1;
    for (int i : g2[u]) {
        if (!dfn[i]) {
            tarjan(i) , low[u] = min(low[u] , low[i]);
        }else if (vis[i]) low[u] = min(low[u] , dfn[i]);
    }
    if (low[u] == dfn[u]) {
        for (int v = -1; v!= u;) {
            v = st[--top];
            vis[v] = 0;
            scc[v] = u;
        }
    }
}
vector<vector<int>> solve(int n , int m , vector<pair<int , int>> &relations) {
    snt = dnt = top = 0;
    for (int i = 0;i <= n + m + 10;i++) {
        ma[i] = lk[i] = dfn[i] = low[i] = scc[i] = 0;
    }
    for (int i = 1; i <= n;i++) {
        g[i].clear(); g2[i].clear();
    }
    for (auto &[l , r] : relations) {
        g[l].emplace_back(r);
    }
    for (int i = 1;i <= n;i++) {
        for (int j = 0;j <= n + m + 10;j++)
            vis[j] = 0;
        dfs(i);
    }
    for (int i = 1;i <= m;i++) lk[ma[i]] = i;
    for (int i = 0;i <= n + m + 1;i++) g2[i].clear();
    for (int i = 1;i <= n;i++) {
        g2[0].emplace_back(i);
        for (int j : g[i]) g2[i].push_back(n + j);
    }
    for (int i = 1;i <= m;i++) {
        g2[n + i].emplace_back(ma[i]) , g2[n + i].emplace_back(n + m + 1);
    }
    for (int i = 1;i <= n;i++) {
        if (!lk[i]) g2[m + n + 1].push_back(i);
    }
    for (int j = 0;j <= n + m + 10;j++)
        vis[j] = 0;
    for (int i = 1;i <= n + m + 1;i++) if (!dfn[i]) tarjan(i);
    vector<vector<int>>ans;
    ans.emplace_back(vector<int>{});
    for (int i = 1;i <= n;++i) {
        vector<int>temp;
        for (int j : g[i]) {
            if (scc[i] == scc[n + j]) temp.emplace_back(j);
        }
        sort(temp.begin() , temp.end());
        ans.emplace_back(temp);
    }
    return ans;
}