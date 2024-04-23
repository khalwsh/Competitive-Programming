bool CheckCycleEffect(vector<vector<int>>&adj,int source,int dist) {
    //apply floyed first
    int n = (int)adj.size();
    for (int i = 0; i < n; i++) {
        if (adj[i][i] != 0 && adj[source][i] < inf && adj[i][dist] < inf)
            return true;
    }
    return false;
}