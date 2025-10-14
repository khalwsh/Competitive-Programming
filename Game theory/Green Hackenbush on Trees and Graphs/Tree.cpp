const int N = 2e5 + 1;
vector<int> adj[N];

int dfs(int u, int p) {
    int g = 0;
    for (int v: adj[u]) if (v != p) g ^= (dfs(v, u) + 1);
    return g;
}