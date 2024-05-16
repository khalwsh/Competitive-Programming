pair<int, int> calc(int u, int par = -1) {
    int diam = 0;
    int mxHeights[3] = {-1, -1, -1};    // keep 2 highest trees
    for (auto &v: adj[u])
        if (v != par) {
            auto p = calc(v, u);
            diam = max(diam, p.first);
            mxHeights[0] = p.second + 1;
            sort(mxHeights, mxHeights + 3);
        }
    for (int i = 0; i < 3; i++)
        if (mxHeights[i] == -1)
            mxHeights[i] = 0;
    diam = max(diam, mxHeights[1] + mxHeights[2]);
    return {diam, mxHeights[2]};
}
int diameter(int root){
    return calc(root).first;
}