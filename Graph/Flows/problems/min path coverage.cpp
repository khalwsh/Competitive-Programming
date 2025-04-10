#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = array<int, 4>; // node , normal or redusinal , size when added , index

vector<Edge> adj[505];
int vis[505];
int n;

int dfs(int s, int f) {
    if (s == n) return f;
    vis[s] = 1;
    for (auto &[i, w, j, m] : adj[s]) {
        if (w > 0 && !vis[i]) {
            int b = dfs(i, 1);
            if (b > 0) {
                w -= b;
                adj[i][j][1] += b;
                return b;
            }
        }
    }
    return 0;
}

void solve() {
    int m;
    cin >> n >> m;
    while (m--) {
        int x, y;
        cin >> x >> y;
        int j1 = adj[y].size();
        int j2 = adj[x].size();
        adj[x].push_back({y, 1, j1, m + 1});
        adj[y].push_back({x, 0, j2, -m - 1});
    }

    int ans = 0;
    while (true) {
        memset(vis, 0, sizeof(vis));
        int f = dfs(1, 1);
        ans += f;
        if (!f) break;
    }

    cout << ans << '\n';

    bool visitedEdges[1005] = {0};
    for (int i = 0; i < ans; i++) {
        vector<int> path = {1};
        int x = 1;
        while (x != n) {
            for (auto &[i, w, j, m] : adj[x]) {
                if (w == 0 && m > 0 && !visitedEdges[m]) {
                    path.push_back(i);
                    x = i;
                    visitedEdges[m] = 1;
                    break;
                }
            }
        }
        cout << path.size() << '\n';
        for (int node : path) cout << node << " ";
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
