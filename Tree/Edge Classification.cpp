int bridges,lvl [N],dp [N];
vector<int> adj [N];
void dfs (int vertex) {
    dp[vertex] = 0;
    for (int nxt : adj[vertex]) {
        if (lvl[nxt] == 0) { 
            //parent child edge
            lvl[nxt] = lvl[vertex] + 1;
            dfs(nxt);
            dp[vertex] += dp[nxt];
        } else if (lvl[nxt] < lvl[vertex]) {
            //backward edge [vertex,nxt]
            dp[vertex]++;
        } else if (lvl[nxt] > lvl[vertex]) {
            //forward edge [vertex,nxt]
            dp[vertex]--;
        }
    }
//  the parent edge isn't a back-edge, subtract 1 to compensate 
    dp[vertex]--;
    if (lvl[vertex] > 1 && dp[vertex] == 0) {
        bridges++;
    }
}
