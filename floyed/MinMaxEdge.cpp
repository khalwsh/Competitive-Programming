void MaxMinEdgeONPath(vector<vector<int>>&adj) {
    //adj[i][j] -- > represent the min(max edge) you can get in the shortest path between i , j
    int n = (int)adj.size();
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++)
                adj[i][j] = min(adj[i][j], max(adj[i][k], adj[k][j]));
        }
    }
}