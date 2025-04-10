void LongestPath(vector<vector<int>>&adj,int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adj[i][j] = max(adj[i][j], max(adj[i][k], adj[k][j]));
            }
        }
    }
}