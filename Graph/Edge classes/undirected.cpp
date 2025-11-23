// if you want to extract edges do it after you run dfs
// because you traverse edge more than 1 time so it can be duplicated
// so run then check if (tin[u] < tin[b]) tree edge otherwise backward edge
const int N = 3e5 + 5;
vector<int> adj[N];
vector<pair<int,int>> e;
int tin[N];
bool vis[N];
int timer = 0;

// if duplication matter make sure before do any classifier 
// this edge is not used before with any direction
// the first one is the correct one
set<pair<int , int>> seen; 
void dfs(int u , int p = -1) {
    vis[u] = true;
    tin[u] = ++timer;
    for (int v : adj[u]) {
        if (vis[v] && tin[u] < tin[v]) {
            // forward edge
            continue;
        }
        if (!vis[v]) {
            // tree edge
            dfs(v , u);
        } else if (v != p) {
            // backword edge
        }
    }
}