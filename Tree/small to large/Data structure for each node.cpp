const int N = 1e5 + 10;
vector<int>adj[N];
int bg[N] , sz[N] , ans[N] , n;

void dfs1(int u , int p) {
    bg[u] = -1;
    sz[u] = 1;
    for (auto &v : adj[u]) {
        if (v == p)continue;
        dfs1(v , u);
        sz[u] += sz[v];
        if (bg[u] == -1 || sz[bg[u]] < sz[v]) {
            bg[u] = v;
        }
    }
}
void dfs2(int u , int p) {
    for (auto &v : adj[u]) {
        if (v == p)continue;
        dfs2(v , u);
    }
    if (bg[u] != -1) {
        // swap your data with your big child : swap(freq[u] , freq[bg[u]])
    }
    
    // insert yourself : freq[c[u]]++

    for (auto &v : adj[u]) {
        if (v == p || v == bg[u])continue;
        // merge your data structure with your child data structure
    }
    // calculate answer
}