int n,m;
vector<int>adj[N];
vector<int>tour;
int in[N],out[N];
int Start=-1,End=-1;
bool euler(){
    for(int i=0;i<n;i++){
        if(out[i]-in[i]>1||in[i]-out[i]>1)return false;
        if(in[i]==out[i]+1){
            if(End!=-1)return false;
            End = i;
        }
        if(in[i]+1==out[i]){
            if(Start!=-1)return false;
            Start = i;
        }
    }
    return true;
}
void dfs(int node){
    while(out[node]){
        dfs(adj[node][--out[node]]);
    }
    tour.emplace_back(node);
}