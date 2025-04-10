bool NegativeCycle(vector<vector<int>>&adj,int n) {
    //apply floyed first
    for (int i = 0; i < n; i++)
        if (adj[i][i] != 0)
            return true;
    return false;
}