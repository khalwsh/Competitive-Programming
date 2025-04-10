int n;
int id[N],values[N];
vector<int>adj[N];
vector<int>sets[N];
int res = 0;
int dfs(int node,int par){
    int a = id[node];
    for(auto &val:adj[node]){
        if(val==par)continue;
        int b = dfs(val,node);
        if(sets[a].size() > sets[b].size())
            swap(a,b);
        for(auto &x:sets[a]){
            //small set append it to set[b]
        }
        sets[a].clear();
    }
    return a;
}
void init(){
    for(int i=0;i<n;i++){
        sets[i][values[i]]++;
        id[i] = i;
    }
}