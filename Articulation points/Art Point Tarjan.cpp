int dfn[N],LowLink[N],ndfn = 0;
vector<int>adj[N];
bool IsArtPoints[N];
vector<int>ArtPoints;
void Tarjan(int node,int parent){
    dfn[node] = LowLink[node] = ndfn++;
    int child = 0;
    for(auto &val:adj[node]){
        if(dfn[val]==-1){
            child++;
            Tarjan(val,node);
            LowLink[node] = min(LowLink[node],LowLink[val]);
            if(LowLink[val]>=dfn[node]){
                if(parent==-1&&child<=1)continue;
                IsArtPoints[node] = true;
            }
        }else if(parent!=val){
            LowLink[node] = min(LowLink[node],dfn[val]);
        }
    }
}
void Art(int n){
    ndfn = 0;
    for(int i=0;i<n;i++){
        dfn[i] = -1;
        IsArtPoints[i] = false;
        LowLink[i] = 0;
    }
    for(int i=0;i<n;i++){
        if(dfn[i]==-1)Tarjan(i,-1);
    }
    for(int i=0;i<n;i++){
        if(IsArtPoints[i])ArtPoints.emplace_back(i);
    }
}