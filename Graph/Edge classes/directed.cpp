const int N = 3e5 + 5;
vector<int> adj[N];
int tin[N] , tout[N];
bool vis[N];
int timer = 0;

void dfs(int u , int p = -1) {
    vis[u] = true;
    tin[u] = ++timer;
    for (int v : adj[u]) {
        if (!vis[v]) {
            // tree edge

	    // dfs here
        }
        else {
            if (tin[v] < tin[u] && tout[v] == 0){
                // back edge
            }
            else if (tin[v] > tin[u] && tout[v] != 0) {
                // forward edge
            }
            else if (tin[v] < tin[u] && tout[v] != 0) {
                // cross edge
            }
        }
    }
    tout[u] = ++timer;
}