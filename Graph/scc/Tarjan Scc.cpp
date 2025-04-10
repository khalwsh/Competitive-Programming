vector<vector<int>> adj , dag , comps;
int comp[N] , inStack[N] , lowLink[N] , dfn[N] , deg[N];
stack<int> st;
int ndfn;
void tarjan(int u){
    dfn[u] = lowLink[u] = ndfn++;
    inStack[u] = true;
    st.push(u);
    for(auto &v : adj[u]){
        if(dfn[v] == -1){
            tarjan(v);
            lowLink[u] = min(lowLink[u] , lowLink[v]);
        }else if(inStack[v]){
            lowLink[u] = min(lowLink[u] , dfn[v]);
        }
    }
    if(dfn[u] == lowLink[u]){
        // head of component
        int x = -1;
        comps.emplace_back(vector<int>());
        while(x != u){
            x = st.top(); st.pop(); inStack[x] = 0;
            comps.back().emplace_back(x);
            comp[x] = (int)comps.size() - 1;
        }
    }
}
void genDag(){
    dag.resize(comps.size());
    for(int u = 0 ; u < adj.size() ; u++){
        for(auto &v :adj[u]){
            if(comp[u] != comp[v]){
                dag[comp[u]].emplace_back(comp[v]);
                deg[comp[v]]++;
            }
        }
    }
}
void SCC(int n){
    ndfn = 0;
    comps.clear();
    for(int i=0;i<n;i++){
        dfn[i] = -1;
        lowLink[i] = inStack[i] = deg[i] = 0;
    }
    for(int i = 0 ; i < n ; i++)
        if(dfn[i] == -1) tarjan(i);
    genDag();
}