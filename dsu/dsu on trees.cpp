int n;
int id[N],ans[N];
vector<int>adj[N];
set<int>sets[N];
int Merge(int a,int b){
    if(sets[a].size() > sets[b].size())swap(a,b);//small to large trick
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