int n;
int id[N],ans[N],values[N];
vector<int>adj[N];
set<int>sets[N];
int Merge(int a,int b){
    if(sets[a].size() > sets[b].size())swap(a,b);
    for(auto &val:sets[a]){
        sets[b].insert(val);
    }
    sets[a].clear();
    return b;
}
int dfs(int node,int par){
    int cur = id[node];
    for(auto &val:adj[node]){
        if(val==par)continue;
        cur = Merge(cur,dfs(val,node));
    }
    ans[node] = (int)sets[cur].size();
    return cur;
}
void init(){
    for(int i=0;i<n;i++){
        sets[i].clear();
        adj[i].clear();
    }
    for(int i=0;i<n;i++){
        sets[i].insert(values[i]);
        id[i] = i;
    }
}