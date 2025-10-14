long long dfs(int u,int p){
    long long x=0;
    for(auto [v,w]: adj[u]) if(v!=p){
        long long child = sg(v,u);
        if(w==1) x ^= (child + 1);      // w = 1
        else if((w & 1LL) == 0) x ^= child; // w > 1 even
        else x ^= (child ^ 1LL);        // w > 1 odd
    }
    return x;
}