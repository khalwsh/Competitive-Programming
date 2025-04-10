int diameter(vector<vector<int>>&adj) {
    int n = (int) adj.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
            }
        }
    }
    int graph_diameter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] < inf)
                graph_diameter = max(graph_diameter, adj[i][j]);
        }
    }
    return graph_diameter;
}