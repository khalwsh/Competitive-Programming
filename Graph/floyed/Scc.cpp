int n;
vector<vector<int>>adj;
vector<int> comp(n, -1);
vector<vector<int>>scc() {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (comp[i] == -1) {
            comp[i] = cnt++;
            for (int j = 0; j < n; j++) {
                if (adj[i][j] < inf && adj[j][i] < inf)
                    comp[j] = comp[i];
            }
        }
    }
    vector<vector<int>>CompGraph(cnt,vector<int>(cnt));
    for(int i=0;i<n;i++) {
        for (int j = 0; j < n; j++) {
            if (adj[i][j] != inf) {
                CompGraph[comp[i]][comp[j]] += 1;
            }
        }
    }
    return CompGraph;//compressed graph
}