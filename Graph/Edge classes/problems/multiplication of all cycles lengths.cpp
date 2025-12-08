// all cycles must be simple
const int N = 3e5 + 5;
vector<int> adj[N];
int tin[N] , depth[N];
bool vis[N];
int timer = 0;
__int128 dfs(int u , int p = -1) {
    vis[u] = true;
    tin[u] = ++timer;
    depth[u] = (p == -1 ? 1 : depth[p] + 1);
    __int128 res = 1;
    for (int v : adj[u]) {
        if (vis[v] && tin[u] < tin[v]) {
            // forward edge
            // res *= (depth[u] - depth[v] + 1);
            continue;
        }
        if (!vis[v]) {
            // tree edge
            res *= dfs(v , u);
        } else if (v != p) {
            // backword edge
            res *= (depth[u] - depth[v] + 1);
        }
    }
    return res;
}