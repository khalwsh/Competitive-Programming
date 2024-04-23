vector<vector<int>>adj,parent;
vector<int>path;
void GetPath(int i,int j){
    if(i != j){
        GetPath(i , parent[i][j]);
    }
    path.emplace_back(j);
}