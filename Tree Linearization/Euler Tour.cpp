int Euler[N],Ind[N],Timer = 0;
vector<int>adj[N];
void dfs(int node,int par){
    Euler[Timer] = node;
    Ind[node] = Timer;
    Timer++;
    for(auto &val:adj[node]){
        if(val==par)continue;
        dfs(val,node);
        Euler[Timer++] = node;
    }
}