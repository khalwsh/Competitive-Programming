vector<int>adj[N];
vector<pair<int,int>>bridges;
int dfn[N], LowLink[N],ndfn = 0;
void Tarjan(int node,int parent){
    dfn[node] = LowLink[node] = ndfn++;
    for(auto &val:adj[node]){
        if(dfn[val]==-1){
            Tarjan(val,node);
            LowLink[node] = min(LowLink[node],LowLink[val]);
        }else if(parent!=val){
            LowLink[node] = min(LowLink[node],dfn[val]);
        }
    }
    if(LowLink[node]==dfn[node] && ~parent){
        bridges.emplace_back(parent,node);
    }
}
void Bridges(int n){
    memset(dfn,-1,sizeof dfn);
    for(int i=0;i<n;i++){
        if(dfn[i]==-1){
            Tarjan(i,-1);
        }
    }
}