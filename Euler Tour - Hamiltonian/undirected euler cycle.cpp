int n,m;
set<int>adj[N];
int degree[N];
vector<int>tour;
void dfs(int node){
    while((int)adj[node].size()){
        int x = *adj[node].rbegin();
        adj[node].erase(x);
        if(adj[x].count(node)){
            adj[x].erase(node);
            dfs(x);
        }
    }
    tour.emplace_back(node);
}
bool check(){
    for(int i=0;i<n;i++){
        if(degree[i]&1){
            return false;
        }
    }
    return true;
}
bool get(){
    dfs(0);
    reverse(tour.begin(),tour.end());
    if(tour.size()!=m+1){
        return false;
    }
    return true;
}