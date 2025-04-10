void MaxMinEdge(vector<vector<int>>&adj,int n) {
    //find road that min value is maximum
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                adj[i][j] = max(adj[i][j], min(adj[i][k], adj[k][j]));
        }
    }
}